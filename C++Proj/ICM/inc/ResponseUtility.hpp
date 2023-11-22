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
	/// 获取指定板坯，指定区域所经过的道次数
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
	/// 从ActualResponse中获取指定数据存于msgData中
	/// </summary>
	/// <param name="msgData">数据缓存</param>
	/// <param name="msgName">消息名</param>
	/// <param name="varName">数据缓存中的属性名称 key</param>
	/// <param name="prodRespId">TB_PDI中ID</param>
	/// <param name="eqName">设备名称</param>
	/// <param name="propName">属性名称</param>
	/// <param name="passNo">道次</param>
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

