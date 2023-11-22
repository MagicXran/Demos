#pragma once

#include "DBOraclePool.hpp"
#include "ActualResponseFlyw.h"
#include "loggers.hpp"

/// <summary>
/// Project specific helper/utilty class for the response model. 
/// </summary>
class ResponseUtility
{
public:
	/// <summary>
	/// ��ȡָ��������ָ�������������ĵ�����
	/// </summary>
	/// <param name="matId"></param>
	/// <returns></returns>
	static inline int GetMaxPassNo(const shared_define::ID_TYPE pdi_id, const std::string& equipName)
	{
		auto max_passno = -1;
		try
		{
			auto equipId = ActualResponseFlyw::CacheEquipNameId()[equipName];
			auto sel_ = fmt::format("select max(pass_no) maxpass from actual_responses where resp_id={0} and template_id={1}", pdi_id, equipId);
			auto res = DB::OracleDB::OracleDML::executeQuery(sel_);

			if (res.rs_.Next())
			{
				max_passno = res.rs_.Get<int>("maxpass");
			}
			else
			{
				renaissance::log::LOG_ERR(fmt::format("The pdi_id:{0} is not exist in TB_PDI, in GetMaxPassNo()", pdi_id));
			}
		}
		catch (const std::exception& e)
		{
			renaissance::log::LOG_ERR(fmt::format("Error in GetMaxPassNo to search pdi_id:{0} in TB_PDI, reason:{1}", pdi_id, e.what()));
			return max_passno;
		}

		return max_passno;
	}

	/// <summary>
	/// ��ActualResponse�л�ȡָ�����ݴ���msgData��
	/// </summary>
	/// <param name="msgData">���ݻ���</param>
	/// <param name="msgName">��Ϣ��</param>
	/// <param name="varName">���ݻ����е��������� key</param>
	/// <param name="prodRespId">TB_PDI��ID</param>
	/// <param name="eqName">�豸����</param>
	/// <param name="propName">��������</param>
	/// <param name="passNo">����</param>
	static inline void SetMsgFloatVarFromActRespNValue(shared_define::tm_message::tm_map_type& msgData, const std::string& msgName, const std::string& varName, int prodRespId, const std::string& eqName, const std::string& propName, int passNo)
	{
		try
		{
			auto actResp = ActualResponseFlyw::FindOne(prodRespId, eqName, propName, passNo);
			if (actResp == nullptr)
				throw std::logic_error(fmt::format("No data found for (ProdRespId, Equipment, Property, PassNo) = ({0}, {1}, {2}, {3})!", prodRespId, eqName, propName, passNo));
			if (msgData.find(varName) == msgData.end())
				throw std::logic_error(fmt::format("Dictionary does not contain the variable '{0}'!", varName));
			if (actResp->dataType_ == 1)
			{
				msgData[varName] = std::to_string((int)actResp->nValue_);
			}
			else
			{
				msgData[varName] = std::to_string(actResp->nValue_);
			}
		}
		catch (const std::exception& e)
		{
			throw std::logic_error(fmt::format("Updating variable '{0}' in message '{1}' to  data dictionary failed! reason:{2}", varName, msgName, e.what()));
		}
	}

private:

};

