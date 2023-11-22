///****************************************************************************
/// @author  : Renaissance                                                        
/// @date    :                                                                 
/// @file    :                                                                 
/// @brief   : 实现连接Oracle，进行DML操作;                                                              
///----------------------------------------------------------------------------
///                           Change History                                   
///----------------------------------------------------------------------------
///                              
///****************************************************************************

#ifndef _DB_ORACLE_OCI_H
#define _DB_ORACLE_OCI_H

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <stack>

#include "ocilib/ocilib.hpp"
#include "fmt/core.h"

#include "IDataBase.h"
#include "project_shared.h"
#include "loggers.hpp"


namespace DB
{
	namespace OracleDB
	{
		/// <summary>
		/// 默认时间格式
		/// </summary>
		const ocilib::ostring default_format = "YYYY-MM-DD HH24:MI:SS";
		const ocilib::ostring default_out_format = "YYYYMMDDHH24MISS";

		/// <summary>
		/// 用于保存Oracle查询数据的结构体
		/// conn_ 析构自动释放,
		/// </summary>
		struct ResultRecord
		{
			/*数据库链接*/
			ocilib::Connection conn_;
			/*数据库语句处理对象*/
			ocilib::Statement stmt_;
			/*结果集*/
			ocilib::Resultset rs_;

			ResultRecord(ocilib::Connection conn, ocilib::Statement st, ocilib::Resultset rs) :conn_(std::move(conn)), stmt_(std::move(st)), rs_(/*std::move*/(rs))
			{
			};

			explicit ResultRecord() = default;
			~ResultRecord()
			{
				if (!conn_.IsNull())
				{
					conn_.Close();
				}
			}

		};

		/// <summary>
		/// 定义回调函数：每次取一行，处理后若返回true则依次取下一行，false则退出.
		/// </summary>
		using callback = bool(*)(const ocilib::Resultset&);



		class EnvironmentSingleton
		{
		public:
			static EnvironmentSingleton& getInstance()
			{
				static EnvironmentSingleton instance;
				return instance;
			}

			EnvironmentSingleton(const EnvironmentSingleton&) = delete;
			EnvironmentSingleton& operator=(const EnvironmentSingleton&) = delete;

		private:
			EnvironmentSingleton()
			{
				ocilib::Environment::Initialize(ocilib::Environment::Threaded);
				ocilib::Environment::EnableWarnings(true);
				renaissance::log::LOG_INFO_NUM(2001, "EnvironmentSingleton 构造 ");
			}

			~EnvironmentSingleton()
			{

				renaissance::log::LOG_INFO_NUM(2001, "~EnvironmentSingleton 析构 ");

				std::cout << "~EnvironmentSingleton" << std::endl;

				ocilib::Environment::Cleanup();
			}
		};



		/// <summary>
		/// 因为ocilib::Connection被包装为智能指针，所以无需回收，自动释放。
		/// </summary>
		class OraclePoolSingleton
		{
		public:

			static OraclePoolSingleton& getInstance(/*const DBConfigInfo info*/)
			{
				static OraclePoolSingleton instance;
				return instance;
			}

		public:
			using ConnectionType = ocilib::Connection;


			/// <summary>
			/// 针对此现场软件架构设计，因为在处理TM时,会触发大量IO密集型操作，导致连接激增，所以开辟连接池大些.
			/// 获取连接：有一下几种情况：
			/// 1. 维护的连接池中有连接，直接返回，无需收回，连接析构时自动释放;
			/// 2. 池中资源紧张时，前提是阈值有效时 max_value > 0:
			///		a. 未到达最大阈值，动态增加连接,每次按 y=75+e^(ratio*x) 倍率增加, 直到达到max时维持不变.
			///		b. 若阈值无效 max_value = 0，则采用 指数平滑法 扩张
			/// 3. 指数平滑法，是一个小幅度的关光滑上升的曲线,x<= 20  满足Oracle 默认连接数量限制要求.
			/// </summary>
			/// <param name="enableES">是否启用指数平滑法(exponential smoothing),在阈值无效的扩张阶段策略</param>
			/// <returns></returns>
			inline ConnectionType  getConnection(uint8_t enableES = 1);


			/// <summary>
			/// 获取当前池中资源数
			/// </summary>
			/// <returns></returns>
			inline size_t  getPoolSize() const { return conns_.size(); };

		public:

#pragma region 构造

			OraclePoolSingleton()
			{
				loadConfigFile();
			};

			~OraclePoolSingleton() {
				if (!conns_.empty())
				{
					conns_.clear();
				}
			};
#pragma endregion

		private:

			/// <summary>
			/// 加载配置
			/// </summary>
			inline void loadConfigFile();


#pragma region 成员属性声明

			// 启用指数平滑法时, 建议 <= es_limit
			inline static uint8_t delta_increase = 0;

			// ES策略限制
			const static uint8_t  es_limit = 20;

			// Oracle 默认连接数上限
			inline static uint8_t MAX_PROCESS = 150;

			bool unlimit = false;

			std::list<ConnectionType> conns_;
			//std::mutex mtx_;
			//std::condition_variable notify_;

			uint16_t max_;  // if(max_ <= 0 ) 则 无上限要求
			uint8_t min_;

			uint8_t timeout_;  // unit: second
			float ratio_;

			std::string services_name_;
			std::string user_;
			std::string pwd_;

#pragma endregion


		};

		//TODO: 后期适配加载配置文件信息
		void OraclePoolSingleton::loadConfigFile()
		{
			//std::ifstream jfile(R"(C:\Projects\ICM\JsonParser\test.json)");
			//jso jsonflie = json::parse(jfile);
			services_name_ = "datacentre";  /*L2server 上的 Oracle Server, 连接 PCS Nercar server 端需要自连接.*/
			user_ = "scc";
			pwd_ = "scc";
			max_ = 0;
			min_ = 5;
			ratio_ = 0.205f;

			conns_.clear();

			DB::OracleDB::EnvironmentSingleton::getInstance();

#pragma region 校验参数
			if (max_ <= 0)
			{
				unlimit = true;
				renaissance::log::LOG_INFO_NUM(1000, "启用无上限制度!");
			}
			else if (max_ <= min_)
			{
				renaissance::log::LOG_ERR_NUM(1001, fmt::format("无效参数, 资源池阈值:{0} 不能小于最小值 :{1}", max_, min_));
				throw std::invalid_argument(fmt::format("无效参数, 资源池阈值:{0} 不能小于最小值 :{1}", max_, min_));
			}

			if (ratio_ <= 0)
			{
				renaissance::log::LOG_ERR_NUM(1002, fmt::format("无效参数, 叠加倍率:{0} 不能 <= 0,却默认倍率 1.5", ratio_));
				//throw std::invalid_argument(fmt::format("无效参数, 叠加倍率:{0} 不能 <= 0", ratio_));
			}
#pragma endregion

#pragma region 填充连接池
			for (auto i = 0; i < min_; ++i)
			{
				conns_.push_back(ConnectionType(services_name_, user_, pwd_));
			}
#pragma endregion

#pragma region 获取Oracle server 最大连接数
			/*try
			{
				ocilib::Connection conc(services_name_, user_, pwd_);
				ocilib::Statement stmt(conc);
				stmt.Execute("select value from v$parameter where name = 'processes'");
				auto res = stmt.GetResultset();
				if (res.Next())
					cout << res.Get<int>("value") << endl;
			}
			catch (const std::exception&)
			{

			}*/
#pragma endregion

		}

		OraclePoolSingleton::ConnectionType OraclePoolSingleton::getConnection(uint8_t enableES)
		{
			ConnectionType conn;

			try
			{
				//std::unique_lock lock(mtx_);

				//2.a 
				if (!conns_.empty())
				{
					conn = conns_.front();
					conns_.pop_front();
				}
				else
				{
					//2.a
					if (conns_.size() < 1)
					{
						// e = 2*x + 1
						auto expand_ = 1;
						++delta_increase;

						//2.a
						if (!unlimit)
						{
							delta_increase = (delta_increase > es_limit ? 2 : delta_increase);
							expand_ = static_cast<uint16_t>((std::exp(ratio_ * delta_increase) + (MAX_PROCESS / 4)));
							if (expand_ >= max_)
							{
								expand_ = max_;
							}
						}
						//2.b 
						else
						{
							if (enableES)
							{
								renaissance::log::LOG_INFO_NUM(1006, "启用指数平滑法");
								delta_increase = (delta_increase > es_limit ? 2 : delta_increase);
								expand_ = static_cast<uint16_t>((std::exp(ratio_ * delta_increase) + (MAX_PROCESS / 4)));
							}
							else
							{
								expand_ = static_cast<uint16_t>(delta_increase * delta_increase + 1 + min_);
							}
						}

						renaissance::log::LOG_INFO_NUM(1006, fmt::format("扩容至: {0}, delta_increase:{1}", expand_, delta_increase));

						for (auto i = 0; i < expand_; ++i)
						{
							conns_.push_back(ConnectionType(services_name_, user_, pwd_));
						}

						conn = conns_.front();
						conns_.pop_front();
					}
				}
			}
			catch (const std::exception& e)
			{
				renaissance::log::LOG_ERR_NUM(1000, fmt::format("获取连接失败:{0}", e.what()));
				throw std::logic_error(fmt::format("Error occured in getConnection: {0}", e.what()));
			}
			//renaissance::log::LOG_INFO_NUM(1005, fmt::format("剩余连接数:{0}", conns_.size()));
			return conn;
		}


		class OracleDML
		{

		public:
			 static ResultRecord executeQuery(const std::string& sql, bool enES = true)
			{
				try
				{
					auto conn = OraclePoolSingleton::getInstance().getConnection(enES);
					ocilib::Statement stmt(conn);
					stmt.Execute(sql);
					auto rs = stmt.GetResultset();
					return ResultRecord(conn, stmt, rs);;
				}
				catch (ocilib::Exception& e)
				{
					throw std::logic_error(fmt::format("Error execute  reason:{}", e.what()));
				}
			}

			 static int execute(const std::string& sql, bool enES = true)
			{
				auto affect_row = -1;
				auto conn = OraclePoolSingleton::getInstance().getConnection();

				try
				{
					ocilib::Statement stmt(conn);
					stmt.Execute(sql);
					conn.Commit();
					affect_row = stmt.GetAffectedRows();
				}
				catch (ocilib::Exception& e)
				{
					conn.Rollback();
					throw std::logic_error(fmt::format("Error execute reason:[{0}]", e.what()));
				}
				return affect_row;
			}

			 static size_t getPoolSize()
			{
				return OraclePoolSingleton::getInstance().getPoolSize();
			}

			 static OraclePoolSingleton::ConnectionType getConnection(bool enableES = true)
			{
				return OraclePoolSingleton::getInstance().getConnection(enableES);
			}
		private:
		};

	}

	namespace OracleDB
	{
		class OracleConnectionPool : public DB::ConnectionPool
		{
		public:
			static inline OracleConnectionPool& getOracleInstance(shared_define::DBinfo& info_ = shared_define::L2DB::l2_db_info)
			{
				// c++11 ~ 语言规范，要求local static 变量初始化期间，埼其余线程等待~
				static OracleConnectionPool instance(info_);
				return instance;
			}

			OracleConnectionPool(const OracleConnectionPool&) = delete;
			OracleConnectionPool& operator=(const OracleConnectionPool&) = delete;
#pragma region Common function
		public:

			/// <summary>
			/// 测试链接是否通畅
			/// </summary>
			/// <returns></returns>
			inline bool test()
			{
				try
				{
					executeQuery("select to_char(sysdate, 'yyyy-MM-dd HH24:mi:ss') from dual", [](const ocilib::Resultset& rs) {
						std::cout << "current time: " << rs.Get<std::string>(1) << std::endl;
						return true;
						});
					return true;
				}
				catch (ocilib::Exception& e)
				{
					std::cerr << e.what() << std::endl;
					return false;
				}
			}

			inline bool	test(ocilib::Connection& conn)
			{
				try
				{
					executeQuery("select to_char(sysdate, 'yyyy-MM-dd HH24:mi:ss') from dual", conn, [](const ocilib::Resultset& rs) {
						std::cout << "current time: " << rs.Get<std::string>(1) << std::endl;
						return true;
						});
					return true;
				}
				catch (ocilib::Exception& e)
				{
					std::cerr << e.what() << std::endl;
					return false;
				}
			}

			inline unsigned int getCurBusyConnSize()
			{
				return pool_.GetBusyConnectionsCount();
			}

			inline unsigned int getCurOpenConnSize()
			{
				return pool_.GetOpenedConnectionsCount();
			}

			/// <summary>
			/// 释放链接
			/// </summary>
			inline void shutDown() override
			{
				//m_cond.notify_all();

				pool_.Close();

				// delete OCI environment for all resources
				//ocilib::Environment::Cleanup();
			}

			// 线程安全,执行增删改语句，返回受影响的行数
			inline int execute(const std::string& sql) override
			{
				auto affect_row = -1;
				//std::scoped_lock lock(m_mtx);
				auto conn = pool_.GetConnection();

				try
				{
					ocilib::Statement stmt(conn);
					stmt.Execute(sql);
					conn.Commit();
					affect_row = stmt.GetAffectedRows();
				}
				catch (ocilib::Exception& e)
				{
					conn.Rollback();
					throw std::logic_error(fmt::format("Error execute reason:[{0}]", e.what()));
				}
				return affect_row;
			}

			/// <summary>
			/// 线程安全，执行查询语句
			/// </summary>
			/// <typeparam name="T">callback prototype</typeparam>
			/// <param name="sql">查询语句</param>
			/// <param name="callback">It shall return true to continue fetching the resultset or false to stop the fetch</param>
			//template<class T>
			inline void executeQuery(const std::string& sql, void* func) override
			{
				//std::scoped_lock lock(m_mtx);
				auto conn = pool_.GetConnection();
				try
				{
					ocilib::Statement stmt(conn);
					stmt.Execute(sql, (callback)func);
					conn.Commit();
				}
				catch (ocilib::Exception& e)
				{
					throw std::logic_error(fmt::format("Error executeQuery sql: {0},  reason:[{1}]", sql, e.what()));

				}
			}

			/// <summary>
			/// 可直接执行lambda函数
			/// </summary>
			/// <param name="sql"></param>
			/// <param name="func"></param>
			inline void executeQuery(const std::string& sql, callback func)
			{
				//std::scoped_lock lock(m_mtx);
				auto conn = pool_.GetConnection();
				try
				{
					ocilib::Statement stmt(conn);
					stmt.Execute(sql, func);
					conn.Commit();
				}
				catch (ocilib::Exception& e)
				{
					//renaissance::log::LOG_ERR(fmt::format("The error in {0}, sql:{1} , reason:{2}", " executeQuery(const std::string& sql, callback func)", sql, e.what()));
					throw std::logic_error(fmt::format("Error executeQuery sql: {0},  reason:[{1}]", sql, e.what()));
				}
			}

			inline void executeQuery(const std::string& sql, ocilib::Connection& conn, callback func)
			{
				//std::scoped_lock lock(m_mtx);
				try
				{
					ocilib::Statement stmt(conn);
					stmt.Execute(sql, func);
					conn.Commit();
				}
				catch (ocilib::Exception& e)
				{
					std::cerr << "Error in ocilib::Resultset executeQuery(...): reason =>> " << e.what() << std::endl;
					throw e.what();
				}
			}

			inline ResultRecord executeQuery(const std::string& sql)
			{
				//std::scoped_lock lock(m_mtx);
				auto conn = pool_.GetConnection();
				try
				{
					ocilib::Statement stmt(conn);
					stmt.Execute(sql);
					conn.Commit();
					auto rs = stmt.GetResultset();
					return ResultRecord(conn, stmt, rs);;
				}
				catch (ocilib::Exception& e)
				{
					//renaissance::log::LOG_ERR(fmt::format("The error in {0}, sql:{1} , reason:{2}", " executeQuery", sql, e.what()));
					//std::cerr << "Error in ocilib::Resultset executeQuery(" + sql + "): reason =>> " << e.what() << std::endl;
					throw std::logic_error(fmt::format("Error execute  reason:{}", e.what()));
				}
			}

			inline void beginTransaction() override
			{
			};
			inline void commitTransaction() {
			};
			inline void rollbackTransaction() {
			};

#pragma endregion

#pragma region private functino

		private:
			OracleConnectionPool(shared_define::DBinfo& info_) {
				// Initialize OCI environment for all threads， 已开启多线程安全支持
				DB::OracleDB::EnvironmentSingleton::getInstance();

				pool_.Open(info_.service_name_, info_.user_, info_.pwd_, ocilib::Pool::ConnectionPool, info_.min_, info_.max_);

				// 与最大数量一致
				//pool_.Open(info_.service_name_, info_.user_, info_.pwd_, ocilib::Pool::SessionPool, info_.min_, info_.max_);

				// 一直等待
				//pool_.SetNoWait(false);
				//pool_.SetTimeout(3);

				std::cout << "timeout: " << pool_.GetTimeout() << std::endl;
				std::cout << "GetStatementCacheSize: " << pool_.GetStatementCacheSize() << std::endl;
				std::cout << "GetMaxSize: " << pool_.GetMaxSize() << std::endl;
				std::cout << "GetMinSize: " << pool_.GetMinSize() << std::endl;
			};

			OracleConnectionPool() = default;
			~OracleConnectionPool()
			{
				shutDown();
				std::cerr << "析构 OracleConnectionPool ~" << std::endl;
			};

#pragma endregion

#pragma region private fields

		private:
			ocilib::Pool pool_;
#pragma endregion

		};

		/// <summary>
		/// note：使用前要保证初始化环境：ocilib::Environment::Initialize(ocilib::Environment::Threaded);
		///		  不在操作数据库后保证释放： ocilib::Environment::Cleanup();
		/// </summary>
		class OracleManager
		{

		private:
			OracleManager(const OracleManager&) = delete;
			OracleManager& operator=(const OracleManager&) = delete;

		public:

			explicit OracleManager() {
				DB::OracleDB::EnvironmentSingleton::getInstance();
			};

			~OracleManager() = default;


		public:

			inline bool test(shared_define::DBinfo info)
			{
				bool flag_ = false;
				try
				{
					ocilib::Connection conn(info.service_name_, info.user_, info.pwd_);
					flag_ = conn.PingServer();
				}
				catch (ocilib::Exception& e)
				{
					std::cerr << e.what() << std::endl;
					throw std::logic_error(fmt::format("Test connection is failed: {}", e.what()));
				}

				return flag_;
			}

			inline ResultRecord executeQuery(shared_define::DBinfo info, const std::string& sql)
			{
				try
				{
					ocilib::Connection conn(info.service_name_, info.user_, info.pwd_);
					ocilib::Statement stmt(conn);
					stmt.Execute(sql);
					conn.Commit();
					return ResultRecord(std::move(conn), std::move(stmt), stmt.GetResultset());
				}
				catch (ocilib::Exception& e)
				{
					throw std::logic_error(fmt::format("Error in executeQuery reason: {0}", e.what()));
				}
			}

			int execute(shared_define::DBinfo info, const std::string& sql)
			{
				auto affect_row = -1;

				try
				{
					//DB::OracleDB::EnvironmentSingleton::getInstance();
					ocilib::Connection conn(info.service_name_, info.user_, info.pwd_);
					try
					{
						ocilib::Statement stmt(conn);
						stmt.Execute(sql);
						conn.Commit();
						affect_row = stmt.GetAffectedRows();
					}
					catch (ocilib::Exception& ex)
					{
						conn.Rollback();
						throw std::logic_error(fmt::format("Error execute reason:{}", ex.what()));
					}
				}
				catch (const std::exception& e)
				{
					throw std::logic_error(fmt::format("连接失败:{}", e.what()));
				}

				return affect_row;
			}
		};
	}
}

#endif