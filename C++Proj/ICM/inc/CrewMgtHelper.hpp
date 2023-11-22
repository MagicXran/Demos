#pragma once


#include "DBOraclePool.hpp"
#include "loggers.hpp"



struct ShiftInfo
{
	int		_shiftNo = 0;  /*0(��),1,2,3(��)*/
	int     _crew = 0;    /*1:ҹ, 4:��*/
	std::string _shiftName = ""; /*1:�ף�2,3,4*/
	std::string _crewName = "";  /*2:�װ� 1:ҹ�࣬3:��*/
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
	/// ��ѯ���������Ϣ
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
				renaissance::log::LOG_ERR_NUM(3420, fmt::format("��ȡ��ǰ����ʧ�ܣ������ڼ�¼! "));
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

