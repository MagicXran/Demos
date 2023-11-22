#pragma once

#include "DBOraclePool.hpp"
#include "universal_toolbox.hpp"

class RequestUtility
{
public:
	/// <summary>
	/// 按照指定规则生成卷号: 10位卷号
	/// </summary>
	/// <returns></returns>
	inline static std::string GenerateRequestName()
	{

		auto res = DB::OracleDB::OracleDML::executeQuery("SELECT COIL_ID_SEQ.NEXTVAL AS SEQ_NO FROM DUAL");
		if (res.rs_.Next())
		{
			auto seq_no = res.rs_.Get<int>("SEQ_NO");
			//cout << "seq_no: " << seq_no << endl;
			return uni_box::utils::format("D%d%06d00", uni_box::time_tools::getYday() % 10, seq_no);
		}
		else
		{
			throw std::logic_error("Failed to get sequence number for coil id!");
		}
	}

	inline static bool UpdateAllowed(const std::string& stateName, int sub_state, int ReqTypes)
	{
		if (ReqTypes == (int)shared_define::mes_message::ReqTypesEnum::ProductionOrder)
		{
			if (stateName == shared_define::OrderStateTypes::OrderIsDraft ||
				stateName == shared_define::OrderStateTypes::OrderIsReleased ||
				stateName == shared_define::OrderStateTypes::OrderIsDispatched ||
				stateName == shared_define::OrderStateTypes::OrderInProduction && (sub_state < (int)shared_define::SubStatesEnum::IsDischarged)
				)
			{
				return true;
			}
			else
				return false;
		}
		else
		{
			if (stateName == shared_define::OrderStateTypes::OrderIsDraft ||
				stateName == shared_define::OrderStateTypes::OrderIsReleased ||
				stateName == shared_define::OrderStateTypes::OrderIsDispatched
				)
			{
				return true;
			}
			else
				return false;
		}
	}


	/// <summary>
	/// 根据物料所处状态,判断是否允许删除
	/// </summary>
	/// <param name="state"></param>
	/// <returns></returns>
	inline static bool DeleteAllowed(const std::string& stateName)
	{
		if (stateName == shared_define::OrderStateTypes::OrderIsDraft ||
			stateName == shared_define::OrderStateTypes::OrderIsReleased ||
			stateName == shared_define::OrderStateTypes::OrderIsDispatched ||
			stateName == shared_define::OrderStateTypes::OrderIsStopped ||
			stateName == shared_define::OrderStateTypes::OrderIsFinished
			)
		{
			return true;
		}
		else
			return false;
	}

	/// <summary>
	/// 判断是否需要通知外部系统
	/// </summary>
	/// <param name="state"></param>
	/// <returns></returns>
	inline static bool DataNotificationRequired(const std::string& stateName)
	{
		if (stateName == shared_define::OrderStateTypes::OrderIsDispatched ||
			stateName == shared_define::OrderStateTypes::OrderInProduction ||
			stateName == shared_define::OrderStateTypes::OrderIsStopped)
			return true;
		else
			return false;
	}


	/// <summary>
	/// 为轧制计划分配序号
	/// </summary>
	/// <param name="listType"></param>
	/// <returns></returns>
	inline static double GetNextSeqNoForScheduleList(int listType)
	{
		std::string seqName;
		if (listType == (int)shared_define::mes_message::ListTypesEnum::ProductionScheduleList)
		{
			seqName = "PROD_SCHED_LIST_SEQ";
		}
		else if (listType == (int)shared_define::mes_message::ListTypesEnum::GhostScheduleList)
			seqName = "GHOST_SCHED_LIST_SEQ";
		else return -1;

		try
		{
			auto res = DB::OracleDB::OracleDML::executeQuery(uni_box::utils::format("SELECT %s.NEXTVAL AS SEQ_NO FROM DUAL", seqName.c_str()));
			if (res.rs_.Next())
			{
				auto seq_no = res.rs_.Get<double>("SEQ_NO");
				//cout << "seq_no: " << seq_no << endl;
				return seq_no;
			}
			else
			{
				throw std::logic_error("Failed to get sequence number for listType!");
			}
		}
		catch (std::exception& e)
		{
			throw e;
		}
	}


	/// <summary>
	/// 寻找临近出钢ID
	/// </summary>
	/// <param name="prevReqName"></param>
	/// <returns></returns>
	inline static shared_define::ID_TYPE FindNextOrderInLine(const std::string& prevReqName)
	{
		try
		{
			auto res = DB::OracleDB::OracleDML::executeQuery(fmt::format("SELECT ID,SEQUENCE_IN_LIST FROM TB_PDI where COIL_ID='{0}'", prevReqName));
			auto conn = res.conn_;
			ocilib::Statement stmt(conn);

			if (res.rs_.Next())
			{
				auto prevSeq = res.rs_.Get<double>("SEQUENCE_IN_LIST");
				auto query_ = fmt::format("select ID from TB_PDI where REQUEST_TYPE=1 and SEQUENCE_IN_LIST > {0} and STATENAME = '{1}' and SUBSTATE in ({2},{3}) ", prevSeq, shared_define::OrderStateTypes::OrderInProduction, (int)shared_define::SubStatesEnum::IsCharged, (int)shared_define::SubStatesEnum::IsNextToDischarge);

				//renaissance::log::LOG_INFO(fmt::format("执行sql:{}", query_));

				stmt.Execute(query_);
				auto nextRes = stmt.GetResultset();
				if (nextRes.Next())
				{
					auto nextId = nextRes.Get<shared_define::ID_TYPE>("ID");
					//renaissance::log::LOG_INFO(fmt::format("存在下快出钢物料,ID:{}", nextId));
					return nextId;
				}
				else
				{
					//renaissance::log::LOG_WARN(fmt::format("不存在下快出钢物料,基准卷号 matId:{}", prevReqName));
					return -1;
				}
			}
			else
			{
				return -1;
			}
		}
		catch (const std::exception& e)
		{
			throw std::logic_error(fmt::format("Failed to find nextorder in line after order {0}， reason:{1}", prevReqName, e.what()));
		}
	}
};
