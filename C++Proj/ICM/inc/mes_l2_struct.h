/*
* Copyright (c) 2004, NERCAR
* All rights reserved.
*
* 文件名称：mes_l2_struct
* 摘    要：与宝信MES通信电文的结构体映射
*			 关于详细通信规约，请参考宝信给的iXcom静态规约.pdf
*
* 版本历史：
*     2023-02-03    v1.0     XGZ     创建
*/

#ifndef _MES_L2_COMMUNICATION_H_
#define _MES_L2_COMMUNICATION_H_

#include <map>
#include <any>
#include <string>
#include "project_shared.h"

//单字节对齐
#pragma pack(1)

/// 与MES通信的电文映射结构体
namespace mes_l2_msg_define {


	constexpr auto COIL_LEN = 11;
	constexpr auto SLAB_LEN = 13;

	/**
	* @description	: Universal message header
	* @MsgId		:
	* @note			: 与宝信MES通信，通用电文头，29byte
	*/
	struct  common_header
	{
		char msg_len[shared_define::mes_message::LENGTH_LEN]; //telegram length:"0100"
		char msg_id[shared_define::mes_message::IDENTITY_LEN];  //tel number:"L3ML01"
		char msg_send_date[shared_define::mes_message::DATESEND_LEN];//len:8 , eg. “20060101”
		char msg_send_time[shared_define::mes_message::TIMESEND_LEN];// Six digits hhmmss eg.“121201”
		char send_code[shared_define::mes_message::SENDER_LEN]; //发送端主机的描述码，是个 2 字符的字 符串，不能含有空格或结束符. eg. "M2"
		char recv_code[shared_define::mes_message::RECEIVER_LEN];//接收端描述码,eg. "S2"
		char flag; //传送功能码,大写字母 'D' ;表示发数据，'A'：发送电文成功； 'B'：电文传送过程出错.当数据接收正确结束后，应答电文返回的传送功能码必须设为“A”；如果数据接收异 常结束，应答电文返回的传送功能码必须设为“B”
	};

	/**
	* @description	: 心跳电文
	* @MsgId		: "999999"
	* @note			: 心跳电文号固定为 “999999” ，长度为 30 字节，无数据内容
	*				  flag表示电文的目的，固定为 'C'
	*/
	struct heart_beat
	{
		struct common_header header;
		char end_character; // = 0x0a;
	};

	/**
	* @description	: 响应电文
	* @MsgId		:
	* @note			:
	*
	*/
	struct response_msg
	{
		struct common_header header;
		char  field_info[shared_define::mes_message::TEXT_FIELD_LENGTH]; /*当传送功能码为'A'时表示电文发送成功,控制域填充空格;当传送功能码为'B'时表示电文传送过程出错，应以西文字符串指明出错的原因与地点*/
		char end_character; // = 0x0a;
	};

	/**
	* @description	: MLL301 - Request Data from L3
	* @MsgId		: 1201
	* @note			: L2——>L3 请求订单
	* 注: 所有电文结构体声明之大小均为通信规约中指定的大小,使用char[]字段时考虑 [大小+1],以为`\0`结尾;
	*/
	struct MLL301
	{
		struct common_header header;
		int REQUEST_TYPE;
		char SLAB_ID[14];
		char end_character = 0x0a; // = 0x0a;
	};

	/**
	* @description	: MLL302 - Slab Charge Report
	* @MsgId		: 1202
	* @note			: L2——>L3 Slab Charge Report
	* 注: 所有电文结构体声明之大小均为通信规约中指定的大小,使用char[]字段时考虑 [大小+1],以为`\0`结尾;
	*/
	struct MLL302
	{
		struct common_header header;
		char GENERATETIME[17];
		char SLAB_ID[13];
		char COIL_ID[11];
		char ROLLING_SCHED_ID[10];
		char FURNACE_NO;
		char CHARGE_TIME[14];
		char SHIFT_NO;
		char SHIFT_TEAM;
		char CHARGE_TEMP[4];
		char SLAB_WEIGHT_ACT[6];
		char end_character = 0x0a; // = 0x0a;
	};


	/**
	* @description	: MLL303 - Slab Discharge Report
	* @MsgId		: 1203, 102bytes
	* @note			: L2——>L3 Slab Discharge Report
	* 注: 所有电文结构体声明之大小均为通信规约中指定的大小,使用char[]字段时考虑 [大小+1],以为`\0`结尾;
	*/
	struct MLL303
	{
		struct common_header header;
		char GENERATETIME[17];
		char SLAB_ID[13];
		char COIL_ID[11];
		char ROLLING_SCHED_ID[10];
		char FURNACE_NO;
		char DISCHARGE_TIME[14];
		char SHIFT_NO;
		char SHIFT_TEAM;
		char DISCHARGE_TEMP[4];
		char end_character = 0x0a; // = 0x0a;
	};


	/// <summary>
	/// SLAB CANCEL RPT
	/// </summary>
	struct MLL304
	{
		struct common_header header;
		char GENERATETIME[17];         //
		char SLAB_ID[13];			   //C13
		char COIL_ID[11];			   //C11
		char ROLLING_SCHED_ID[10];	   //C10
		char REJECT_LOCATION;		   //C1
		char REJECT_REASON;			   //C1
		char SCRAP_OR_TRFBAR;		   //C1
		char REJECT_TIME[14];		   //C14
		char OPERATOR[6];			   //C6
		char SHIFT_NO;				   //C1
		char SHIFT_TEAM;			   //C1
		char SLAB_WEIGHT[6];		   //N6
		char TRANSFER_BAR_THICKN[6];   //N6.3
		char TRANSFER_BAR_WIDTH[6];	   //N5.1
		char TRANSFER_BAR_LENGTH[8];   //N8
		char TAKE_OFF_PLACE[20];	   //C20
		char end_character; // = 0x0a;

		MLL304()
		{
			memset(this, 0x00, sizeof(MLL304));
			this->end_character = 0x0a;
		}

	};


	struct MLL305
	{
		struct common_header header;
		char GENERATETIME[17];         //
		char COIL_ID[11];
		char SLAB_ID[13];
		char ROLLING_SCHED_ID[10];
		char ROLLING_START_TIME[14];
		char ROLLING_END_TIME[14];
		char SHIFT_NO;
		char SHIFT_TEAM;
		char RM_EXIT_SLAB_THICKN[6];
		char RM_EXIT_SLAB_WIDTH[5];
		char RM_EXIT_SLAB_LENGTH[5];
		char RM_EXIT_SLAB_TEMP[4];
		char FM_EXIT_THICKN_AVG[6];
		char FM_EXIT_THICKN_MAX[6];
		char FM_EXIT_THICKN_MIN[6];
		char FM_EXIT_WIDTH_AVG[5];
		char FM_EXIT_WIDTH_MAX[5];
		char FM_EXIT_WIDTH_MIN[5];
		char FM_EXIT_LENGTH[5];
		char COIL_OUTER_DIA[4];
		char COIL_WEIGHT_CALC[6];
		char FM_ENTRY_TEMP_AVG[4];
		char FM_EXIT_TEMP_AVG[4];
		char COILING_TEMP_AVG[4];
		char CROWN_AVG[8];
		char CROWN_MAX[8];
		char CROWN_MIN[8];
		char FLATNESS_AVG[8];
		char FLATNESS_MAX[8];
		char FLATNESS_MIN[8];
		char COILER_ID;
		char WEDGE_AVG[8];
		char WEDGE_MAX[8];
		char WEDGE_MIN[8];
		char end_character; // = 0x0a;

	};

	/// <summary>
	/// 
	/// </summary>
	struct MLL306
	{
		struct common_header header;
		char GENERATETIME[17];         //
		char COIL_ID[11];
		char SAMPLE_TIME[14];
		char end_character ; // = 0x0a;
	};

	struct MLL307
	{
		struct common_header header;
		char GENERATETIME[17];
		char COIL_ID[11];
		char WEIGHING_TIME[14];
		char COIL_WEIGHT[6];
		char end_character; // = 0x0a;
	};

	struct MLL308
	{
		struct common_header header;
		char GENERATETIME[17];
		char COIL_ID[11];
		char TRACK_PLACE[2];
		char end_character; // = 0x0a;
	};



	/// <summary>
	/// MLL309 - Roll Change Report
	/// </summary>
	struct MLL309
	{
		struct common_header header;
		char GENERATETIME[17];
		char ROLL_SET_ID[10];
		char ROLL_TYPE[2];
		char ROLL_KIND;
		char ROLL_LOCATION[3];
		char ROLL_CHANGE_TIME[14];
		char ROLLED_TONNAGE[10]; //ton 
		char ROLLED_LENGTH[10]; //km
		char ROLL_ID[10];
		char end_character; // = 0x0a;
	};



	/**
	* @description	: L3ML01 - Rolling Schedule from L3
	* @MsgId		: 1101
	* @note			:
	*/
	struct L3ML01
	{
		//struct common_header header;
		char SEND_STATUS; //
		char ROLLING_SCHEDULE_ID[10];
		char TARGET_CHARGE_DATE[14];
		char TARGET_ROLLING_DATE[14];
		char HOT_CHARGING;
		char SEQUENCE_NO[8];
		char SLAB_ID[mes_l2_msg_define::SLAB_LEN];
		char COIL_ID[mes_l2_msg_define::COIL_LEN];
		char HEAT_ID[10];
		char STEEL_GRADE[16];
		char SLAB_THICKNESS[6];
		char SLAB_WIDTH[5];
		char SLAB_LENGTH[5];
		char SLAB_CALC_WEIGHT[6];
		char SLAB_TAPER_STATUS;
		char SLAB_TAPER_VALUE[5];
		char GRADE_TRANS_CODE;
		char FERRITIC_ROLLING;
		char CHARGE_TEMP_AIM[4];
		char DISCHARGE_TEMP_AIM[4];
		char PLATE_FLAG;
		char RM_EXIT_TEMP_AIM[4];
		char RM_EXIT_TEMP_MAX[4];
		char RM_EXIT_TEMP_MIN[4];
		char RM_THICKN_AIM[6];
		char RM_WIDTH_AIM[5];
		char NO_COILBOX_FLAG[4];
		char CS_TEMP_AIM[4];
		char CS_TEMP_MAX[4];
		char CS_TEMP_MIN[4];
		char FM_EXIT_THICKN_AIM[6];
		char FM_EXIT_THICKN_MAX[6];
		char FM_EXIT_THICKN_MIN[6];
		char FM_EXIT_WIDTH_AIM[5];
		char FM_EXIT_WIDTH_MAX[5];
		char FM_EXIT_WIDTH_MIN[5];
		char FM_EXIT_TEMP_AIM[4];
		char FM_EXIT_TEMP_MAX[4];
		char FM_EXIT_TEMP_MIN[4];
		char COILING_TEMP_AIM[4];
		char COILING_TEMP_MAX[4];
		char COILING_TEMP_MIN[4];
		char FM_EXIT_CROWN_AIM[4];
		char FM_EXIT_CROWN_MAX[4];
		char FM_EXIT_CROWN_MIN[4];
		char FM_EXIT_FLATNESS_AIM[4];
		char FM_EXIT_FLATNESS_MAX[4];
		char FM_EXIT_FLATNESS_MIN[4];
		char FM_EXIT_THICK_ALT[6];
		char FM_EXIT_TEMP_ALT[4];
		char COILING_TEMP_ALT[4];
		char IM_COOLING_TEMP[4];
		char IM_RECOVERY_TIME[3];
		char COOLING_RATE_CODE;
		char COILER_HOT_HEAD_LENGTH[5];
		char COILER_HOT_HEAD_TEMP_OFFS[4];
		char COILER_HOT_TAIL_LENGTH[5];
		char COILER_HOT_TAIL_TEMP_OFFS[4];
		char SAMPLE_FLAG;
		char SAMPLE_ID[12];
		char COIL_DEST_AREA;
		char CUSTOMER_ORDER[10];
		char PRODUCTION_STD[50];
		char EXTRA_STRAPS_NO;
		char USE_ANALYSIS_FLAG;
		char C_ACTUAL[7];
		char SI_ACTUAL[7];
		char MN_ACTUAL[7];
		char P_ACTUAL[7];
		char S_ACTUAL[7];
		char CR_ACTUAL[7];
		char NI_ACTUAL[7];
		char CU_ACTUAL[7];
		char MO_ACTUAL[7];
		char V_ACTUAL[7];
		char TI_ACTUAL[7];
		char AL_ACTUAL[7];
		char B_ACTUAL[7];
		char NB_ACTUAL[7];
		char N_ACTUAL[7];
		char W_ACTUAL[7];
		char SN_ACTUAL[7];
		char O_ACTUAL[7];
		char H_ACTUAL[7];
		char MG_ACTUAL[7];
		char CO_ACTUAL[7];
		char ZR_ACTUAL[7];
		char TA_CONTENT[7];
		char ZN_ACTUAL[7];
		char FE_ACTUAL[7];
		char INSPECTION_INSTR[100];
		char ROLLING_INSTR[100];
		char STEEL_TYPE[10];
		char END_CHARACTER;

		//std::string SEND_STATUS; //
		//std::string ROLLING_SCHEDULE_ID;
		//std::string TARGET_CHARGE_DATE;
		//std::string TARGET_ROLLING_DATE;
		//std::string HOT_CHARGING;
		//std::string SEQUENCE_NO;
		//std::string SLAB_ID;
		//std::string COIL_ID;
		//std::string HEAT_ID;
		//std::string STEEL_GRADE;
		//std::string SLAB_THICKNESS;
		//std::string SLAB_WIDTH;
		//std::string SLAB_LENGTH;
		//std::string SLAB_CALC_WEIGHT;
		//std::string SLAB_TAPER_STATUS;
		//std::string SLAB_TAPER_VALUE;
		//std::string GRADE_TRANS_CODE;
		//std::string FERRITIC_ROLLING;
		//std::string CHARGE_TEMP_AIM;
		//std::string DISCHARGE_TEMP_AIM;
		//std::string PLATE_FLAG;
		//std::string RM_EXIT_TEMP_AIM;
		//std::string RM_EXIT_TEMP_MAX;
		//std::string RM_EXIT_TEMP_MIN;
		//std::string RM_THICKN_AIM;
		//std::string RM_WIDTH_AIM;
		//std::string NO_COILBOX_FLAG;
		//std::string CS_TEMP_AIM;
		//std::string CS_TEMP_MAX;
		//std::string CS_TEMP_MIN;
		//std::string FM_EXIT_THICKN_AIM;
		//std::string FM_EXIT_THICKN_MAX;
		//std::string FM_EXIT_THICKN_MIN;
		//std::string FM_EXIT_WIDTH_AIM;
		//std::string FM_EXIT_WIDTH_MAX;
		//std::string FM_EXIT_WIDTH_MIN;
		//std::string FM_EXIT_TEMP_AIM;
		//std::string FM_EXIT_TEMP_MAX;
		//std::string FM_EXIT_TEMP_MIN;
		//std::string COILING_TEMP_AIM;
		//std::string COILING_TEMP_MAX;
		//std::string COILING_TEMP_MIN;
		//std::string FM_EXIT_CROWN_AIM;
		//std::string FM_EXIT_CROWN_MAX;
		//std::string FM_EXIT_CROWN_MIN;
		//std::string FM_EXIT_FLATNESS_AIM;
		//std::string FM_EXIT_FLATNESS_MAX;
		//std::string FM_EXIT_FLATNESS_MIN;
		//std::string FM_EXIT_THICK_ALT;
		//std::string FM_EXIT_TEMP_ALT;
		//std::string COILING_TEMP_ALT;
		//std::string IM_COOLING_TEMP;
		//std::string IM_RECOVERY_TIME;
		//std::string COOLING_RATE_CODE;
		//std::string COILER_HOT_HEAD_LENGTH;
		//std::string COILER_HOT_HEAD_TEMP_OFFS;
		//std::string COILER_HOT_TAIL_LENGTH;
		//std::string COILER_HOT_TAIL_TEMP_OFFS;
		//std::string SAMPLE_FLAG;
		//std::string SAMPLE_ID;
		//std::string COIL_DEST_AREA;
		//std::string CUSTOMER_ORDER;
		//std::string PRODUCTION_STD;
		//std::string EXTRA_STRAPS_NO;
		//std::string USE_ANALYSIS_FLAG;
		//std::string C_ACTUAL;
		//std::string SI_ACTUAL;
		//std::string MN_ACTUAL;
		//std::string P_ACTUAL;
		//std::string S_ACTUAL;
		//std::string CR_ACTUAL;
		//std::string NI_ACTUAL;
		//std::string CU_ACTUAL;
		//std::string MO_ACTUAL;
		//std::string V_ACTUAL;
		//std::string TI_ACTUAL;
		//std::string AL_ACTUAL;
		//std::string B_ACTUAL;
		//std::string NB_ACTUAL;
		//std::string N_ACTUAL;
		//std::string W_ACTUAL;
		//std::string SN_ACTUAL;
		//std::string O_ACTUAL;
		//std::string H_ACTUAL;
		//std::string MG_ACTUAL;
		//std::string CO_ACTUAL;
		//std::string ZR_ACTUAL;
		//std::string TA_CONTENT;
		//std::string ZN_ACTUAL;
		//std::string FE_ACTUAL;
		//std::string INSPECTION_INSTR;
		//std::string ROLLING_INSTR;
		//std::string STEEL_TYPE;
		//std::string END_CHARACTER;
	};

	struct L3ML01Wrapper
	{
		L3ML01 data;

	};

	using EOMEvtHandler = void (*)(std::any sender, std::any data, std::any paramList[]);

	struct L3ML02
	{
		char ROLL_SET_ID[10];
		char ROLL_TYPE[2];
		char ROLL_QUALITY[2];
		char ROLL_KIND;
		char LOCATION[3];
		char TOP_OS_ROLL_ID[10];
		char TOP_OS_ROLL_DIA[6];
		char TOP_OS_ROLL_CROWN[4];
		char TOP_OS_ROLL_CROWN_MAX[4];
		char TOP_OS_ROLL_CROWN_MIN[4];
		char BTM_DS_ROLL_ID[10];
		char BTM_DS_ROLL_DIA[6];
		char BTM_DS_ROLL_CROWN[4];
		char BTM_DS_ROLL_CROWN_MAX[4];
		char BTM_DS_ROLL_CROWN_MIN[4];
		char TONNAGE_LIMIT[8];
		char LENGTH_LIMIT[8];
		char EDGER_ROLL_TAPER[6];
	};

	struct L3ML03
	{
		char CONFIRM_FLAG;
		char MATERIAL_ID[12];
		char MESSAGE_ID[6];
		char REJECT_REASON[20];
	};


}

#pragma  pack()
#endif
