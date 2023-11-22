///****************************************************************************
/// @author  : Renaissance                                                        
/// @date    :                                                                 
/// @file    :                                                                 
/// @brief   : ʵ������Oracle������DML����;                                                              
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
		/// Ĭ��ʱ���ʽ
		/// </summary>
		const ocilib::ostring default_format = "YYYY-MM-DD HH24:MI:SS";
		const ocilib::ostring default_out_format = "YYYYMMDDHH24MISS";

		/// <summary>
		/// ���ڱ���Oracle��ѯ���ݵĽṹ��
		/// conn_ �����Զ��ͷ�,
		/// </summary>
		struct ResultRecord
		{
			/*���ݿ�����*/
			ocilib::Connection conn_;
			/*���ݿ���䴦�����*/
			ocilib::Statement stmt_;
			/*�����*/
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
		/// ����ص�������ÿ��ȡһ�У������������true������ȡ��һ�У�false���˳�.
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
				renaissance::log::LOG_INFO_NUM(2001, "EnvironmentSingleton ���� ");
			}

			~EnvironmentSingleton()
			{

				renaissance::log::LOG_INFO_NUM(2001, "~EnvironmentSingleton ���� ");

				std::cout << "~EnvironmentSingleton" << std::endl;

				ocilib::Environment::Cleanup();
			}
		};



		/// <summary>
		/// ��Ϊocilib::Connection����װΪ����ָ�룬����������գ��Զ��ͷš�
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
			/// ��Դ��ֳ�����ܹ���ƣ���Ϊ�ڴ���TMʱ,�ᴥ������IO�ܼ��Ͳ������������Ӽ��������Կ������ӳش�Щ.
			/// ��ȡ���ӣ���һ�¼��������
			/// 1. ά�������ӳ��������ӣ�ֱ�ӷ��أ������ջأ���������ʱ�Զ��ͷ�;
			/// 2. ������Դ����ʱ��ǰ������ֵ��Чʱ max_value > 0:
			///		a. δ���������ֵ����̬��������,ÿ�ΰ� y=75+e^(ratio*x) ��������, ֱ���ﵽmaxʱά�ֲ���.
			///		b. ����ֵ��Ч max_value = 0������� ָ��ƽ���� ����
			/// 3. ָ��ƽ��������һ��С���ȵĹع⻬����������,x<= 20  ����Oracle Ĭ��������������Ҫ��.
			/// </summary>
			/// <param name="enableES">�Ƿ�����ָ��ƽ����(exponential smoothing),����ֵ��Ч�����Ž׶β���</param>
			/// <returns></returns>
			inline ConnectionType  getConnection(uint8_t enableES = 1);


			/// <summary>
			/// ��ȡ��ǰ������Դ��
			/// </summary>
			/// <returns></returns>
			inline size_t  getPoolSize() const { return conns_.size(); };

		public:

#pragma region ����

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
			/// ��������
			/// </summary>
			inline void loadConfigFile();


#pragma region ��Ա��������

			// ����ָ��ƽ����ʱ, ���� <= es_limit
			inline static uint8_t delta_increase = 0;

			// ES��������
			const static uint8_t  es_limit = 20;

			// Oracle Ĭ������������
			inline static uint8_t MAX_PROCESS = 150;

			bool unlimit = false;

			std::list<ConnectionType> conns_;
			//std::mutex mtx_;
			//std::condition_variable notify_;

			uint16_t max_;  // if(max_ <= 0 ) �� ������Ҫ��
			uint8_t min_;

			uint8_t timeout_;  // unit: second
			float ratio_;

			std::string services_name_;
			std::string user_;
			std::string pwd_;

#pragma endregion


		};

		//TODO: ����������������ļ���Ϣ
		void OraclePoolSingleton::loadConfigFile()
		{
			//std::ifstream jfile(R"(C:\Projects\ICM\JsonParser\test.json)");
			//jso jsonflie = json::parse(jfile);
			services_name_ = "datacentre";  /*L2server �ϵ� Oracle Server, ���� PCS Nercar server ����Ҫ������.*/
			user_ = "scc";
			pwd_ = "scc";
			max_ = 0;
			min_ = 5;
			ratio_ = 0.205f;

			conns_.clear();

			DB::OracleDB::EnvironmentSingleton::getInstance();

#pragma region У�����
			if (max_ <= 0)
			{
				unlimit = true;
				renaissance::log::LOG_INFO_NUM(1000, "�����������ƶ�!");
			}
			else if (max_ <= min_)
			{
				renaissance::log::LOG_ERR_NUM(1001, fmt::format("��Ч����, ��Դ����ֵ:{0} ����С����Сֵ :{1}", max_, min_));
				throw std::invalid_argument(fmt::format("��Ч����, ��Դ����ֵ:{0} ����С����Сֵ :{1}", max_, min_));
			}

			if (ratio_ <= 0)
			{
				renaissance::log::LOG_ERR_NUM(1002, fmt::format("��Ч����, ���ӱ���:{0} ���� <= 0,ȴĬ�ϱ��� 1.5", ratio_));
				//throw std::invalid_argument(fmt::format("��Ч����, ���ӱ���:{0} ���� <= 0", ratio_));
			}
#pragma endregion

#pragma region ������ӳ�
			for (auto i = 0; i < min_; ++i)
			{
				conns_.push_back(ConnectionType(services_name_, user_, pwd_));
			}
#pragma endregion

#pragma region ��ȡOracle server ���������
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
								renaissance::log::LOG_INFO_NUM(1006, "����ָ��ƽ����");
								delta_increase = (delta_increase > es_limit ? 2 : delta_increase);
								expand_ = static_cast<uint16_t>((std::exp(ratio_ * delta_increase) + (MAX_PROCESS / 4)));
							}
							else
							{
								expand_ = static_cast<uint16_t>(delta_increase * delta_increase + 1 + min_);
							}
						}

						renaissance::log::LOG_INFO_NUM(1006, fmt::format("������: {0}, delta_increase:{1}", expand_, delta_increase));

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
				renaissance::log::LOG_ERR_NUM(1000, fmt::format("��ȡ����ʧ��:{0}", e.what()));
				throw std::logic_error(fmt::format("Error occured in getConnection: {0}", e.what()));
			}
			//renaissance::log::LOG_INFO_NUM(1005, fmt::format("ʣ��������:{0}", conns_.size()));
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
				// c++11 ~ ���Թ淶��Ҫ��local static ������ʼ���ڼ䣬�������̵߳ȴ�~
				static OracleConnectionPool instance(info_);
				return instance;
			}

			OracleConnectionPool(const OracleConnectionPool&) = delete;
			OracleConnectionPool& operator=(const OracleConnectionPool&) = delete;
#pragma region Common function
		public:

			/// <summary>
			/// ���������Ƿ�ͨ��
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
			/// �ͷ�����
			/// </summary>
			inline void shutDown() override
			{
				//m_cond.notify_all();

				pool_.Close();

				// delete OCI environment for all resources
				//ocilib::Environment::Cleanup();
			}

			// �̰߳�ȫ,ִ����ɾ����䣬������Ӱ�������
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
			/// �̰߳�ȫ��ִ�в�ѯ���
			/// </summary>
			/// <typeparam name="T">callback prototype</typeparam>
			/// <param name="sql">��ѯ���</param>
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
			/// ��ֱ��ִ��lambda����
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
				// Initialize OCI environment for all threads�� �ѿ������̰߳�ȫ֧��
				DB::OracleDB::EnvironmentSingleton::getInstance();

				pool_.Open(info_.service_name_, info_.user_, info_.pwd_, ocilib::Pool::ConnectionPool, info_.min_, info_.max_);

				// ���������һ��
				//pool_.Open(info_.service_name_, info_.user_, info_.pwd_, ocilib::Pool::SessionPool, info_.min_, info_.max_);

				// һֱ�ȴ�
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
				std::cerr << "���� OracleConnectionPool ~" << std::endl;
			};

#pragma endregion

#pragma region private fields

		private:
			ocilib::Pool pool_;
#pragma endregion

		};

		/// <summary>
		/// note��ʹ��ǰҪ��֤��ʼ��������ocilib::Environment::Initialize(ocilib::Environment::Threaded);
		///		  ���ڲ������ݿ��֤�ͷţ� ocilib::Environment::Cleanup();
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
					throw std::logic_error(fmt::format("����ʧ��:{}", e.what()));
				}

				return affect_row;
			}
		};
	}
}

#endif