#pragma once

#include "project_shared.h"
//单字节对齐
#pragma pack(1)
/// <summary>
/// 与TM相关结构体定义
/// </summary>
namespace tm_l2_msg_define
{

	/// <summary>
	/// 通用TM消息头 96 byte
	/// </summary>
	struct TM_HEADER
	{
		char MSGTYPE_INFO[5];
		char MSGSEQ_INFO[10];
		char VERCODE_INFO;
		char VERRC_INFO[3];
		char HEADLGTH_INFO[2];
		char DATALGTH_INFO[5];
		char EVDATE_INFO[8];
		char EVTIME_INFO[6];
		char SENDER_INFO[12];
		char RECEIVER_INFO[12];
		char SCHEMA_INFO[20];
		char MSGID_INFO[9];
		char FILLER_INFO[3];
	};

	// define in TMMessageHeader from abb l2
	constexpr  int HEADER_LENGTH = 96;
#ifdef ENABLE_STRUCT

	constexpr  int MSGTYPE_INFO[2]{ 0, 5 };
	constexpr  int MSGSEQ_INFO[2]{ 5, 10 };
	constexpr  int VERCODE_INFO[2]{ 15, 1 };
	constexpr  int VERRC_INFO[2]{ 16, 3 };
	constexpr  int HEADLGTH_INFO[2]{ 19, 2 };
	constexpr  int DATALGTH_INFO[2]{ 21, 5 };
	constexpr  int EVDATE_INFO[2]{ 26, 8 };
	constexpr  int EVTIME_INFO[2]{ 34, 6 };
	constexpr  int SENDER_INFO[2]{ 40, 12 };
	constexpr  int RECEIVER_INFO[2]{ 52, 12 };
	constexpr  int SCHEMA_INFO[2]{ 64, 20 };
	constexpr  int MSGID_INFO[2]{ 84, 9 };
	constexpr  int FILLER_INFO[2]{ 93, 3 };

#endif

#pragma region 1020 Message define
	//////////////////////////////////////////////////////////////////////////
	// 
	// 每个消息组成格式：
	// 
	// 通用消息头[96 bytes] + 每个电文的固定头部 [64: 可变] + 数据长度 [38：可变[头部信息+数数据实体+尾部信息]]
	// 
	//////////////////////////////////////////////////////////////////////////

#ifdef ENABLE_STRUCT

	namespace tm1020
	{
		// Constants
		constexpr auto MSGTYPE = "1020";

		// Length of the fixed part of the message
		constexpr int FIXEDPART_LENGTH = 64;

		// Constants defining the startpos and length of the fields in the data string
		constexpr int	EVENTTYPE_INFO[2]{ 0, 1 };
		constexpr int	FLAGQUAL_INFO[2]{ 1, 1 };
		constexpr int	EXTORDERID_INFO[2]{ 2, 20 };
		constexpr int	NOORDITEMS_INFO[2]{ 22, 6 };
		constexpr int	STARTITEMNO_INFO[2]{ 28, 6 };
		constexpr int	ROUTE_INFO[2]{ 34, 5 };
		constexpr int	DATE_INFO[2]{ 39, 8 };
		constexpr int	TIME_INFO[2]{ 47, 6 };
		constexpr int	FILLER_INFO_[2]{ 53, 8 };
		constexpr int	NORECORDS_INFO[2]{ 61, 3 };

		// 每个变量长度
		constexpr int TOT_LENGTH = 38;

		constexpr int	INDEX_INFO[2]{ 0, 3 };
		constexpr int	DTYPE_INFO[2]{ 3, 1 };
		constexpr int	VALUE_INFO[2]{ 4, 24 };
		constexpr int	FILLER_INFO_V[2]{ 28, 10 };

}
#endif

	// default time
	constexpr auto	DEFAULT_TIME = "00010101";
	constexpr auto	DEFAULT_DATE = "000000";


	/// <summary>
	/// 1020 消息头 64 byte
	/// </summary>
	struct TM_1020_HEADER
	{
		char	EVENTTYPE_INFO;
		char	FLAGQUAL_INFO;
		char	EXTORDERID_INFO[20];
		char	NOORDITEMS_INFO[6];
		char	STARTITEMNO_INFO[6];
		char	ROUTE_INFO[5];
		char	DATE_INFO[8];
		char	TIME_INFO[6];
		char	FILLER_INFO[8];
		char	NORECORDS_INFO[3];
	};


	struct L2TM1020STRIPBODY
	{
		//char ROLLING_ORDER_ID[38]; //T Rolling Order Identity (Coil Id)
		//char PROD_SEQ_NO[38]; //R 用科学计数法转换
		//char PROD_MAT_TYPE[38]; //T 
		//char SLAB_ID[38]; //T
		//char SLAB_LENGTH[38]; //R
		//char SLAB_WIDTH[38]; //R
		//char SLAB_WEIGHT_CALC[38]; //I
		//char COIL_DEST_AREA[38]; //I
		//char SAMPLE_FLAG[38]; //I
		//char SAMPLE_ID[38]; //T
		//char EXTRA_STRAPS_NO[38]; //I
		//char SLAB_THICKNESS[38]; //R
		//char GRADE[38]; //T
		//char HEATNO[38]; //T
		//char HOT_CHARGING[38]; //I
		//char DISCHARGE_TEMP_AIM[38]; //I
		std::string ROLLING_ORDER_ID; //T Rolling Order Identity (Coil Id)
		std::string PROD_SEQ_NO; //R 用科学计数法转换
		std::string PROD_MAT_TYPE; //T 
		std::string SLAB_ID; //T
		std::string SLAB_LENGTH; //R
		std::string SLAB_WIDTH; //R
		std::string SLAB_WEIGHT_CALC; //I
		std::string COIL_DEST_AREA; //I
		std::string SAMPLE_FLAG; //I
		std::string SAMPLE_ID; //T
		std::string EXTRA_STRAPS_NO; //I
		std::string SLAB_THICKNESS; //R
		std::string GRADE; //T
		std::string HEATNO; //T
		std::string HOT_CHARGING; //I
		std::string DISCHARGE_TEMP_AIM; //I

		//L2TM1020STRIPBODY()
		//{
		//	memset(this, 0x00, sizeof(L2TM1020STRIPBODY));
		//}
	};

	/// <summary>
	/// 不同消息长度不同，谓之变长
	/// From: PDIDataLite : TMVariable
	/// </summary>
	struct L2TM1020
	{
		TM_HEADER COMMON_HEADER;
		TM_1020_HEADER HEADER1020;
		L2TM1020STRIPBODY BODY;
	};
#pragma endregion



}

#pragma  pack()