/*************************************************************************
*
*			通用定义头文件
*						--- created by renaissancer
*					    --- time: 2023-01-13
*
*
*************************************************************************/

#ifndef PROJECT_SHARED_H_
#define PROJECT_SHARED_H_

#include <cstdint>
#include <string>
#include <unordered_map>
#include <functional>
#include <any>
#include <vector>
#include <iostream>

/// <summary>
/// 通用定义
/// </summary>
namespace  shared_define
{

#pragma region 配置文件路径

	/// <summary>
	///  ServerApp.json为整个ServerApp通用的文件配置
	/// </summary>
	constexpr auto ServerInfoPath = R"(D:/SG1450L2Server/Config/ServerApp.json)";
	//constexpr auto ServerInfoPath = R"(C:/Repository/rm-transformation-of-shagang/ServerApps/Config/ServerApp.json)";

#pragma endregion

#pragma region 类型定义

	/// <summary>
	/// 定义TB_PDI中 ID 类型
	/// </summary>
	using ID_TYPE = int;

	/// <summary>
	/// 化学成分类型
	/// </summary>
	using CHEMI_TYPE = float;

	using EquipPropNameType = std::vector<std::string>;


	/// <summary>
	/// 设备名:id
	/// </summary>
	using  EquipNameIdType = std::unordered_map<std::string, shared_define::ID_TYPE>;


	/// <summary>
	/// 属性名对应的值类型
	/// </summary>
	using  PropNameDataType = std::unordered_map<std::string, int>;


	/// <summary>
	/// 属性名对应ID
	/// </summary>
	using  PropNameIdType = std::unordered_map<std::string, shared_define::ID_TYPE>;

	/// <summary>
	/// {prop_id : data_type}
	/// </summary>
	using  PropIdDataType = std::unordered_map<shared_define::ID_TYPE, int>;

	/// <summary>
	/// 表示大于零
	/// </summary>
	constexpr auto NonZero = 1;

#pragma endregion

#pragma region 公共常量定义

	const std::string  MIN_DATETIME("00010101000000");
	constexpr auto MIN_DATE_LEN = 19;

	constexpr auto  MAX_BUFFER_SIZE = 1024 * 3;

	// 字符 '0'
	constexpr auto CHARACTER_ZERO = 48;
	// 字符 '1'
	constexpr auto CHARACTER_ONE = 49;

	//最大字段长度
	constexpr auto MAX_FIELD_LEN = 200;

	enum ByteOrder
	{
		LittleEndian = 0, BigEndian = 1, UnkownEndian = 2
	};

	/// <summary>
	/// L1 VIP && L2 byte orders
	/// </summary>
	constexpr auto VIPMLByteOrder = ByteOrder::BigEndian;

	constexpr auto L3MLByteOrder = LittleEndian;

	/// <summary>
	/// Model 与 本系统通信字节序
	/// </summary>
	constexpr auto ModelMLByteOrder = ByteOrder::LittleEndian;

	/// <summary>
	/// Data type I = integer, R= real, B= boolean, T= Text (20 char)
	/// </summary>
	enum ValueType
	{
		B = 1, D = 2, I = 3, R, T
	};


	/// <summary>
	/// Enumeration for the send report status
	/// </summary>
	enum SendReportStatus { NotSent = 0, Sent = 1, Acknowledged = 2, Rejected = 4, Failed = 8 };

#pragma endregion

#pragma region 公共结构体定义

	struct ComInfo
	{
		std::string name_;
		std::string _tag;
		std::any _value;
	};

#pragma region EquipNames

	struct EquipNames
	{
		///<summary>Coil Box</summary>
		static constexpr auto CBOX = "CBOX";
		///<summary>Crop Shear</summary>
		static constexpr auto CS = "CS";
		///<summary>Coiling Temperature Control</summary>
		static constexpr auto CTC = "CTC";
		///<summary>CTC Model Report</summary>
		static constexpr auto CTC_MODEL_RPT = "CTC_MODEL_RPT";
		///<summary>CTC Model Setup</summary>
		static constexpr auto CTC_MODEL_SU = "CTC_MODEL_SU";
		///<summary>Down Coilers 1-3</summary>
		static constexpr auto DC = "DC";
		///<summary>DC Model Setup</summary>
		static constexpr auto DC_MODEL_SU = "DC_MODEL_SU";
		///<summary>Roughing Mill 1, Edger</summary>
		static constexpr auto E1 = "E1";
		///<summary>Roughing Mill 2, Edger</summary>
		static constexpr auto E2 = "E2";
		///<summary>Finishing Mill, Stand 1</summary>
		static constexpr auto F1 = "F1";
		///<summary>Finishing Mill, Stand 2</summary>
		static constexpr auto F2 = "F2";
		///<summary>Finishing Mill, Stand 3</summary>
		static constexpr auto F3 = "F3";
		///<summary>Finishing Mill, Stand 4</summary>
		static constexpr auto F4 = "F4";
		///<summary>Finishing Mill, Stand 5</summary>
		static constexpr auto F5 = "F5";
		///<summary>Finishing Mill, Stand 6</summary>
		static constexpr auto F6 = "F6";
		///<summary>Finishing Mill, Stand 7</summary>
		static constexpr auto F7 = "F7";
		///<summary>Furnaces 1-3</summary>
		static constexpr auto FCE = "FCE";
		///<summary>Furnace Entry Area</summary>
		static constexpr auto FCE_ENTRY = "FCE_ENTRY";
		///<summary>Furnace Exit Area</summary>
		static constexpr auto FCE_EXIT = "FCE_EXIT";
		///<summary>Finishing Area</summary>
		static constexpr auto FIN = "FIN";
		///<summary>Finishing Mill</summary>
		static constexpr auto FM = "FM";
		///<summary>FM Model Report</summary>
		static constexpr auto FM_MODEL_RPT = "FM_MODEL_RPT";
		///<summary>FM Model Setup, Common</summary>
		static constexpr auto FM_MODEL_SU = "FM_MODEL_SU";
		///<summary>FM Model Setup, Stand 1</summary>
		static constexpr auto FM_MODEL_SU_F1 = "FM_MODEL_SU_F1";
		///<summary>FM Model Setup, Stand 2</summary>
		static constexpr auto FM_MODEL_SU_F2 = "FM_MODEL_SU_F2";
		///<summary>FM Model Setup, Stand 3</summary>
		static constexpr auto FM_MODEL_SU_F3 = "FM_MODEL_SU_F3";
		///<summary>FM Model Setup, Stand 4</summary>
		static constexpr auto FM_MODEL_SU_F4 = "FM_MODEL_SU_F4";
		///<summary>FM Model Setup, Stand 5</summary>
		static constexpr auto FM_MODEL_SU_F5 = "FM_MODEL_SU_F5";
		///<summary>FM Model Setup, Stand 6</summary>
		static constexpr auto FM_MODEL_SU_F6 = "FM_MODEL_SU_F6";
		///<summary>FM Model Setup, Stand 7</summary>
		static constexpr auto FM_MODEL_SU_F7 = "FM_MODEL_SU_F7";
		///<summary>Misc Mill data</summary>
		static constexpr auto MILL = "MILL";
		///<summary>Roughing Mill 1, Rougher</summary>
		static constexpr auto R1 = "R1";
		///<summary>Roughing Mill 2, Rougher</summary>
		static constexpr auto R2 = "R2";
		///<summary>Reject Data</summary>
		static constexpr auto REJ_DATA = "REJ_DATA";
		///<summary>RM Common</summary>
		static constexpr auto RM = "RM";
		///<summary>Roughing Mill 1, Common</summary>
		static constexpr auto RM1 = "RM1";
		///<summary>RM1 Model Setup, Common</summary>
		static constexpr auto RM1_MODEL_SU = "RM1_MODEL_SU";
		///<summary>RM1 Model Setup, Pass</summary>
		static constexpr auto RM1_MODEL_SU_PX = "RM1_MODEL_SU_PX";
		///<summary>Roughing Mill 1, Pass</summary>
		static constexpr auto RM1_PX = "RM1_PX";
		///<summary>Roughing Mill 2</summary>
		static constexpr auto RM2 = "RM2";
		///<summary>RM2 Model Setup, Common</summary>
		static constexpr auto RM2_MODEL_SU = "RM2_MODEL_SU";
		///<summary>RM2 Model Setup, Pass</summary>
		static constexpr auto RM2_MODEL_SU_PX = "RM2_MODEL_SU_PX";
		///<summary>Roughing Mill 2, Pass</summary>
		static constexpr auto RM2_PX = "RM2_PX";
		///<summary>RM Model Report</summary>
		static constexpr auto RM_MODEL_RPT = "RM_MODEL_RPT";
	};

#pragma endregion

#pragma region ProNames

	struct PropNames
	{
		///<summary>0 =  model defaults, 1 = actual analysis data</summary>
		static constexpr auto CHEM_ACT_FLAG = "CHEM_ACT_FLAG";
		///<summary>Aluminium content</summary>
		static constexpr auto CHEM_Al = "CHEM_Al";
		///<summary>Boron content</summary>
		static constexpr auto CHEM_B = "CHEM_B";
		///<summary>Carbon content</summary>
		static constexpr auto CHEM_C = "CHEM_C";
		///<summary>Cobalt content</summary>
		static constexpr auto CHEM_Co = "CHEM_Co";
		///<summary>Chromium content</summary>
		static constexpr auto CHEM_Cr = "CHEM_Cr";
		///<summary>Copper content</summary>
		static constexpr auto CHEM_Cu = "CHEM_Cu";
		///<summary>Iron content</summary>
		static constexpr auto CHEM_Fe = "CHEM_Fe";
		///<summary>Hydrogen content</summary>
		static constexpr auto CHEM_H = "CHEM_H";
		///<summary>Magnesium content</summary>
		static constexpr auto CHEM_Mg = "CHEM_Mg";
		///<summary>Manganese content</summary>
		static constexpr auto CHEM_Mn = "CHEM_Mn";
		///<summary>Molybdenum content</summary>
		static constexpr auto CHEM_Mo = "CHEM_Mo";
		///<summary>Nitrogen content</summary>
		static constexpr auto CHEM_N = "CHEM_N";
		///<summary>Niobium content</summary>
		static constexpr auto CHEM_Nb = "CHEM_Nb";
		///<summary>Nickel content</summary>
		static constexpr auto CHEM_Ni = "CHEM_Ni";
		///<summary>Oxygen content</summary>
		static constexpr auto CHEM_O = "CHEM_O";
		///<summary>Phosphorus content</summary>
		static constexpr auto CHEM_P = "CHEM_P";
		///<summary>Sulfur content</summary>
		static constexpr auto CHEM_S = "CHEM_S";
		///<summary>Silicon content</summary>
		static constexpr auto CHEM_Si = "CHEM_Si";
		///<summary>Tin content</summary>
		static constexpr auto CHEM_Sn = "CHEM_Sn";
		///<summary>Tantalum content</summary>
		static constexpr auto CHEM_Ta = "CHEM_Ta";
		///<summary>Titanium content</summary>
		static constexpr auto CHEM_Ti = "CHEM_Ti";
		///<summary>Vanadium content</summary>
		static constexpr auto CHEM_V = "CHEM_V";
		///<summary>Tungsten content</summary>
		static constexpr auto CHEM_W = "CHEM_W";
		///<summary>Zinc content</summary>
		static constexpr auto CHEM_Zn = "CHEM_Zn";
		///<summary>Zirconium content</summary>
		static constexpr auto CHEM_Zr = "CHEM_Zr";
		///<summary>0 = no coilbox, 1 = coilbox</summary>
		static constexpr auto COIL_BOX_FLAG = "COIL_BOX_FLAG";
		///<summary>Coil Box used for material</summary>
		static constexpr auto COIL_BOX_USED = "COIL_BOX_USED";
		///<summary>Coil destination Exit Area number 1-3</summary>
		static constexpr auto COIL_DEST_AREA = "COIL_DEST_AREA";
		///<summary>Coil Exit Area number</summary>
		static constexpr auto COIL_EXIT_AREA_NO = "COIL_EXIT_AREA_NO";
		///<summary>Active crew when coiling finished</summary>
		static constexpr auto COIL_FIN_CREW = "COIL_FIN_CREW";
		///<summary>Active shift when coiling finished</summary>
		static constexpr auto COIL_FIN_SHIFT = "COIL_FIN_SHIFT";
		///<summary>Coil inner diameter (mandrel)</summary>
		static constexpr auto COIL_INNER_DIAMETER = "COIL_INNER_DIAMETER";
		///<summary>Inspection Code</summary>
		static constexpr auto COIL_INSPECTION_CODE = "COIL_INSPECTION_CODE";
		///<summary>Inspection remark</summary>
		static constexpr auto COIL_INSPECTION_REMARK = "COIL_INSPECTION_REMARK";
		///<summary>Coil outer diameter</summary>
		static constexpr auto COIL_OUTER_DIAMETER = "COIL_OUTER_DIAMETER";
		///<summary>Date & time for coil sample</summary>
		static constexpr auto COIL_SAMPLE_TIME = "COIL_SAMPLE_TIME";
		///<summary>Date a time for coil weighing</summary>
		static constexpr auto COIL_WEIGH_TIME_ACT = "COIL_WEIGH_TIME_ACT";
		///<summary>Actual coil weight</summary>
		static constexpr auto COIL_WEIGHT_ACT = "COIL_WEIGHT_ACT";
		///<summary>Coil calculated weight</summary>
		static constexpr auto COIL_WEIGHT_CALC = "COIL_WEIGHT_CALC";
		///<summary>Measured coil weight</summary>
		static constexpr auto COIL_WEIGHT_MEAS = "COIL_WEIGHT_MEAS";
		///<summary>Hot head length</summary>
		static constexpr auto COILING_HOT_HEAD_LENGTH = "COILING_HOT_HEAD_LENGTH";
		///<summary>Hot head temperature offset</summary>
		static constexpr auto COILING_HOT_HEAD_TEMP_OFFS = "COILING_HOT_HEAD_TEMP_OFFS";
		///<summary>Hot tail length</summary>
		static constexpr auto COILING_HOT_TAIL_LENGTH = "COILING_HOT_TAIL_LENGTH";
		///<summary>Hot tail temperature offset</summary>
		static constexpr auto COILING_HOT_TAIL_TEMP_OFFS = "COILING_HOT_TAIL_TEMP_OFFS";
		///<summary>Coiling temperature target</summary>
		static constexpr auto COILING_TEMP_AIM = "COILING_TEMP_AIM";
		///<summary>Coiling  max temperature</summary>
		static constexpr auto COILING_TEMP_AIM_MAX = "COILING_TEMP_AIM_MAX";
		///<summary>Coiling  min temperature</summary>
		static constexpr auto COILING_TEMP_AIM_MIN = "COILING_TEMP_AIM_MIN";
		///<summary>Alternative temp target used when alt thick used</summary>
		static constexpr auto COILING_TEMP_ALT = "COILING_TEMP_ALT";
		///<summary>Slabs containing mixed grades. 0 = normal grade, 1 = mixed grade</summary>
		static constexpr auto CONS_MAT_GRADE_TRANS = "CONS_MAT_GRADE_TRANS";
		///<summary>Charge number from Steel making process</summary>
		static constexpr auto CONS_MAT_HEAT_ID = "CONS_MAT_HEAT_ID";
		///<summary>Slab length from caster</summary>
		static constexpr auto CONS_MAT_LENGTH = "CONS_MAT_LENGTH";
		///<summary>Slab sequence number within rolling schedule</summary>
		static constexpr auto CONS_MAT_SEQ_NO = "CONS_MAT_SEQ_NO";
		///<summary>Slab width taper, changing casting width. 0=No Taper, 1=Taper</summary>
		static constexpr auto CONS_MAT_TAPER_STATUS = "CONS_MAT_TAPER_STATUS";
		///<summary>Delta width less than maximum width</summary>
		static constexpr auto CONS_MAT_TAPER_VALUE = "CONS_MAT_TAPER_VALUE";
		///<summary>Slab thickness</summary>
		static constexpr auto CONS_MAT_THICKNESS = "CONS_MAT_THICKNESS";
		///<summary>Slab calculated weight</summary>
		static constexpr auto CONS_MAT_WEIGHT_CALC = "CONS_MAT_WEIGHT_CALC";
		///<summary>Slab width from caster</summary>
		static constexpr auto CONS_MAT_WIDTH = "CONS_MAT_WIDTH";
		///<summary>early/late cooling, 0 = model default, 1 = early, 2 = late, 3 = distributed</summary>
		static constexpr auto COOLING_RATE_CODE = "COOLING_RATE_CODE";
		///<summary>Crop Shear head cut length</summary>
		static constexpr auto CS_HEAD_CUT_LENGTH = "CS_HEAD_CUT_LENGTH";
		///<summary>Crop Shear head cut weight</summary>
		static constexpr auto CS_HEAD_CUT_WEIGHT = "CS_HEAD_CUT_WEIGHT";
		///<summary>Crop Shear tail cut length</summary>
		static constexpr auto CS_TAIL_CUT_LENGTH = "CS_TAIL_CUT_LENGTH";
		///<summary>Crop Shear tail cut weight</summary>
		static constexpr auto CS_TAIL_CUT_WEIGHT = "CS_TAIL_CUT_WEIGHT";
		///<summary>Crop Shear temperature aim for ferritic rolling else zero.</summary>
		static constexpr auto CS_TEMP_AIM = "CS_TEMP_AIM";
		///<summary>Crop Shear temperature max for ferritic rolling else zero.</summary>
		static constexpr auto CS_TEMP_AIM_MAX = "CS_TEMP_AIM_MAX";
		///<summary>Crop Shear temperature min for ferritic rolling else zero.</summary>
		static constexpr auto CS_TEMP_AIM_MIN = "CS_TEMP_AIM_MIN";
		///<summary>Crop Shear (FM Entry) temperature average</summary>
		static constexpr auto CS_TEMP_AVG = "CS_TEMP_AVG";
		///<summary>Crop Shear (FM Entry) temperature data</summary>
		static constexpr auto CS_TEMP_DAQ = "CS_TEMP_DAQ";
		///<summary>Crop Shear (FM Entry) temperature max</summary>
		static constexpr auto CS_TEMP_MAX = "CS_TEMP_MAX";
		///<summary>Crop Shear (FM Entry) temperature min</summary>
		static constexpr auto CS_TEMP_MIN = "CS_TEMP_MIN";
		///<summary>Crop Shear total cut weight</summary>
		static constexpr auto CS_TOT_CUT_WEIGHT = "CS_TOT_CUT_WEIGHT";
		///<summary>Coiling temp control, actual bottom sprays group 1</summary>
		static constexpr auto CTC_ACT_BTM_SPRAYS_1_DAQ = "CTC_ACT_BTM_SPRAYS_1_DAQ";
		///<summary>Coiling temp control, actual bottom sprays group 2</summary>
		static constexpr auto CTC_ACT_BTM_SPRAYS_2_DAQ = "CTC_ACT_BTM_SPRAYS_2_DAQ";
		///<summary>Coiling temp control, actual bottom sprays group 3</summary>
		static constexpr auto CTC_ACT_BTM_SPRAYS_3_DAQ = "CTC_ACT_BTM_SPRAYS_3_DAQ";
		///<summary>Coiling temp control, actual top sprays group 1</summary>
		static constexpr auto CTC_ACT_TOP_SPRAYS_1_DAQ = "CTC_ACT_TOP_SPRAYS_1_DAQ";
		///<summary>Coiling temp control, actual top sprays group 2</summary>
		static constexpr auto CTC_ACT_TOP_SPRAYS_2_DAQ = "CTC_ACT_TOP_SPRAYS_2_DAQ";
		///<summary>Coiling temp control, actual top sprays group 3</summary>
		static constexpr auto CTC_ACT_TOP_SPRAYS_3_DAQ = "CTC_ACT_TOP_SPRAYS_3_DAQ";
		///<summary>Coiling temp control, coiling temperature average</summary>
		static constexpr auto CTC_COILING_TEMP_AVG = "CTC_COILING_TEMP_AVG";
		///<summary>Coiling temp control, coiling temperature data</summary>
		static constexpr auto CTC_COILING_TEMP_DAQ = "CTC_COILING_TEMP_DAQ";
		///<summary>Coiling temp control, coiling temperature above max</summary>
		static constexpr auto CTC_COILING_TEMP_GTMAX = "CTC_COILING_TEMP_GTMAX";
		///<summary>Coiling temp control, coiling temperature in tolerance</summary>
		static constexpr auto CTC_COILING_TEMP_INTOL = "CTC_COILING_TEMP_INTOL";
		///<summary>Coiling temp control, coiling temperature below min</summary>
		static constexpr auto CTC_COILING_TEMP_LTMIN = "CTC_COILING_TEMP_LTMIN";
		///<summary>Coiling temp control, coiling temperature max</summary>
		static constexpr auto CTC_COILING_TEMP_MAX = "CTC_COILING_TEMP_MAX";
		///<summary>Coiling temp control, coiling temperature max</summary>
		static constexpr auto CTC_COILING_TEMP_MIN = "CTC_COILING_TEMP_MIN";
		///<summary>Coiling temp control, actual temperature reference</summary>
		static constexpr auto CTC_COILING_TEMP_REF_ACT = "CTC_COILING_TEMP_REF_ACT";
		///<summary>Coiling temp control, coiling temperature speed data</summary>
		static constexpr auto CTC_COILING_TEMP_SPEED_DAQ = "CTC_COILING_TEMP_SPEED_DAQ";
		///<summary>Coiling temp control, cooling exit temperature average</summary>
		static constexpr auto CTC_EXIT_TEMP_AVG = "CTC_EXIT_TEMP_AVG";
		///<summary>Coiling temp control, cooling exit temperature data</summary>
		static constexpr auto CTC_EXIT_TEMP_DAQ = "CTC_EXIT_TEMP_DAQ";
		///<summary>Coiling temp control, cooling exit temperature max</summary>
		static constexpr auto CTC_EXIT_TEMP_MAX = "CTC_EXIT_TEMP_MAX";
		///<summary>Coiling temp control, cooling exit temperature min</summary>
		static constexpr auto CTC_EXIT_TEMP_MIN = "CTC_EXIT_TEMP_MIN";
		///<summary>Coiling temp control, cooling exit temperature speed data</summary>
		static constexpr auto CTC_EXIT_TEMP_SPEED_DAQ = "CTC_EXIT_TEMP_SPEED_DAQ";
		///<summary>Coiling temp control, intermediate temperature average</summary>
		static constexpr auto CTC_IM_TEMP_AVG = "CTC_IM_TEMP_AVG";
		///<summary>Coiling temp control, intermediate temperature data</summary>
		static constexpr auto CTC_IM_TEMP_DAQ = "CTC_IM_TEMP_DAQ";
		///<summary>Coiling temp control, intermediate temperature max</summary>
		static constexpr auto CTC_IM_TEMP_MAX = "CTC_IM_TEMP_MAX";
		///<summary>Coiling temp control, intermediate temperature min</summary>
		static constexpr auto CTC_IM_TEMP_MIN = "CTC_IM_TEMP_MIN";
		///<summary>Coiling temp control, intermediate temperature strip speed data</summary>
		static constexpr auto CTC_IM_TEMP_SPEED_DAQ = "CTC_IM_TEMP_SPEED_DAQ";
		///<summary>Measured spray units used at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_ACT_SPRAY_UNITS_1 = "CTC_RPT_ACT_SPRAY_UNITS_1";
		///<summary>Measured spray units used at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_ACT_SPRAY_UNITS_2 = "CTC_RPT_ACT_SPRAY_UNITS_2";
		///<summary>Coiler entry temp error at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_CLE_TEMP_ERR_1 = "CTC_RPT_CLE_TEMP_ERR_1";
		///<summary>Coiler entry temp error at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_CLE_TEMP_ERR_2 = "CTC_RPT_CLE_TEMP_ERR_2";
		///<summary>Cumulative length at Coiler entry pyrometer</summary>
		static constexpr auto CTC_RPT_CLR_ENTRY_CUM_LENGTH = "CTC_RPT_CLR_ENTRY_CUM_LENGTH";
		///<summary>Cobble flag at learning</summary>
		static constexpr auto CTC_RPT_COBBLE_FLAG_1 = "CTC_RPT_COBBLE_FLAG_1";
		///<summary>Cobble flag at learning</summary>
		static constexpr auto CTC_RPT_COBBLE_FLAG_2 = "CTC_RPT_COBBLE_FLAG_2";
		///<summary>Measured spray units used at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_CTC_SPRAY_UNITS_1 = "CTC_RPT_CTC_SPRAY_UNITS_1";
		///<summary>Measured spray units used at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_CTC_SPRAY_UNITS_2 = "CTC_RPT_CTC_SPRAY_UNITS_2";
		///<summary>Time of CTC at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_CTC_TIME_1 = "CTC_RPT_CTC_TIME_1";
		///<summary>Time of CTC at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_CTC_TIME_2 = "CTC_RPT_CTC_TIME_2";
		///<summary>Delta temp feedback at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_DTEMP_FB_CORR_1 = "CTC_RPT_DTEMP_FB_CORR_1";
		///<summary>Delta temp feedback at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_DTEMP_FB_CORR_2 = "CTC_RPT_DTEMP_FB_CORR_2";
		///<summary>Feed back spray units used at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_FB_SPRAY_UNITS_1 = "CTC_RPT_FB_SPRAY_UNITS_1";
		///<summary>Feed back spray units used at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_FB_SPRAY_UNITS_2 = "CTC_RPT_FB_SPRAY_UNITS_2";
		///<summary>Feed forward spray units used at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_FF_SPRAY_UNITS_1 = "CTC_RPT_FF_SPRAY_UNITS_1";
		///<summary>Feed forward spray units used at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_FF_SPRAY_UNITS_2 = "CTC_RPT_FF_SPRAY_UNITS_2";
		///<summary>Cumulative length at FM exit pyrometer</summary>
		static constexpr auto CTC_RPT_FM_EXIT_CUM_LENGTH = "CTC_RPT_FM_EXIT_CUM_LENGTH";
		///<summary>FM exit temp accumulated error at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_FMX_TEMP_A_ERR_1 = "CTC_RPT_FMX_TEMP_A_ERR_1";
		///<summary>FM exit temp accumulated error at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_FMX_TEMP_A_ERR_2 = "CTC_RPT_FMX_TEMP_A_ERR_2";
		///<summary>FM exit temp error meas-model at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_FMX_TEMP_M_ERR_1 = "CTC_RPT_FMX_TEMP_M_ERR_1";
		///<summary>FM exit temp error meas-model at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_FMX_TEMP_M_ERR_2 = "CTC_RPT_FMX_TEMP_M_ERR_2";
		///<summary>FM exit thickness at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_FMX_THICKNESS_1 = "CTC_RPT_FMX_THICKNESS_1";
		///<summary>FM exit thickness at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_FMX_THICKNESS_2 = "CTC_RPT_FMX_THICKNESS_2";
		///<summary>Forward loop temp error pred-target at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_FWDL_TEMP_ERR_1 = "CTC_RPT_FWDL_TEMP_ERR_1";
		///<summary>Forward loop temp error pred-target at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_FWDL_TEMP_ERR_2 = "CTC_RPT_FWDL_TEMP_ERR_2";
		///<summary>Impossible control condition, temp cold w/o sprays</summary>
		static constexpr auto CTC_RPT_IMPOSS_CTRL_COND_1 = "CTC_RPT_IMPOSS_CTRL_COND_1";
		///<summary>Impossible control condition, temp cold w/o sprays</summary>
		static constexpr auto CTC_RPT_IMPOSS_CTRL_COND_2 = "CTC_RPT_IMPOSS_CTRL_COND_2";
		///<summary>Impossible control conditions at learning</summary>
		static constexpr auto CTC_RPT_IMPOSS_LEARN_COND_1 = "CTC_RPT_IMPOSS_LEARN_COND_1";
		///<summary>Impossible control conditions at learning</summary>
		static constexpr auto CTC_RPT_IMPOSS_LEARN_COND_2 = "CTC_RPT_IMPOSS_LEARN_COND_2";
		///<summary>Insufficient sprays flag at learning</summary>
		static constexpr auto CTC_RPT_INSUFF_SPRAYS_FLG_1 = "CTC_RPT_INSUFF_SPRAYS_FLG_1";
		///<summary>Insufficient sprays flag at learning</summary>
		static constexpr auto CTC_RPT_INSUFF_SPRAYS_FLG_2 = "CTC_RPT_INSUFF_SPRAYS_FLG_2";
		///<summary>Learning update accomplished</summary>
		static constexpr auto CTC_RPT_LEARN_UPD_ACCOMP_1 = "CTC_RPT_LEARN_UPD_ACCOMP_1";
		///<summary>Learning update accomplished</summary>
		static constexpr auto CTC_RPT_LEARN_UPD_ACCOMP_2 = "CTC_RPT_LEARN_UPD_ACCOMP_2";
		///<summary>Measured average control zone speed unreasonable</summary>
		static constexpr auto CTC_RPT_M_CLE_AVG_SPEED_NGD_1 = "CTC_RPT_M_CLE_AVG_SPEED_NGD_1";
		///<summary>Measured average control zone speed unreasonable</summary>
		static constexpr auto CTC_RPT_M_CLE_AVG_SPEED_NGD_2 = "CTC_RPT_M_CLE_AVG_SPEED_NGD_2";
		///<summary>Bad measured data at learning</summary>
		static constexpr auto CTC_RPT_MDL_BAD_DATA_1 = "CTC_RPT_MDL_BAD_DATA_1";
		///<summary>Bad measured data at learning</summary>
		static constexpr auto CTC_RPT_MDL_BAD_DATA_2 = "CTC_RPT_MDL_BAD_DATA_2";
		///<summary>Ctr get failure at feedback</summary>
		static constexpr auto CTC_RPT_MDL_FB_GET_ERROR_1 = "CTC_RPT_MDL_FB_GET_ERROR_1";
		///<summary>Ctr get failure at feedback</summary>
		static constexpr auto CTC_RPT_MDL_FB_GET_ERROR_2 = "CTC_RPT_MDL_FB_GET_ERROR_2";
		///<summary>Model learning permissive at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MDL_LRN_PERM_1 = "CTC_RPT_MDL_LRN_PERM_1";
		///<summary>Model learning permissive at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MDL_LRN_PERM_2 = "CTC_RPT_MDL_LRN_PERM_2";
		///<summary>Model spray efficiency at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MDL_SPRAY_EFF_1 = "CTC_RPT_MDL_SPRAY_EFF_1";
		///<summary>Model spray efficiency at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MDL_SPRAY_EFF_2 = "CTC_RPT_MDL_SPRAY_EFF_2";
		///<summary>Measured Coiler entry bottom temperature at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_CBTM_TEMP_1 = "CTC_RPT_MEAS_CBTM_TEMP_1";
		///<summary>Measured Coiler entry bottom temperature at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_CBTM_TEMP_2 = "CTC_RPT_MEAS_CBTM_TEMP_2";
		///<summary>Measured Coiler entry temperature at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_CENT_TEMP_1 = "CTC_RPT_MEAS_CENT_TEMP_1";
		///<summary>Measured Coiler entry temperature at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_CENT_TEMP_2 = "CTC_RPT_MEAS_CENT_TEMP_2";
		///<summary>Measured coiler entry speed at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_CLE_SPEED_1 = "CTC_RPT_MEAS_CLE_SPEED_1";
		///<summary>Measured coiler entry speed at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_CLE_SPEED_2 = "CTC_RPT_MEAS_CLE_SPEED_2";
		///<summary>Measured coiler entry temp unreasonable</summary>
		static constexpr auto CTC_RPT_MEAS_CLE_TEMP_NGD_1 = "CTC_RPT_MEAS_CLE_TEMP_NGD_1";
		///<summary>Measured coiler entry temp unreasonable</summary>
		static constexpr auto CTC_RPT_MEAS_CLE_TEMP_NGD_2 = "CTC_RPT_MEAS_CLE_TEMP_NGD_2";
		///<summary>Measured control zone entry speed at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_CZE_SPEED_1 = "CTC_RPT_MEAS_CZE_SPEED_1";
		///<summary>Measured control zone entry speed at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_CZE_SPEED_2 = "CTC_RPT_MEAS_CZE_SPEED_2";
		///<summary>Measured control zone entry temperature at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_CZE_TEMP_1 = "CTC_RPT_MEAS_CZE_TEMP_1";
		///<summary>Measured control zone entry temperature at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_CZE_TEMP_2 = "CTC_RPT_MEAS_CZE_TEMP_2";
		///<summary>Measured control zone average speed at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_CZN_SPEED_1 = "CTC_RPT_MEAS_CZN_SPEED_1";
		///<summary>Measured control zone average speed at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_CZN_SPEED_2 = "CTC_RPT_MEAS_CZN_SPEED_2";
		///<summary>Measured control zone exit speed at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_CZX_SPEED_1 = "CTC_RPT_MEAS_CZX_SPEED_1";
		///<summary>Measured control zone exit speed at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_CZX_SPEED_2 = "CTC_RPT_MEAS_CZX_SPEED_2";
		///<summary>Measured control zone exit temperature at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_CZX_TEMP_1 = "CTC_RPT_MEAS_CZX_TEMP_1";
		///<summary>Measured control zone exit temperature at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_CZX_TEMP_2 = "CTC_RPT_MEAS_CZX_TEMP_2";
		///<summary>Measured FM exit temperature at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_EXIT_TEMP_1 = "CTC_RPT_MEAS_EXIT_TEMP_1";
		///<summary>Measured FM exit temperature at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_EXIT_TEMP_2 = "CTC_RPT_MEAS_EXIT_TEMP_2";
		///<summary>Measured FM exit thickness at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_EXIT_THICKN_1 = "CTC_RPT_MEAS_EXIT_THICKN_1";
		///<summary>Measured FM exit thickness at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_EXIT_THICKN_2 = "CTC_RPT_MEAS_EXIT_THICKN_2";
		///<summary>Measured FM exit strip speed at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_FMX_SPEED_1 = "CTC_RPT_MEAS_FMX_SPEED_1";
		///<summary>Measured FM exit strip speed at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_FMX_SPEED_2 = "CTC_RPT_MEAS_FMX_SPEED_2";
		///<summary>Measured control zone entry temperature at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_ROT_TEMP_1 = "CTC_RPT_MEAS_ROT_TEMP_1";
		///<summary>Measured control zone entry temperature at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_ROT_TEMP_2 = "CTC_RPT_MEAS_ROT_TEMP_2";
		///<summary>Measured spray efficiency at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_SPRAY_EFF_1 = "CTC_RPT_MEAS_SPRAY_EFF_1";
		///<summary>Measured spray efficiency at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_MEAS_SPRAY_EFF_2 = "CTC_RPT_MEAS_SPRAY_EFF_2";
		///<summary>Spray units on at model learn THD/RUN, MAIN/VERN, TOP/BTM</summary>
		static constexpr auto CTC_RPT_ON_SPRAY_UNITS_1_1 = "CTC_RPT_ON_SPRAY_UNITS_1.1";
		///<summary>Spray units on at model learn THD/RUN, MAIN/VERN, TOP/BTM</summary>
		static constexpr auto CTC_RPT_ON_SPRAY_UNITS_1_2 = "CTC_RPT_ON_SPRAY_UNITS_1.2";
		///<summary>Spray units on at model learn THD/RUN, MAIN/VERN, TOP/BTM</summary>
		static constexpr auto CTC_RPT_ON_SPRAY_UNITS_1_3 = "CTC_RPT_ON_SPRAY_UNITS_1.3";
		///<summary>Spray units on at model learn THD/RUN, MAIN/VERN, TOP/BTM</summary>
		static constexpr auto CTC_RPT_ON_SPRAY_UNITS_1_4 = "CTC_RPT_ON_SPRAY_UNITS_1.4";
		///<summary>Spray units on at model learn THD/RUN, MAIN/VERN, TOP/BTM</summary>
		static constexpr auto CTC_RPT_ON_SPRAY_UNITS_2_1 = "CTC_RPT_ON_SPRAY_UNITS_2.1";
		///<summary>Spray units on at model learn THD/RUN, MAIN/VERN, TOP/BTM</summary>
		static constexpr auto CTC_RPT_ON_SPRAY_UNITS_2_2 = "CTC_RPT_ON_SPRAY_UNITS_2.2";
		///<summary>Spray units on at model learn THD/RUN, MAIN/VERN, TOP/BTM</summary>
		static constexpr auto CTC_RPT_ON_SPRAY_UNITS_2_3 = "CTC_RPT_ON_SPRAY_UNITS_2.3";
		///<summary>Spray units on at model learn THD/RUN, MAIN/VERN, TOP/BTM</summary>
		static constexpr auto CTC_RPT_ON_SPRAY_UNITS_2_4 = "CTC_RPT_ON_SPRAY_UNITS_2.4";
		///<summary>Looping detected on ROT</summary>
		static constexpr auto CTC_RPT_ROT_LOOPING_DETECT_1 = "CTC_RPT_ROT_LOOPING_DETECT_1";
		///<summary>Looping detected on ROT</summary>
		static constexpr auto CTC_RPT_ROT_LOOPING_DETECT_2 = "CTC_RPT_ROT_LOOPING_DETECT_2";
		///<summary>Cumulative length at ROT pyrometer</summary>
		static constexpr auto CTC_RPT_ROT_PYR_CUM_LENGTH = "CTC_RPT_ROT_PYR_CUM_LENGTH";
		///<summary>Repredicted control zone speed at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_RPRE_AVG_SPEED_1 = "CTC_RPT_RPRE_AVG_SPEED_1";
		///<summary>Repredicted control zone speed at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_RPRE_AVG_SPEED_2 = "CTC_RPT_RPRE_AVG_SPEED_2";
		///<summary>Repredicted coiler entry temp at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_RPRE_CLE_TEMP_1 = "CTC_RPT_RPRE_CLE_TEMP_1";
		///<summary>Repredicted coiler entry temp at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_RPRE_CLE_TEMP_2 = "CTC_RPT_RPRE_CLE_TEMP_2";
		///<summary>Repredicted control zone entry temp at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_RPRE_CZE_TEMP_1 = "CTC_RPT_RPRE_CZE_TEMP_1";
		///<summary>Repredicted control zone entry temp at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_RPRE_CZE_TEMP_2 = "CTC_RPT_RPRE_CZE_TEMP_2";
		///<summary>Repredicted control zone exit temp at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_RPRE_CZX_TEMP_1 = "CTC_RPT_RPRE_CZX_TEMP_1";
		///<summary>Repredicted control zone exit temp at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_RPRE_CZX_TEMP_2 = "CTC_RPT_RPRE_CZX_TEMP_2";
		///<summary>Repredicted temp error pred-meas at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_RPRE_TEMP_ERR_1 = "CTC_RPT_RPRE_TEMP_ERR_1";
		///<summary>Repredicted temp error pred-meas at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_RPRE_TEMP_ERR_2 = "CTC_RPT_RPRE_TEMP_ERR_2";
		///<summary>Speed error flag at learning</summary>
		static constexpr auto CTC_RPT_SPEED_ERROR_FLG_1 = "CTC_RPT_SPEED_ERROR_FLG_1";
		///<summary>Speed error flag at learning</summary>
		static constexpr auto CTC_RPT_SPEED_ERROR_FLG_2 = "CTC_RPT_SPEED_ERROR_FLG_2";
		///<summary>Speed up interference flag at learing</summary>
		static constexpr auto CTC_RPT_SPEED_UP_INTERF_FLG_1 = "CTC_RPT_SPEED_UP_INTERF_FLG_1";
		///<summary>Speed up interference flag at learing</summary>
		static constexpr auto CTC_RPT_SPEED_UP_INTERF_FLG_2 = "CTC_RPT_SPEED_UP_INTERF_FLG_2";
		///<summary>Spray units error meas-pred at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_SPRAYS_ERR_1 = "CTC_RPT_SPRAYS_ERR_1";
		///<summary>Spray units error meas-pred at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_SPRAYS_ERR_2 = "CTC_RPT_SPRAYS_ERR_2";
		///<summary>Spray units on at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_SPRAYS_ON_1 = "CTC_RPT_SPRAYS_ON_1";
		///<summary>Spray units on at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_SPRAYS_ON_2 = "CTC_RPT_SPRAYS_ON_2";
		///<summary>Total number of sprays at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_SPRAYS_TOTAL_1_1 = "CTC_RPT_SPRAYS_TOTAL_1.1";
		///<summary>Total number of sprays at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_SPRAYS_TOTAL_1_2 = "CTC_RPT_SPRAYS_TOTAL_1.2";
		///<summary>Total number of sprays at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_SPRAYS_TOTAL_1_3 = "CTC_RPT_SPRAYS_TOTAL_1.3";
		///<summary>Total number of sprays at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_SPRAYS_TOTAL_1_4 = "CTC_RPT_SPRAYS_TOTAL_1.4";
		///<summary>Total number of sprays at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_SPRAYS_TOTAL_2_1 = "CTC_RPT_SPRAYS_TOTAL_2.1";
		///<summary>Total number of sprays at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_SPRAYS_TOTAL_2_2 = "CTC_RPT_SPRAYS_TOTAL_2.2";
		///<summary>Total number of sprays at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_SPRAYS_TOTAL_2_3 = "CTC_RPT_SPRAYS_TOTAL_2.3";
		///<summary>Total number of sprays at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_SPRAYS_TOTAL_2_4 = "CTC_RPT_SPRAYS_TOTAL_2.4";
		///<summary>Cumulative length of strip tail</summary>
		static constexpr auto CTC_RPT_STR_TAIL_CUM_LENGTH = "CTC_RPT_STR_TAIL_CUM_LENGTH";
		///<summary>Temp offset error at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_TEMP_OFFS_ERR_1 = "CTC_RPT_TEMP_OFFS_ERR_1";
		///<summary>Temp offset error at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_TEMP_OFFS_ERR_2 = "CTC_RPT_TEMP_OFFS_ERR_2";
		///<summary>Vernier feedback permissive at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_VERN_FB_PERM_1 = "CTC_RPT_VERN_FB_PERM_1";
		///<summary>Vernier feedback permissive at model learn THD/RUN</summary>
		static constexpr auto CTC_RPT_VERN_FB_PERM_2 = "CTC_RPT_VERN_FB_PERM_2";
		///<summary>3 semicolon separated 1char(0/1) groups</summary>
		static constexpr auto CTC_SU_AIR_SPRAYS = "CTC_SU_AIR_SPRAYS";
		///<summary>Alarm bits w setup error reasons</summary>
		static constexpr auto CTC_SU_ALARM_WORD = "CTC_SU_ALARM_WORD";
		///<summary>Model calculation status</summary>
		static constexpr auto CTC_SU_CALC_STATUS = "CTC_SU_CALC_STATUS";
		///<summary>Last calculation time</summary>
		static constexpr auto CTC_SU_CALC_TIME = "CTC_SU_CALC_TIME";
		///<summary>Coiling temperature target</summary>
		static constexpr auto CTC_SU_COILING_TEMP_AIM = "CTC_SU_COILING_TEMP_AIM";
		///<summary>Coiling temperature max</summary>
		static constexpr auto CTC_SU_COILING_TEMP_MAX = "CTC_SU_COILING_TEMP_MAX";
		///<summary>Coiling temperature min</summary>
		static constexpr auto CTC_SU_COILING_TEMP_MIN = "CTC_SU_COILING_TEMP_MIN";
		///<summary>Model error text</summary>
		static constexpr auto CTC_SU_ERROR_TEXT = "CTC_SU_ERROR_TEXT";
		///<summary>Event bits w calculation events</summary>
		static constexpr auto CTC_SU_EVENT_WORD = "CTC_SU_EVENT_WORD";
		///<summary>Material grade</summary>
		static constexpr auto CTC_SU_GRADE = "CTC_SU_GRADE";
		///<summary>16 semicolon separated 4char(0/1) groups</summary>
		static constexpr auto CTC_SU_MAIN_BTM_SPRAYS = "CTC_SU_MAIN_BTM_SPRAYS";
		///<summary>16 semicolon separated 4char(0/1) groups</summary>
		static constexpr auto CTC_SU_MAIN_BTM_SPRAYS_H_HEAD = "CTC_SU_MAIN_BTM_SPRAYS_H_HEAD";
		///<summary>16 semicolon separated 4char(0/1) groups</summary>
		static constexpr auto CTC_SU_MAIN_TOP_SPRAYS = "CTC_SU_MAIN_TOP_SPRAYS";
		///<summary>16 semicolon separated 4char(0/1) groups</summary>
		static constexpr auto CTC_SU_MAIN_TOP_SPRAYS_H_HEAD = "CTC_SU_MAIN_TOP_SPRAYS_H_HEAD";
		///<summary>21 semicolon separated 1char(0/1) groups</summary>
		static constexpr auto CTC_SU_SIDE_SPRAYS = "CTC_SU_SIDE_SPRAYS";
		///<summary>3 semicolon separated 8char(0/1) groups</summary>
		static constexpr auto CTC_SU_TRIM_BTM_SPRAYS = "CTC_SU_TRIM_BTM_SPRAYS";
		///<summary>3 semicolon separated 8char(0/1) groups</summary>
		static constexpr auto CTC_SU_TRIM_BTM_SPRAYS_H_HEAD = "CTC_SU_TRIM_BTM_SPRAYS_H_HEAD";
		///<summary>3 semicolon separated 8char(0/1) groups</summary>
		static constexpr auto CTC_SU_TRIM_TOP_SPRAYS = "CTC_SU_TRIM_TOP_SPRAYS";
		///<summary>3 semicolon separated 8char(0/1) groups</summary>
		static constexpr auto CTC_SU_TRIM_TOP_SPRAYS_H_HEAD = "CTC_SU_TRIM_TOP_SPRAYS_H_HEAD";
		///<summary>Customer Order Id for Coil label</summary>
		static constexpr auto CUSTOMER_ORDER_ID = "CUSTOMER_ORDER_ID";
		///<summary>0 = cut head and tail, 1 = cut head only, 2 = cut tail only</summary>
		static constexpr auto CUT_MODE = "CUT_MODE";
		///<summary>Alarm bits w setup error reasons</summary>
		static constexpr auto DC_SU_ALARM_WORD = "DC_SU_ALARM_WORD";
		///<summary>Model calculation status</summary>
		static constexpr auto DC_SU_CALC_STATUS = "DC_SU_CALC_STATUS";
		///<summary>Last calculation time</summary>
		static constexpr auto DC_SU_CALC_TIME = "DC_SU_CALC_TIME";
		///<summary>Coiler bending torque reference</summary>
		static constexpr auto DC_SU_COILER_BENDING_TRQREF = "DC_SU_COILER_BENDING_TRQREF";
		///<summary>Tensile strength at coiler</summary>
		static constexpr auto DC_SU_COILER_TENSIL_STREN_PRED = "DC_SU_COILER_TENSIL_STREN_PRED";
		///<summary>Predicted yield stress on ROT</summary>
		static constexpr auto DC_SU_COILER_YIELD_STRESS_PRED = "DC_SU_COILER_YIELD_STRESS_PRED";
		///<summary></summary>
		static constexpr auto DC_SU_COILING_TEMP_AIM = "DC_SU_COILING_TEMP_AIM";
		///<summary>Thickness at coiling temp</summary>
		static constexpr auto DC_SU_COILING_TEMP_THICKN = "DC_SU_COILING_TEMP_THICKN";
		///<summary>Width at coiling temp</summary>
		static constexpr auto DC_SU_COILING_TEMP_WIDTH = "DC_SU_COILING_TEMP_WIDTH";
		///<summary>Cold thickness</summary>
		static constexpr auto DC_SU_COLD_THICKNESS = "DC_SU_COLD_THICKNESS";
		///<summary>Cold width</summary>
		static constexpr auto DC_SU_COLD_WIDTH = "DC_SU_COLD_WIDTH";
		///<summary>Model error text</summary>
		static constexpr auto DC_SU_ERROR_TEXT = "DC_SU_ERROR_TEXT";
		///<summary>Event bits w calculation events</summary>
		static constexpr auto DC_SU_EVENT_WORD = "DC_SU_EVENT_WORD";
		///<summary></summary>
		static constexpr auto DC_SU_FM_EXIT_STRIP_SPEED_THD = "DC_SU_FM_EXIT_STRIP_SPEED_THD";
		///<summary>Steel grade</summary>
		static constexpr auto DC_SU_STEEL_GRADE = "DC_SU_STEEL_GRADE";
		///<summary>Steel grade group (L1 setup)</summary>
		static constexpr auto DC_SU_STEEL_GRADE_GROUP = "DC_SU_STEEL_GRADE_GROUP";
		///<summary>Steel grade index (L1 setup)</summary>
		static constexpr auto DC_SU_STEEL_GRADE_INDEX = "DC_SU_STEEL_GRADE_INDEX";
		///<summary>Steel specific weight</summary>
		static constexpr auto DC_SU_STEEL_SPEC_WEIGHT = "DC_SU_STEEL_SPEC_WEIGHT";
		///<summary>Predicted strip length</summary>
		static constexpr auto DC_SU_STRIP_LENGTH_PRED = "DC_SU_STRIP_LENGTH_PRED";
		///<summary>Tension reference between Mill and Pinch Roll</summary>
		static constexpr auto DC_SU_TENSION_REF_ML_PR = "DC_SU_TENSION_REF_ML-PR";
		///<summary>Tension reference between Pinch Roll and Mandrel</summary>
		static constexpr auto DC_SU_TENSION_REF_PR_DC = "DC_SU_TENSION_REF_PR-DC";
		///<summary>Coiler number</summary>
		static constexpr auto DOWN_COILER_NO = "DOWN_COILER_NO";
		///<summary>Edger stand used in pass</summary>
		static constexpr auto EDGER_ACTIVE = "EDGER_ACTIVE";
		///<summary>Material entry speed average</summary>
		static constexpr auto ENTRY_SPEED_AVG = "ENTRY_SPEED_AVG";
		///<summary>Material entry speed data</summary>
		static constexpr auto ENTRY_SPEED_DAQ = "ENTRY_SPEED_DAQ";
		///<summary>Material entry temperature average</summary>
		static constexpr auto ENTRY_TEMP_AVG = "ENTRY_TEMP_AVG";
		///<summary>Material entry temperature data</summary>
		static constexpr auto ENTRY_TEMP_DAQ = "ENTRY_TEMP_DAQ";
		///<summary>Material entry temperature in tolerance</summary>
		static constexpr auto ENTRY_TEMP_INTOL = "ENTRY_TEMP_INTOL";
		///<summary>Material entry temperature max</summary>
		static constexpr auto ENTRY_TEMP_MAX = "ENTRY_TEMP_MAX";
		///<summary>Material entry temperature min</summary>
		static constexpr auto ENTRY_TEMP_MIN = "ENTRY_TEMP_MIN";
		///<summary>Material entry width average</summary>
		static constexpr auto ENTRY_WIDTH_AVG = "ENTRY_WIDTH_AVG";
		///<summary>Material entry width data</summary>
		static constexpr auto ENTRY_WIDTH_DAQ = "ENTRY_WIDTH_DAQ";
		///<summary>Material entry width max</summary>
		static constexpr auto ENTRY_WIDTH_MAX = "ENTRY_WIDTH_MAX";
		///<summary>Material entry width min</summary>
		static constexpr auto ENTRY_WIDTH_MIN = "ENTRY_WIDTH_MIN";
		///<summary>Estimated charge date and time</summary>
		static constexpr auto ESTIMATED_CHARGE_TIME = "ESTIMATED_CHARGE_TIME";
		///<summary>Material exit length</summary>
		static constexpr auto EXIT_LENGTH = "EXIT_LENGTH";
		///<summary>Material exit speed average</summary>
		static constexpr auto EXIT_SPEED_AVG = "EXIT_SPEED_AVG";
		///<summary>Material exit speed data</summary>
		static constexpr auto EXIT_SPEED_DAQ = "EXIT_SPEED_DAQ";
		///<summary>Material exit temperature average</summary>
		static constexpr auto EXIT_TEMP_AVG = "EXIT_TEMP_AVG";
		///<summary>Material exit temperature data</summary>
		static constexpr auto EXIT_TEMP_DAQ = "EXIT_TEMP_DAQ";
		///<summary>Material exit temperature in tolerance</summary>
		static constexpr auto EXIT_TEMP_INTOL = "EXIT_TEMP_INTOL";
		///<summary>Material exit temperature max</summary>
		static constexpr auto EXIT_TEMP_MAX = "EXIT_TEMP_MAX";
		///<summary>Material exit temperature min</summary>
		static constexpr auto EXIT_TEMP_MIN = "EXIT_TEMP_MIN";
		///<summary>Material exit thickness (calc hot) average</summary>
		static constexpr auto EXIT_THICKNESS_AVG = "EXIT_THICKNESS_AVG";
		///<summary>Material exit thickness (calc hot) data</summary>
		static constexpr auto EXIT_THICKNESS_DAQ = "EXIT_THICKNESS_DAQ";
		///<summary>Material exit thickness (calc hot) max</summary>
		static constexpr auto EXIT_THICKNESS_MAX = "EXIT_THICKNESS_MAX";
		///<summary>Material exit thickness (calc hot) min</summary>
		static constexpr auto EXIT_THICKNESS_MIN = "EXIT_THICKNESS_MIN";
		///<summary>Material exit width average</summary>
		static constexpr auto EXIT_WIDTH_AVG = "EXIT_WIDTH_AVG";
		///<summary>Material exit width data</summary>
		static constexpr auto EXIT_WIDTH_DAQ = "EXIT_WIDTH_DAQ";
		///<summary>Material exit width max</summary>
		static constexpr auto EXIT_WIDTH_MAX = "EXIT_WIDTH_MAX";
		///<summary>Material exit width min</summary>
		static constexpr auto EXIT_WIDTH_MIN = "EXIT_WIDTH_MIN";
		///<summary>0=no extra straps, X=number of extra straps.</summary>
		static constexpr auto EXTRA_STRAPS_NO = "EXTRA_STRAPS_NO";
		///<summary>Active crew when shift charged</summary>
		static constexpr auto FCE_CHARGE_CREW = "FCE_CHARGE_CREW";
		///<summary>Active shift when slab charged</summary>
		static constexpr auto FCE_CHARGE_SHIFT = "FCE_CHARGE_SHIFT";
		///<summary>Slab charging temperature</summary>
		static constexpr auto FCE_CHARGE_TEMP = "FCE_CHARGE_TEMP";
		///<summary>Slab charge date & time</summary>
		static constexpr auto FCE_CHARGE_TIME = "FCE_CHARGE_TIME";
		///<summary>Furnace Aim Charging Temp</summary>
		static constexpr auto FCE_CHG_TEMP_AIM = "FCE_CHG_TEMP_AIM";
		///<summary>Furnace Aim DisCharging Temp</summary>
		static constexpr auto FCE_DCHG_TEMP_AIM = "FCE_DCHG_TEMP_AIM";
		///<summary>Active crew when slab discharged</summary>
		static constexpr auto FCE_DISCHARGE_CREW = "FCE_DISCHARGE_CREW";
		///<summary>Active shift when slab discharged</summary>
		static constexpr auto FCE_DISCHARGE_SHIFT = "FCE_DISCHARGE_SHIFT";
		///<summary>Slab charging temperature</summary>
		static constexpr auto FCE_DISCHARGE_TEMP = "FCE_DISCHARGE_TEMP";
		///<summary>Slab discharge date & time</summary>
		static constexpr auto FCE_DISCHARGE_TIME = "FCE_DISCHARGE_TIME";
		///<summary>Slab furnace number (update by charge and discharge)</summary>
		static constexpr auto FCE_FURNACE_NO = "FCE_FURNACE_NO";
		///<summary>0=Non ferritic rolling, 1 = Ferritic rolling</summary>
		static constexpr auto FERRITIC_ROLLING = "FERRITIC_ROLLING";
		///<summary>FM Descaling Code, 0 = Default, others to be defined</summary>
		static constexpr auto FM_DESCALING_CODE = "FM_DESCALING_CODE";
		///<summary>FM Exit crown C40 (cold) average</summary>
		static constexpr auto FM_EXIT_CROWN_BODYAVG = "FM_EXIT_CROWN_BODYAVG";
		///<summary>FM Exit crown C40 (cold) max</summary>
		static constexpr auto FM_EXIT_CROWN_BODYMAX = "FM_EXIT_CROWN_BODYMAX";
		///<summary>FM Exit crown C40 (cold) min</summary>
		static constexpr auto FM_EXIT_CROWN_BODYMIN = "FM_EXIT_CROWN_BODYMIN";
		///<summary>FM Exit crown C40 (cold) data</summary>
		static constexpr auto FM_EXIT_CROWN_DAQ = "FM_EXIT_CROWN_DAQ";
		///<summary>FM Exit crown C40 (cold) above max tolerance</summary>
		static constexpr auto FM_EXIT_CROWN_GTMAX = "FM_EXIT_CROWN_GTMAX";
		///<summary>FM Exit crown C40 (cold) in tolerance</summary>
		static constexpr auto FM_EXIT_CROWN_INTOL = "FM_EXIT_CROWN_INTOL";
		///<summary>FM Exit crown C40 (cold) below min tolerance</summary>
		static constexpr auto FM_EXIT_CROWN_LTMIN = "FM_EXIT_CROWN_LTMIN";
		///<summary>FM Exit asymmetric flatness (cold) average</summary>
		static constexpr auto FM_EXIT_FLATN_ASYM_AVG = "FM_EXIT_FLATN_ASYM_AVG";
		///<summary>FM Exit asymmetric flatness (cold) data</summary>
		static constexpr auto FM_EXIT_FLATN_ASYM_DAQ = "FM_EXIT_FLATN_ASYM_DAQ";
		///<summary>FM Exit asymmetric flatness (cold) max</summary>
		static constexpr auto FM_EXIT_FLATN_ASYM_MAX = "FM_EXIT_FLATN_ASYM_MAX";
		///<summary>FM Exit asymmetric flatness (cold) min</summary>
		static constexpr auto FM_EXIT_FLATN_ASYM_MIN = "FM_EXIT_FLATN_ASYM_MIN";
		///<summary>FM Exit symmetric flatness (cold) average</summary>
		static constexpr auto FM_EXIT_FLATN_SYM_BODYAVG = "FM_EXIT_FLATN_SYM_BODYAVG";
		///<summary>FM Exit symmetric flatness (cold) max</summary>
		static constexpr auto FM_EXIT_FLATN_SYM_BODYMAX = "FM_EXIT_FLATN_SYM_BODYMAX";
		///<summary>FM Exit symmetric flatness (cold) min</summary>
		static constexpr auto FM_EXIT_FLATN_SYM_BODYMIN = "FM_EXIT_FLATN_SYM_BODYMIN";
		///<summary>FM Exit symmetric flatness (cold) data</summary>
		static constexpr auto FM_EXIT_FLATN_SYM_DAQ = "FM_EXIT_FLATN_SYM_DAQ";
		///<summary>FM Exit symmetric flatness (cold) above max</summary>
		static constexpr auto FM_EXIT_FLATN_SYM_GTMAX = "FM_EXIT_FLATN_SYM_GTMAX";
		///<summary>FM Exit symmetric flatness (cold) in tolerance</summary>
		static constexpr auto FM_EXIT_FLATN_SYM_INTOL = "FM_EXIT_FLATN_SYM_INTOL";
		///<summary>FM Exit symmetric flatness (cold) below min</summary>
		static constexpr auto FM_EXIT_FLATN_SYM_LTMIN = "FM_EXIT_FLATN_SYM_LTMIN";
		///<summary>FM Exit temperature average</summary>
		static constexpr auto FM_EXIT_TEMP_AVG = "FM_EXIT_TEMP_AVG";
		///<summary>FM Exit temperature data</summary>
		static constexpr auto FM_EXIT_TEMP_DAQ = "FM_EXIT_TEMP_DAQ";
		///<summary>FM Exit temperature above max tolerance</summary>
		static constexpr auto FM_EXIT_TEMP_GTMAX = "FM_EXIT_TEMP_GTMAX";
		///<summary>FM Exit temperature in tolerance</summary>
		static constexpr auto FM_EXIT_TEMP_INTOL = "FM_EXIT_TEMP_INTOL";
		///<summary>FM Exit temperature below min tolerance</summary>
		static constexpr auto FM_EXIT_TEMP_LTMIN = "FM_EXIT_TEMP_LTMIN";
		///<summary>FM Exit temperature max</summary>
		static constexpr auto FM_EXIT_TEMP_MAX = "FM_EXIT_TEMP_MAX";
		///<summary>FM Exit temperature min</summary>
		static constexpr auto FM_EXIT_TEMP_MIN = "FM_EXIT_TEMP_MIN";
		///<summary>FM Exit temperature, actual reference</summary>
		static constexpr auto FM_EXIT_TEMP_REF_ACT = "FM_EXIT_TEMP_REF_ACT";
		///<summary>FM Exit thickness, actual reference</summary>
		static constexpr auto FM_EXIT_THICKN_REF_ACT = "FM_EXIT_THICKN_REF_ACT";
		///<summary>FM Exit thickness average</summary>
		static constexpr auto FM_EXIT_THICKNESS_BODYAVG = "FM_EXIT_THICKNESS_BODYAVG";
		///<summary>FM Exit thickness max</summary>
		static constexpr auto FM_EXIT_THICKNESS_BODYMAX = "FM_EXIT_THICKNESS_BODYMAX";
		///<summary>FM Exit thickness min</summary>
		static constexpr auto FM_EXIT_THICKNESS_BODYMIN = "FM_EXIT_THICKNESS_BODYMIN";
		///<summary>FM Exit thickness data</summary>
		static constexpr auto FM_EXIT_THICKNESS_DAQ = "FM_EXIT_THICKNESS_DAQ";
		///<summary>FM Exit thickness above max tolerance</summary>
		static constexpr auto FM_EXIT_THICKNESS_GTMAX = "FM_EXIT_THICKNESS_GTMAX";
		///<summary>FM Exit thickness in tolerance</summary>
		static constexpr auto FM_EXIT_THICKNESS_INTOL = "FM_EXIT_THICKNESS_INTOL";
		///<summary>FM Exit thickness below min tolerance</summary>
		static constexpr auto FM_EXIT_THICKNESS_LTMIN = "FM_EXIT_THICKNESS_LTMIN";
		///<summary>FM Exit wedge W40 (cold) average</summary>
		static constexpr auto FM_EXIT_WEDGE_BODYAVG = "FM_EXIT_WEDGE_BODYAVG";
		///<summary>FM Exit wedge W40 (cold) max</summary>
		static constexpr auto FM_EXIT_WEDGE_BODYMAX = "FM_EXIT_WEDGE_BODYMAX";
		///<summary>FM Exit wedge W40 (cold) min</summary>
		static constexpr auto FM_EXIT_WEDGE_BODYMIN = "FM_EXIT_WEDGE_BODYMIN";
		///<summary>FM Exit wedge W40 (cold) data</summary>
		static constexpr auto FM_EXIT_WEDGE_DAQ = "FM_EXIT_WEDGE_DAQ";
		///<summary>FM Exit wedge W40 (cold) above max tolerance</summary>
		static constexpr auto FM_EXIT_WEDGE_GTMAX = "FM_EXIT_WEDGE_GTMAX";
		///<summary>FM Exit wedge W40 (cold) in tolerance</summary>
		static constexpr auto FM_EXIT_WEDGE_INTOL = "FM_EXIT_WEDGE_INTOL";
		///<summary>FM Exit wedge W40 (cold) below min tolerance</summary>
		static constexpr auto FM_EXIT_WEDGE_LTMIN = "FM_EXIT_WEDGE_LTMIN";
		///<summary>FM Exit width (cold) average</summary>
		static constexpr auto FM_EXIT_WIDTH_BODYAVG = "FM_EXIT_WIDTH_BODYAVG";
		///<summary>FM Exit width (cold) max</summary>
		static constexpr auto FM_EXIT_WIDTH_BODYMAX = "FM_EXIT_WIDTH_BODYMAX";
		///<summary>FM Exit width (cold) min</summary>
		static constexpr auto FM_EXIT_WIDTH_BODYMIN = "FM_EXIT_WIDTH_BODYMIN";
		///<summary>FM Exit width (cold) data</summary>
		static constexpr auto FM_EXIT_WIDTH_DAQ = "FM_EXIT_WIDTH_DAQ";
		///<summary>FM Exit width (cold) above max tolerance</summary>
		static constexpr auto FM_EXIT_WIDTH_GTMAX = "FM_EXIT_WIDTH_GTMAX";
		///<summary>FM Exit width (cold) in tolerance</summary>
		static constexpr auto FM_EXIT_WIDTH_INTOL = "FM_EXIT_WIDTH_INTOL";
		///<summary>FM Exit width (cold) below min tolerance</summary>
		static constexpr auto FM_EXIT_WIDTH_LTMIN = "FM_EXIT_WIDTH_LTMIN";
		///<summary>FM Interstand Cooling Practice Code, 0 = Default, others to be defined</summary>
		static constexpr auto FM_ISTCOOL_CODE = "FM_ISTCOOL_CODE";
		///<summary>FM Exit thickness error</summary>
		static constexpr auto FM_RPT_EXIT_THICKNESS_ERR = "FM_RPT_EXIT_THICKNESS_ERR";
		///<summary>Head measured rhometer asymmetrical flatness</summary>
		static constexpr auto FM_RPT_H_MEAS_ASYM_FLATNESS = "FM_RPT_H_MEAS_ASYM_FLATNESS";
		///<summary>Head measured camber</summary>
		static constexpr auto FM_RPT_H_MEAS_CAMBER = "FM_RPT_H_MEAS_CAMBER";
		///<summary>Head measured crown</summary>
		static constexpr auto FM_RPT_H_MEAS_CROWN = "FM_RPT_H_MEAS_CROWN";
		///<summary>Head measured rhometer symmetrical flatness</summary>
		static constexpr auto FM_RPT_H_MEAS_SYM_FLATNESS = "FM_RPT_H_MEAS_SYM_FLATNESS";
		///<summary>F7 xray gauge deviation, head scan</summary>
		static constexpr auto FM_RPT_H_SCAN_XRAY_GAUGE_DEV = "FM_RPT_H_SCAN_XRAY_GAUGE_DEV";
		///<summary>Learning repredicted to measured power ratio</summary>
		static constexpr auto FM_RPT_LEARN_POWER_RATIO_1 = "FM_RPT_LEARN_POWER_RATIO_1";
		///<summary>Learning repredicted to measured power ratio</summary>
		static constexpr auto FM_RPT_LEARN_POWER_RATIO_2 = "FM_RPT_LEARN_POWER_RATIO_2";
		///<summary>Learning repredicted to measured power ratio</summary>
		static constexpr auto FM_RPT_LEARN_POWER_RATIO_3 = "FM_RPT_LEARN_POWER_RATIO_3";
		///<summary>Learning repredicted to measured power ratio</summary>
		static constexpr auto FM_RPT_LEARN_POWER_RATIO_4 = "FM_RPT_LEARN_POWER_RATIO_4";
		///<summary>Learning repredicted to measured power ratio</summary>
		static constexpr auto FM_RPT_LEARN_POWER_RATIO_5 = "FM_RPT_LEARN_POWER_RATIO_5";
		///<summary>Learning repredicted to measured power ratio</summary>
		static constexpr auto FM_RPT_LEARN_POWER_RATIO_6 = "FM_RPT_LEARN_POWER_RATIO_6";
		///<summary>Learning repredicted to measured power ratio</summary>
		static constexpr auto FM_RPT_LEARN_POWER_RATIO_7 = "FM_RPT_LEARN_POWER_RATIO_7";
		///<summary>Learning repredicted to measured yield stress ratio</summary>
		static constexpr auto FM_RPT_LEARN_YIELD_STR_RATIO_1 = "FM_RPT_LEARN_YIELD_STR_RATIO_1";
		///<summary>Learning repredicted to measured yield stress ratio</summary>
		static constexpr auto FM_RPT_LEARN_YIELD_STR_RATIO_2 = "FM_RPT_LEARN_YIELD_STR_RATIO_2";
		///<summary>Learning repredicted to measured yield stress ratio</summary>
		static constexpr auto FM_RPT_LEARN_YIELD_STR_RATIO_3 = "FM_RPT_LEARN_YIELD_STR_RATIO_3";
		///<summary>Learning repredicted to measured yield stress ratio</summary>
		static constexpr auto FM_RPT_LEARN_YIELD_STR_RATIO_4 = "FM_RPT_LEARN_YIELD_STR_RATIO_4";
		///<summary>Learning repredicted to measured yield stress ratio</summary>
		static constexpr auto FM_RPT_LEARN_YIELD_STR_RATIO_5 = "FM_RPT_LEARN_YIELD_STR_RATIO_5";
		///<summary>Learning repredicted to measured yield stress ratio</summary>
		static constexpr auto FM_RPT_LEARN_YIELD_STR_RATIO_6 = "FM_RPT_LEARN_YIELD_STR_RATIO_6";
		///<summary>Learning repredicted to measured yield stress ratio</summary>
		static constexpr auto FM_RPT_LEARN_YIELD_STR_RATIO_7 = "FM_RPT_LEARN_YIELD_STR_RATIO_7";
		///<summary>Cascaded looper speed correction and operator offset</summary>
		static constexpr auto FM_RPT_P_CASC_LOOPER_SP_OFFS_1 = "FM_RPT_P_CASC_LOOPER_SP_OFFS_1";
		///<summary>Cascaded looper speed correction and operator offset</summary>
		static constexpr auto FM_RPT_P_CASC_LOOPER_SP_OFFS_2 = "FM_RPT_P_CASC_LOOPER_SP_OFFS_2";
		///<summary>Cascaded looper speed correction and operator offset</summary>
		static constexpr auto FM_RPT_P_CASC_LOOPER_SP_OFFS_3 = "FM_RPT_P_CASC_LOOPER_SP_OFFS_3";
		///<summary>Cascaded looper speed correction and operator offset</summary>
		static constexpr auto FM_RPT_P_CASC_LOOPER_SP_OFFS_4 = "FM_RPT_P_CASC_LOOPER_SP_OFFS_4";
		///<summary>Cascaded looper speed correction and operator offset</summary>
		static constexpr auto FM_RPT_P_CASC_LOOPER_SP_OFFS_5 = "FM_RPT_P_CASC_LOOPER_SP_OFFS_5";
		///<summary>Cascaded looper speed correction and operator offset</summary>
		static constexpr auto FM_RPT_P_CASC_LOOPER_SP_OFFS_6 = "FM_RPT_P_CASC_LOOPER_SP_OFFS_6";
		///<summary>Cascaded looper speed correction and operator offset</summary>
		static constexpr auto FM_RPT_P_CASC_LOOPER_SP_OFFS_7 = "FM_RPT_P_CASC_LOOPER_SP_OFFS_7";
		///<summary>Ksi stand factors used for this bar</summary>
		static constexpr auto FM_RPT_P_KSI_STAND_FCTR_1 = "FM_RPT_P_KSI_STAND_FCTR_1";
		///<summary>Ksi stand factors used for this bar</summary>
		static constexpr auto FM_RPT_P_KSI_STAND_FCTR_2 = "FM_RPT_P_KSI_STAND_FCTR_2";
		///<summary>Ksi stand factors used for this bar</summary>
		static constexpr auto FM_RPT_P_KSI_STAND_FCTR_3 = "FM_RPT_P_KSI_STAND_FCTR_3";
		///<summary>Ksi stand factors used for this bar</summary>
		static constexpr auto FM_RPT_P_KSI_STAND_FCTR_4 = "FM_RPT_P_KSI_STAND_FCTR_4";
		///<summary>Ksi stand factors used for this bar</summary>
		static constexpr auto FM_RPT_P_KSI_STAND_FCTR_5 = "FM_RPT_P_KSI_STAND_FCTR_5";
		///<summary>Ksi stand factors used for this bar</summary>
		static constexpr auto FM_RPT_P_KSI_STAND_FCTR_6 = "FM_RPT_P_KSI_STAND_FCTR_6";
		///<summary>Ksi stand factors used for this bar</summary>
		static constexpr auto FM_RPT_P_KSI_STAND_FCTR_7 = "FM_RPT_P_KSI_STAND_FCTR_7";
		///<summary>Ksi steel grade factors used for this bar</summary>
		static constexpr auto FM_RPT_P_KSI_STEEL_GRDE_FCTR_1 = "FM_RPT_P_KSI_STEEL_GRDE_FCTR_1";
		///<summary>Ksi steel grade factors used for this bar</summary>
		static constexpr auto FM_RPT_P_KSI_STEEL_GRDE_FCTR_2 = "FM_RPT_P_KSI_STEEL_GRDE_FCTR_2";
		///<summary>Ksi steel grade factors used for this bar</summary>
		static constexpr auto FM_RPT_P_KSI_STEEL_GRDE_FCTR_3 = "FM_RPT_P_KSI_STEEL_GRDE_FCTR_3";
		///<summary>Ksi steel grade factors used for this bar</summary>
		static constexpr auto FM_RPT_P_KSI_STEEL_GRDE_FCTR_4 = "FM_RPT_P_KSI_STEEL_GRDE_FCTR_4";
		///<summary>Ksi steel grade factors used for this bar</summary>
		static constexpr auto FM_RPT_P_KSI_STEEL_GRDE_FCTR_5 = "FM_RPT_P_KSI_STEEL_GRDE_FCTR_5";
		///<summary>Ksi steel grade factors used for this bar</summary>
		static constexpr auto FM_RPT_P_KSI_STEEL_GRDE_FCTR_6 = "FM_RPT_P_KSI_STEEL_GRDE_FCTR_6";
		///<summary>Ksi steel grade factors used for this bar</summary>
		static constexpr auto FM_RPT_P_KSI_STEEL_GRDE_FCTR_7 = "FM_RPT_P_KSI_STEEL_GRDE_FCTR_7";
		///<summary>Progressive learned stand yield stress</summary>
		static constexpr auto FM_RPT_P_LRN_STAND_YIELD_STR_1 = "FM_RPT_P_LRN_STAND_YIELD_STR_1";
		///<summary>Progressive learned stand yield stress</summary>
		static constexpr auto FM_RPT_P_LRN_STAND_YIELD_STR_2 = "FM_RPT_P_LRN_STAND_YIELD_STR_2";
		///<summary>Progressive learned stand yield stress</summary>
		static constexpr auto FM_RPT_P_LRN_STAND_YIELD_STR_3 = "FM_RPT_P_LRN_STAND_YIELD_STR_3";
		///<summary>Progressive learned stand yield stress</summary>
		static constexpr auto FM_RPT_P_LRN_STAND_YIELD_STR_4 = "FM_RPT_P_LRN_STAND_YIELD_STR_4";
		///<summary>Progressive learned stand yield stress</summary>
		static constexpr auto FM_RPT_P_LRN_STAND_YIELD_STR_5 = "FM_RPT_P_LRN_STAND_YIELD_STR_5";
		///<summary>Progressive learned stand yield stress</summary>
		static constexpr auto FM_RPT_P_LRN_STAND_YIELD_STR_6 = "FM_RPT_P_LRN_STAND_YIELD_STR_6";
		///<summary>Progressive learned stand yield stress</summary>
		static constexpr auto FM_RPT_P_LRN_STAND_YIELD_STR_7 = "FM_RPT_P_LRN_STAND_YIELD_STR_7";
		///<summary>Progressive measure camber</summary>
		static constexpr auto FM_RPT_P_MEAS_CAMBER = "FM_RPT_P_MEAS_CAMBER";
		///<summary>Progressive measure crown</summary>
		static constexpr auto FM_RPT_P_MEAS_CROWN = "FM_RPT_P_MEAS_CROWN";
		///<summary>Progressive measured descaler spray pattern no good</summary>
		static constexpr auto FM_RPT_P_MEAS_DSC_SPRAY_P_NGD = "FM_RPT_P_MEAS_DSC_SPRAY_P_NGD";
		///<summary>Progressive measured exit temp no good</summary>
		static constexpr auto FM_RPT_P_MEAS_EXIT_TEMP_NGD = "FM_RPT_P_MEAS_EXIT_TEMP_NGD";
		///<summary>Progressive measured exit thickness no good</summary>
		static constexpr auto FM_RPT_P_MEAS_EXIT_THICKN_NGD = "FM_RPT_P_MEAS_EXIT_THICKN_NGD";
		///<summary>Progressive measured exit width no good</summary>
		static constexpr auto FM_RPT_P_MEAS_EXIT_WIDTH_NGD = "FM_RPT_P_MEAS_EXIT_WIDTH_NGD";
		///<summary>Progressive measured interstand spray pattern no good</summary>
		static constexpr auto FM_RPT_P_MEAS_IST_SPRAY_P_NGD = "FM_RPT_P_MEAS_IST_SPRAY_P_NGD";
		///<summary>Progressive measured looper tensions no good</summary>
		static constexpr auto FM_RPT_P_MEAS_LOOPER_TENS_NGD = "FM_RPT_P_MEAS_LOOPER_TENS_NGD";
		///<summary>Progressive measured stand forces no good</summary>
		static constexpr auto FM_RPT_P_MEAS_STAND_FORCES_NGD = "FM_RPT_P_MEAS_STAND_FORCES_NGD";
		///<summary>Progressive measured stand gaps no good</summary>
		static constexpr auto FM_RPT_P_MEAS_STAND_GAPS_NGD = "FM_RPT_P_MEAS_STAND_GAPS_NGD";
		///<summary>Progressive measured stand speeds no good</summary>
		static constexpr auto FM_RPT_P_MEAS_STAND_SPEEDS_NGD = "FM_RPT_P_MEAS_STAND_SPEEDS_NGD";
		///<summary>Progressive measured stand volts no good</summary>
		static constexpr auto FM_RPT_P_MEAS_STAND_VOLTS_NGD = "FM_RPT_P_MEAS_STAND_VOLTS_NGD";
		///<summary>Setup and learning oil use mismatch</summary>
		static constexpr auto FM_RPT_P_OIL_USE_NGD = "FM_RPT_P_OIL_USE_NGD";
		///<summary>F7 xray gauge deviation, progressive scan</summary>
		static constexpr auto FM_RPT_P_SCAN_XRAY_GAUGE_DEV = "FM_RPT_P_SCAN_XRAY_GAUGE_DEV";
		///<summary>Steel grade index at learning disagrees with FMDCLC</summary>
		static constexpr auto FM_RPT_P_STEEL_GRADE_INX_NGD = "FM_RPT_P_STEEL_GRADE_INX_NGD";
		///<summary>Thickness range index at learning disagrees with FMDCLC</summary>
		static constexpr auto FM_RPT_P_THICKN_RANGE_IDX_NGD = "FM_RPT_P_THICKN_RANGE_IDX_NGD";
		///<summary>Snap shot measured camber</summary>
		static constexpr auto FM_RPT_S_MEAS_CAMBER = "FM_RPT_S_MEAS_CAMBER";
		///<summary>snap shot measured crown</summary>
		static constexpr auto FM_RPT_S_MEAS_CROWN = "FM_RPT_S_MEAS_CROWN";
		///<summary>Snap shot measured exit thickness no good</summary>
		static constexpr auto FM_RPT_S_MEAS_EXIT_THICKN_NGD = "FM_RPT_S_MEAS_EXIT_THICKN_NGD";
		///<summary>Snap shot measured exit width no good</summary>
		static constexpr auto FM_RPT_S_MEAS_EXIT_WIDTH_NGD = "FM_RPT_S_MEAS_EXIT_WIDTH_NGD";
		///<summary>Snap shot measured stand amps no good</summary>
		static constexpr auto FM_RPT_S_MEAS_STAND_AMPS_NGD = "FM_RPT_S_MEAS_STAND_AMPS_NGD";
		///<summary>Snap shot measured stand forces no good</summary>
		static constexpr auto FM_RPT_S_MEAS_STAND_FORCES_NGD = "FM_RPT_S_MEAS_STAND_FORCES_NGD";
		///<summary>Snap shot measured stand gaps no good</summary>
		static constexpr auto FM_RPT_S_MEAS_STAND_GAPS_NGD = "FM_RPT_S_MEAS_STAND_GAPS_NGD";
		///<summary>Snap shot measured stand speeds no good</summary>
		static constexpr auto FM_RPT_S_MEAS_STAND_SPEEDS_NGD = "FM_RPT_S_MEAS_STAND_SPEEDS_NGD";
		///<summary>F7 xray gauge deviation, snap shot scan</summary>
		static constexpr auto FM_RPT_S_SCAN_XRAY_GAUGE_DEV = "FM_RPT_S_SCAN_XRAY_GAUGE_DEV";
		///<summary>Strip crown error measured – predicted</summary>
		static constexpr auto FM_RPT_STRIP_CROWN_ERR_M_P = "FM_RPT_STRIP_CROWN_ERR_M-P";
		///<summary>Stand thickness difference</summary>
		static constexpr auto FM_RPT_THICKNESS_DIFF_1 = "FM_RPT_THICKNESS_DIFF_1";
		///<summary>Stand thickness difference</summary>
		static constexpr auto FM_RPT_THICKNESS_DIFF_2 = "FM_RPT_THICKNESS_DIFF_2";
		///<summary>Stand thickness difference</summary>
		static constexpr auto FM_RPT_THICKNESS_DIFF_3 = "FM_RPT_THICKNESS_DIFF_3";
		///<summary>Stand thickness difference</summary>
		static constexpr auto FM_RPT_THICKNESS_DIFF_4 = "FM_RPT_THICKNESS_DIFF_4";
		///<summary>Stand thickness difference</summary>
		static constexpr auto FM_RPT_THICKNESS_DIFF_5 = "FM_RPT_THICKNESS_DIFF_5";
		///<summary>Stand thickness difference</summary>
		static constexpr auto FM_RPT_THICKNESS_DIFF_6 = "FM_RPT_THICKNESS_DIFF_6";
		///<summary>Stand thickness difference</summary>
		static constexpr auto FM_RPT_THICKNESS_DIFF_7 = "FM_RPT_THICKNESS_DIFF_7";
		///<summary>Update FM crown and temperature model, long term</summary>
		static constexpr auto FM_RPT_UPD_FM_CROWN_TEMP_MDL_L = "FM_RPT_UPD_FM_CROWN_TEMP_MDL_L";
		///<summary>Update FM force and temperature model, long term</summary>
		static constexpr auto FM_RPT_UPD_FM_FORCE_TEMP_MDL_L = "FM_RPT_UPD_FM_FORCE_TEMP_MDL_L";
		///<summary>Update FM force and temperature model, short term</summary>
		static constexpr auto FM_RPT_UPD_FM_FORCE_TEMP_MDL_S = "FM_RPT_UPD_FM_FORCE_TEMP_MDL_S";
		///<summary>Update FM gap offset</summary>
		static constexpr auto FM_RPT_UPD_FM_GAP_OFFS = "FM_RPT_UPD_FM_GAP_OFFS";
		///<summary>Update FM temperature offset</summary>
		static constexpr auto FM_RPT_UPD_FM_TEMP_OFFS = "FM_RPT_UPD_FM_TEMP_OFFS";
		///<summary>Update FM thickness offset</summary>
		static constexpr auto FM_RPT_UPD_FM_THICKN_OFFS = "FM_RPT_UPD_FM_THICKN_OFFS";
		///<summary>Work roll effective crown at FM crown learning</summary>
		static constexpr auto FM_RPT_WR_EFF_CROWN_AT_LEARN_1 = "FM_RPT_WR_EFF_CROWN_AT_LEARN_1";
		///<summary>Work roll effective crown at FM crown learning</summary>
		static constexpr auto FM_RPT_WR_EFF_CROWN_AT_LEARN_2 = "FM_RPT_WR_EFF_CROWN_AT_LEARN_2";
		///<summary>Work roll effective crown at FM crown learning</summary>
		static constexpr auto FM_RPT_WR_EFF_CROWN_AT_LEARN_3 = "FM_RPT_WR_EFF_CROWN_AT_LEARN_3";
		///<summary>Work roll effective crown at FM crown learning</summary>
		static constexpr auto FM_RPT_WR_EFF_CROWN_AT_LEARN_4 = "FM_RPT_WR_EFF_CROWN_AT_LEARN_4";
		///<summary>Work roll effective crown at FM crown learning</summary>
		static constexpr auto FM_RPT_WR_EFF_CROWN_AT_LEARN_5 = "FM_RPT_WR_EFF_CROWN_AT_LEARN_5";
		///<summary>Work roll effective crown at FM crown learning</summary>
		static constexpr auto FM_RPT_WR_EFF_CROWN_AT_LEARN_6 = "FM_RPT_WR_EFF_CROWN_AT_LEARN_6";
		///<summary>Work roll effective crown at FM crown learning</summary>
		static constexpr auto FM_RPT_WR_EFF_CROWN_AT_LEARN_7 = "FM_RPT_WR_EFF_CROWN_AT_LEARN_7";
		///<summary>Yeild stress modifier error</summary>
		static constexpr auto FM_RPT_YIELD_STRESS_MOD_ERR_1 = "FM_RPT_YIELD_STRESS_MOD_ERR_1";
		///<summary>Yeild stress modifier error</summary>
		static constexpr auto FM_RPT_YIELD_STRESS_MOD_ERR_2 = "FM_RPT_YIELD_STRESS_MOD_ERR_2";
		///<summary>Yeild stress modifier error</summary>
		static constexpr auto FM_RPT_YIELD_STRESS_MOD_ERR_3 = "FM_RPT_YIELD_STRESS_MOD_ERR_3";
		///<summary>Yeild stress modifier error</summary>
		static constexpr auto FM_RPT_YIELD_STRESS_MOD_ERR_4 = "FM_RPT_YIELD_STRESS_MOD_ERR_4";
		///<summary>Yeild stress modifier error</summary>
		static constexpr auto FM_RPT_YIELD_STRESS_MOD_ERR_5 = "FM_RPT_YIELD_STRESS_MOD_ERR_5";
		///<summary>Yeild stress modifier error</summary>
		static constexpr auto FM_RPT_YIELD_STRESS_MOD_ERR_6 = "FM_RPT_YIELD_STRESS_MOD_ERR_6";
		///<summary>Yeild stress modifier error</summary>
		static constexpr auto FM_RPT_YIELD_STRESS_MOD_ERR_7 = "FM_RPT_YIELD_STRESS_MOD_ERR_7";
		///<summary>AGC monitor product gain</summary>
		static constexpr auto FM_SU_AGC_MONITOR_GAIN = "FM_SU_AGC_MONITOR_GAIN";
		///<summary>AGC monitor max limit</summary>
		static constexpr auto FM_SU_AGC_MONITOR_MAX_LIMIT = "FM_SU_AGC_MONITOR_MAX_LIMIT";
		///<summary>AGC monitor min limit</summary>
		static constexpr auto FM_SU_AGC_MONITOR_MIN_LIMIT = "FM_SU_AGC_MONITOR_MIN_LIMIT";
		///<summary>Alarm bits w setup error reasons</summary>
		static constexpr auto FM_SU_ALARM_WORD = "FM_SU_ALARM_WORD";
		///<summary>Model calculation status</summary>
		static constexpr auto FM_SU_CALC_STATUS = "FM_SU_CALC_STATUS";
		///<summary>Last calculation time</summary>
		static constexpr auto FM_SU_CALC_TIME = "FM_SU_CALC_TIME";
		///<summary>Aluminium content</summary>
		static constexpr auto FM_SU_CHEM_Al = "FM_SU_CHEM_Al";
		///<summary>Boron content</summary>
		static constexpr auto FM_SU_CHEM_B = "FM_SU_CHEM_B";
		///<summary>Carbon content</summary>
		static constexpr auto FM_SU_CHEM_C = "FM_SU_CHEM_C";
		///<summary>Cobalt content</summary>
		static constexpr auto FM_SU_CHEM_Co = "FM_SU_CHEM_Co";
		///<summary>Chromium content</summary>
		static constexpr auto FM_SU_CHEM_Cr = "FM_SU_CHEM_Cr";
		///<summary>Copper content</summary>
		static constexpr auto FM_SU_CHEM_Cu = "FM_SU_CHEM_Cu";
		///<summary>Iron content</summary>
		static constexpr auto FM_SU_CHEM_Fe = "FM_SU_CHEM_Fe";
		///<summary>Hydrogen content</summary>
		static constexpr auto FM_SU_CHEM_H = "FM_SU_CHEM_H";
		///<summary>Magnesium content</summary>
		static constexpr auto FM_SU_CHEM_Mg = "FM_SU_CHEM_Mg";
		///<summary>Manganese content</summary>
		static constexpr auto FM_SU_CHEM_Mn = "FM_SU_CHEM_Mn";
		///<summary>Molybdenum content</summary>
		static constexpr auto FM_SU_CHEM_Mo = "FM_SU_CHEM_Mo";
		///<summary>Nitrogen content</summary>
		static constexpr auto FM_SU_CHEM_N = "FM_SU_CHEM_N";
		///<summary>Niobium content</summary>
		static constexpr auto FM_SU_CHEM_Nb = "FM_SU_CHEM_Nb";
		///<summary>Nickel content</summary>
		static constexpr auto FM_SU_CHEM_Ni = "FM_SU_CHEM_Ni";
		///<summary>Oxygen content</summary>
		static constexpr auto FM_SU_CHEM_O = "FM_SU_CHEM_O";
		///<summary>Phosphorus content</summary>
		static constexpr auto FM_SU_CHEM_P = "FM_SU_CHEM_P";
		///<summary>Sulfur content</summary>
		static constexpr auto FM_SU_CHEM_S = "FM_SU_CHEM_S";
		///<summary>Silicon content</summary>
		static constexpr auto FM_SU_CHEM_Si = "FM_SU_CHEM_Si";
		///<summary>Tin content</summary>
		static constexpr auto FM_SU_CHEM_Sn = "FM_SU_CHEM_Sn";
		///<summary>Tantalum content</summary>
		static constexpr auto FM_SU_CHEM_Ta = "FM_SU_CHEM_Ta";
		///<summary>Titanium content</summary>
		static constexpr auto FM_SU_CHEM_Ti = "FM_SU_CHEM_Ti";
		///<summary>Vanadium content</summary>
		static constexpr auto FM_SU_CHEM_V = "FM_SU_CHEM_V";
		///<summary>Tungsten content</summary>
		static constexpr auto FM_SU_CHEM_W = "FM_SU_CHEM_W";
		///<summary>Zinc content</summary>
		static constexpr auto FM_SU_CHEM_Zn = "FM_SU_CHEM_Zn";
		///<summary>Zirconium content</summary>
		static constexpr auto FM_SU_CHEM_Zr = "FM_SU_CHEM_Zr";
		///<summary>Crown Target</summary>
		static constexpr auto FM_SU_CROWN_AIM = "FM_SU_CROWN_AIM";
		///<summary>Crown Max</summary>
		static constexpr auto FM_SU_CROWN_MAX = "FM_SU_CROWN_MAX";
		///<summary>Crown Min</summary>
		static constexpr auto FM_SU_CROWN_MIN = "FM_SU_CROWN_MIN";
		///<summary>Crop shear temperature target</summary>
		static constexpr auto FM_SU_CS_TEMP_AIM = "FM_SU_CS_TEMP_AIM";
		///<summary>Crop shear temperature predicted</summary>
		static constexpr auto FM_SU_CS_TEMP_PRED = "FM_SU_CS_TEMP_PRED";
		///<summary>Dilatometer index</summary>
		static constexpr auto FM_SU_DILATOMETER_IDX = "FM_SU_DILATOMETER_IDX";
		///<summary>Entry strip speed predicted</summary>
		static constexpr auto FM_SU_ENTRY_STRIP_SPEED_PRED = "FM_SU_ENTRY_STRIP_SPEED_PRED";
		///<summary>Entry strip width (hot)</summary>
		static constexpr auto FM_SU_ENTRY_STRIP_WIDTH = "FM_SU_ENTRY_STRIP_WIDTH";
		///<summary>Model error text</summary>
		static constexpr auto FM_SU_ERROR_TEXT = "FM_SU_ERROR_TEXT";
		///<summary>Event bits w calculation events</summary>
		static constexpr auto FM_SU_EVENT_WORD = "FM_SU_EVENT_WORD";
		///<summary>Exit strip length</summary>
		static constexpr auto FM_SU_EXIT_STRIP_LENGTH = "FM_SU_EXIT_STRIP_LENGTH";
		///<summary>Exit strip width (hot)</summary>
		static constexpr auto FM_SU_EXIT_STRIP_WIDTH = "FM_SU_EXIT_STRIP_WIDTH";
		///<summary>Exit Temperature Target</summary>
		static constexpr auto FM_SU_EXIT_TEMP_AIM = "FM_SU_EXIT_TEMP_AIM";
		///<summary>Exit Temperature Max</summary>
		static constexpr auto FM_SU_EXIT_TEMP_MAX = "FM_SU_EXIT_TEMP_MAX";
		///<summary>Exit Temperature Min</summary>
		static constexpr auto FM_SU_EXIT_TEMP_MIN = "FM_SU_EXIT_TEMP_MIN";
		///<summary>Exit pyrometer reference predicted</summary>
		static constexpr auto FM_SU_EXIT_TEMP_PRED = "FM_SU_EXIT_TEMP_PRED";
		///<summary>Exit Thickness Target (cold)</summary>
		static constexpr auto FM_SU_EXIT_THICKN_GAUGE_REF = "FM_SU_EXIT_THICKN_GAUGE_REF";
		///<summary>Stand predicted exit thickness</summary>
		static constexpr auto FM_SU_EXIT_THICKN_PRED = "FM_SU_EXIT_THICKN_PRED";
		///<summary>Exit Thickness Max</summary>
		static constexpr auto FM_SU_EXIT_THICKNESS_MAX = "FM_SU_EXIT_THICKNESS_MAX";
		///<summary>Exit Thickness Min</summary>
		static constexpr auto FM_SU_EXIT_THICKNESS_MIN = "FM_SU_EXIT_THICKNESS_MIN";
		///<summary>Width gauge reference (cold)</summary>
		static constexpr auto FM_SU_EXIT_WIDTH_GAUGE_REF = "FM_SU_EXIT_WIDTH_GAUGE_REF";
		///<summary>Exit width max</summary>
		static constexpr auto FM_SU_EXIT_WIDTH_MAX = "FM_SU_EXIT_WIDTH_MAX";
		///<summary>Exit width min</summary>
		static constexpr auto FM_SU_EXIT_WIDTH_MIN = "FM_SU_EXIT_WIDTH_MIN";
		///<summary>Flatness Target</summary>
		static constexpr auto FM_SU_FLATNESS_AIM = "FM_SU_FLATNESS_AIM";
		///<summary>Flatness Max</summary>
		static constexpr auto FM_SU_FLATNESS_MAX = "FM_SU_FLATNESS_MAX";
		///<summary>Flatness Min</summary>
		static constexpr auto FM_SU_FLATNESS_MIN = "FM_SU_FLATNESS_MIN";
		///<summary>Material grade</summary>
		static constexpr auto FM_SU_GRADE = "FM_SU_GRADE";
		///<summary>latest stand to apply crown correction based on flatness envelop</summary>
		static constexpr auto FM_SU_LAST_CROWN_CORR_STD = "FM_SU_LAST_CROWN_CORR_STD";
		///<summary>Flatness control sensitivity factor for last stand </summary>
		static constexpr auto FM_SU_LAST_STD_FLATN_DFRCE_DIU = "FM_SU_LAST_STD_FLATN_DFRCE/DIU";
		///<summary>Last working stand number</summary>
		static constexpr auto FM_SU_LAST_WST_NO = "FM_SU_LAST_WST_NO";
		///<summary>Delivery stand strip speed max</summary>
		static constexpr auto FM_SU_LAST_WST_STRIP_SPEED_MAX = "FM_SU_LAST_WST_STRIP_SPEED_MAX";
		///<summary>Delivery stand strip speed reference</summary>
		static constexpr auto FM_SU_LAST_WST_STRIP_SPEED_REF = "FM_SU_LAST_WST_STRIP_SPEED_REF";
		///<summary>Primary entry descaling selected</summary>
		static constexpr auto FM_SU_PRIM_ENTRY_DESC_ON = "FM_SU_PRIM_ENTRY_DESC_ON";
		///<summary>Primary exit descaling selected</summary>
		static constexpr auto FM_SU_PRIM_EXIT_DESC_ON = "FM_SU_PRIM_EXIT_DESC_ON";
		///<summary>Release transfer bar for rolling in FM</summary>
		static constexpr auto FM_SU_RELEASE = "FM_SU_RELEASE";
		///<summary>Stand AGC gaugemeter gain</summary>
		static constexpr auto FM_SU_S_AGC_GAUGEM_GAIN = "FM_SU_S_AGC_GAUGEM_GAIN";
		///<summary>Stand min limit for AGC lock-on mode</summary>
		static constexpr auto FM_SU_S_AGC_LOCKON_MAX_LIM = "FM_SU_S_AGC_LOCKON_MAX_LIM";
		///<summary>Stand max limit for AGC lock-on mode</summary>
		static constexpr auto FM_SU_S_AGC_LOCKON_MIN_LIM = "FM_SU_S_AGC_LOCKON_MIN_LIM";
		///<summary>Stand AGC roll gap force (use for absolute AGC)</summary>
		static constexpr auto FM_SU_S_AGC_RGAP_FORCE = "FM_SU_S_AGC_RGAP_FORCE";
		///<summary>Stand strip modulus:delta force/delta exit thickness</summary>
		static constexpr auto FM_SU_S_DFORCE___DTHICK = "FM_SU_S_DFORCE_/ DTHICK";
		///<summary>Profile control sensitivity factor (dForce / dCrown)</summary>
		static constexpr auto FM_SU_S_DFRCE_DCROWN = "FM_SU_S_DFRCE/DCROWN";
		///<summary>Stand transfer function:delta roll bending force/delta force</summary>
		static constexpr auto FM_SU_S_DRBENDFRCE___DFRCE = "FM_SU_S_DRBENDFRCE_/ DFRCE";
		///<summary>Stand transfer function:delta gap/delta roll bending force</summary>
		static constexpr auto FM_SU_S_DRGAP___DRBENDFRCE = "FM_SU_S_DRGAP_/ DRBENDFRCE";
		///<summary>Stand predicted exit thickness</summary>
		static constexpr auto FM_SU_S_EXIT_THICKN_PRED = "FM_SU_S_EXIT_THICKN_PRED";
		///<summary>Stand strip temperature in roll gap</summary>
		static constexpr auto FM_SU_S_GAP_STRIP_TEMP = "FM_SU_S_GAP_STRIP_TEMP";
		///<summary>Stand interstand cooling reference</summary>
		static constexpr auto FM_SU_S_IST_COOL_REF = "FM_SU_S_IST_COOL_REF";
		///<summary>Stand lead speed factor</summary>
		static constexpr auto FM_SU_S_LEAD_SPEED_FACTOR = "FM_SU_S_LEAD_SPEED_FACTOR";
		///<summary>Stand looper angle reference</summary>
		static constexpr auto FM_SU_S_LOOPER_ANGLE_REF = "FM_SU_S_LOOPER_ANGLE_REF";
		///<summary>Stand looper tension reference</summary>
		static constexpr auto FM_SU_S_LOOPER_TENS_REF = "FM_SU_S_LOOPER_TENS_REF";
		///<summary>Stand predicted motor torque</summary>
		static constexpr auto FM_SU_S_MOTOR_TRQ_PRED = "FM_SU_S_MOTOR_TRQ_PRED";
		///<summary>Stand oil film offset applied to gap</summary>
		static constexpr auto FM_SU_S_OIL_FILM_OFFSET = "FM_SU_S_OIL_FILM_OFFSET";
		///<summary>Stand relation between work rolls pherip. speeds including forward slip</summary>
		static constexpr auto FM_SU_S_R_FACTOR = "FM_SU_S_R-FACTOR";
		///<summary>Stand predicted roll gap force</summary>
		static constexpr auto FM_SU_S_RGAP_FORCE_PRED = "FM_SU_S_RGAP_FORCE_PRED";
		///<summary>Stand gap offsets incl. thermal crown, wear, roll shifting & roll bending</summary>
		static constexpr auto FM_SU_S_RGAP_OFFSET = "FM_SU_S_RGAP_OFFSET";
		///<summary>Stand gap reference</summary>
		static constexpr auto FM_SU_S_RGAP_REFERENCE = "FM_SU_S_RGAP_REFERENCE";
		///<summary>Stand roll bending reference</summary>
		static constexpr auto FM_SU_S_ROLL_BEND_REF = "FM_SU_S_ROLL_BEND_REF";
		///<summary>Stand roll shift position</summary>
		static constexpr auto FM_SU_S_ROLL_SHIFT_POS = "FM_SU_S_ROLL_SHIFT_POS";
		///<summary>Stand Stand dummied request</summary>
		static constexpr auto FM_SU_S_STAND_WORKING = "FM_SU_S_STAND_WORKING";
		///<summary>Stand stretch curve width component</summary>
		static constexpr auto FM_SU_S_STRETCH_CURVE_W_COMP = "FM_SU_S_STRETCH_CURVE_W_COMP";
		///<summary>Stand predicted strip forward slip</summary>
		static constexpr auto FM_SU_S_STRIP_FWD_SLIP_PRED = "FM_SU_S_STRIP_FWD_SLIP_PRED";
		///<summary>Stand thickness reduction</summary>
		static constexpr auto FM_SU_S_THICKN_REDUCTION = "FM_SU_S_THICKN_REDUCTION";
		///<summary>Alternative temperature target</summary>
		static constexpr auto FM_SU_TEMP_ALT_AIM = "FM_SU_TEMP_ALT_AIM";
		///<summary>Exit temperature expansion coefficient</summary>
		static constexpr auto FM_SU_TEMP_EXP_COEFF = "FM_SU_TEMP_EXP_COEFF";
		///<summary>Alternative thickness target</summary>
		static constexpr auto FM_SU_THICKN_ALT_AIM = "FM_SU_THICKN_ALT_AIM";
		///<summary>Total rolling time</summary>
		static constexpr auto FM_SU_TOT_ROLLING_TIME = "FM_SU_TOT_ROLLING_TIME";
		///<summary>Predicted transfer bar thickness</summary>
		static constexpr auto FM_SU_TRF_BAR_THICKN_PRED = "FM_SU_TRF_BAR_THICKN_PRED";
		///<summary>0=Cold Charge, 1=Hot Charge</summary>
		static constexpr auto HOT_CHARGING = "HOT_CHARGING";
		///<summary>Horizontal stand used in pass</summary>
		static constexpr auto HSTAND_ACTIVE = "HSTAND_ACTIVE";
		///<summary>Intermediate cooling recovery time.</summary>
		static constexpr auto IM_COOLING_RECOVER_TIME = "IM_COOLING_RECOVER_TIME";
		///<summary>Interm cooling temp for Dual Phase. 0 = No Interm. Temp target.</summary>
		static constexpr auto IM_COOLING_TEMP_AIM = "IM_COOLING_TEMP_AIM";
		///<summary>Instruction for operator for inspection.</summary>
		static constexpr auto INSPECTION_INSTRUCTION = "INSPECTION_INSTRUCTION";
		///<summary>Interstand cooling flow average</summary>
		static constexpr auto IST_COOLING_FLOW = "IST_COOLING_FLOW";
		///<summary>Delivery status for cancel report</summary>
		static constexpr auto L3_CANCEL_RPT_STATUS = "L3_CANCEL_RPT_STATUS";
		///<summary>Delivery status for charge report</summary>
		static constexpr auto L3_CHARGE_RPT_STATUS = "L3_CHARGE_RPT_STATUS";
		///<summary>Delivery status for coil transport report</summary>
		static constexpr auto L3_COIL_TRANSPORT_RPT_STATUS = "L3_COIL_TRANSPORT_RPT_STATUS";
		///<summary>Delivery status for discharge report</summary>
		static constexpr auto L3_DISCHARGE_RPT_STATUS = "L3_DISCHARGE_RPT_STATUS";
		///<summary>Delivery status for production report</summary>
		static constexpr auto L3_PRODUCTION_RPT_STATUS = "L3_PRODUCTION_RPT_STATUS";
		///<summary>Delivery status for sample report</summary>
		static constexpr auto L3_SAMPLE_RPT_STATUS = "L3_SAMPLE_RPT_STATUS";
		///<summary>Delivery status for wight report</summary>
		static constexpr auto L3_WEIGHT_RPT_STATUS = "L3_WEIGHT_RPT_STATUS";
		///<summary>Last working stand number</summary>
		static constexpr auto LAST_WORKING_STAND_NO = "LAST_WORKING_STAND_NO";
		///<summary>Material production crew</summary>
		static constexpr auto MAT_CREW = "MAT_CREW";
		///<summary>Material final length</summary>
		static constexpr auto MAT_END_LENGTH = "MAT_END_LENGTH";
		///<summary>Material end quality class</summary>
		static constexpr auto MAT_END_QUALITY_CLASS = "MAT_END_QUALITY_CLASS";
		///<summary>Matreial final temperature</summary>
		static constexpr auto MAT_END_TEMP = "MAT_END_TEMP";
		///<summary>Material final thickness</summary>
		static constexpr auto MAT_END_THICKNESS = "MAT_END_THICKNESS";
		///<summary>End Rolling Time</summary>
		static constexpr auto MAT_END_TIME = "MAT_END_TIME";
		///<summary>Material final weight</summary>
		static constexpr auto MAT_END_WEIGHT = "MAT_END_WEIGHT";
		///<summary>Material final width</summary>
		static constexpr auto MAT_END_WIDTH = "MAT_END_WIDTH";
		///<summary>Material production shift</summary>
		static constexpr auto MAT_SHIFT = "MAT_SHIFT";
		///<summary>Start Rolling Time</summary>
		static constexpr auto MAT_START_TIME = "MAT_START_TIME";
		///<summary>Material density for weight calculations</summary>
		static constexpr auto MATERIAL_DENSITY = "MATERIAL_DENSITY";
		///<summary>Motor rpm average</summary>
		static constexpr auto MOTOR_RPM_AVG = "MOTOR_RPM_AVG";
		///<summary>Motor rpm data</summary>
		static constexpr auto MOTOR_RPM_DAQ = "MOTOR_RPM_DAQ";
		///<summary>Motor torque average</summary>
		static constexpr auto MOTOR_TRQ_AVG = "MOTOR_TRQ_AVG";
		///<summary>Motor torque data</summary>
		static constexpr auto MOTOR_TRQ_DAQ = "MOTOR_TRQ_DAQ";
		///<summary>Total number of passes</summary>
		static constexpr auto NO_OF_PASSES = "NO_OF_PASSES";
		///<summary>0=Strip rolling, 1=Plate rolling</summary>
		static constexpr auto PLATE_FLAG = "PLATE_FLAG";
		///<summary>Primary entry descaler spray On</summary>
		static constexpr auto PRIMARY_ENTRY_DESC_ON = "PRIMARY_ENTRY_DESC_ON";
		///<summary>Primary exit descaler spray On</summary>
		static constexpr auto PRIMARY_EXIT_DESC_ON = "PRIMARY_EXIT_DESC_ON";
		///<summary>Crown Target</summary>
		static constexpr auto PROD_MAT_CROWN_AIM = "PROD_MAT_CROWN_AIM";
		///<summary>Crown Max</summary>
		static constexpr auto PROD_MAT_CROWN_MAX = "PROD_MAT_CROWN_MAX";
		///<summary>Crown Min</summary>
		static constexpr auto PROD_MAT_CROWN_MIN = "PROD_MAT_CROWN_MIN";
		///<summary>Flatness Target</summary>
		static constexpr auto PROD_MAT_FLATNESS_AIM = "PROD_MAT_FLATNESS_AIM";
		///<summary>Flatness Max</summary>
		static constexpr auto PROD_MAT_FLATNESS_MAX = "PROD_MAT_FLATNESS_MAX";
		///<summary>Flatness Min</summary>
		static constexpr auto PROD_MAT_FLATNESS_MIN = "PROD_MAT_FLATNESS_MIN";
		///<summary>Finish Temperature Target</summary>
		static constexpr auto PROD_MAT_TEMP_AIM = "PROD_MAT_TEMP_AIM";
		///<summary>Alternative temperature target</summary>
		static constexpr auto PROD_MAT_TEMP_ALT = "PROD_MAT_TEMP_ALT";
		///<summary>Finish Temperature Max</summary>
		static constexpr auto PROD_MAT_TEMP_MAX = "PROD_MAT_TEMP_MAX";
		///<summary>Finish Temperature Min</summary>
		static constexpr auto PROD_MAT_TEMP_MIN = "PROD_MAT_TEMP_MIN";
		///<summary>Material Produced Thickness Target (cold)</summary>
		static constexpr auto PROD_MAT_THICKNESS_AIM = "PROD_MAT_THICKNESS_AIM";
		///<summary>Alternative thickness target.</summary>
		static constexpr auto PROD_MAT_THICKNESS_ALT = "PROD_MAT_THICKNESS_ALT";
		///<summary>Material Produced Thickness Max </summary>
		static constexpr auto PROD_MAT_THICKNESS_MAX = "PROD_MAT_THICKNESS_MAX";
		///<summary>Material Produced Thickness Min</summary>
		static constexpr auto PROD_MAT_THICKNESS_MIN = "PROD_MAT_THICKNESS_MIN";
		///<summary>Wedge Target</summary>
		static constexpr auto PROD_MAT_WEDGE_AIM = "PROD_MAT_WEDGE_AIM";
		///<summary>Wedge Max</summary>
		static constexpr auto PROD_MAT_WEDGE_MAX = "PROD_MAT_WEDGE_MAX";
		///<summary>Wedge Min</summary>
		static constexpr auto PROD_MAT_WEDGE_MIN = "PROD_MAT_WEDGE_MIN";
		///<summary>Material Produced Width Target (cold)</summary>
		static constexpr auto PROD_MAT_WIDTH_AIM = "PROD_MAT_WIDTH_AIM";
		///<summary>Material Produced Width Max</summary>
		static constexpr auto PROD_MAT_WIDTH_MAX = "PROD_MAT_WIDTH_MAX";
		///<summary>Material Produced Width Min</summary>
		static constexpr auto PROD_MAT_WIDTH_MIN = "PROD_MAT_WIDTH_MIN";
		///<summary>Production Standard for Coil label</summary>
		static constexpr auto PRODUCTION_STD = "PRODUCTION_STD";
		///<summary>Active crew at reject</summary>
		static constexpr auto REJECT_CREW = "REJECT_CREW";
		///<summary>Reject description</summary>
		static constexpr auto REJECT_DESCRIPTION = "REJECT_DESCRIPTION";
		///<summary>Rejected transfer bar length</summary>
		static constexpr auto REJECT_LENGTH = "REJECT_LENGTH";
		///<summary>Reject location (1-6 according to customer spec)</summary>
		static constexpr auto REJECT_LOCATION = "REJECT_LOCATION";
		///<summary>Rejected material classification (1=Scrap,2=TrfBar,0=neither)</summary>
		static constexpr auto REJECT_MAT_CLASS = "REJECT_MAT_CLASS";
		///<summary>Reject operator code</summary>
		static constexpr auto REJECT_OPERATOR = "REJECT_OPERATOR";
		///<summary>Reject reason code (1=Prod, 2=Equipment,3=others)</summary>
		static constexpr auto REJECT_REASON_CODE = "REJECT_REASON_CODE";
		///<summary>Active shift at reject</summary>
		static constexpr auto REJECT_SHIFT = "REJECT_SHIFT";
		///<summary>Rejected transfer bar thickness</summary>
		static constexpr auto REJECT_THICKNESS = "REJECT_THICKNESS";
		///<summary>Reject date & time</summary>
		static constexpr auto REJECT_TIME = "REJECT_TIME";
		///<summary>Rejected transfer bar width</summary>
		static constexpr auto REJECT_WIDTH = "REJECT_WIDTH";
		///<summary>Tracking Zone name where reject occurred</summary>
		static constexpr auto REJECT_ZONE = "REJECT_ZONE";
		///<summary>RM Descaling Code, 0 = Default, others to be defined</summary>
		static constexpr auto RM_DESCALING_CODE = "RM_DESCALING_CODE";
		///<summary>RM target temp when rolling strips</summary>
		static constexpr auto RM_EXIT_TEMP_AIM = "RM_EXIT_TEMP_AIM";
		///<summary>RM max temp when rolling strips</summary>
		static constexpr auto RM_EXIT_TEMP_AIM_MAX = "RM_EXIT_TEMP_AIM_MAX";
		///<summary>RM min temp when rolling strips</summary>
		static constexpr auto RM_EXIT_TEMP_AIM_MIN = "RM_EXIT_TEMP_AIM_MIN";
		///<summary>RM target thickness when rolling strips</summary>
		static constexpr auto RM_EXIT_THICKNESS_AIM = "RM_EXIT_THICKNESS_AIM";
		///<summary>RM target width when rolling strips</summary>
		static constexpr auto RM_EXIT_WIDTH_AIM = "RM_EXIT_WIDTH_AIM";
		///<summary>Edger in auto 1</summary>
		static constexpr auto RM_RPT_EDGER_IN_AUTO_1 = "RM_RPT_EDGER_IN_AUTO_1";
		///<summary>Edger in auto 2</summary>
		static constexpr auto RM_RPT_EDGER_IN_AUTO_2 = "RM_RPT_EDGER_IN_AUTO_2";
		///<summary>Edger ksi ratio error 1</summary>
		static constexpr auto RM_RPT_EDGER_KSI_RATIO_ERR_1 = "RM_RPT_EDGER_KSI_RATIO_ERR_1";
		///<summary>Edger ksi ratio error 2</summary>
		static constexpr auto RM_RPT_EDGER_KSI_RATIO_ERR_2 = "RM_RPT_EDGER_KSI_RATIO_ERR_2";
		///<summary>Rougher hardness factor 1</summary>
		static constexpr auto RM_RPT_ROUGHER_HARDN_FCTR_1 = "RM_RPT_ROUGHER_HARDN_FCTR_1";
		///<summary>Rougher hardness factor 2</summary>
		static constexpr auto RM_RPT_ROUGHER_HARDN_FCTR_2 = "RM_RPT_ROUGHER_HARDN_FCTR_2";
		///<summary>Rougher in auto 1</summary>
		static constexpr auto RM_RPT_ROUGHER_IN_AUTO_1 = "RM_RPT_ROUGHER_IN_AUTO_1";
		///<summary>Rougher in auto 2</summary>
		static constexpr auto RM_RPT_ROUGHER_IN_AUTO_2 = "RM_RPT_ROUGHER_IN_AUTO_2";
		///<summary>Rougher ksi ratio error 1</summary>
		static constexpr auto RM_RPT_ROUGHER_KSI_RATIO_ERR_1 = "RM_RPT_ROUGHER_KSI_RATIO_ERR_1";
		///<summary>Rougher ksi ratio error 2</summary>
		static constexpr auto RM_RPT_ROUGHER_KSI_RATIO_ERR_2 = "RM_RPT_ROUGHER_KSI_RATIO_ERR_2";
		///<summary>Rougher measured ksi 1</summary>
		static constexpr auto RM_RPT_ROUGHER_MEAS_KSI_1 = "RM_RPT_ROUGHER_MEAS_KSI_1";
		///<summary>Rougher measured ksi 2</summary>
		static constexpr auto RM_RPT_ROUGHER_MEAS_KSI_2 = "RM_RPT_ROUGHER_MEAS_KSI_2";
		///<summary>Update Edger calibration</summary>
		static constexpr auto RM_RPT_UPDATE_EDGER_CALIB = "RM_RPT_UPDATE_EDGER_CALIB";
		///<summary>Update RM global</summary>
		static constexpr auto RM_RPT_UPDATE_RM_GLOBAL = "RM_RPT_UPDATE_RM_GLOBAL";
		///<summary>Update RM model</summary>
		static constexpr auto RM_RPT_UPDATE_RM_MODEL = "RM_RPT_UPDATE_RM_MODEL";
		///<summary>Update RM temperature</summary>
		static constexpr auto RM_RPT_UPDATE_RM_TEMP = "RM_RPT_UPDATE_RM_TEMP";
		///<summary>Update RM width</summary>
		static constexpr auto RM_RPT_UPDATE_RM_WIDTH = "RM_RPT_UPDATE_RM_WIDTH";
		///<summary>Update RM width safety margin</summary>
		static constexpr auto RM_RPT_UPDATE_RM_WIDTH_MARGIN = "RM_RPT_UPDATE_RM_WIDTH_MARGIN";
		///<summary>Alarm bits w setup error reasons</summary>
		static constexpr auto RM_SU_ALARM_WORD = "RM_SU_ALARM_WORD";
		///<summary>Model calculation status</summary>
		static constexpr auto RM_SU_CALC_STATUS = "RM_SU_CALC_STATUS";
		///<summary>Last calculation time</summary>
		static constexpr auto RM_SU_CALC_TIME = "RM_SU_CALC_TIME";
		///<summary>Coil Box bending torque</summary>
		static constexpr auto RM_SU_CBOX_BENDING_TORQUE = "RM_SU_CBOX_BENDING_TORQUE";
		///<summary>Dilatometer curve id for gauge</summary>
		static constexpr auto RM_SU_DILATOM_CURVE_ID = "RM_SU_DILATOM_CURVE_ID";
		///<summary>Model error text</summary>
		static constexpr auto RM_SU_ERROR_TEXT = "RM_SU_ERROR_TEXT";
		///<summary>Event bits w calculation events</summary>
		static constexpr auto RM_SU_EVENT_WORD = "RM_SU_EVENT_WORD";
		///<summary>Predicted exit length (hot)</summary>
		static constexpr auto RM_SU_EXIT_LENGTH_PRED = "RM_SU_EXIT_LENGTH_PRED";
		///<summary>Predicted exit temperature</summary>
		static constexpr auto RM_SU_EXIT_TEMP_PRED = "RM_SU_EXIT_TEMP_PRED";
		///<summary>Predicted exit thickness (hot)</summary>
		static constexpr auto RM_SU_EXIT_THICKN_PRED = "RM_SU_EXIT_THICKN_PRED";
		///<summary>Predicted exit width (hot)</summary>
		static constexpr auto RM_SU_EXIT_WIDTH_PRED = "RM_SU_EXIT_WIDTH_PRED";
		///<summary>Material Grade</summary>
		static constexpr auto RM_SU_GRADE = "RM_SU_GRADE";
		///<summary>Number of passes</summary>
		static constexpr auto RM_SU_NO_OF_PASSES = "RM_SU_NO_OF_PASSES";
		///<summary>Pass AGC maximum force limit</summary>
		static constexpr auto RM_SU_P_AGC_FORCE_MAX_LIMIT = "RM_SU_P_AGC_FORCE_MAX_LIMIT";
		///<summary>Pass AGC minimum force limit</summary>
		static constexpr auto RM_SU_P_AGC_FORCE_MIN_LIMIT = "RM_SU_P_AGC_FORCE_MIN_LIMIT";
		///<summary>Pass AGC gaugemeter gain</summary>
		static constexpr auto RM_SU_P_AGC_GAUGEM_GAIN = "RM_SU_P_AGC_GAUGEM_GAIN";
		///<summary>Pass AGC roll gap force for absolute AGC</summary>
		static constexpr auto RM_SU_P_AGC_ROLL_GAP_FORCE = "RM_SU_P_AGC_ROLL_GAP_FORCE";
		///<summary>Pass descaling selected</summary>
		static constexpr auto RM_SU_P_DESC_ON = "RM_SU_P_DESC_ON";
		///<summary>Pass modulus, delta force / delta gap</summary>
		static constexpr auto RM_SU_P_DFORCE___DGAP = "RM_SU_P_DFORCE_/ DGAP";
		///<summary>Pass strip modulus, delta force / delta exit thickness</summary>
		static constexpr auto RM_SU_P_DFORCE___DTHICK = "RM_SU_P_DFORCE_/ DTHICK";
		///<summary>Pass predicted drive torque</summary>
		static constexpr auto RM_SU_P_DRIVE_TORQUE_PRED = "RM_SU_P_DRIVE_TORQUE_PRED";
		///<summary>Pass transfer function, delta thickness / delta gap</summary>
		static constexpr auto RM_SU_P_DTHICK___DGAP = "RM_SU_P_DTHICK_/ DGAP";
		///<summary>Pass edger exit width</summary>
		static constexpr auto RM_SU_P_EDGER_EXIT_WIDTH = "RM_SU_P_EDGER_EXIT_WIDTH";
		///<summary>Pass edger roll force</summary>
		static constexpr auto RM_SU_P_EDGER_FORCE = "RM_SU_P_EDGER_FORCE";
		///<summary>Pass edger gap reference</summary>
		static constexpr auto RM_SU_P_EDGER_GAP_REF = "RM_SU_P_EDGER_GAP_REF";
		///<summary>Pass peripheral speed reference, thread</summary>
		static constexpr auto RM_SU_P_EDGER_SPREF_THREAD = "RM_SU_P_EDGER_SPREF_THREAD";
		///<summary>Pass Edger Active during pass</summary>
		static constexpr auto RM_SU_P_EDGER_WORKING = "RM_SU_P_EDGER_WORKING";
		///<summary>Pass predicted entry width (hot)</summary>
		static constexpr auto RM_SU_P_ENTRY_WIDTH_PRED = "RM_SU_P_ENTRY_WIDTH_PRED";
		///<summary>Pass entry width gauge reference (cold)</summary>
		static constexpr auto RM_SU_P_ENTRY_WIDTH_REF = "RM_SU_P_ENTRY_WIDTH_REF";
		///<summary>Pass exit strip length</summary>
		static constexpr auto RM_SU_P_EXIT_STRIP_LENGTH = "RM_SU_P_EXIT_STRIP_LENGTH";
		///<summary>Pass predicted exit thickness</summary>
		static constexpr auto RM_SU_P_EXIT_THICKN_PRED = "RM_SU_P_EXIT_THICKN_PRED";
		///<summary>Pass predicted exit width (hot)</summary>
		static constexpr auto RM_SU_P_EXIT_WIDTH_PRED = "RM_SU_P_EXIT_WIDTH_PRED";
		///<summary>Pass exit width gauge reference (cold)</summary>
		static constexpr auto RM_SU_P_EXIT_WIDTH_REF = "RM_SU_P_EXIT_WIDTH_REF";
		///<summary>Pass predicted forward slip out of edger</summary>
		static constexpr auto RM_SU_P_FWD_SLIP_EDGER = "RM_SU_P_FWD_SLIP_EDGER";
		///<summary>Pass edger gap offset 1, head length</summary>
		static constexpr auto RM_SU_P_GAP_OFFS_HEAD_LEN1 = "RM_SU_P_GAP_OFFS_HEAD_LEN1";
		///<summary>Pass edger gap offset 2, head length</summary>
		static constexpr auto RM_SU_P_GAP_OFFS_HEAD_LEN2 = "RM_SU_P_GAP_OFFS_HEAD_LEN2";
		///<summary>Pass edger gap offset 3, head length</summary>
		static constexpr auto RM_SU_P_GAP_OFFS_HEAD_LEN3 = "RM_SU_P_GAP_OFFS_HEAD_LEN3";
		///<summary>Pass edger gap offset 4, head length</summary>
		static constexpr auto RM_SU_P_GAP_OFFS_HEAD_LEN4 = "RM_SU_P_GAP_OFFS_HEAD_LEN4";
		///<summary>Pass edger gap offset 1, head short stroke</summary>
		static constexpr auto RM_SU_P_GAP_OFFS_HEAD_SS1 = "RM_SU_P_GAP_OFFS_HEAD_SS1";
		///<summary>Pass edger gap offset 2, head short stroke</summary>
		static constexpr auto RM_SU_P_GAP_OFFS_HEAD_SS2 = "RM_SU_P_GAP_OFFS_HEAD_SS2";
		///<summary>Pass edger gap offset 3, head short stroke</summary>
		static constexpr auto RM_SU_P_GAP_OFFS_HEAD_SS3 = "RM_SU_P_GAP_OFFS_HEAD_SS3";
		///<summary>Pass edger gap offset 4, head short stroke</summary>
		static constexpr auto RM_SU_P_GAP_OFFS_HEAD_SS4 = "RM_SU_P_GAP_OFFS_HEAD_SS4";
		///<summary>Pass edger gap offset 1, tail length</summary>
		static constexpr auto RM_SU_P_GAP_OFFS_TAIL_LEN1 = "RM_SU_P_GAP_OFFS_TAIL_LEN1";
		///<summary>Pass edger gap offset 2, tail length</summary>
		static constexpr auto RM_SU_P_GAP_OFFS_TAIL_LEN2 = "RM_SU_P_GAP_OFFS_TAIL_LEN2";
		///<summary>Pass edger gap offset 3, tail length</summary>
		static constexpr auto RM_SU_P_GAP_OFFS_TAIL_LEN3 = "RM_SU_P_GAP_OFFS_TAIL_LEN3";
		///<summary>Pass edger gap offset 4, tail length</summary>
		static constexpr auto RM_SU_P_GAP_OFFS_TAIL_LEN4 = "RM_SU_P_GAP_OFFS_TAIL_LEN4";
		///<summary>Pass edger gap offset 1, tail short stroke</summary>
		static constexpr auto RM_SU_P_GAP_OFFS_TAIL_SS1 = "RM_SU_P_GAP_OFFS_TAIL_SS1";
		///<summary>Pass edger gap offset 2, tail short stroke</summary>
		static constexpr auto RM_SU_P_GAP_OFFS_TAIL_SS2 = "RM_SU_P_GAP_OFFS_TAIL_SS2";
		///<summary>Pass edger gap offset 3, tail short stroke</summary>
		static constexpr auto RM_SU_P_GAP_OFFS_TAIL_SS3 = "RM_SU_P_GAP_OFFS_TAIL_SS3";
		///<summary>Pass edger gap offset 4, tail short stroke</summary>
		static constexpr auto RM_SU_P_GAP_OFFS_TAIL_SS4 = "RM_SU_P_GAP_OFFS_TAIL_SS4";
		///<summary>Pass strip temperature in roll gap</summary>
		static constexpr auto RM_SU_P_GAP_STRIP_TEMP = "RM_SU_P_GAP_STRIP_TEMP";
		///<summary>Pass Hstand active during pass</summary>
		static constexpr auto RM_SU_P_HSTAND_WORKING = "RM_SU_P_HSTAND_WORKING";
		///<summary>Pass oil film offset applied to gap</summary>
		static constexpr auto RM_SU_P_OIL_FILM_OFFSET = "RM_SU_P_OIL_FILM_OFFSET";
		///<summary>Pass area in / area out at edger to stand</summary>
		static constexpr auto RM_SU_P_RFACTOR_EDGER = "RM_SU_P_RFACTOR_EDGER";
		///<summary>Pass area in / area out at horizontal stand</summary>
		static constexpr auto RM_SU_P_RFACTOR_RM = "RM_SU_P_RFACTOR_RM";
		///<summary>Pass predicted roll gap force</summary>
		static constexpr auto RM_SU_P_ROLL_GAP_FORCE_PRED = "RM_SU_P_ROLL_GAP_FORCE_PRED";
		///<summary>Pass roll peripheral speed ref run</summary>
		static constexpr auto RM_SU_P_ROLL_SPREF_RUN = "RM_SU_P_ROLL_SPREF_RUN";
		///<summary>Pass roll peripheral speed ref tailout</summary>
		static constexpr auto RM_SU_P_ROLL_SPREF_TAILOUT = "RM_SU_P_ROLL_SPREF_TAILOUT";
		///<summary>Pass roll peripheral speed ref thread</summary>
		static constexpr auto RM_SU_P_ROLL_SPREF_THREAD = "RM_SU_P_ROLL_SPREF_THREAD";
		///<summary>Pass stand gap reference</summary>
		static constexpr auto RM_SU_P_STAND_GAP_REF = "RM_SU_P_STAND_GAP_REF";
		///<summary>Pass stretch curve width component</summary>
		static constexpr auto RM_SU_P_STRETCH_CURVE_W_COMP = "RM_SU_P_STRETCH_CURVE_W_COMP";
		///<summary>Pass predicted strip forward slip</summary>
		static constexpr auto RM_SU_P_STRIP_FWD_SLIP = "RM_SU_P_STRIP_FWD_SLIP";
		///<summary>Pass predicted strip run speed</summary>
		static constexpr auto RM_SU_P_STRIP_RUN_SPEED_PRED = "RM_SU_P_STRIP_RUN_SPEED_PRED";
		///<summary>Pass strip tension edger to stand</summary>
		static constexpr auto RM_SU_P_STRIP_TENSION_EDGER = "RM_SU_P_STRIP_TENSION_EDGER";
		///<summary>Pass thickness reduction</summary>
		static constexpr auto RM_SU_P_THICKN_REDUCTION = "RM_SU_P_THICKN_REDUCTION";
		///<summary>Pass total gap offset applied</summary>
		static constexpr auto RM_SU_P_TOTAL_GAP_OFFSET = "RM_SU_P_TOTAL_GAP_OFFSET";
		///<summary>Pass width control sensitivity parameter</summary>
		static constexpr auto RM_SU_P_WIDTH_CTRL_SENS = "RM_SU_P_WIDTH_CTRL_SENS";
		///<summary>Primary entry descaling selected</summary>
		static constexpr auto RM_SU_PRIM_ENTRY_DESC_ON = "RM_SU_PRIM_ENTRY_DESC_ON";
		///<summary>Primary exit descaling selected</summary>
		static constexpr auto RM_SU_PRIM_EXIT_DESC_ON = "RM_SU_PRIM_EXIT_DESC_ON";
		///<summary>Ski-Up Constant</summary>
		static constexpr auto RM_SU_SKIUP_CONST1 = "RM_SU_SKIUP_CONST1";
		///<summary>Ski-Up Constant</summary>
		static constexpr auto RM_SU_SKIUP_CONST2 = "RM_SU_SKIUP_CONST2";
		///<summary>Ski-Up Constant</summary>
		static constexpr auto RM_SU_SKIUP_CONST3 = "RM_SU_SKIUP_CONST3";
		///<summary>Ski-Up Constant</summary>
		static constexpr auto RM_SU_SKIUP_CONST4 = "RM_SU_SKIUP_CONST4";
		///<summary>Slab length used by model</summary>
		static constexpr auto RM_SU_SLAB_LENGTH = "RM_SU_SLAB_LENGTH";
		///<summary>Slab thickness used by model</summary>
		static constexpr auto RM_SU_SLAB_THICKNESS = "RM_SU_SLAB_THICKNESS";
		///<summary>Slab width used by model</summary>
		static constexpr auto RM_SU_SLAB_WIDTH = "RM_SU_SLAB_WIDTH";
		///<summary>0=model default, X=Desired number of passes in RM1</summary>
		static constexpr auto RM1_PASS_NO = "RM1_PASS_NO";
		///<summary>0=model default, X=Desired number of passes in RM2</summary>
		static constexpr auto RM2_PASS_NO = "RM2_PASS_NO";
		///<summary>Roll bending force average</summary>
		static constexpr auto ROLL_BENDING_FORCE_AVG = "ROLL_BENDING_FORCE_AVG";
		///<summary>Roll bending force data</summary>
		static constexpr auto ROLL_BENDING_FORCE_DAQ = "ROLL_BENDING_FORCE_DAQ";
		///<summary>Roll crown</summary>
		static constexpr auto ROLL_CROWN = "ROLL_CROWN";
		///<summary>Roll crown max</summary>
		static constexpr auto ROLL_CROWN_MAX = "ROLL_CROWN_MAX";
		///<summary>Roll crown min</summary>
		static constexpr auto ROLL_CROWN_MIN = "ROLL_CROWN_MIN";
		///<summary>Roll diameter</summary>
		static constexpr auto ROLL_DIAMETER = "ROLL_DIAMETER";
		///<summary>End rolling date & time</summary>
		static constexpr auto ROLL_END_TIME = "ROLL_END_TIME";
		///<summary>Roll force average</summary>
		static constexpr auto ROLL_FORCE_AVG = "ROLL_FORCE_AVG";
		///<summary>Roll force data</summary>
		static constexpr auto ROLL_FORCE_DAQ = "ROLL_FORCE_DAQ";
		///<summary>Roll gap average</summary>
		static constexpr auto ROLL_GAP_AVG = "ROLL_GAP_AVG";
		///<summary>Roll gap data</summary>
		static constexpr auto ROLL_GAP_DAQ = "ROLL_GAP_DAQ";
		///<summary>Roll kind (E, W or B)</summary>
		static constexpr auto ROLL_KIND = "ROLL_KIND";
		///<summary>Roll location (RM1, RM2, F1..F7)</summary>
		static constexpr auto ROLL_LOCATION = "ROLL_LOCATION";
		///<summary>Roll position (TOP, BTM, OS, DS)</summary>
		static constexpr auto ROLL_POS = "ROLL_POS";
		///<summary>Roll material e.g. 01=Iron</summary>
		static constexpr auto ROLL_QUALITY = "ROLL_QUALITY";
		///<summary>Roll Set Id</summary>
		static constexpr auto ROLL_SET_ID = "ROLL_SET_ID";
		///<summary>Roll shift position average</summary>
		static constexpr auto ROLL_SHIFT_POS_AVG = "ROLL_SHIFT_POS_AVG";
		///<summary>Roll shift position data</summary>
		static constexpr auto ROLL_SHIFT_POS_DAQ = "ROLL_SHIFT_POS_DAQ";
		///<summary>Roll speed average</summary>
		static constexpr auto ROLL_SPEED_AVG = "ROLL_SPEED_AVG";
		///<summary>Roll speed data</summary>
		static constexpr auto ROLL_SPEED_DAQ = "ROLL_SPEED_DAQ";
		///<summary>Start rolling date & time</summary>
		static constexpr auto ROLL_START_TIME = "ROLL_START_TIME";
		///<summary>Roll taper value</summary>
		static constexpr auto ROLL_TAPER = "ROLL_TAPER";
		///<summary>Roll Type e.g. 02=Parabolic</summary>
		static constexpr auto ROLL_TYPE = "ROLL_TYPE";
		///<summary>Active crew when material rolled</summary>
		static constexpr auto ROLLING_CREW = "ROLLING_CREW";
		///<summary>Instruction for operator for special handling of the material</summary>
		static constexpr auto ROLLING_INSTRUCTION = "ROLLING_INSTRUCTION";
		///<summary>Rolling Schedule. For reference only</summary>
		static constexpr auto ROLLING_SCHEDULE = "ROLLING_SCHEDULE";
		///<summary>Active shift when material rolled</summary>
		static constexpr auto ROLLING_SHIFT = "ROLLING_SHIFT";
		///<summary>Pass rolling time (time when material is being processed)</summary>
		static constexpr auto ROLLING_TIME = "ROLLING_TIME";
		///<summary>0=No sample, 1=sample</summary>
		static constexpr auto SAMPLE_FLAG = "SAMPLE_FLAG";
		///<summary>Sample identity</summary>
		static constexpr auto SAMPLE_ID = "SAMPLE_ID";
		///<summary>Model setup status</summary>
		static constexpr auto SETUP_STATUS = "SETUP_STATUS";
		///<summary>Slab length actual (meas or pdi)</summary>
		static constexpr auto SLAB_LENGTH_ACT = "SLAB_LENGTH_ACT";
		///<summary>Slab length measured</summary>
		static constexpr auto SLAB_LENGTH_MEAS = "SLAB_LENGTH_MEAS";
		///<summary>Slab temperature actual</summary>
		static constexpr auto SLAB_TEMP_ACT = "SLAB_TEMP_ACT";
		///<summary>Slab weight actual (meas or pdi)</summary>
		static constexpr auto SLAB_WEIGHT_ACT = "SLAB_WEIGHT_ACT";
		///<summary>Slab weight measured</summary>
		static constexpr auto SLAB_WEIGHT_MEAS = "SLAB_WEIGHT_MEAS";
		///<summary>Slab width actual (meas or pdi)</summary>
		static constexpr auto SLAB_WIDTH_ACT = "SLAB_WIDTH_ACT";
		///<summary>Slab width measured</summary>
		static constexpr auto SLAB_WIDTH_MEAS = "SLAB_WIDTH_MEAS";
		///<summary>Stand descaler ON</summary>
		static constexpr auto STAND_DESCALER_ON = "STAND_DESCALER_ON";
		///<summary>External designation of material</summary>
		static constexpr auto STEEL_TYPE = "STEEL_TYPE";
		///<summary>Strip tension (entry) average</summary>
		static constexpr auto STRIP_TENSION_AVG = "STRIP_TENSION_AVG";
		///<summary>Strip tension (entry) data</summary>
		static constexpr auto STRIP_TENSION_DAQ = "STRIP_TENSION_DAQ";
		///<summary>Material thickness reduction</summary>
		static constexpr auto THICKNESS_REDUCTION = "THICKNESS_REDUCTION";
		///<summary>Total rolling time (time when material is being processed)</summary>
		static constexpr auto TOT_ROLLING_TIME = "TOT_ROLLING_TIME";
		///<summary>Stand working (1=WST)</summary>
		static constexpr auto WORKING_STAND = "WORKING_STAND";
	};
#pragma endregion

#pragma endregion

#pragma region  MES 相关常量
	namespace mes_message {


#pragma region 响应报文
		//响应报文总长均为110
		constexpr auto  MSG_RESPONSE_LENGTH = "0110";
		constexpr auto  TEXT_FIELD_LENGTH = 80;

		// 响应电文控制域
		constexpr auto  REP_VALIDITY_CODE = 'A'; //电文发送成功
		constexpr auto  REP_INVALIDITY_CODE = 'B';
#pragma endregion

#pragma region 电文字段长度定义

		/**
		* 电文字段长度定义
		*/

		//最大允许电文长度
		constexpr auto MAX_BYTES_ALLOWED = 3000;
		constexpr auto MIN_BYTES_ALLOWED = 8;


		//电文头
		constexpr auto HEADER_LENGTH = 29;

		constexpr auto LENGTH_POS = 0;
		constexpr auto LENGTH_LEN = 4;

		//电文号
		constexpr auto IDENTITY_POS = 4;
		constexpr auto IDENTITY_LEN = 6;

		constexpr auto DATESEND_POS = 10;
		constexpr auto DATESEND_LEN = 8;

		constexpr auto TIMESEND_POS = 18;
		constexpr auto TIMESEND_LEN = 6;

		constexpr auto SENDER_POS = 24;
		constexpr auto SENDER_LEN = 2;

		constexpr auto RECEIVER_POS = 26;
		constexpr auto RECEIVER_LEN = 2;

		constexpr auto FUNCCODE_POS = 28;
		constexpr auto FUNCCODE_LEN = 1;

		constexpr auto GENERATETIME_POS = 29;
		constexpr auto GENERATETIME_LEN = 17;

		constexpr auto ENDCODE_LEN = 1;
		constexpr auto END_BYTE = 0x0a;

#pragma endregion

		/// <summary>
		///  List types enumaration used in Alignment Class
		/// </summary>
		enum ListTypesEnum { ProductionScheduleList = 1, GhostScheduleList = 2 };


		enum OperateType
		{
			ORDER_INSERT_UPATE = 1, /*删除操作*/
			ORDER_DELETE = 9 /*更新或新增操作*/
		};

		enum OperationTypeEnum { InsertCmd = 0, UpdateCmd, DeleteCmd, L2DeleteCmd, SchedCancelCmd };
		//删除操作
		//constexpr auto  ORDER_DELETE = 9;

		//更新或新增操作
		//constexpr auto  ORDER_INSERT_UPATE = 1;

		enum MsgType {
			ORDER = 1 /*L3订单*/, NEW_ROLL /*新辊数据*/, RECV_ACK /*接收L3发来响应*/, HEART /*接收心跳*/,
			REQUEST_DATA /*向L3请求数据:废弃*/,
			CHARGE_RPT /*装炉报告*/, DISCHARGE_RPT /*出炉报告*/, CANCEL_RPT /*板坯取消*/, PROD_RPT /*产品报告*/,
			SAMPLE_RPT /*采样报告*/, WET_RPT /*称重实绩*/, TRANSPORT_RPT /*运输报告*/, ROLL_CHANGE_RPT /*换辊实绩*/
		};

#pragma region Order Management

		/// <summary>
		///  Produced Order Templates
		/// </summary>
		enum class ReqTemplateEnum { Strip = 101, Plate = 102 };

		/// <summary>
		/// Production Request Types Enum
		/// </summary>
		enum ReqTypesEnum { ProductionOrder = 1, GhostOrder = 2 };

		/// <summary>
		/// 表示TB_PDI中记录是否被删除
		/// </summary>
		enum TB_PDI_RECORD_STATUS { Normal = 1, Abandoned = 2 };

#pragma endregion

		//电文头中的传送功能码
		enum FunctionCode {
			ACKNOLEDGED = 'A'/*电文传送成功*/, NOTACKNOLEDGED = 'B'/*电文传输过程出错*/,
			LIVEMSG = 'C' /*心跳*/, DATAMESSAGE = 'D' /*数据电文*/
		};
	}

#pragma endregion

#pragma region Tracking Manager
	namespace tm_message
	{
		/// <summary>
		/// 通用参数
		/// </summary>
		struct GeneralRefer
		{
			//电文ID
			int identify;
			int passNo;
			// 一般为自增主键ID
			ID_TYPE id;
			std::string itemName;
		};

		/// TMMEssage 定义存储数据类型
		/// </summary>
		using tm_map_type = std::unordered_map<std::string, std::string>;


		/// <summary>
		/// 缓存ComInfo信息
		/// </summary>
		//using tm_comInfo_map_type = std::unordered_map<std::string, ComInfo>;



		/// <summary>
		/// Setup Models Ghost Mode Enum
		/// </summary>
		enum SetupModelsGhostModesEnum { None_ = 0, RM_ = 1, FM_ = 2, Coiler_ = 4, All_ = 7 };

		/// <summary>
		/// Setup Models Request Types Enum
		/// </summary>
		enum SetupModelsRequestEnum { Test = 1, NextToExtract = 2, Extract = 3, PDIRequestResponse = 4 };



		/// <summary>
		/// Tracking Manager PDIData operations (I = Add/Change, D = Delete and F = Finish)
		/// </summary>
		enum TMPDIOperationEnum { I, D, F };

		/// <summary>
		/// Route definitions used by Tracking Manager
		/// </summary>
		enum TrackRoutesEnum { Strip = 1, Plate = 2, GhostStrip = 91, GhostPlate = 92 };

		/// <summary>
		///  Return Types sent by TM
		/// </summary>
		enum TMPDIVerificationCodeEnum { I_, R_, A_ };

		/// <summary>
		/// Tracking Manager Segment Request events
		/// </summary>
		enum TMSegReqEventEnum { RequestOrder = 1, Rejected = 2, ProductionStarted = 20, Finished = 90, ForcedDelete = 97 };


		/// <summary>
		/// 接受TM电文类型 identify
		/// </summary>
		enum TMMessageType
		{
			PDIMsgForStripAck = 1011020,
			PDIMsgForPlateAck = 1021020,
			SegReqEvent = 1031,
			TrackingZoneEvent = 7001,
			FCEEntryPDLog = 5018001,
			FCEChargePDLog = 5118001,
			FCENextDischargePDLog = 5138001,
			FCEDischargePDLog = 5158001,
			DescalerPDLog = 5218001,
			RM1RollStartPDLog = 5318001,
			RM1RollEndPDLog = 5348001,
			RM1PassPDLog = 5418001,
			RM1PassEndPDLog = 5448001,
			RM2RollStartPDLog = 5518001,
			RM2RollEndPDLog = 5548001,
			RM2PassPDLog = 5618001,
			RM2PassEndPDLog = 5648001,
			CBOXPDLog = 5718001,
			CSHeadPDLog = 5818001,
			CSTailPDLog = 5848001,
			FMEntryPDLog = 6018001,
			FMStand1PDLog = 6118001,
			FMStand2PDLog = 6128001,
			FMStand3PDLog = 6138001,
			FMStand4PDLog = 6148001,
			FMStand5PDLog = 6158001,
			FMStand6PDLog = 6168001,
			FMStand7PDLog = 6178001,
			FMExitPDLog = 6198001,
			DCCoilStartPDLog = 6318001,
			DCCoilEndPDLog = 6348001,
			FINCoilSamplePDLog = 7018001,
			FINCoilWeightPDLog = 7038001,
			FINProdEndPDLog = 7058001
		};

#pragma region TMMessagePDLog

		/// <summary>
		/// 数据类型映射
		/// </summary>
		static std::unordered_map<std::string, int> DataTypeStrIntMap =
		{
			{"I",1},
			{"R",2},
			{"T",3},
			{"D",4},
		};


#pragma endregion


#pragma region PDIMsgForStrip/Plate

		static std::unordered_map<int, std::string> PDIMsgForStripAckMap = {
		{0,"ROLLING_ORDER_ID"},
		{1,"PROD_SEQ_NO"},
		{2,"PROD_MAT_TYPE"},
		{3,"SLAB_ID"},
		{4,"SLAB_LENGTH"},
		{5,"SLAB_WIDTH"},
		{6,"SLAB_WEIGHT_CALC"},
		{7,"COIL_DEST_AREA"},
		{8,"SAMPLE_FLAG"},
		{9,"SAMPLE_ID"},
		{10,"EXTRA_STRAPS_NO"},
		{11,"SLAB_THICKNESS"},
		{12,"GRADE"},
		{13,"HEATNO"},
		{14,"HOT_CHARGING"},
		{15,"DISCHARGE_TEMP_AIM"},
		};


		static std::unordered_map<int, std::string> PDIMsgForPlateAckMap = {
			{0,"ROLLING_ORDER_ID"},
			{1,"PROD_SEQ_NO"},
			{2,"PROD_MAT_TYPE"},
			{3,"SLAB_ID"},
			{4,"SLAB_LENGTH"},
			{5,"SLAB_WIDTH"},
			{6,"SLAB_WEIGHT_CALC"},
			{7,"SLAB_THICKNESS"},
			{8,"GRADE"},
			{9,"HEATNO"},
			{10,"HOT_CHARGING"},
			{11,"DISCHARGE_TEMP_AIM"},
		};


#pragma endregion

		static std::unordered_map<std::string, int> ZoneName_Value = {

			//Virtual Zone for canceling remaining slabs in a schedule
			{"SLABSTORAGEY1" , 1000},
			//Virtual Zone for canceling remaining slabs in a schedule
			{"SLABSTORAGEY2" , 2000},

			// Real tracking zones
			{"SY" ,             11000}                       ,
			{"SYGR" ,          12000   }                       ,
			{"FUENW" ,         31000    }                       ,
			{"FU3ENRT" ,       32000      }                       ,
			{"FU2ENRT" ,       35000      }                       ,
			{"FU1ENRT" ,       38000      }                       ,
			{"FU3" ,           33000  }                       ,
			{"FU2" ,           36000  }                       ,
			{"FU1" ,           39000  }                       ,
			{"FRRT" ,          41000   }                       ,
			{"FU3EXRT" ,       42000      }                       ,
			{"FU2EXRT" ,       43000      }                       ,
			{"FU1EXRT" ,       44000      }                       ,
			{"RM1EN" ,         45000    }                       ,
			{"RM1" ,           46000  }                       ,
			{"RM1EX" ,         47000    }                       ,
			{"RM2EN" ,         48000    }                       ,
			{"RM2" ,           49000  }                       ,
			{"RM2EX" ,         50000    }                       ,
			{"STC" ,           51000  }                       ,
			{"FMCB " ,         52000    }                       ,
			{"FMEN " ,         53000    }                       ,
			{"FM" ,            54000 }                       ,
			{"ROT" ,           55000  }                       ,
			{"DC1ENRT" ,       56000      }                       ,
			{"DC1" ,           57000  }                       ,
			{"CH1CC1" ,        58000     }                       ,
			{"CH1CBM" ,        59000     }                       ,
			{"CH1CC2" ,        60000     }                       ,
			{"DCH1CCV" ,       61000      }                       ,
			{"DC2ENRT" ,       63000      }                       ,
			{"DC2" ,           64000  }                       ,
			{"CH2CC1" ,        65000     }                       ,
			{"CH2CBM" ,        66000     }                       ,
			{"CH2CC2" ,        67000     }                       ,
			{"DCH2CCV" ,       68000      }                       ,
			{"DC3ENRT" ,       70000      }                       ,
			{"DC3" ,           71000  }                       ,
			{"CH3CC1" ,        72000     }                       ,
			{"CH3CBM" ,        73000     }                       ,
			{"CH3CC2" ,        74000     }                       ,
			{"DCH3CCV" ,       75000      }                       ,
			{"WB1" ,           77000  }                       ,
			{"CLD" ,           78000  }                       ,
			{"IST" ,           79000  }                       ,
			{"WB2" ,           81000  }                       ,
			{"WB3" ,           82000  }                       ,
			{"CTS1" ,          84000   }                       ,
			{"WB4" ,           85000  }                       ,
			{"CTS2" ,          87000   }                       ,
			{"WB7" ,           89000  }                       ,
			{"CTS4" ,          91000   }                       ,
			{"WB6" ,           93000  }                       ,
			{"CTS3" ,          95000             }                       ,
		};

		enum ZonesEnum
		{
			///<summary>
			/// Virtual Zone for canceling remaining slabs in a schedule
			/// 用于取消计划中剩余板的虚拟区域
			///</summary>
			SLABSTORAGEY1 = 1000,
			///<summary>
			/// Virtual Zone for canceling individule slabs
			///</summary>
			SLABSTORAGEY2 = 2000,

			// Real tracking zones
			SY = 11000,
			SYGR = 12000,
			FUENW = 31000,
			FU3ENRT = 32000,
			FU2ENRT = 35000,
			FU1ENRT = 38000,
			FU3 = 33000,
			FU2 = 36000,
			FU1 = 39000,
			FRRT = 41000,
			FU3EXRT = 42000,
			FU2EXRT = 43000,
			FU1EXRT = 44000,
			RM1EN = 45000,
			RM1 = 46000,
			RM1EX = 47000,
			RM2EN = 48000,
			RM2 = 49000,
			RM2EX = 50000,
			STC = 51000,
			FMCB = 52000,
			FMEN = 53000,
			FM = 54000,
			ROT = 55000,
			DC1ENRT = 56000,
			DC1 = 57000,
			CH1CC1 = 58000,
			CH1CBM = 59000,
			CH1CC2 = 60000,
			DCH1CCV = 61000,
			DC2ENRT = 63000,
			DC2 = 64000,
			CH2CC1 = 65000,
			CH2CBM = 66000,
			CH2CC2 = 67000,
			DCH2CCV = 68000,
			DC3ENRT = 70000,
			DC3 = 71000,
			CH3CC1 = 72000,
			CH3CBM = 73000,
			CH3CC2 = 74000,
			DCH3CCV = 75000,
			WB1 = 77000,
			CLD = 78000,
			IST = 79000,
			WB2 = 81000,
			WB3 = 82000,
			CTS1 = 84000,
			WB4 = 85000,
			CTS2 = 87000,
			WB7 = 89000,
			CTS4 = 91000,
			WB6 = 93000,
			CTS3 = 95000
		};

		enum TMPDIReturnCodes
		{
			OK = 888,

		};

		/// <summary>
		/// 存储物料状态信息
		/// </summary>
		struct TMInfo
		{
			int EventType;  /*What happened in TM : Entry = 1, Exit = 2, Remove = 3, Insert = 4. See enum TrackEvent*/
			int TMStatus;
			int ItemType;
			int Gate;
			std::string ZoneName;
			std::string Item;
			std::string TimeStamp;
			std::string OtherEvent;
		};

		/// <summary>
		/// Tracking Manager Remove Reasons
		/// </summary>
		enum TrackRemoveReason { PickOutList_ = 1, Scrapped_ = 8, Finished_ = 9 };


		/// <summary>
		/// Tracking Manager Tracking Event
		/// </summary>
		enum TrackEvent { Idle = 0, Entry = 1, Exit = 2, Remove = 3, Insert = 4 };


		/// <summary>
		/// Type of items			
		/// </summary>
		enum ItemTypeEnum { ProductionRequest = 0, Material = 1, SubMaterial = 2 };
	}
#pragma endregion

#pragma region 跟踪状态迁移

	struct OrderStateTypes
	{
		//OrderIsDraft = 1,//MES下发后，二级先数据有效值校验
		//OrderIsReleased = 2,//二级DRAFT 验证变为此状态，发给TM服务器
		//OrderIsDispatched,//TM给二级反馈是否接收成功，（譬如TM检测到卷号重复，返回false）;
		//OrderInProduction, //已核对（在称重处）
		//OrderIsStopped,//轧线休止
		//OrderIsFinished//轧制成功
		static constexpr auto  OrderIsDraft = "DRAFT";//MES下发后，二级先数据有效值校验
		static constexpr auto  OrderIsReleased = "RLS";//二级DRAFT 验证变为此状态，发给TM服务器
		static constexpr auto  OrderIsDispatched = "DSPT";//TM给二级反馈是否接收成功，（譬如TM检测到卷号重复，返回false）;
		static constexpr auto  OrderInProduction = "PRD"; //已核对（在称重处）接收TM发SegReqEvent
		static constexpr auto  OrderIsStopped = "STOPPED";//轧线休止
		static constexpr auto  OrderIsFinished = "FIN";//轧制成功
	};

	enum OrderStatesEnum { OrderIsDraft = 1, OrderIsReleased = 3, OrderIsDispatched, OrderInProduction, OrderIsStopped, OrderIsFinished };

	enum SubStatesEnum
	{
		//BtwRM1RM2 added for ghost rolling, so more mtrl can be in mill
		AsInitial = 0, IsCharged = 1, IsNextToDischarge = 2, IsDischarged = 4, InRM1Rolling = 8,
		InRM2Rolling = 16, InFMRolling = 32, IsRolled = 128, IsCompleted = 256, IsRejected = 512
	};

#pragma endregion

#pragma region Roll Management
	namespace roll_management
	{
		/// <summary>
		/// Roll Locations i.e. equipment names for parent equipments for rolls
		/// managed by Roll Management Service:</summary>
		enum RollLocationsEnum
		{
			E1OSR_LOC, E1DSR_LOC, R1TWR_LOC, R1BWR_LOC,
			E2OSR_LOC, E2DSR_LOC, R2TBR_LOC, R2TWR_LOC, R2BWR_LOC, R2BBR_LOC,
			F1TBR_LOC, F1TWR_LOC, F1BWR_LOC, F1BBR_LOC,
			F2TBR_LOC, F2TWR_LOC, F2BWR_LOC, F2BBR_LOC,
			F3TBR_LOC, F3TWR_LOC, F3BWR_LOC, F3BBR_LOC,
			F4TBR_LOC, F4TWR_LOC, F4BWR_LOC, F4BBR_LOC,
			F5TBR_LOC, F5TWR_LOC, F5BWR_LOC, F5BBR_LOC,
			F6TBR_LOC, F6TWR_LOC, F6BWR_LOC, F6BBR_LOC,
			F7TBR_LOC, F7TWR_LOC, F7BWR_LOC, F7BBR_LOC
		};


		/// <summary>
		/// Roll Templates:
		/// For Rolls managed by Roll Management Service:</summary>
		enum RollTemplatesEnum { RMER, RMBR, RMWR, FMBR, FMWR };


		/// <summary>
		/// Equipment States:
		/// </summary>
		enum RollStatesEnum { NoState, StandBy, InMill };

		/// <summary>
		/// Equipment Types:
		/// </summary>
		enum EquipmentTypesEnum
		{
			RouteEquipment = 1,
			EOMEquipment = 2,
			RollEquipment = 4
		};

	}
#pragma endregion

#pragma region Model Manger

	namespace model
	{


#pragma region 电文信息
		constexpr auto MDS_CALC_ID = 202;

		/// <summary>
		/// 消息长度信息
		/// </summary>
		constexpr auto  MSG_LEN_POS = 0;
		constexpr auto  MSG_LEN_LEN = 2;

		/// <summary>
		/// 消息id信息
		/// </summary>
		constexpr auto  MSG_ID_POS = 2;
		constexpr auto  MSG_ID_LEN = 2;

		/// <summary>
		/// 计数器信息
		/// </summary>
		constexpr auto  MSG_CTR_POS = 4;
		constexpr auto  MSG_CTR_LEN = 8;

#pragma endregion

		/// <summary>
		/// Setup Models Request Types Enum
		/// </summary>
		enum SetupModelsRequestEnum { Test = 1, NextToExtract = 2, Extract = 3, PDIRequestResponse = 4 };

		/// <summary>
		/// Setup Models Ghost Mode Enum
		/// </summary>
		enum SetupModelsGhostModesEnum { None = 0, RM = 1, FM = 2, Coiler = 4, All = 7 };
	}

#pragma endregion

#pragma region 通道名称定义

	enum SendType
	{
		ToChannel = 1, /*socket通信*/
		ToIPC = 2  /*进程间通信*/
	};

	namespace L3Net
	{
		constexpr auto RECV_L3_CHANNEL = "L3MLChannel";
		constexpr auto SEND_L3_CHANNEL = "MLL3Channel";
	}

	namespace ModelNet
	{
		constexpr auto RECV_MDS1_CHANNEL = "MDS1L2Channel";
		constexpr auto RECV_MDS2_CHANNEL = "MDS2L2Channel";
		constexpr auto SEND_MDS1_CHANNEL = "L2MDS1Channel";
		constexpr auto SEND_MDS2_CHANNEL = "L2MDS2Channel";

		namespace mds1
		{
			constexpr auto LocalIpAddress = "172.28.4.152";
			constexpr auto RemoteIpAddress = "172.28.4.184";
			constexpr auto Port = 5501;
		}

		namespace mds2
		{
			constexpr auto LocalIpAddress = "172.28.4.152";
			constexpr auto RemoteIpAddress = "172.28.4.185";
			constexpr auto Port = 5501;
		}
	}

	namespace L1VipNet
	{


#pragma region 地址信息

		constexpr auto MESL1FCEChannel = "MESL1FCEChannel";
		constexpr auto MESL1RM1Channel = "MESL1RM1Channel";
		constexpr auto MESL1RM2Channel = "MESL1RM2Channel";
		constexpr auto MESL1FMChannel = "MESL1FMChannel";
		constexpr auto MESL1DCChannel = "MESL1DCChannel";

#pragma endregion


#pragma region 电文信息

		/// <summary>
		/// The header length.
		/// </summary>
		constexpr auto HEADER_LENGHT = 4;

		/// <summary>
		/// The position in a message where the length is stored.
		/// </summary>
		constexpr auto LENGTH_POS = 0;
		constexpr auto LENGTH_LEN = 2;

		/// <summary>
		/// The position in a message where the identity is stored.
		/// </summary>
		constexpr auto IDENTITY_POS = 2;
		constexpr auto IDENTITY_LEN = 2;


		/// <summary>
		/// 有关RM1换辊、磨损消息号
		/// </summary>
		enum RM1MessageType
		{
			L1_PS21_ALIVE = 101,
			START_GHOST_ROLLING = 102,
			RM1_ROLL_CHANGE = 104,
			RM1_ROLL_WEAR = 105,
			FCE_DISCHARGE = 106
		};

		enum FCEMessageType
		{
			L1_FCE_CONSUMABLES = 1801,
			L2_ALIVE_FCE = 1802
		};

		enum RM2MessageType
		{
			L1_PS31_ALIVE = 101,
			RM2_ROLL_CHANGE = 103,
			RM2_ROLL_WEAR = 104,
			MILL_STOP = 105,
			L2_ALIVE_PS31 = 201
		};

		enum FMMessageType
		{
			L1_PS42_ALIVE = 101,
			FM1_ROLL_CHANGE = 103,
			FM2_ROLL_CHANGE = 104,
			FM3_ROLL_CHANGE = 105,
			FM4_ROLL_CHANGE = 106,
			FM5_ROLL_CHANGE = 107,
			FM6_ROLL_CHANGE = 108,
			FM7_ROLL_CHANGE = 109,
			FM_ROLL_WEAR = 110
		};

		enum DCMessageType
		{
			L1_PS67_ALIVE = 101
		};


#pragma endregion

	}

#pragma endregion

#pragma region 数据库相关定义

	/*************************************************************************
	*
	* 数据库相关定义
	*
	*************************************************************************/

	struct DBinfo
	{
		std::string service_name_;
		std::string user_;
		std::string pwd_;
		unsigned int min_;
		// 我们服务器一般配置：core_count = 2（物理cpu数量）*16 （cpu 核数）， effective_spindle_count=5
		//connections = ((core_count * 2) + effective_spindle_count:RAID数量)
		unsigned int max_;
	};

#pragma region 二级相关数据库

	namespace L2DB
	{

		/// <summary>
		/// L2 Oracle数据库的连接文件名
		/// </summary>
		constexpr auto L2UDL_NAME = "DBA.UDL";
		constexpr auto L2_DB_NAME = "nercar";
		constexpr auto L2_DB_USERNAME = "scc";
		constexpr auto L2_DB_PWD = "scc";
		//constexpr auto L2UDL_NAME = "C:\\ProjectItem\\QianGang\\Config\\DBA.UDL";

		//static DBinfo l2_db_info{ false,L2_DB_NAME,L2_DB_USERNAME,L2_DB_PWD,5,2 * 16 + 5 };

		//链接分配方案，平均分配每个进程
		static DBinfo l2_db_info{ L2_DB_NAME,L2_DB_USERNAME,L2_DB_PWD,5,5 * 16 + 5 };
	}

#pragma endregion

#pragma region TM 相关数据库

	namespace TMDB
	{
		constexpr auto TM_UDL_NAME = "TM_DBA.UDL";
		constexpr auto TM_DB_NAME = "rmc_db";
		constexpr auto TM_DB_USERNAME = "rm_ext";
		constexpr auto TM_DB_PWD = "rm_ext";

		constexpr auto TO_TM_TABLE = "rm_ext.msgtoabbtrack_tab";
		constexpr auto FROM_TM_TABLE = "rm_ext.msgfromabbtrack_tab";
		constexpr auto TO_TM_SEQ = "rm_ext.msgtoabbtrack_seq.nextval";
		constexpr auto FROM_TM_SEQ = "msgfromabbtrack_seq.nextval";

		static DBinfo tm_db_info{ TM_DB_NAME,TM_DB_USERNAME,TM_DB_PWD,2,8 };
	}

#pragma endregion

#pragma region 消息结构相关定义

	/*************************************************************************
	*
	* 消息结构相关定义
	*
	*************************************************************************/

	using data_type = void*;
	using addr_number_type = int32_t;

	constexpr auto IP_LEN = 16;
	constexpr auto TABLE_NAME_LEN = 50;
	constexpr auto CONN_INFO_LEN = 128;
	constexpr auto SPARE_LEN = 128;
	/// <summary>
	/// 地址信息
	/// </summary>
	struct addr_info
	{
		/******* socket ***********/
		addr_number_type	  port_;
		char				  ip_[IP_LEN];

		/******* db ***********/
		char		          table_name_[TABLE_NAME_LEN]; /*表名*/
		char		          conn_info_[CONN_INFO_LEN];	   /*连接信息*/
		char		          spare_[SPARE_LEN];	   /*预留*/
	};
#pragma endregion

#pragma region TB_PDI 表定义
	constexpr auto PDI_TIME_LEN = 14;
#pragma endregion

#pragma endregion
}

/// <summary>
/// 通用事件定义
/// </summary>
namespace event_define
{
	/// <summary>
	/// 状态改变事件
	/// </summary>
	using  PRStateChangeOccuredEventHandler = std::function<void(shared_define::ID_TYPE id)>;

	/// <summary>
	/// 数据改变事件
	/// </summary>
	using  PRDataChangeOccuredEventHandler = std::function<void(shared_define::ID_TYPE id, int opType)>;

	/// <summary>
	/// 准备TM PDI数据事件
	/// </summary>
	using  TMPDIDataReadyEventHandler = std::function<void(std::string matId, int opCode)>;


	using  RecvTMMessageEventHandler = std::function<void(std::string header, std::string body)>;
}

#endif