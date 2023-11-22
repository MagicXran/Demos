#pragma once


#include "DBOraclePool.hpp"
#include "loggers.hpp"



struct ShiftInfo
{
	int		_shiftNo = 0;  /*0(甲),1,2,3(丁)*/
	int     _crew = 0;    /*1:夜, 4:白*/
	std::string _shiftName = ""; /*1:甲，2,3,4*/
	std::string _crewName = "";  /*2:白班 1:夜班，3:中*/
	std::string _shiftStartTime = "";
	std::string _shiftEndTime = "";
};

/// <summary>
/// Helper class for Shift and Crew handling
/// </summary>
class CrewMgtHelper
{
public:
#pragma region Helper class for Shift and Crew handling

public:

	/// <summary>
	/// 查询当天班组信息
	/// </summary>
	/// <returns></returns>
	[[nodiscard]] inline static ShiftInfo GetCurrentShiftInfo() noexcept
	{
		ShiftInfo shift{ 0,0,"00","00:00:00","00:00:00" };
		try
		{
			//static ocilib::Connection conn("nercar", "scc", "scc");
			//ocilib::Statement stmt(conn);
			//stmt.Execute("select CURSHIFT,CURCREW from SHIFTVIEW");
			//conn.Commit();
			//auto res = stmt.GetResultset();


			auto res = DB::OracleDB::OracleDML::executeQuery("select CURSHIFT,CURCREW from SHIFTVIEW@lk_pri");
			if (res.rs_.Next())
			{
				shift._shiftName = res.rs_.Get<std::string>("CURSHIFT");
				shift._crewName = res.rs_.Get<std::string>("CURCREW");
			}
			else
			{
				renaissance::log::LOG_ERR_NUM(3420, fmt::format("获取当前帮助失败！不存在记录! "));
			}
		}
		catch (const std::exception& e)
		{
			renaissance::log::LOG_ERR(fmt::format("The error occurred in GetCurrentShiftInfo(), reason: {0}", e.what()));
		}

		return shift;

	}
#pragma endregion


private:

};

