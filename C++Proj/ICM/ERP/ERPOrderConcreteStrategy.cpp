#include "ERPOrderConcreteStrategy.h"
#include "tm_l2_struct.h"
#include "StateUtility.hpp"
#include "RequestUtility.hpp"
ERPOrderConcreteStrategy::~ERPOrderConcreteStrategy()
{
	m_log << end_t;
}

ERPOrderConcreteStrategy::ERPOrderConcreteStrategy() :m_log(__FUNCTION__)
{
}

void ERPOrderConcreteStrategy::PreProcessMsgData(void* datas, shared_define::mes_message::ReqTemplateEnum orderType)
{
	int use_analysis_flag = 0; /*默认使用本地化学成分*/
	auto pdi_data = static_cast<mes_l2_msg_define::L3ML01*>(datas);

	std::string slabId;
	std::string steelGrade;
	int  isvalid = 1; //0:L3级下发计划关键字段校验失败，1：关键字段校验成功
	std::string error_info; // 错误原因

	try
	{
		//考虑去除首位空格
		slabId.assign(pdi_data->SLAB_ID, sizeof(pdi_data->SLAB_ID));
		uni_box::utils::trimBlank(slabId);
		steelGrade.assign(pdi_data->STEEL_GRADE, sizeof(pdi_data->STEEL_GRADE));
		uni_box::utils::trimBlank(steelGrade);


#pragma region Replace tolerance with factory std && 关键字段校验

		float tgtThickness = uni_box::utils::parseStringToNumber<float>(pdi_data->FM_EXIT_THICKN_AIM, "000.000");
		float tgtWidth = uni_box::utils::parseStringToNumber<float>(pdi_data->FM_EXIT_WIDTH_AIM, "0000.0");
		float tgtFlat = uni_box::utils::parseStringToNumber<float>(pdi_data->FM_EXIT_FLATNESS_AIM, "0000");
		m_log << fmt::format("目标厚度:{0},目标宽度:{1},平坦度目标值:{1}", tgtThickness, tgtWidth, tgtFlat).c_str() << end_l;

		float maxThick = uni_box::utils::parseStringToNumber<float>(pdi_data->FM_EXIT_THICKN_MAX, "000.000");
		float minThick = uni_box::utils::parseStringToNumber<float>(pdi_data->FM_EXIT_THICKN_MIN, "000.000");
		m_log << fmt::format("L3下发厚度最值:[{0},{1}]", minThick, maxThick).c_str() << end_l;

		if (maxThick <= minThick)
		{
			ALARM(AL_ERROR, 6299, "校验失败: 厚度最大值:%f  <=  厚度最小值%f", maxThick, minThick);
			isvalid = 0;
			error_info = "厚度最值校验失败";
		}

		float maxWidth = uni_box::utils::parseStringToNumber<float>(pdi_data->FM_EXIT_WIDTH_MAX, "0000.0");
		float minWidth = uni_box::utils::parseStringToNumber<float>(pdi_data->FM_EXIT_WIDTH_MIN, "0000.0");
		m_log << fmt::format("L3下发宽度最值:[{0},{1}]", minWidth, maxWidth).c_str() << end_l;

		if (maxWidth <= minWidth)
		{
			ALARM(AL_ERROR, 6299, "校验失败: 宽度最大值:%f  <=  宽度最小值%f", maxWidth, minWidth);
			isvalid = 0;
			error_info = "宽度最值校验失败";
		}

		auto minFlat = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_FLATNESS_MIN, "0000");
		auto maxFlat = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_FLATNESS_MAX, "0000");
		m_log << fmt::format("L3下发平坦度最值:[{0},{1}]", minFlat, maxFlat).c_str() << end_l;


		auto fm_exit_crown_min = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_CROWN_MIN, "0000");
		auto fm_exit_crown_max = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_CROWN_MAX, "0000");
		m_log << fmt::format("L3下发凸度最值:[{0},{1}]", fm_exit_crown_min, fm_exit_crown_max).c_str() << end_l;
		if (fm_exit_crown_max < fm_exit_crown_min)
		{
			ALARM(AL_ERROR, 6299, "校验失败: 凸度最大值:%f  <  凸度最小值%f", fm_exit_crown_max, fm_exit_crown_min);
			isvalid = 0;
			error_info = "凸度最值校验失败";
		}

		auto fm_exit_temp_aim = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_TEMP_AIM, "0000");
		auto coiling_temp_aim = uni_box::utils::parseStringToNumber<int>(pdi_data->COILING_TEMP_AIM, "0000");

		if (fm_exit_temp_aim < 1)
		{
			ALARM(AL_ERROR, 6299, "校验失败: 终轧目标温度:%d 为0", fm_exit_temp_aim);
			isvalid = 0;
			error_info = " 终轧目标温度为0,校验失败";
		}

		if (coiling_temp_aim < 1)
		{
			ALARM(AL_ERROR, 6299, "校验失败: 层冷目标温度:%d 为0", coiling_temp_aim);
			isvalid = 0;
			error_info = " 层冷目标温度为0,校验失败";
		}


		//: 通过Oracle function 去优化查询
		float tolThickUpper = 0.0f;
		float tolThickLower = 0.0f;
		float tolWidthUpper = 0.0f;
		float tolWidthLower = 0.0f;
		float tolFlatUpper = 0.0f;
		float tolFlatLower = 0.0f;
		int ret = 0;  /*查询结果是否正确*/

		auto conn_nercar = DB::OracleDB::OracleDML::getConnection();

		try
		{
			ocilib::Statement stmt_funct(conn_nercar);
			stmt_funct.Prepare("BEGIN :ret := get_technic(:1, :2, :3, :4, :5, :6, :7, :8, :9); END;");
			stmt_funct.Bind(":1", tgtThickness, ocilib::BindInfo::In);
			stmt_funct.Bind(":2", tgtWidth, ocilib::BindInfo::In);
			stmt_funct.Bind(":3", steelGrade, steelGrade.size(), ocilib::BindInfo::In);
			stmt_funct.Bind(":4", tolThickUpper, ocilib::BindInfo::Out);
			stmt_funct.Bind(":5", tolThickLower, ocilib::BindInfo::Out);
			stmt_funct.Bind(":6", tolWidthUpper, ocilib::BindInfo::Out);
			stmt_funct.Bind(":7", tolWidthLower, ocilib::BindInfo::Out);
			stmt_funct.Bind(":8", tolFlatUpper, ocilib::BindInfo::Out);
			stmt_funct.Bind(":9", tolFlatLower, ocilib::BindInfo::Out);
			stmt_funct.Bind(":ret", ret, ocilib::BindInfo::Out);
			stmt_funct.ExecutePrepared();

			if (ret)
			{
#pragma region thickness
				m_log << fmt::format("本地工艺表中厚度上下限范围:[{0},{1}]", tolThickLower, tolThickUpper).c_str() << end_l;
				//采用公差带小的
				if ((maxThick - minThick) > (tolThickUpper - tolThickLower))
				{
					minThick = tgtThickness + tolThickLower;
					maxThick = tgtThickness + tolThickUpper;
					m_log << fmt::format("采用本地工艺表厚度最值:[{0},{1}]", minThick, maxThick).c_str() << end_l;
				}
#pragma endregion

#pragma region widthness
				m_log << fmt::format("本地工艺表中宽度上下限范围:[{0},{1}]", tolWidthLower, tolWidthUpper).c_str() << end_l;

				//采用公差带小的
				if ((maxWidth - minWidth) > (tolWidthUpper - tolWidthLower))
				{
					minWidth = tgtWidth + tolWidthLower;
					maxWidth = tgtWidth + tolWidthUpper;
					m_log << fmt::format("采用本地工艺表宽度最值:[{0},{1}]", minWidth, maxWidth).c_str() << end_l;
				}
#pragma endregion

#pragma region Flatness
				m_log << fmt::format("本地工艺表中平坦度上下限范围:[{0},{1}]", tolFlatLower, tolFlatUpper).c_str() << end_l;

				//采用公差带小的
				if ((maxFlat - minFlat) > (tolFlatUpper - tolFlatLower))
				{
					minFlat = tgtFlat + tolFlatLower;
					maxFlat = tgtFlat + tolFlatUpper;
					m_log << fmt::format("采用本地工艺表平坦度最值:[{0},{1}]", minFlat, maxFlat).c_str() << end_l;
				}
#pragma endregion
			}
			else
			{
				ALARM(AL_ERROR, 6233, "查询PCS中 TB_TECHNIC 失败!");
			}
		}
		catch (const std::exception& ex)
		{
			ALARM(AL_ERROR, 6235, "查询工艺表失败:%s", ex.what());
		}

#pragma region 废弃查询
		/*auto sel_tol = fmt::format("select THKTOLUP,THKTOLLOW,WIDTOLUP,WIDTOLLOW,FLATDETUP,FLATDETDOWN from tb_technic@lk_pri t "
						"where t.qualitycode = (select q.qualitycode from tb_qualitycode@lk_pri q   where q.steelgrade = '{2}') "
						"and t.coilthkmax > {0} and t.coilthkmin <= {0}  and t.coilwidmax > {1} and t.coilwidmin <= {1}", tgtThickness, tgtWidth, steelGrade);*/
						//m_log << "查询本地公差表" << end_l;
						//m_log << sel_tol.c_str() << end_l;
						//auto res_tol = DB::OracleDB::OracleDML::executeQuery(sel_tol);
						//auto conn_nercar = res_tol.conn_;

		//if (res_tol.rs_.Next())
		//{

		//	tolThickUpper = res_tol.rs_.Get<float>("THKTOLUP");
		//	tolThickLower = res_tol.rs_.Get<float>("THKTOLLOW");
		//	m_log << fmt::format("本地工艺表中厚度上下限范围:[{0},{1}]", tolThickLower, tolThickUpper).c_str() << end_l;

		//	//采用公差带小的
		//	if ((maxThick - minThick) > (tolThickUpper - tolThickLower))
		//	{
		//		minThick = tgtThickness + tolThickLower;
		//		maxThick = tgtThickness + tolThickUpper;
		//		m_log << fmt::format("采用本地工艺表厚度最值:[{0},{1}]", minThick, maxThick).c_str() << end_l;
		//	}

		//	tolWidthUpper = res_tol.rs_.Get<float>("WIDTOLUP");
		//	tolWidthLower = res_tol.rs_.Get<float>("WIDTOLLOW");
		//	m_log << fmt::format("本地工艺表中宽度上下限范围:[{0},{1}]", tolWidthLower, tolWidthUpper).c_str() << end_l;

		//	//采用公差带小的
		//	if ((maxWidth - minWidth) > (tolWidthUpper - tolWidthLower))
		//	{
		//		minWidth = tgtWidth + tolWidthLower;
		//		maxWidth = tgtWidth + tolWidthUpper;
		//		m_log << fmt::format("采用本地工艺表宽度最值:[{0},{1}]", minWidth, maxWidth).c_str() << end_l;
		//	}

		//	tolFlatUpper = res_tol.rs_.Get<float>("FLATDETUP");
		//	tolFlatLower = res_tol.rs_.Get<float>("FLATDETDOWN");
		//	m_log << fmt::format("本地工艺表中平坦度上下限范围:[{0},{1}]", tolFlatLower, tolFlatUpper).c_str() << end_l;

		//	//采用公差带小的
		//	if ((maxFlat - minFlat) > (tolFlatUpper - tolFlatLower))
		//	{
		//		minFlat = tgtFlat + tolFlatLower;
		//		maxFlat = tgtFlat + tolFlatUpper;
		//		m_log << fmt::format("采用本地工艺表平坦度最值:[{0},{1}]", minFlat, maxFlat).c_str() << end_l;
		//	}
		//}
		//else
		//{
		//	ALARM(AL_ERROR, 6201, "本地工艺表没有维护对应档位的工艺");
		//}
#pragma endregion

#pragma endregion

		//使用同一连接进行操作
		auto conn_datacentre = DB::OracleDB::OracleDML::getConnection();
		ocilib::Statement stmt(conn_datacentre);

		std::string sql; /*要执行的sql*/
		std::string coil_id; /*生成钢卷号*/

		if (m_opr_mode == shared_define::mes_message::OperationTypeEnum::InsertCmd)
		{
			try
			{
				// Generate a new request name 生成卷号
				coil_id = RequestUtility::GenerateRequestName();
				memcpy(pdi_data->COIL_ID, coil_id.data(), coil_id.size());
				m_log << "生成卷号：" << coil_id.c_str() << end_l;

				// create tb_pdi record
				sql = "INSERT INTO TB_PDI (REQUEST_TYPE,SEND_STATUS, ROLLING_SCHEDULE_ID, TARGET_CHARGE_DATE, TARGET_ROLLING_DATE, HOT_CHARGING,SLAB_ID,COIL_ID, SEQUENCE_NO,  HEAT_ID, STEEL_GRADE, SLAB_THICKNESS, SLAB_WIDTH, SLAB_LENGTH, SLAB_CALC_WEIGHT, SLAB_TAPER_STATUS, SLAB_TAPER_VALUE, GRADE_TRANS_CODE,FERRITIC_ROLLING, CHARGE_TEMP_AIM, DISCHARGE_TEMP_AIM, PLATE_FLAG, RM_EXIT_TEMP_AIM, RM_EXIT_TEMP_MAX, RM_EXIT_TEMP_MIN, RM_THICKN_AIM, RM_WIDTH_AIM, NO_COILBOX_FLAG, CS_TEMP_AIM, CS_TEMP_MAX, CS_TEMP_MIN, FM_EXIT_THICKN_AIM, FM_EXIT_THICKN_MAX, FM_EXIT_THICKN_MIN, FM_EXIT_WIDTH_AIM, FM_EXIT_WIDTH_MAX, FM_EXIT_WIDTH_MIN, FM_EXIT_TEMP_AIM, FM_EXIT_TEMP_MAX, FM_EXIT_TEMP_MIN, COILING_TEMP_AIM, COILING_TEMP_MAX, COILING_TEMP_MIN, FM_EXIT_CROWN_AIM, FM_EXIT_CROWN_MAX, FM_EXIT_CROWN_MIN, FM_EXIT_FLATNESS_AIM, FM_EXIT_FLATNESS_MAX, FM_EXIT_FLATNESS_MIN, FM_EXIT_THICK_ALT, FM_EXIT_TEMP_ALT, COILING_TEMP_ALT, IM_COOLING_TEMP, IM_RECOVERY_TIME, COOLING_RATE_CODE, COILER_HOT_HEAD_LENGTH, COILER_HOT_HEAD_TEMP_OFFS, COILER_HOT_TAIL_LENGTH, COILER_HOT_TAIL_TEMP_OFFS, SAMPLE_FLAG, SAMPLE_ID, COIL_DEST_AREA, CUSTOMER_ORDER, PRODUCTION_STD, EXTRA_STRAPS_NO, USE_ANALYSIS_FLAG, C_ACTUAL, SI_ACTUAL, MN_ACTUAL, P_ACTUAL, S_ACTUAL, CR_ACTUAL, NI_ACTUAL, CU_ACTUAL, MO_ACTUAL, V_ACTUAL, TI_ACTUAL, AL_ACTUAL, B_ACTUAL, NB_ACTUAL, N_ACTUAL, W_ACTUAL, SN_ACTUAL, O_ACTUAL, H_ACTUAL, MG_ACTUAL, CO_ACTUAL, ZR_ACTUAL, TA_CONTENT, ZN_ACTUAL, FE_ACTUAL, INSPECTION_INSTR, ROLLING_INSTR, STEEL_TYPE, PROD_REQ_TEMPLATE, SEQUENCE_IN_LIST,ISVALID,ERROR_INFO) VALUES (:REQUEST_TYPE, :SEND_STATUS,:ROLLING_SCHEDULE_ID, :TARGET_CHARGE_DATE,:TARGET_ROLLING_DATE,:HOT_CHARGING,:SLAB_ID,:COIL_ID,:SEQUENCE_NO,:HEAT_ID,:STEEL_GRADE,:SLAB_THICKNESS,:SLAB_WIDTH,:SLAB_LENGTH,:SLAB_CALC_WEIGHT,:SLAB_TAPER_STATUS,:SLAB_TAPER_VALUE,:GRADE_TRANS_CODE,:FERRITIC_ROLLING,:CHARGE_TEMP_AIM,:DISCHARGE_TEMP_AIM,:PLATE_FLAG,:RM_EXIT_TEMP_AIM,:RM_EXIT_TEMP_MAX,:RM_EXIT_TEMP_MIN,:RM_THICKN_AIM,:RM_WIDTH_AIM,:NO_COILBOX_FLAG,:CS_TEMP_AIM,:CS_TEMP_MAX,:CS_TEMP_MIN,:FM_EXIT_THICKN_AIM,:FM_EXIT_THICKN_MAX,:FM_EXIT_THICKN_MIN,:FM_EXIT_WIDTH_AIM,:FM_EXIT_WIDTH_MAX,:FM_EXIT_WIDTH_MIN,:FM_EXIT_TEMP_AIM,:FM_EXIT_TEMP_MAX,:FM_EXIT_TEMP_MIN,:COILING_TEMP_AIM,:COILING_TEMP_MAX,:COILING_TEMP_MIN,:FM_EXIT_CROWN_AIM,:FM_EXIT_CROWN_MAX,:FM_EXIT_CROWN_MIN,:FM_EXIT_FLATNESS_AIM,:FM_EXIT_FLATNESS_MAX,:FM_EXIT_FLATNESS_MIN,:FM_EXIT_THICK_ALT,:FM_EXIT_TEMP_ALT,:COILING_TEMP_ALT,:IM_COOLING_TEMP,:IM_RECOVERY_TIME,:COOLING_RATE_CODE,:COILER_HOT_HEAD_LENGTH,:COILER_HOT_HEAD_TEMP_OFFS,:COILER_HOT_TAIL_LENGTH,:COILER_HOT_TAIL_TEMP_OFFS,:SAMPLE_FLAG,:SAMPLE_ID,:COIL_DEST_AREA,:CUSTOMER_ORDER,:PRODUCTION_STD,:EXTRA_STRAPS_NO,:USE_ANALYSIS_FLAG,:C_ACTUAL,:SI_ACTUAL,:MN_ACTUAL,:P_ACTUAL,:S_ACTUAL,:CR_ACTUAL,:NI_ACTUAL,:CU_ACTUAL,:MO_ACTUAL,:V_ACTUAL,:TI_ACTUAL,:AL_ACTUAL,:B_ACTUAL,:NB_ACTUAL,:N_ACTUAL,:W_ACTUAL,:SN_ACTUAL,:O_ACTUAL,:H_ACTUAL,:MG_ACTUAL,:CO_ACTUAL,:ZR_ACTUAL,:TA_CONTENT,:ZN_ACTUAL,:FE_ACTUAL,:INSPECTION_INSTR,:ROLLING_INSTR,:STEEL_TYPE,:PROD_REQ_TEMPLATE,:SEQUENCE_IN_LIST,:ISVALID,:ERROR_INFO)";


				stmt.Prepare(sql);

				// 预处理数值型变量
				int RequestType = (int)shared_define::mes_message::ReqTypesEnum::ProductionOrder;
				stmt.Bind(":REQUEST_TYPE", RequestType, ocilib::BindInfo::In);

				int PROD_REQ_TEMPLATE = static_cast<int>(orderType);
				stmt.Bind(":PROD_REQ_TEMPLATE", PROD_REQ_TEMPLATE, ocilib::BindInfo::In);

				auto SEQUENCE_IN_LIST = RequestUtility::GetNextSeqNoForScheduleList((int)(shared_define::mes_message::ListTypesEnum::ProductionScheduleList));
				stmt.Bind(":SEQUENCE_IN_LIST", SEQUENCE_IN_LIST, ocilib::BindInfo::In);

				stmt.Bind(":COIL_ID", coil_id, coil_id.size(), ocilib::BindInfo::In);

			}
			catch (const std::exception& e)
			{
				ALARM(AL_ERROR, 6202, "The error occurred in inserting order data into TB_PDI ,reason:%s", e.what());
			}

		}
		// 更新时，默认卷号不变,以板坯号为索引
		else if (m_opr_mode == shared_define::mes_message::OperationTypeEnum::UpdateCmd)
		{
			try
			{
				sql = "UPDATE TB_PDI SET "
					"SEND_STATUS = :SEND_STATUS,"
					"ROLLING_SCHEDULE_ID = :ROLLING_SCHEDULE_ID, "
					"TARGET_CHARGE_DATE = :TARGET_CHARGE_DATE, "
					"TARGET_ROLLING_DATE = :TARGET_ROLLING_DATE,  "
					"HOT_CHARGING = :HOT_CHARGING, "
					"SEQUENCE_NO = :SEQUENCE_NO, "
					"HEAT_ID = :HEAT_ID, "
					"STEEL_GRADE = :STEEL_GRADE, "
					"SLAB_THICKNESS = :SLAB_THICKNESS,	"
					"SLAB_WIDTH = :SLAB_WIDTH, "
					"SLAB_LENGTH = :SLAB_LENGTH, "
					"SLAB_CALC_WEIGHT = :SLAB_CALC_WEIGHT, "
					"SLAB_TAPER_STATUS = :SLAB_TAPER_STATUS, "
					"SLAB_TAPER_VALUE = :SLAB_TAPER_VALUE, "
					"GRADE_TRANS_CODE = :GRADE_TRANS_CODE, "
					"FERRITIC_ROLLING = :FERRITIC_ROLLING, "
					"CHARGE_TEMP_AIM = :CHARGE_TEMP_AIM, "
					"DISCHARGE_TEMP_AIM = :DISCHARGE_TEMP_AIM, "
					"PLATE_FLAG = :PLATE_FLAG, "
					"RM_EXIT_TEMP_AIM = :RM_EXIT_TEMP_AIM, "
					"RM_EXIT_TEMP_MAX = :RM_EXIT_TEMP_MAX, "
					"RM_EXIT_TEMP_MIN = :RM_EXIT_TEMP_MIN, "
					"RM_THICKN_AIM = :RM_THICKN_AIM, "
					"RM_WIDTH_AIM = :RM_WIDTH_AIM, "
					"NO_COILBOX_FLAG = :NO_COILBOX_FLAG, "
					"CS_TEMP_AIM = :CS_TEMP_AIM, "
					"CS_TEMP_MAX = :CS_TEMP_MAX, "
					"CS_TEMP_MIN = :CS_TEMP_MIN, "
					"FM_EXIT_THICKN_AIM = :FM_EXIT_THICKN_AIM, "
					"FM_EXIT_THICKN_MAX = :FM_EXIT_THICKN_MAX, "
					"FM_EXIT_THICKN_MIN = :FM_EXIT_THICKN_MIN, "
					"FM_EXIT_WIDTH_AIM = :FM_EXIT_WIDTH_AIM, "
					"FM_EXIT_WIDTH_MAX = :FM_EXIT_WIDTH_MAX, "
					"FM_EXIT_WIDTH_MIN = :FM_EXIT_WIDTH_MIN, "
					"FM_EXIT_TEMP_AIM = :FM_EXIT_TEMP_AIM, "
					"FM_EXIT_TEMP_MAX = :FM_EXIT_TEMP_MAX, "
					"FM_EXIT_TEMP_MIN = :FM_EXIT_TEMP_MIN, "
					"COILING_TEMP_AIM = :COILING_TEMP_AIM, "
					"COILING_TEMP_MAX = :COILING_TEMP_MAX, "
					"COILING_TEMP_MIN = :COILING_TEMP_MIN, "
					"FM_EXIT_CROWN_AIM = :FM_EXIT_CROWN_AIM, "
					"FM_EXIT_CROWN_MAX = :FM_EXIT_CROWN_MAX, "
					"FM_EXIT_CROWN_MIN = :FM_EXIT_CROWN_MIN, "
					"FM_EXIT_FLATNESS_AIM = :FM_EXIT_FLATNESS_AIM, "
					"FM_EXIT_FLATNESS_MAX = :FM_EXIT_FLATNESS_MAX, "
					"FM_EXIT_FLATNESS_MIN = :FM_EXIT_FLATNESS_MIN, "
					"FM_EXIT_THICK_ALT = :FM_EXIT_THICK_ALT, "
					"FM_EXIT_TEMP_ALT = :FM_EXIT_TEMP_ALT, "
					"COILING_TEMP_ALT = :COILING_TEMP_ALT, "
					"IM_COOLING_TEMP = :IM_COOLING_TEMP, "
					"IM_RECOVERY_TIME = :IM_RECOVERY_TIME, "
					"COOLING_RATE_CODE = :COOLING_RATE_CODE, "
					"COILER_HOT_HEAD_LENGTH = :COILER_HOT_HEAD_LENGTH, "
					"COILER_HOT_HEAD_TEMP_OFFS = :COILER_HOT_HEAD_TEMP_OFFS, "
					"COILER_HOT_TAIL_LENGTH = :COILER_HOT_TAIL_LENGTH, "
					"COILER_HOT_TAIL_TEMP_OFFS = :COILER_HOT_TAIL_TEMP_OFFS, "
					"SAMPLE_FLAG = :SAMPLE_FLAG, "
					"SAMPLE_ID = :SAMPLE_ID, "
					"COIL_DEST_AREA = :COIL_DEST_AREA, "
					"CUSTOMER_ORDER = :CUSTOMER_ORDER, "
					"PRODUCTION_STD = :PRODUCTION_STD, "
					"EXTRA_STRAPS_NO = :EXTRA_STRAPS_NO, "
					"USE_ANALYSIS_FLAG = :USE_ANALYSIS_FLAG, "
					"C_ACTUAL = :C_ACTUAL, "
					"SI_ACTUAL = :SI_ACTUAL, "
					"MN_ACTUAL = :MN_ACTUAL, "
					"P_ACTUAL = :P_ACTUAL, "
					"S_ACTUAL = :S_ACTUAL, "
					"CR_ACTUAL = :CR_ACTUAL, "
					"NI_ACTUAL = :NI_ACTUAL, "
					"CU_ACTUAL = :CU_ACTUAL, "
					"MO_ACTUAL = :MO_ACTUAL, "
					"V_ACTUAL = :V_ACTUAL, "
					"TI_ACTUAL = :TI_ACTUAL, "
					"AL_ACTUAL = :AL_ACTUAL, "
					"B_ACTUAL = :B_ACTUAL, "
					"NB_ACTUAL = :NB_ACTUAL, "
					"N_ACTUAL = :N_ACTUAL, "
					"W_ACTUAL = :W_ACTUAL, "
					"SN_ACTUAL = :SN_ACTUAL, "
					"O_ACTUAL = :O_ACTUAL, "
					"H_ACTUAL = :H_ACTUAL, "
					"MG_ACTUAL = :MG_ACTUAL, "
					"CO_ACTUAL = :CO_ACTUAL, "
					"ZR_ACTUAL = :ZR_ACTUAL, "
					"TA_CONTENT = :TA_CONTENT, "
					"ZN_ACTUAL = :ZN_ACTUAL, "
					"FE_ACTUAL = :FE_ACTUAL, "
					"INSPECTION_INSTR = :INSPECTION_INSTR, "
					"ROLLING_INSTR = :ROLLING_INSTR, "
					"UPDATE_TIME = sysdate, "
					"STEEL_TYPE = :STEEL_TYPE, "
					"ISVALID = :ISVALID, "
					"ERROR_INFO = :ERROR_INFO "
					"WHERE SLAB_ID = :SLAB_ID ";

				stmt.Prepare(sql);
				//#pragma region 存储字段值
				//
				//				// 预处理数值型变量
				//				int status = uni_box::utils::Char2Int(pdi_data->SEND_STATUS);
				//				stmt.Bind(":SEND_STATUS", status, ocilib::BindInfo::In);
				//
				//				// 预处理字符串变量
				//				std::string rollId(pdi_data->ROLLING_SCHEDULE_ID, sizeof(pdi_data->ROLLING_SCHEDULE_ID));
				//				stmt.Bind(":ROLLING_SCHEDULE_ID", rollId, rollId.size(), ocilib::BindInfo::In);
				//
				//				// 预处理日期型变量
				//				std::string target_charge(pdi_data->TARGET_CHARGE_DATE, sizeof(pdi_data->TARGET_CHARGE_DATE));
				//				if (target_charge.length() != shared_define::PDI_TIME_LEN)
				//				{
				//					ALARM(AL_ERROR, 6165, "TARGET_CHARGE_DATE [%s], 长度校验错误,不为 14.", target_charge.c_str());
				//					target_charge = "20000000000000";
				//				}
				//				ocilib::Date target_charge_date(target_charge, "yyyy-MM-dd HH24:mi:ss");
				//				stmt.Bind(":TARGET_CHARGE_DATE", target_charge_date, ocilib::BindInfo::In);
				//
				//				std::string target_rolling(pdi_data->TARGET_ROLLING_DATE, sizeof(pdi_data->TARGET_ROLLING_DATE));
				//				if (target_rolling.length() != shared_define::PDI_TIME_LEN)
				//				{
				//					ALARM(AL_ERROR, 6166, "TARGET_ROLLING_DATE [%s], 长度校验错误,不为 14, 采用当前时间.", target_rolling.c_str());
				//					target_rolling = uni_box::time_tools::getCurrentTime("%Y%m%d%H%M%S");
				//				}
				//				ocilib::Date target_rolling_date(target_rolling, "yyyy-MM-dd HH24:mi:ss");
				//				stmt.Bind(":TARGET_ROLLING_DATE", target_rolling_date, ocilib::BindInfo::In);
				//
				//				int hot_charging = uni_box::utils::Char2Int(pdi_data->HOT_CHARGING);
				//				stmt.Bind(":HOT_CHARGING", hot_charging, ocilib::BindInfo::In);
				//
				//				std::string sno(pdi_data->SEQUENCE_NO, sizeof(pdi_data->SEQUENCE_NO));
				//				int sequence_no = std::stoi(sno);
				//				stmt.Bind(":SEQUENCE_NO", sequence_no, ocilib::BindInfo::In);
				//
				//				std::string heat_id(pdi_data->HEAT_ID, sizeof(pdi_data->HEAT_ID));
				//				stmt.Bind(":ROLLING_SCHEDULE_ID", heat_id, heat_id.size(), ocilib::BindInfo::In);
				//
				//				stmt.Bind(":STEEL_GRADE", steelGrade, steelGrade.size(), ocilib::BindInfo::In);
				//
				//				auto slab_thick = uni_box::utils::parseStringToNumber<float>(pdi_data->SLAB_THICKNESS, "000.000");
				//				stmt.Bind(":SLAB_THICKNESS", slab_thick, ocilib::BindInfo::In);
				//
				//				auto slab_width = uni_box::utils::parseStringToNumber<float>(pdi_data->SLAB_WIDTH, "0000.0");
				//				stmt.Bind(":SLAB_WIDTH", slab_width, ocilib::BindInfo::In);
				//
				//				auto slab_length = uni_box::utils::parseStringToNumber<float>(pdi_data->SLAB_LENGTH, "000.000");
				//				stmt.Bind(":SLAB_LENGTH", slab_length, ocilib::BindInfo::In);
				//
				//				auto slab_calc_weight = uni_box::utils::parseStringToNumber<int>(pdi_data->SLAB_CALC_WEIGHT, "00000");
				//				stmt.Bind(":SLAB_CALC_WEIGHT", slab_calc_weight, ocilib::BindInfo::In);
				//
				//				int slab_taper_status = uni_box::utils::Char2Int(pdi_data->SLAB_TAPER_STATUS);
				//				stmt.Bind(":SLAB_TAPER_STATUS", slab_taper_status, ocilib::BindInfo::In);
				//
				//				std::string slab_taper_value(pdi_data->SLAB_TAPER_VALUE, sizeof(pdi_data->SLAB_TAPER_VALUE));
				//				stmt.Bind(":SLAB_TAPER_VALUE", slab_taper_value, slab_taper_value.size(), ocilib::BindInfo::In);
				//
				//				int grade_trans_code = uni_box::utils::Char2Int(pdi_data->GRADE_TRANS_CODE);
				//				stmt.Bind(":GRADE_TRANS_CODE", grade_trans_code, ocilib::BindInfo::In);
				//
				//				int ferritic_rolling = uni_box::utils::Char2Int(pdi_data->FERRITIC_ROLLING);
				//				stmt.Bind(":FERRITIC_ROLLING", ferritic_rolling, ocilib::BindInfo::In);
				//
				//				auto charge_temp_aim = uni_box::utils::parseStringToNumber<int>(pdi_data->CHARGE_TEMP_AIM, "0000");
				//				stmt.Bind(":CHARGE_TEMP_AIM", charge_temp_aim, ocilib::BindInfo::In);
				//
				//				auto discharge_temp_aim = uni_box::utils::parseStringToNumber<int>(pdi_data->DISCHARGE_TEMP_AIM, "0000");
				//				stmt.Bind(":DISCHARGE_TEMP_AIM", discharge_temp_aim, ocilib::BindInfo::In);
				//
				//				int plate_flag = uni_box::utils::Char2Int(pdi_data->PLATE_FLAG);
				//				stmt.Bind(":PLATE_FLAG", plate_flag, ocilib::BindInfo::In);
				//
				//				auto rm_exit_temp_aim = uni_box::utils::parseStringToNumber<int>(pdi_data->RM_EXIT_TEMP_AIM, "0000");
				//				stmt.Bind(":RM_EXIT_TEMP_AIM", rm_exit_temp_aim, ocilib::BindInfo::In);
				//
				//				auto rm_exit_temp_max = uni_box::utils::parseStringToNumber<int>(pdi_data->RM_EXIT_TEMP_MAX, "0000");
				//				stmt.Bind(":RM_EXIT_TEMP_MAX", rm_exit_temp_max, ocilib::BindInfo::In);
				//
				//				auto rm_exit_temp_min = uni_box::utils::parseStringToNumber<int>(pdi_data->RM_EXIT_TEMP_MIN, "0000");
				//				stmt.Bind(":RM_EXIT_TEMP_MIN", rm_exit_temp_min, ocilib::BindInfo::In);
				//
				//				auto rm_thickn_aim = uni_box::utils::parseStringToNumber<float>(pdi_data->RM_THICKN_AIM, "000.000");
				//				stmt.Bind(":RM_THICKN_AIM", rm_thickn_aim, ocilib::BindInfo::In);
				//
				//				auto rm_width_aim = uni_box::utils::parseStringToNumber<float>(pdi_data->RM_WIDTH_AIM, "0000.0");
				//				stmt.Bind(":RM_WIDTH_AIM", rm_width_aim, ocilib::BindInfo::In);
				//
				//				auto no_coilbox_flag = uni_box::utils::parseStringToNumber<int>(pdi_data->NO_COILBOX_FLAG, "0000");
				//				stmt.Bind(":NO_COILBOX_FLAG", no_coilbox_flag, ocilib::BindInfo::In);
				//
				//				auto cs_temp_aim = uni_box::utils::parseStringToNumber<int>(pdi_data->CS_TEMP_AIM, "0000");
				//				stmt.Bind(":CS_TEMP_AIM", cs_temp_aim, ocilib::BindInfo::In);
				//
				//				auto cs_temp_max = uni_box::utils::parseStringToNumber<int>(pdi_data->CS_TEMP_MAX, "0000");
				//				stmt.Bind(":CS_TEMP_MAX", cs_temp_max, ocilib::BindInfo::In);
				//
				//				auto cs_temp_min = uni_box::utils::parseStringToNumber<int>(pdi_data->CS_TEMP_MIN, "0000");
				//				stmt.Bind(":CS_TEMP_MIN", cs_temp_min, ocilib::BindInfo::In);
				//
				//				auto fm_exit_thickn_aim = uni_box::utils::parseStringToNumber<float>(pdi_data->FM_EXIT_THICKN_AIM, "000.000");
				//				stmt.Bind(":FM_EXIT_THICKN_AIM", fm_exit_thickn_aim, ocilib::BindInfo::In);
				//
				//				stmt.Bind(":FM_EXIT_THICKN_MAX", maxThick, ocilib::BindInfo::In);
				//
				//				stmt.Bind(":FM_EXIT_THICKN_MIN", minThick, ocilib::BindInfo::In);
				//
				//				auto fm_exit_width_aim = uni_box::utils::parseStringToNumber<float>(pdi_data->FM_EXIT_WIDTH_AIM, "0000.0");
				//				stmt.Bind(":FM_EXIT_WIDTH_AIM", fm_exit_width_aim, ocilib::BindInfo::In);
				//
				//				stmt.Bind(":FM_EXIT_WIDTH_MIN", minWidth, ocilib::BindInfo::In);
				//
				//				stmt.Bind(":FM_EXIT_WIDTH_MAX", maxWidth, ocilib::BindInfo::In);
				//
				//				auto FM_EXIT_TEMP_AIM = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_TEMP_AIM, "0000");
				//				stmt.Bind(":FM_EXIT_TEMP_AIM", FM_EXIT_TEMP_AIM, ocilib::BindInfo::In);
				//
				//				auto FM_EXIT_TEMP_MAX = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_TEMP_MAX, "0000");
				//				stmt.Bind(":FM_EXIT_TEMP_MAX", FM_EXIT_TEMP_MAX, ocilib::BindInfo::In);
				//
				//				auto FM_EXIT_TEMP_MIN = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_TEMP_MIN, "0000");
				//				stmt.Bind(":FM_EXIT_TEMP_MIN", FM_EXIT_TEMP_MIN, ocilib::BindInfo::In);
				//
				//				auto COILING_TEMP_AIM = uni_box::utils::parseStringToNumber<int>(pdi_data->COILING_TEMP_AIM, "0000");
				//				stmt.Bind(":COILING_TEMP_AIM", COILING_TEMP_AIM, ocilib::BindInfo::In);
				//
				//				auto COILING_TEMP_MAX = uni_box::utils::parseStringToNumber<int>(pdi_data->COILING_TEMP_MAX, "0000");
				//				stmt.Bind(":COILING_TEMP_MAX", COILING_TEMP_MAX, ocilib::BindInfo::In);
				//
				//				auto COILING_TEMP_MIN = uni_box::utils::parseStringToNumber<int>(pdi_data->COILING_TEMP_MIN, "0000");
				//				stmt.Bind(":COILING_TEMP_MIN", COILING_TEMP_MIN, ocilib::BindInfo::In);
				//
				//				auto FM_EXIT_CROWN_AIM = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_CROWN_AIM, "0000");
				//				stmt.Bind(":FM_EXIT_CROWN_AIM", FM_EXIT_CROWN_AIM, ocilib::BindInfo::In);
				//
				//				auto FM_EXIT_CROWN_MAX = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_CROWN_MAX, "0000");
				//				stmt.Bind(":FM_EXIT_CROWN_MAX", FM_EXIT_CROWN_MAX, ocilib::BindInfo::In);
				//
				//				auto FM_EXIT_CROWN_MIN = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_CROWN_MIN, "0000");
				//				stmt.Bind(":FM_EXIT_CROWN_MIN", FM_EXIT_CROWN_MIN, ocilib::BindInfo::In);
				//
				//				auto FM_EXIT_FLATNESS_AIM = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_FLATNESS_AIM, "0000");
				//				stmt.Bind(":FM_EXIT_FLATNESS_AIM", FM_EXIT_FLATNESS_AIM, ocilib::BindInfo::In);
				//
				//				stmt.Bind(":FM_EXIT_FLATNESS_MAX", maxFlat, ocilib::BindInfo::In);
				//
				//				stmt.Bind(":FM_EXIT_FLATNESS_MIN", minFlat, ocilib::BindInfo::In);
				//
				//				auto FM_EXIT_THICK_ALT = uni_box::utils::parseStringToNumber<float>(pdi_data->FM_EXIT_THICK_ALT, "000.000");
				//				stmt.Bind(":FM_EXIT_THICK_ALT", FM_EXIT_THICK_ALT, ocilib::BindInfo::In);
				//
				//				auto FM_EXIT_TEMP_ALT = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_TEMP_ALT, "0000");
				//				stmt.Bind(":FM_EXIT_TEMP_ALT", FM_EXIT_TEMP_ALT, ocilib::BindInfo::In);
				//
				//				auto COILING_TEMP_ALT = uni_box::utils::parseStringToNumber<int>(pdi_data->COILING_TEMP_ALT, "0000");
				//				stmt.Bind(":COILING_TEMP_ALT", COILING_TEMP_ALT, ocilib::BindInfo::In);
				//
				//				auto IM_COOLING_TEMP = uni_box::utils::parseStringToNumber<int>(pdi_data->IM_COOLING_TEMP, "0000");
				//				stmt.Bind(":IM_COOLING_TEMP", IM_COOLING_TEMP, ocilib::BindInfo::In);
				//
				//				auto IM_RECOVERY_TIME = uni_box::utils::parseStringToNumber<float>(pdi_data->IM_RECOVERY_TIME, "0.00");
				//				stmt.Bind(":IM_RECOVERY_TIME", IM_RECOVERY_TIME, ocilib::BindInfo::In);
				//
				//				int COOLING_RATE_CODE = uni_box::utils::Char2Int(pdi_data->COOLING_RATE_CODE);
				//				stmt.Bind(":COOLING_RATE_CODE", COOLING_RATE_CODE, ocilib::BindInfo::In);
				//
				//				auto COILER_HOT_HEAD_LENGTH = uni_box::utils::parseStringToNumber<float>(pdi_data->COILER_HOT_HEAD_LENGTH, "0000.0");
				//				stmt.Bind(":COILER_HOT_HEAD_LENGTH", COILER_HOT_HEAD_LENGTH, ocilib::BindInfo::In);
				//
				//				auto COILER_HOT_HEAD_TEMP_OFFS = uni_box::utils::parseStringToNumber<int>(pdi_data->COILER_HOT_HEAD_TEMP_OFFS, "0000");
				//				stmt.Bind(":COILER_HOT_HEAD_TEMP_OFFS", COILER_HOT_HEAD_TEMP_OFFS, ocilib::BindInfo::In);
				//
				//				auto COILER_HOT_TAIL_LENGTH = uni_box::utils::parseStringToNumber<float>(pdi_data->COILER_HOT_TAIL_LENGTH, "0000.0");
				//				stmt.Bind(":COILER_HOT_TAIL_LENGTH", COILER_HOT_TAIL_LENGTH, ocilib::BindInfo::In);
				//
				//				auto COILER_HOT_TAIL_TEMP_OFFS = uni_box::utils::parseStringToNumber<int>(pdi_data->COILER_HOT_TAIL_TEMP_OFFS, "0000");
				//				stmt.Bind(":COILER_HOT_TAIL_TEMP_OFFS", COILER_HOT_TAIL_TEMP_OFFS, ocilib::BindInfo::In);
				//
				//				int SAMPLE_FLAG = uni_box::utils::Char2Int(pdi_data->SAMPLE_FLAG);
				//				stmt.Bind(":SAMPLE_FLAG", SAMPLE_FLAG, ocilib::BindInfo::In);
				//
				//				std::string SAMPLE_ID(pdi_data->SAMPLE_ID, sizeof(pdi_data->SAMPLE_ID));
				//				stmt.Bind(":SAMPLE_ID", SAMPLE_ID, SAMPLE_ID.size(), ocilib::BindInfo::In);
				//
				//				int COIL_DEST_AREA = uni_box::utils::Char2Int(pdi_data->COIL_DEST_AREA);
				//				stmt.Bind(":COIL_DEST_AREA", COIL_DEST_AREA, ocilib::BindInfo::In);
				//
				//				std::string CUSTOMER_ORDER(pdi_data->CUSTOMER_ORDER, sizeof(pdi_data->CUSTOMER_ORDER));
				//				stmt.Bind(":CUSTOMER_ORDER", CUSTOMER_ORDER, CUSTOMER_ORDER.size(), ocilib::BindInfo::In);
				//
				//				std::string PRODUCTION_STD(pdi_data->PRODUCTION_STD, sizeof(pdi_data->PRODUCTION_STD));
				//				stmt.Bind(":PRODUCTION_STD", PRODUCTION_STD, PRODUCTION_STD.size(), ocilib::BindInfo::In);
				//
				//				int EXTRA_STRAPS_NO = uni_box::utils::Char2Int(pdi_data->EXTRA_STRAPS_NO);
				//				stmt.Bind(":EXTRA_STRAPS_NO", EXTRA_STRAPS_NO, ocilib::BindInfo::In);
				//
				//				int USE_ANALYSIS_FLAG = uni_box::utils::Char2Int(pdi_data->USE_ANALYSIS_FLAG);
				//				stmt.Bind(":USE_ANALYSIS_FLAG", USE_ANALYSIS_FLAG, ocilib::BindInfo::In);
				//
				//				std::string INSPECTION_INSTR(pdi_data->INSPECTION_INSTR, sizeof(pdi_data->INSPECTION_INSTR));
				//				stmt.Bind(":INSPECTION_INSTR", INSPECTION_INSTR, INSPECTION_INSTR.size(), ocilib::BindInfo::In);
				//
				//				std::string ROLLING_INSTR(pdi_data->ROLLING_INSTR, sizeof(pdi_data->ROLLING_INSTR));
				//				stmt.Bind(":ROLLING_INSTR", ROLLING_INSTR, ROLLING_INSTR.size(), ocilib::BindInfo::In);
				//
				//				std::string STEEL_TYPE(pdi_data->STEEL_TYPE, sizeof(pdi_data->STEEL_TYPE));
				//				stmt.Bind(":STEEL_TYPE", STEEL_TYPE, STEEL_TYPE.size(), ocilib::BindInfo::In);
				//
				//				stmt.Bind(":SLAB_ID", slabId, slabId.size(), ocilib::BindInfo::In);
				//#pragma endregion
			}
			catch (std::exception& e)
			{
				ALARM(AL_ERROR, 6203, "The error occurred in updating order data into TB_PDI ,reason:%s", e.what());
			}
		}
		else
		{
			ALARM(AL_ERROR, 6204, "并无删除操作处理，检查逻辑链是否异常！");
		}

		try
		{
#pragma region 存储字段值

			int status = uni_box::utils::Char2Int(pdi_data->SEND_STATUS);
			stmt.Bind(":SEND_STATUS", status, ocilib::BindInfo::In);

			// 预处理字符串变量
			std::string rollId(pdi_data->ROLLING_SCHEDULE_ID, sizeof(pdi_data->ROLLING_SCHEDULE_ID));
			uni_box::utils::trimBlank(rollId);
			stmt.Bind(":ROLLING_SCHEDULE_ID", rollId, rollId.size(), ocilib::BindInfo::In);

			// 预处理日期型变量
			std::string target_charge(pdi_data->TARGET_CHARGE_DATE, sizeof(pdi_data->TARGET_CHARGE_DATE));
			uni_box::utils::trimBlank(target_charge);
			if (target_charge.length() != shared_define::PDI_TIME_LEN)
			{
				ALARM(AL_ERROR, 6205, "TARGET_CHARGE_DATE [%s], 长度校验错误,不为 14.", target_charge.c_str());
				target_charge = "20000000000000";
			}
			ocilib::Date target_charge_date(target_charge, "yyyy-MM-dd HH24:mi:ss");
			stmt.Bind(":TARGET_CHARGE_DATE", target_charge_date, ocilib::BindInfo::In);

			std::string target_rolling(pdi_data->TARGET_ROLLING_DATE, sizeof(pdi_data->TARGET_ROLLING_DATE));
			uni_box::utils::trimBlank(target_rolling);
			if (target_rolling.length() != shared_define::PDI_TIME_LEN)
			{
				ALARM(AL_ERROR, 6206, "TARGET_ROLLING_DATE [%s], 长度校验错误,不为 14, 采用当前时间.", target_rolling.c_str());
				target_rolling = uni_box::time_tools::getCurrentTime("%Y%m%d%H%M%S");
			}
			ocilib::Date target_rolling_date(target_rolling, "yyyy-MM-dd HH24:mi:ss");
			stmt.Bind(":TARGET_ROLLING_DATE", target_rolling_date, ocilib::BindInfo::In);

			int hot_charging = uni_box::utils::Char2Int(pdi_data->HOT_CHARGING);
			stmt.Bind(":HOT_CHARGING", hot_charging, ocilib::BindInfo::In);

			stmt.Bind(":SLAB_ID", slabId, slabId.size(), ocilib::BindInfo::In);

			std::string sno(pdi_data->SEQUENCE_NO, sizeof(pdi_data->SEQUENCE_NO));
			int sequence_no = std::stoi(sno);
			stmt.Bind(":SEQUENCE_NO", sequence_no, ocilib::BindInfo::In);

			std::string heat_id(pdi_data->HEAT_ID, sizeof(pdi_data->HEAT_ID));
			uni_box::utils::trimBlank(heat_id);
			stmt.Bind(":HEAT_ID", heat_id, heat_id.size(), ocilib::BindInfo::In);

			stmt.Bind(":STEEL_GRADE", steelGrade, steelGrade.size(), ocilib::BindInfo::In);

			auto slab_thick = uni_box::utils::parseStringToNumber<float>(pdi_data->SLAB_THICKNESS, "000.000");
			stmt.Bind(":SLAB_THICKNESS", slab_thick, ocilib::BindInfo::In);

			auto slab_width = uni_box::utils::parseStringToNumber<float>(pdi_data->SLAB_WIDTH, "0000.0");
			stmt.Bind(":SLAB_WIDTH", slab_width, ocilib::BindInfo::In);

			auto slab_length = uni_box::utils::parseStringToNumber<float>(pdi_data->SLAB_LENGTH, "00.000");
			stmt.Bind(":SLAB_LENGTH", slab_length, ocilib::BindInfo::In);

			auto slab_calc_weight = uni_box::utils::parseStringToNumber<int>(pdi_data->SLAB_CALC_WEIGHT, "000000");
			stmt.Bind(":SLAB_CALC_WEIGHT", slab_calc_weight, ocilib::BindInfo::In);

			int slab_taper_status = uni_box::utils::Char2Int(pdi_data->SLAB_TAPER_STATUS);
			stmt.Bind(":SLAB_TAPER_STATUS", slab_taper_status, ocilib::BindInfo::In);

			std::string slab_taper_value(pdi_data->SLAB_TAPER_VALUE, sizeof(pdi_data->SLAB_TAPER_VALUE));
			uni_box::utils::trimBlank(slab_taper_value);
			stmt.Bind(":SLAB_TAPER_VALUE", slab_taper_value, slab_taper_value.size(), ocilib::BindInfo::In);

			int grade_trans_code = uni_box::utils::Char2Int(pdi_data->GRADE_TRANS_CODE);
			stmt.Bind(":GRADE_TRANS_CODE", grade_trans_code, ocilib::BindInfo::In);

			int ferritic_rolling = uni_box::utils::Char2Int(pdi_data->FERRITIC_ROLLING);
			stmt.Bind(":FERRITIC_ROLLING", ferritic_rolling, ocilib::BindInfo::In);

			auto charge_temp_aim = uni_box::utils::parseStringToNumber<int>(pdi_data->CHARGE_TEMP_AIM, "0000");
			stmt.Bind(":CHARGE_TEMP_AIM", charge_temp_aim, ocilib::BindInfo::In);

			auto discharge_temp_aim = uni_box::utils::parseStringToNumber<int>(pdi_data->DISCHARGE_TEMP_AIM, "0000");
			stmt.Bind(":DISCHARGE_TEMP_AIM", discharge_temp_aim, ocilib::BindInfo::In);

			int plate_flag = uni_box::utils::Char2Int(pdi_data->PLATE_FLAG);
			stmt.Bind(":PLATE_FLAG", plate_flag, ocilib::BindInfo::In);

			auto rm_exit_temp_aim = uni_box::utils::parseStringToNumber<int>(pdi_data->RM_EXIT_TEMP_AIM, "0000");
			stmt.Bind(":RM_EXIT_TEMP_AIM", rm_exit_temp_aim, ocilib::BindInfo::In);

			auto rm_exit_temp_max = uni_box::utils::parseStringToNumber<int>(pdi_data->RM_EXIT_TEMP_MAX, "0000");
			stmt.Bind(":RM_EXIT_TEMP_MAX", rm_exit_temp_max, ocilib::BindInfo::In);

			auto rm_exit_temp_min = uni_box::utils::parseStringToNumber<int>(pdi_data->RM_EXIT_TEMP_MIN, "0000");
			stmt.Bind(":RM_EXIT_TEMP_MIN", rm_exit_temp_min, ocilib::BindInfo::In);

			auto rm_thickn_aim = uni_box::utils::parseStringToNumber<float>(pdi_data->RM_THICKN_AIM, "000.000");
			stmt.Bind(":RM_THICKN_AIM", rm_thickn_aim, ocilib::BindInfo::In);

			auto rm_width_aim = uni_box::utils::parseStringToNumber<float>(pdi_data->RM_WIDTH_AIM, "0000.0");
			stmt.Bind(":RM_WIDTH_AIM", rm_width_aim, ocilib::BindInfo::In);

			auto no_coilbox_flag = uni_box::utils::parseStringToNumber<int>(pdi_data->NO_COILBOX_FLAG, "0000");
			stmt.Bind(":NO_COILBOX_FLAG", no_coilbox_flag, ocilib::BindInfo::In);

			auto cs_temp_aim = uni_box::utils::parseStringToNumber<int>(pdi_data->CS_TEMP_AIM, "0000");
			stmt.Bind(":CS_TEMP_AIM", cs_temp_aim, ocilib::BindInfo::In);

			auto cs_temp_max = uni_box::utils::parseStringToNumber<int>(pdi_data->CS_TEMP_MAX, "0000");
			stmt.Bind(":CS_TEMP_MAX", cs_temp_max, ocilib::BindInfo::In);

			auto cs_temp_min = uni_box::utils::parseStringToNumber<int>(pdi_data->CS_TEMP_MIN, "0000");
			stmt.Bind(":CS_TEMP_MIN", cs_temp_min, ocilib::BindInfo::In);

			auto fm_exit_thickn_aim = uni_box::utils::parseStringToNumber<float>(pdi_data->FM_EXIT_THICKN_AIM, "000.000");
			stmt.Bind(":FM_EXIT_THICKN_AIM", fm_exit_thickn_aim, ocilib::BindInfo::In);

			stmt.Bind(":FM_EXIT_THICKN_MAX", maxThick, ocilib::BindInfo::In);

			stmt.Bind(":FM_EXIT_THICKN_MIN", minThick, ocilib::BindInfo::In);

			auto fm_exit_width_aim = uni_box::utils::parseStringToNumber<float>(pdi_data->FM_EXIT_WIDTH_AIM, "0000.0");
			stmt.Bind(":FM_EXIT_WIDTH_AIM", fm_exit_width_aim, ocilib::BindInfo::In);

			stmt.Bind(":FM_EXIT_WIDTH_MIN", minWidth, ocilib::BindInfo::In);

			stmt.Bind(":FM_EXIT_WIDTH_MAX", maxWidth, ocilib::BindInfo::In);

			//auto FM_EXIT_TEMP_AIM = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_TEMP_AIM, "0000");
			stmt.Bind(":FM_EXIT_TEMP_AIM", fm_exit_temp_aim, ocilib::BindInfo::In);

			auto FM_EXIT_TEMP_MAX = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_TEMP_MAX, "0000");
			stmt.Bind(":FM_EXIT_TEMP_MAX", FM_EXIT_TEMP_MAX, ocilib::BindInfo::In);

			auto FM_EXIT_TEMP_MIN = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_TEMP_MIN, "0000");
			stmt.Bind(":FM_EXIT_TEMP_MIN", FM_EXIT_TEMP_MIN, ocilib::BindInfo::In);

			//auto COILING_TEMP_AIM = uni_box::utils::parseStringToNumber<int>(pdi_data->COILING_TEMP_AIM, "0000");
			stmt.Bind(":COILING_TEMP_AIM", coiling_temp_aim, ocilib::BindInfo::In);

			auto COILING_TEMP_MAX = uni_box::utils::parseStringToNumber<int>(pdi_data->COILING_TEMP_MAX, "0000");
			stmt.Bind(":COILING_TEMP_MAX", COILING_TEMP_MAX, ocilib::BindInfo::In);

			auto COILING_TEMP_MIN = uni_box::utils::parseStringToNumber<int>(pdi_data->COILING_TEMP_MIN, "0000");
			stmt.Bind(":COILING_TEMP_MIN", COILING_TEMP_MIN, ocilib::BindInfo::In);

			auto FM_EXIT_CROWN_AIM = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_CROWN_AIM, "0000");
			stmt.Bind(":FM_EXIT_CROWN_AIM", FM_EXIT_CROWN_AIM, ocilib::BindInfo::In);

			//auto FM_EXIT_CROWN_MAX = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_CROWN_MAX, "0000");
			stmt.Bind(":FM_EXIT_CROWN_MAX", fm_exit_crown_max, ocilib::BindInfo::In);

			//auto FM_EXIT_CROWN_MIN = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_CROWN_MIN, "0000");
			stmt.Bind(":FM_EXIT_CROWN_MIN", fm_exit_crown_min, ocilib::BindInfo::In);

			auto FM_EXIT_FLATNESS_AIM = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_FLATNESS_AIM, "0000");
			stmt.Bind(":FM_EXIT_FLATNESS_AIM", FM_EXIT_FLATNESS_AIM, ocilib::BindInfo::In);

			stmt.Bind(":FM_EXIT_FLATNESS_MAX", maxFlat, ocilib::BindInfo::In);

			stmt.Bind(":FM_EXIT_FLATNESS_MIN", minFlat, ocilib::BindInfo::In);

			auto FM_EXIT_THICK_ALT = uni_box::utils::parseStringToNumber<float>(pdi_data->FM_EXIT_THICK_ALT, "000.000");
			stmt.Bind(":FM_EXIT_THICK_ALT", FM_EXIT_THICK_ALT, ocilib::BindInfo::In);

			auto FM_EXIT_TEMP_ALT = uni_box::utils::parseStringToNumber<int>(pdi_data->FM_EXIT_TEMP_ALT, "0000");
			stmt.Bind(":FM_EXIT_TEMP_ALT", FM_EXIT_TEMP_ALT, ocilib::BindInfo::In);

			auto COILING_TEMP_ALT = uni_box::utils::parseStringToNumber<int>(pdi_data->COILING_TEMP_ALT, "0000");
			stmt.Bind(":COILING_TEMP_ALT", COILING_TEMP_ALT, ocilib::BindInfo::In);

			auto IM_COOLING_TEMP = uni_box::utils::parseStringToNumber<int>(pdi_data->IM_COOLING_TEMP, "0000");
			stmt.Bind(":IM_COOLING_TEMP", IM_COOLING_TEMP, ocilib::BindInfo::In);

			auto IM_RECOVERY_TIME = uni_box::utils::parseStringToNumber<float>(pdi_data->IM_RECOVERY_TIME, "0.00");
			stmt.Bind(":IM_RECOVERY_TIME", IM_RECOVERY_TIME, ocilib::BindInfo::In);

			int COOLING_RATE_CODE = uni_box::utils::Char2Int(pdi_data->COOLING_RATE_CODE);
			stmt.Bind(":COOLING_RATE_CODE", COOLING_RATE_CODE, ocilib::BindInfo::In);

			auto COILER_HOT_HEAD_LENGTH = uni_box::utils::parseStringToNumber<float>(pdi_data->COILER_HOT_HEAD_LENGTH, "0000.0");
			stmt.Bind(":COILER_HOT_HEAD_LENGTH", COILER_HOT_HEAD_LENGTH, ocilib::BindInfo::In);

			auto COILER_HOT_HEAD_TEMP_OFFS = uni_box::utils::parseStringToNumber<int>(pdi_data->COILER_HOT_HEAD_TEMP_OFFS, "0000");
			stmt.Bind(":COILER_HOT_HEAD_TEMP_OFFS", COILER_HOT_HEAD_TEMP_OFFS, ocilib::BindInfo::In);

			auto COILER_HOT_TAIL_LENGTH = uni_box::utils::parseStringToNumber<float>(pdi_data->COILER_HOT_TAIL_LENGTH, "0000.0");
			stmt.Bind(":COILER_HOT_TAIL_LENGTH", COILER_HOT_TAIL_LENGTH, ocilib::BindInfo::In);

			auto COILER_HOT_TAIL_TEMP_OFFS = uni_box::utils::parseStringToNumber<int>(pdi_data->COILER_HOT_TAIL_TEMP_OFFS, "0000");
			stmt.Bind(":COILER_HOT_TAIL_TEMP_OFFS", COILER_HOT_TAIL_TEMP_OFFS, ocilib::BindInfo::In);

			int SAMPLE_FLAG = uni_box::utils::Char2Int(pdi_data->SAMPLE_FLAG);
			stmt.Bind(":SAMPLE_FLAG", SAMPLE_FLAG, ocilib::BindInfo::In);

			std::string SAMPLE_ID(pdi_data->SAMPLE_ID, sizeof(pdi_data->SAMPLE_ID));
			uni_box::utils::trimBlank(SAMPLE_ID);
			stmt.Bind(":SAMPLE_ID", SAMPLE_ID, SAMPLE_ID.size(), ocilib::BindInfo::In);

			int COIL_DEST_AREA = uni_box::utils::Char2Int(pdi_data->COIL_DEST_AREA);
			stmt.Bind(":COIL_DEST_AREA", COIL_DEST_AREA, ocilib::BindInfo::In);

			std::string CUSTOMER_ORDER(pdi_data->CUSTOMER_ORDER, sizeof(pdi_data->CUSTOMER_ORDER));
			uni_box::utils::trimBlank(CUSTOMER_ORDER);
			stmt.Bind(":CUSTOMER_ORDER", CUSTOMER_ORDER, CUSTOMER_ORDER.size(), ocilib::BindInfo::In);

			std::string PRODUCTION_STD(pdi_data->PRODUCTION_STD, sizeof(pdi_data->PRODUCTION_STD));
			uni_box::utils::trimBlank(PRODUCTION_STD);
			stmt.Bind(":PRODUCTION_STD", PRODUCTION_STD, PRODUCTION_STD.size(), ocilib::BindInfo::In);

			int EXTRA_STRAPS_NO = uni_box::utils::Char2Int(pdi_data->EXTRA_STRAPS_NO);
			stmt.Bind(":EXTRA_STRAPS_NO", EXTRA_STRAPS_NO, ocilib::BindInfo::In);

			use_analysis_flag = uni_box::utils::Char2Int(pdi_data->USE_ANALYSIS_FLAG);
			stmt.Bind(":USE_ANALYSIS_FLAG", use_analysis_flag, ocilib::BindInfo::In);

			std::string INSPECTION_INSTR(pdi_data->INSPECTION_INSTR, sizeof(pdi_data->INSPECTION_INSTR));
			uni_box::utils::trimBlank(INSPECTION_INSTR);
			stmt.Bind(":INSPECTION_INSTR", INSPECTION_INSTR, INSPECTION_INSTR.size(), ocilib::BindInfo::In);

			std::string ROLLING_INSTR(pdi_data->ROLLING_INSTR, sizeof(pdi_data->ROLLING_INSTR));
			uni_box::utils::trimBlank(ROLLING_INSTR);
			stmt.Bind(":ROLLING_INSTR", ROLLING_INSTR, ROLLING_INSTR.size(), ocilib::BindInfo::In);

			std::string STEEL_TYPE(pdi_data->STEEL_TYPE, sizeof(pdi_data->STEEL_TYPE));
			uni_box::utils::trimBlank(STEEL_TYPE);
			stmt.Bind(":STEEL_TYPE", STEEL_TYPE, STEEL_TYPE.size(), ocilib::BindInfo::In);

			stmt.Bind(":ERROR_INFO", error_info, error_info.size(), ocilib::BindInfo::In);
			stmt.Bind(":ISVALID", isvalid, ocilib::BindInfo::In);



#pragma endregion

			double c_ = 0.0;
			double si_ = 0.0;
			double mn_ = 0.0;
			double p_ = 0.0;
			double s_ = 0.0;
			bool isEmpty = false;

			auto sel_ = fmt::format("select C_DEF,SI_DEF,MN_DEF,P_DEF,S_DEF,CR_DEF,NI_DEF,CU_DEF,MO_DEF,V_DEF,TI_DEF,AL_DEF,B_DEF,NB_DEF,N_DEF,W_MAX,SN_DEF,O_DEF,H_DEF,CO_DEF,ZR_DEF,TA_DEF from TB_CHEMICALLMT@lk_pri where STEELGRADE='{}'", steelGrade);
#ifdef ENABLE_DEBUG
			m_log << "执行查询语句:" << end_l;
			m_log << sel_.c_str() << end_l;
#endif
			ocilib::Statement stmt_chemical(conn_nercar);
			stmt_chemical.Execute(sel_);
			auto cc = stmt_chemical.GetResultset();

			if (!cc.Next())
			{
				isEmpty = true;
				ALARM(AL_WARNING, 6207, "The TB_CHEMICALLMT is not found in database for steel grade '%s'!", steelGrade.c_str());
			}
			if (use_analysis_flag == 0)
			{
				if (steelGrade.empty())
					ALARM(AL_WARNING, 6208, "Steel grade not specified in order!");
				else
				{
					if (!isEmpty)
					{
						auto C_ACTUAL = cc.Get<double>("C_DEF");
						stmt.Bind(":C_ACTUAL", C_ACTUAL, ocilib::BindInfo::In);

						auto SI_ACTUAL = cc.Get<double>("SI_DEF");
						stmt.Bind(":SI_ACTUAL", SI_ACTUAL, ocilib::BindInfo::In);

						auto MN_ACTUAL = cc.Get<double>("MN_DEF");
						stmt.Bind(":MN_ACTUAL", MN_ACTUAL, ocilib::BindInfo::In);

						auto P_ACTUAL = cc.Get<double>("P_DEF");
						stmt.Bind(":P_ACTUAL", P_ACTUAL, ocilib::BindInfo::In);

						auto S_ACTUAL = cc.Get<double>("S_DEF");
						stmt.Bind(":S_ACTUAL", S_ACTUAL, ocilib::BindInfo::In);

						auto CR_ACTUAL = cc.Get<double>("CR_DEF");
						stmt.Bind(":CR_ACTUAL", CR_ACTUAL, ocilib::BindInfo::In);

						auto NI_ACTUAL = cc.Get<double>("NI_DEF");
						stmt.Bind(":NI_ACTUAL", NI_ACTUAL, ocilib::BindInfo::In);

						auto CU_ACTUAL = cc.Get<double>("CU_DEF");
						stmt.Bind(":CU_ACTUAL", CU_ACTUAL, ocilib::BindInfo::In);

						auto MO_ACTUAL = cc.Get<double>("MO_DEF");
						stmt.Bind(":MO_ACTUAL", MO_ACTUAL, ocilib::BindInfo::In);

						auto V_ACTUAL = cc.Get<double>("V_DEF");
						stmt.Bind(":V_ACTUAL", V_ACTUAL, ocilib::BindInfo::In);

						auto TI_ACTUAL = cc.Get<double>("TI_DEF");
						stmt.Bind(":TI_ACTUAL", TI_ACTUAL, ocilib::BindInfo::In);

						auto AL_ACTUAL = cc.Get<double>("AL_DEF");
						stmt.Bind(":AL_ACTUAL", AL_ACTUAL, ocilib::BindInfo::In);

						auto B_ACTUAL = cc.Get<double>("B_DEF");
						stmt.Bind(":B_ACTUAL", B_ACTUAL, ocilib::BindInfo::In);

						auto NB_ACTUAL = cc.Get<double>("NB_DEF");
						stmt.Bind(":NB_ACTUAL", NB_ACTUAL, ocilib::BindInfo::In);

						auto N_ACTUAL = cc.Get<double>("N_DEF");
						stmt.Bind(":N_ACTUAL", N_ACTUAL, ocilib::BindInfo::In);

						auto W_ACTUAL = cc.Get<double>("W_MAX");
						stmt.Bind(":W_ACTUAL", W_ACTUAL, ocilib::BindInfo::In);

						auto SN_ACTUAL = cc.Get<double>("SN_DEF");
						stmt.Bind(":SN_ACTUAL", SN_ACTUAL, ocilib::BindInfo::In);

						auto O_ACTUAL = cc.Get<double>("O_DEF");
						stmt.Bind(":O_ACTUAL", O_ACTUAL, ocilib::BindInfo::In);

						auto H_ACTUAL = cc.Get<double>("H_DEF");
						stmt.Bind(":H_ACTUAL", H_ACTUAL, ocilib::BindInfo::In);

						auto MG_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->MG_ACTUAL, "00.00000");
						stmt.Bind(":MG_ACTUAL", MG_ACTUAL, ocilib::BindInfo::In);

						auto CO_ACTUAL = cc.Get<double>("CO_DEF");
						stmt.Bind(":CO_ACTUAL", CO_ACTUAL, ocilib::BindInfo::In);

						auto ZR_ACTUAL = cc.Get<double>("ZR_DEF");
						stmt.Bind(":ZR_ACTUAL", ZR_ACTUAL, ocilib::BindInfo::In);

						auto TA_CONTENT = cc.Get<double>("TA_DEF");
						stmt.Bind(":TA_CONTENT", TA_CONTENT, ocilib::BindInfo::In);

						auto ZN_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->ZN_ACTUAL, "00.00000");
						stmt.Bind(":ZN_ACTUAL", ZN_ACTUAL, ocilib::BindInfo::In);

						auto FE_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->FE_ACTUAL, "00.00000");
						stmt.Bind(":FE_ACTUAL", FE_ACTUAL, ocilib::BindInfo::In);
					}
					else
					{
						ALARM(AL_WARNING, 6209, "The TB_CHEMICALLMT is not found in database for steel grade '%s'!", steelGrade.c_str());
					}
				}

			}
			//采用三级下发化学成分
			else
			{
				auto C_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->C_ACTUAL, "00.00000");
				if (!isEmpty && (C_ACTUAL > cc.Get<double>("C_MAX") || (C_ACTUAL < cc.Get<double>("C_MIN"))))
				{
					//使用本地维护
					c_ = cc.Get<double>("C_DEF");
				}
				else
				{
					c_ = C_ACTUAL;
				}
				stmt.Bind(":C_ACTUAL", c_, ocilib::BindInfo::In);

				auto SI_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->SI_ACTUAL, "00.00000");
				if (!isEmpty && (SI_ACTUAL > cc.Get<double>("SI_MAX") || (C_ACTUAL < cc.Get<double>("SI_MIN"))))
				{
					//使用本地维护
					si_ = cc.Get<double>("SI_DEF");
				}
				else
				{
					si_ = SI_ACTUAL;
				}
				stmt.Bind(":SI_ACTUAL", SI_ACTUAL, ocilib::BindInfo::In);

				auto MN_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->MN_ACTUAL, "00.00000");
				if (!isEmpty && (MN_ACTUAL > cc.Get<double>("MN_MAX") || (MN_ACTUAL < cc.Get<double>("MN_MIN"))))
				{
					//使用本地维护
					mn_ = cc.Get<double>("MN_DEF");
				}
				else
				{
					mn_ = MN_ACTUAL;
				}
				stmt.Bind(":MN_ACTUAL", mn_, ocilib::BindInfo::In);

				auto P_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->P_ACTUAL, "00.00000");
				if (!isEmpty && (P_ACTUAL > cc.Get<double>("P_MAX") || (P_ACTUAL < cc.Get<double>("P_MIN"))))
				{
					//使用本地维护
					p_ = cc.Get<double>("P_DEF");
				}
				else
				{
					p_ = P_ACTUAL;
				}
				stmt.Bind(":P_ACTUAL", p_, ocilib::BindInfo::In);

				auto S_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->S_ACTUAL, "00.00000");
				if (!isEmpty && (S_ACTUAL > cc.Get<double>("S_MAX") || (S_ACTUAL < cc.Get<double>("S_MIN"))))
				{
					//使用本地维护
					s_ = cc.Get<double>("S_DEF");
				}
				else
				{
					s_ = S_ACTUAL;
				}
				stmt.Bind(":S_ACTUAL", s_, ocilib::BindInfo::In);

				auto CR_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->CR_ACTUAL, "00.00000");
				stmt.Bind(":CR_ACTUAL", CR_ACTUAL, ocilib::BindInfo::In);

				auto NI_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->NI_ACTUAL, "00.00000");
				stmt.Bind(":NI_ACTUAL", NI_ACTUAL, ocilib::BindInfo::In);

				auto CU_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->CU_ACTUAL, "00.00000");
				stmt.Bind(":CU_ACTUAL", CU_ACTUAL, ocilib::BindInfo::In);

				auto MO_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->MO_ACTUAL, "00.00000");
				stmt.Bind(":MO_ACTUAL", MO_ACTUAL, ocilib::BindInfo::In);

				auto V_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->V_ACTUAL, "00.00000");
				stmt.Bind(":V_ACTUAL", V_ACTUAL, ocilib::BindInfo::In);

				auto TI_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->TI_ACTUAL, "00.00000");
				stmt.Bind(":TI_ACTUAL", TI_ACTUAL, ocilib::BindInfo::In);

				auto AL_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->AL_ACTUAL, "00.00000");
				stmt.Bind(":AL_ACTUAL", AL_ACTUAL, ocilib::BindInfo::In);

				auto B_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->B_ACTUAL, "00.00000");
				stmt.Bind(":B_ACTUAL", B_ACTUAL, ocilib::BindInfo::In);

				auto NB_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->NB_ACTUAL, "00.00000");
				stmt.Bind(":NB_ACTUAL", NB_ACTUAL, ocilib::BindInfo::In);

				auto N_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->N_ACTUAL, "00.00000");
				stmt.Bind(":N_ACTUAL", N_ACTUAL, ocilib::BindInfo::In);

				auto W_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->W_ACTUAL, "00.00000");
				stmt.Bind(":W_ACTUAL", W_ACTUAL, ocilib::BindInfo::In);

				auto SN_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->SN_ACTUAL, "00.00000");
				stmt.Bind(":SN_ACTUAL", SN_ACTUAL, ocilib::BindInfo::In);

				auto O_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->O_ACTUAL, "00.00000");
				stmt.Bind(":O_ACTUAL", O_ACTUAL, ocilib::BindInfo::In);

				auto H_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->H_ACTUAL, "00.00000");
				stmt.Bind(":H_ACTUAL", H_ACTUAL, ocilib::BindInfo::In);

				auto MG_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->MG_ACTUAL, "00.00000");
				stmt.Bind(":MG_ACTUAL", MG_ACTUAL, ocilib::BindInfo::In);

				auto CO_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->CO_ACTUAL, "00.00000");
				stmt.Bind(":CO_ACTUAL", CO_ACTUAL, ocilib::BindInfo::In);

				auto ZR_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->ZR_ACTUAL, "00.00000");
				stmt.Bind(":ZR_ACTUAL", ZR_ACTUAL, ocilib::BindInfo::In);

				auto TA_CONTENT = uni_box::utils::parseStringToNumber<double>(pdi_data->TA_CONTENT, "00.00000");
				stmt.Bind(":TA_CONTENT", TA_CONTENT, ocilib::BindInfo::In);

				auto ZN_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->ZN_ACTUAL, "00.00000");
				stmt.Bind(":ZN_ACTUAL", ZN_ACTUAL, ocilib::BindInfo::In);

				auto FE_ACTUAL = uni_box::utils::parseStringToNumber<double>(pdi_data->FE_ACTUAL, "00.00000");
				stmt.Bind(":FE_ACTUAL", FE_ACTUAL, ocilib::BindInfo::In);
			}

#ifdef ENABLE_DEBUG
			m_log << "执行SQL语句：" << end_l;
			m_log << sql.c_str() << end_l;
#endif
			stmt.ExecutePrepared();
			conn_datacentre.Commit();
		}
		catch (const std::exception& e)
		{
			conn_datacentre.Rollback();
			throw std::logic_error(fmt::format("向插入或更新TB_DPI时发生错误:reason:{}", e.what()));
		}

	}
	catch (std::exception& e)
	{
		ALARM(AL_ERROR, 6210, "The error occurred in PreProcessMsgData,reason:%s", e.what());
	}
}

void ERPOrderConcreteStrategy::HandleProdReqChanged(const std::string& prodReqId, int opType)
{
	try
	{
		auto sql_ = fmt::format("select STATENAME,IN_STATE, ID from TB_PDI where COIL_ID = '{0}'", prodReqId);
		
#ifdef ENABLE_DEBUG
		m_log << "【HandleProdReqChanged】执行SQL:" << end_l;
		m_log << sql_.c_str() << end_l;
#endif
		auto res = DB::OracleDB::OracleDML::executeQuery(sql_);

		if (res.rs_.Next())
		{
			auto instate = res.rs_.Get<int>("IN_STATE");
			auto statename = res.rs_.Get<std::string>("STATENAME");
			long id = res.rs_.Get<shared_define::ID_TYPE>("ID");

			switch (opType)
			{

			case (int)shared_define::mes_message::OperationTypeEnum::InsertCmd:
			{
				// Call the StateChange method to validate the data for the 
				// new order and if validation is OK change the state to Released.
				if (StateUtility::StateChange(statename, instate))
				{
					// 保存 instate 状态
					auto sql_update = fmt::format("update TB_PDI set IN_STATE = {0}, STATENAME='{1}' where COIL_ID='{2}'"
						, instate
						, statename
						, prodReqId);


					m_log << "ERPOrderConcreteStrategy::HandleProdReqChanged::InsertCmd 执行更新状态：" << end_l;
					m_log << sql_update.c_str() << end_l;

					auto affect = DB::OracleDB::OracleDML::execute(sql_update);

					if (!affect)
					{
						ALARM(AL_ERROR, 6211, "更新失败！卷号=%s", prodReqId.c_str());
					}


					//触发信号给TM，PRStateChangeOccurred
					::Message sendMsg;
					memset(&sendMsg, 0x00, sizeof(sendMsg));
					sendMsg.SetId(EVENT_STATE_CHANGE_OCCURED);
					sendMsg.AddParam("TB_PDI_ID", id);
					sendMsg.Send("TM");
					ALARM(AL_INFO, 6212, "向TM发送状态改变事件！卷号=%s", prodReqId.c_str());
				}
			}
			break;

			case (int)shared_define::mes_message::OperationTypeEnum::UpdateCmd:
			{
				// Check if the order has DRAFT state in which case
				// we try to release it
				if (statename == shared_define::OrderStateTypes::OrderIsDraft)
				{
					if (StateUtility::StateChange(statename, instate))
					{
						// 保存 instate 状态
						auto sql_update = fmt::format("update TB_PDI set IN_STATE = {0}, STATENAME='{1}' where COIL_ID='{2}'"
							, instate
							, statename
							, prodReqId);


						m_log << "ERPOrderConcreteStrategy::HandleProdReqChanged::UpdateCmd 执行更新状态：" << end_l;
						m_log << sql_update.c_str() << end_l;

						auto affect = DB::OracleDB::OracleDML::execute(sql_update);

						if (!affect)
						{
							ALARM(AL_ERROR, 6213, "更新失败！卷号=%s", prodReqId.c_str());
						}
						//触发信号给TM，PRStateChangeOccurred
						Message sendMsg;
						memset(&sendMsg, 0x00, sizeof(sendMsg));

						sendMsg.SetId(EVENT_STATE_CHANGE_OCCURED);
						sendMsg.AddParam("TB_PDI_ID", id);
						sendMsg.Send("TM");
						ALARM(AL_INFO, 6214, "向TM发送状态改变事件！卷号=%s", prodReqId.c_str());
					}
				}
				else
				{
					// Notify system that the order data has changed
					Message sendMsg;
					memset(&sendMsg, 0x00, sizeof(sendMsg));

					sendMsg.SetId(EVENT_DATA_CHANGE_OCCURED);
					sendMsg.AddParam("TB_PDI_ID", id);
					sendMsg.AddParam("opType", (long)opType);
					sendMsg.Send("TM");
					ALARM(AL_INFO, 6215, "向TM发送数据改变事件！卷号=%s", prodReqId.c_str());
					sendMsg.Send("Model");
					ALARM(AL_INFO, 6216, "向Model发送数据改变事件！卷号=%s", prodReqId.c_str());
				}
			}
			break;

			case (int)shared_define::mes_message::OperationTypeEnum::DeleteCmd:
			{
				//修改状态
				{
					// Notify system that the order data has changed
					Message sendMsg;
					memset(&sendMsg, 0x00, sizeof(sendMsg));
					sendMsg.SetId(EVENT_DATA_CHANGE_OCCURED);
					sendMsg.AddParam("TB_PDI_ID", id);
					sendMsg.AddParam("opType", (long)opType);
					sendMsg.Send("TM");
					ALARM(AL_INFO, 6217, "向TM发送数据改变事件！卷号=%s", prodReqId.c_str());

					//TODO:确认是否可以将一份消息发送给多个进程
					sendMsg.Send("Model");
					ALARM(AL_INFO, 6218, "向Model发送数据改变事件！卷号=%s", prodReqId.c_str());

					m_log << "检测到删除操作,移至TMService中延迟删除,卷号:" << prodReqId.c_str() << end_l;
				}

			}
			break;

			case (int)shared_define::mes_message::OperationTypeEnum::L2DeleteCmd: //3
			case (int)shared_define::mes_message::OperationTypeEnum::SchedCancelCmd: //4
			{
				m_log << "处理L2DeleteCmd 或 SchedCancelCmd 操作..." << end_l;
				// Notify system that the order data has changed
				Message sendMsg;
				memset(&sendMsg, 0x00, sizeof(sendMsg));
				sendMsg.SetId(EVENT_DATA_CHANGE_OCCURED);
				sendMsg.AddParam("TB_PDI_ID", (long)id);
				sendMsg.AddParam("opType", (long)opType);
				sendMsg.Send("TM");
				ALARM(AL_INFO, 6219, "向TM发送数据改变事件！卷号=%s", prodReqId.c_str());
				sendMsg.Send("Model");
				ALARM(AL_INFO, 6220, "向Model发送数据改变事件！卷号=%s", prodReqId.c_str());
			}
			break;

			default:
				break;
			}
		}
		else
		{
			ALARM(AL_ERROR, 6221, "Production Request '%s' not found! in TB_PDI", prodReqId.c_str());
		}

	}
	catch (std::exception& e)
	{
		ALARM(AL_ERROR, 6222, "error in HandleProdReqChanged :%s", e.what());
		throw e;
	}
}

void ERPOrderConcreteStrategy::EventHandler(std::shared_ptr<msg::Message>& data)
{
	const char* funcName = "ERPOrderConcreteStrategy::EventHandler";


	m_log << "L3ML01结构体大小:" << (int)sizeof(mes_l2_msg_define::L3ML01) << end_l;

	//接收L3数据
	mes_l2_msg_define::L3ML01 order_datas;
	memset(&order_datas, 0x00, sizeof(mes_l2_msg_define::L3ML01));
	memcpy(&order_datas, data->m_buffer, sizeof(mes_l2_msg_define::L3ML01));



	//存入数据库
	bool				exist_flag = false; //order中的板坯是否已在本地记录中の标识
	std::string			steel_grade; //材质代码
	std::string			slabId; //
	std::string			coil_id; //
	int sendStatus = 0;


	steel_grade.assign(order_datas.STEEL_GRADE, sizeof(order_datas.STEEL_GRADE));
	uni_box::utils::trimBlank(steel_grade);


	slabId.assign(order_datas.SLAB_ID, sizeof(order_datas.SLAB_ID));
	uni_box::utils::trimBlank(slabId);

	if (slabId.empty())
	{
		ALARM(AL_ERROR, 6223, "接收数据,板坯号长度有误,板坯号:%s", slabId.c_str());
	}

	sendStatus = uni_box::utils::Char2Int(order_datas.SEND_STATUS);
	int plateFlag = uni_box::utils::Char2Int(order_datas.PLATE_FLAG);
	shared_define::mes_message::ReqTemplateEnum newOrderType;

	m_log << fmt::format("L3OrderReceived Start:slabId '{0}', Status '{1}'", slabId, sendStatus).c_str() << end_l;

	try
	{
#pragma region 判断数据记录是否存在
		//板坯号是唯一的
		auto sql_sel = fmt::format("select * from TB_PDI where SLAB_ID = '{0}' ", slabId);

		// 获取结果集
		auto record = DB::OracleDB::OracleDML::executeQuery(sql_sel);

		if (!record.rs_.Next())
		{
			ALARM(AL_INFO, 6224, "TB_PDI中不存在该记录:SLAB_ID=%s, 新增之~", slabId.c_str());
		}
		else
		{
			exist_flag = true;
			coil_id = record.rs_.Get<std::string>("COIL_ID");
			uni_box::utils::trimBlank(coil_id);


			if (coil_id.size() < (mes_l2_msg_define::COIL_LEN / 2))
			{
				ALARM(AL_WARNING, 6225, "检测到该记录的卷号长度可能存在问题：matID=%s", coil_id.c_str());
			}
		}

#pragma endregion


		if (plateFlag == 0)
			newOrderType = shared_define::mes_message::ReqTemplateEnum::Strip; //101
		else if (plateFlag == 1)
			newOrderType = shared_define::mes_message::ReqTemplateEnum::Plate;
		else
			throw std::invalid_argument(fmt::format("The PlateFlag has an illegal value = '{0}'!", plateFlag));

		auto opType = shared_define::mes_message::OperationTypeEnum::InsertCmd;

		if (exist_flag)
		{
			opType = shared_define::mes_message::OperationTypeEnum::UpdateCmd;
		};

		if (sendStatus == shared_define::mes_message::OperateType::ORDER_DELETE)
		{
			opType = shared_define::mes_message::OperationTypeEnum::DeleteCmd;
		}

		m_opr_mode = opType;

		switch (opType)
		{
		case shared_define::mes_message::OperationTypeEnum::DeleteCmd:
		{

			//若删除，则根据slabId 判断是否存在记录，若不存在则删除失败。反之则删除成功~
			if (exist_flag)
			{
				// 判断是否允许删除
				if (RequestUtility::DeleteAllowed(record.rs_.Get<std::string>("STATENAME")))
				{
					HandleProdReqChanged(coil_id, (int)shared_define::mes_message::OperationTypeEnum::DeleteCmd);
				}
				else
				{
					ALARM(AL_ERROR, 6226, "Failed to delete order '%s' ! Delete not allowed!", slabId.c_str());
					throw std::logic_error(fmt::format("Failed to delete order slabId '{0}'! Delete not allowed!", slabId));
				}

			}
			else
			{
				ALARM(AL_ERROR, 6227, "未处理情况：delete模式：但TB_PDI中不存在记录 板坯号=%s", slabId.c_str());
				throw std::logic_error(fmt::format("Failed to delete order slabId '{0}'! It does not exist!", slabId));
			}

		}
		break;

		case shared_define::mes_message::OperationTypeEnum::InsertCmd:
		{
			PreProcessMsgData(&order_datas, newOrderType);
			coil_id.assign(order_datas.COIL_ID, sizeof(order_datas.COIL_ID));
			uni_box::utils::trimBlank(coil_id);
			HandleProdReqChanged(coil_id, opType);
		}
		break;

		case shared_define::mes_message::UpdateCmd:
		{
			auto statename = record.rs_.Get<std::string>("STATENAME");
			auto substate = record.rs_.Get<int>("SUBSTATE");
			auto request_type = record.rs_.Get<int>("REQUEST_TYPE");

			if (RequestUtility::UpdateAllowed(statename, substate, request_type))
			{
				PreProcessMsgData(&order_datas, newOrderType);
				HandleProdReqChanged(coil_id, opType);
			}
			else
			{
				throw std::logic_error(fmt::format("Update not allowed for request, slabId= {0}", slabId));
			}
		}
		break;

		default:
			ALARM(AL_ERROR, 6228, "未处理情况：slabId=%s,SEND_STATUS=%d", slabId.c_str(), order_datas.SEND_STATUS);
			break;
		}

	}
	catch (const std::exception& e)
	{
		ALARM(AL_ERROR, 6229, true, "[%s] error:%s", funcName, e.what());
		//throw e;
	}

}

void ERPOrderConcreteStrategy::ReplyMsg(std::shared_ptr<msg::Message>& data, const char nack_ack_flag, const char* descr)
{

	mes_l2_msg_define::response_msg resp;
	memset(&resp, 0x00, sizeof mes_l2_msg_define::response_msg);

	strncpy(resp.header.msg_id, data->m_identity.c_str(), shared_define::mes_message::IDENTITY_LEN);
	strncpy(resp.header.msg_len, "0110", shared_define::mes_message::LENGTH_LEN);
	memcpy(resp.header.msg_send_date, uni_box::time_tools::getCurrentTime("%Y%m%d").c_str(), shared_define::mes_message::DATESEND_LEN);
	memcpy(resp.header.msg_send_time, uni_box::time_tools::getCurrentTime("%H%M%S").c_str(), shared_define::mes_message::TIMESEND_LEN);
	strncpy(resp.header.send_code, data->m_sender.c_str(), shared_define::mes_message::SENDER_LEN);
	strncpy(resp.header.recv_code, data->m_recver.c_str(), shared_define::mes_message::RECEIVER_LEN);
	resp.header.flag = nack_ack_flag;

	char desc[shared_define::mes_message::TEXT_FIELD_LENGTH];
	memset(desc, ' ', shared_define::mes_message::TEXT_FIELD_LENGTH);
	strncpy(desc, descr, strlen(descr));
	memcpy(resp.field_info, desc, shared_define::mes_message::TEXT_FIELD_LENGTH);
	//sprintf(resp.field_info, "%s", desc);
	resp.end_character = 10;

#ifdef ENABLE_DEBUG
	m_log << "执行ERPOrderConcreteStrategy::ReplyMsg() :..." << end_l;
	m_log << "\t \t 先检响应应答电文,电文号:" << data->m_identity.c_str() << end_l;
	m_log << "\t \t 反馈标识:" << nack_ack_flag << ", 描述:" << descr << end_l;
#endif

#ifdef TEST_CAST
	this->Send("RevErp", &resp, sizeof(mes_l2_msg_define::response_msg));
#else
	this->Send(shared_define::L3Net::RECV_L3_CHANNEL, &resp, sizeof(mes_l2_msg_define::response_msg));
#endif // DEBUG

}

void ERPOrderConcreteStrategy::Dispatcher(void* data, const char* sender)
{
}

void ERPOrderConcreteStrategy::Send(const char* ChannelName, const void* Buffer, const long Size)
{
	auto ret = SendData(ChannelName, Buffer, Size);
	if (ret > 0)
	{
		ALARM(AL_INFO, 6230, "向%s发送数据成功,size=%d~", ChannelName, Size);
	}
	else
	{
		ALARM(AL_ERROR, 6231, "向%s发送数据失败, 错误号ret:%d", ChannelName, ret);
	}
}