#pragma once

//#include "AsyncTask.hpp"
#include "CrewMgtHelper.hpp"
#include "ResponseUtility.hpp"

class ProcDataMgtHelper
{
public:

#pragma region Static helper methods for the Process Data Management service.

	/// <summary>
	///  统计指定EquipName的数据
	/// </summary>
	/// <param name="Equip">shared_define::EquipNames</param>
	/// <param name="itemName">matID</param>
	static inline void ConsRMPassData(const std::string& Equip, const std::string& itemName)
	{
		try
		{
			//异步任务
			//renaissance::asyn::AsyncTask task;

			//// Create an empty data dictionary for the actual responses to save
			//shared_define::tm_message::tm_map_type specified;

			//renaissance::log::LOG_INFO(fmt::format("ConsRMPassData Start: matId: '{0}'", itemName));

			//auto max_pass_future = task.submit(ResponseUtility::GetMaxPassNo, itemName);
			//auto shift_future = task.submit(CrewMgtHelper::GetCurrentShiftInfo);

			//// To use the data from the last pass we need the max pass number
			//auto lastPassNo = max_pass_future.get();

			//// Quit if no pass related responses found
			//if (lastPassNo == -1)
			//	throw std::invalid_argument(fmt::format("Failed to determine last pass number in {0} for item '{1}'! ", Equip, itemName));

#pragma region EXIT_LENGTH

			// Get exit length
			//L1 传来采样数据，存入TB_QUALITY_DATA 中，在Oracle中进行统计，然后读取View获得对应信息，最后，存入act_resp中


#pragma endregion





			//auto shiftinfo = shift_future.get();





			renaissance::log::LOG_INFO(fmt::format("ConsRMPassData End: matId: '{0}'", itemName));
		}
		catch (const std::exception&)
		{
			throw std::logic_error(fmt::format("ConsRMPassData happens error: matId: '{0}'", itemName));
		}

	}


	static inline bool IsRM1Active(const std::string& matId, shared_define::ID_TYPE& prodReqId)
	{
		try
		{
			auto sel_ = fmt::format("select ID from TB_PDI where COIL_ID='{0}'  ", matId);
			auto res = DB::OracleDB::OracleDML::executeQuery(sel_);

			if (res.rs_.Next())
			{
				prodReqId = res.rs_.Get< shared_define::ID_TYPE>("ID");
				int maxPassNo = ResponseUtility::GetMaxPassNo(prodReqId, shared_define::EquipNames::RM1_PX);
				return ((maxPassNo >= 0) ? true : false);
			}
			else
			{
				return false;
			}
		}
		catch (const std::exception& e)
		{
			throw std::logic_error(fmt::format("Error in IsRM1Active to search matId:{0} in TB_PDI, reason:{1}", matId, e.what()));
		}

		return false;
	}


	static inline void SaveActualResponse(ActualMapType& specified, ActualInfo& info)
	{
		for (auto& vars : specified)
		{
			if (vars.second.unspecified_flag_)
			{
				//TODO: 未指定Tag不存储
				return;
				if (!vars.second.value_.has_value() || info.propName_.empty() || info.equipName_.empty())
				{
					throw std::invalid_argument(fmt::format("要保存的变量:equipName_{},propName_{},并没有值,或者是有值但没有属性,设备", info.equipName_, info.propName_));
				}

				vars.second.propName_ = info.propName_;
				vars.second.equipName_ = info.equipName_;
				vars.second.setDataType(info.propName_);
				vars.second.setVal(vars.second.value_);
			}

			if (info.prodRespId_ < shared_define::NonZero)
			{
				throw std::invalid_argument("prodRespId_值无效");
			}
			vars.second.prodRespId_ = info.prodRespId_;
			vars.second.Save();
		}
	}
#pragma endregion
private:

};

