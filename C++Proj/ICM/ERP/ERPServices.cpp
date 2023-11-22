#include <map>


#include "fmt/core.h"
#include "DBOraclePool.hpp"
#include "ActualResponseFlyw.h"
#include "CrewMgtHelper.hpp"
#include "ERPServices.h"
#include "StateUtility.hpp"

#include "mes_l2_struct.h"
#include "universal_toolbox.hpp"



ERPServices::ERPServices() :m_log(__FUNCTION__)
{
	m_data.reset();
	m_strategy.reset();
}

ERPServices::ERPServices(std::shared_ptr<msg::Message>&& data) :
	m_log(__FUNCTION__),
	m_data(std::move(data)),
	m_strategy(nullptr)
{

#ifdef ENABLE_DEBUG
	m_log << "ERPServices() constructor1:..." << end_l;
#endif
}

ERPServices::ERPServices(std::shared_ptr<ERPStrategyFactory>&& strategy_factory, std::shared_ptr<msg::Message>&& data) :
	m_log(__FUNCTION__),
	m_data(std::move(data))
{
#ifdef ENABLE_DEBUG
	m_log << "ERPServices() constructor:..." << end_l;
#endif
	m_strategy = std::move(strategy_factory->createEPRConcreteStrategy());
}

ERPServices::~ERPServices()
{
	m_data.reset();
	m_strategy.reset();
	m_log << end_t;
}

void ERPServices::SetMessageHeader(mes_l2_msg_define::common_header& header, const char* len, const char* id_)
{
	memcpy(header.msg_len, len, sizeof(header.msg_len));
	memcpy(header.msg_id, id_, sizeof(header.msg_id));
	memcpy(header.msg_send_date, uni_box::time_tools::getCurrentTime("%Y%m%d").c_str(), shared_define::mes_message::DATESEND_LEN);
	memcpy(header.msg_send_time, uni_box::time_tools::getCurrentTime("%H%M%S").c_str(), shared_define::mes_message::TIMESEND_LEN);
	memcpy(header.send_code, "ML", sizeof(header.send_code));
	memcpy(header.recv_code, "L3", sizeof(header.recv_code));
	header.flag = 'D';
}

void ERPServices::EPRSrvEventHandler()
{

	try
	{
		//校验电文信息
		if (this->checkMessage())
		{
			// 应答电文
			m_strategy->ReplyMsg(m_data, shared_define::mes_message::REP_VALIDITY_CODE, " ");

			//根据类型进行不同操作
			m_strategy->EventHandler(m_data);
		}
		else
		{
			ALARM(AL_ERROR, 6101, "接收消息失败,可能是下发计划信息有误!");
		}

	}
	catch (const std::exception& e)
	{
		ALARM(AL_ERROR, 6102, "EPRService 分发事件时发生错误:%s, 退出~", e.what());
		return;
	}
}

bool ERPServices::checkMessage()
{
	try
	{

#ifdef ENABLE_DEBUG
		m_log << "ERPServices::checkMessage():..." << end_l;
		m_log << "\t \t 收到L3传来电文 电文头: id=" << m_data->m_identity.c_str() << end_l;
		m_log << "\t \t len=" << m_data->m_length.c_str() << ", date=" << m_data->m_date.c_str() << ", time=" << m_data->m_time.c_str() << end_l;
		m_log << "\t \t sender=" << m_data->m_sender.c_str() << ", recver=" << m_data->m_recver.c_str() << ", funccode=" << m_data->m_funccode << end_l;

		m_log << "接收到的字节流数据:" << m_data->m_buffer << end_l;
		m_log << "接收到的字节流长度:" << (int)strlen(m_data->m_buffer) << end_l;

#endif

		//电文长度校验
		auto len = std::stoi(m_data->m_length);
		if (len > shared_define::mes_message::MAX_BYTES_ALLOWED)
		{
			ALARM(AL_ERROR, 6103, "%s", "校验电文长度错误: Message too long, 退出~");
			m_log << "校验电文长度错误: Message too long" << end_l;
			//发送响应电文
			m_strategy->ReplyMsg(m_data, shared_define::mes_message::REP_INVALIDITY_CODE, "Message too long");
			return false;

		}

		////电文尾校验 end = 10
		if (m_data->m_endcode != shared_define::mes_message::END_BYTE)
		{
			ALARM(AL_ERROR, 6104, "%s", "校验电文错误: Invalid message format - end byte not received, 退出~");
			m_log << "校验电文错误: Invalid message format - end byte not received" << end_l;

			//发送响应电文
			m_strategy->ReplyMsg(m_data, shared_define::mes_message::REP_INVALIDITY_CODE, "Invalid message format - end byte not received");
			return false;
		}


		switch (m_data->m_funccode)
		{
		case shared_define::mes_message::DATAMESSAGE:
		case shared_define::mes_message::LIVEMSG:
		{

			if (m_data->m_funccode == shared_define::mes_message::DATAMESSAGE)
			{

				std::string sGenTime(m_data->m_buffer + shared_define::mes_message::GENERATETIME_POS, shared_define::mes_message::GENERATETIME_LEN);

#ifdef ENABLE_DEBUG
				m_log << "\t \t 数据电文中:sGenTime=" << sGenTime.c_str() << end_l;
#endif

				auto data_offset = shared_define::mes_message::HEADER_LENGTH + shared_define::mes_message::GENERATETIME_LEN;
				// extend space
				std::string data_body(m_data->m_buffer + data_offset, std::stoi(m_data->m_length) - data_offset);
				memcpy(m_data->m_buffer, data_body.data(), std::stoi(m_data->m_length) - data_offset);

				m_log << "数据体部分数据:" << m_data->m_buffer << end_l;
				m_log << "数据体部分长度:" << (int)strlen(m_data->m_buffer) << end_l;
			}
		}
		break;

		case shared_define::mes_message::ACKNOLEDGED:
		case shared_define::mes_message::NOTACKNOLEDGED:
		{
			// Ack, Nack
			// pass
		}
		break;

		default:
		{
			ALARM(AL_ERROR, 6105, "Unrecognized function code:%c", m_data->m_funccode);
			m_strategy->ReplyMsg(m_data, shared_define::mes_message::REP_INVALIDITY_CODE, "Unrecognized function code");
		}
		break;
		}

		return true;
	}
	catch (const std::exception& e)
	{
		throw std::logic_error(fmt::format("error in checkMessage, reason: {0}", e.what()));
	}
}

void ERPServices::PrepareL3CoilTransportReport(std::string itemName, int exitAreaNo)
{
	try
	{
		m_log << fmt::format("PrepareL3CoilTransportReport Start: Item '{0}'", itemName).c_str() << end_l;

		mes_l2_msg_define::MLL308 mll308;
		memset(&mll308, 0x00, sizeof(mll308));

		this->SetMessageHeader(mll308.header, "0060", "MLL308");
		memcpy(mll308.GENERATETIME, uni_box::time_tools::getCurrentTime("%Y%m%d%H%M%S", false).c_str(), sizeof(mll308.GENERATETIME));
		memcpy(mll308.COIL_ID, uni_box::utils::PadRight(itemName, sizeof(mll308.COIL_ID), ' ').c_str(), sizeof(mll308.COIL_ID));
		memcpy(mll308.TRACK_PLACE, uni_box::utils::PadRight(std::to_string(exitAreaNo), sizeof(mll308.TRACK_PLACE), ' ').c_str(), sizeof(mll308.TRACK_PLACE));
		mll308.end_character = 0x0a;

		int status1 = 0;
#ifdef TEST_CAST
		ChannelStatus("SendErp", &status1);
		if (status1 == HW_CHNL_WORKING)
		{
			SendData("SendErp", &mll308, sizeof(mll308));
		}
		else
			ALARM(AL_ERROR, 6106, "与L3通道 %s 未建立连接,不向其发送数据！", "SendErp");
#else

		ChannelStatus(shared_define::L3Net::SEND_L3_CHANNEL, &status1);
		if (status1 == HW_CHNL_WORKING)
		{
			SendData(shared_define::L3Net::SEND_L3_CHANNEL, &mll308, sizeof(mll308));
		}
		else
			ALARM(AL_ERROR, 6107, "与L3通道 %s 未建立连接,不向其发送数据！", shared_define::L3Net::SEND_L3_CHANNEL);
#endif 

		m_log << fmt::format("PrepareL3CoilTransportReport End: Item '{0}'", itemName).c_str() << end_l;
	}
	catch (const std::exception& e)
	{
		throw e;
	}
}

void ERPServices::PrepareL3DischargeReport(mes_l2_msg_define::MLL303* datas)
{
	m_log << fmt::format("PrepareL3DischargeReport Start: Item '{0}'", datas->COIL_ID).c_str() << end_l;

	try
	{
		int status1 = 0;
#ifdef TEST_CAST
		ChannelStatus("SendErp", &status1);
		if (status1 == HW_CHNL_WORKING)
		{
			SendData("SendErp", datas, sizeof(mes_l2_msg_define::MLL303));
		}
		else
			ALARM(AL_ERROR, 6108, "与L3通道 %s 未建立连接,不向其发送数据！", "SendErp");
#else

		ChannelStatus(shared_define::L3Net::SEND_L3_CHANNEL, &status1);
		if (status1 == HW_CHNL_WORKING)
		{
			SendData(shared_define::L3Net::SEND_L3_CHANNEL, datas, sizeof(mes_l2_msg_define::MLL303));
		}
		else
			ALARM(AL_ERROR, 6109, "与L3通道 %s 未建立连接,不向其发送数据！", shared_define::L3Net::SEND_L3_CHANNEL);
#endif 
	}
	catch (const std::exception& e)
	{
		ALARM(AL_ERROR, 6110, "向L3发送 MLL303 report失败:%s", e.what());
	}

	m_log << fmt::format("PrepareL3DischargeReport End ").c_str() << end_l;
}

void ERPServices::ReceiveSlabCancelNotify(const shared_define::ID_TYPE prodReqId)
{
	try
	{
		m_log << "Handling HMI delete request request - started" << end_l;

		Message sendMsg;
		sendMsg.SetId(EVENT_DATA_CHANGE_OCCURED);
		sendMsg.AddParam("TB_PDI_ID", (long)prodReqId);
		sendMsg.AddParam("opType", (long)shared_define::mes_message::OperationTypeEnum::L2DeleteCmd);
		sendMsg.Send("TM");
		ALARM(AL_INFO, 6111, "向TM发送L2DeleteCmd事件！TB_PDI ID=%d", prodReqId);

		m_log << "Handling HMI delete request request - end" << end_l;
	}
	catch (const std::exception& e)
	{
		m_log << fmt::format("Failed to handle deletion of '{0}', reason: {1} !", prodReqId, e.what()).c_str() << end_l;
		ALARM(AL_ERROR, 6112, "处理HMI传来板坯吊销操作失败:%s", e.what());
	}
}

void ERPServices::PrepareL3SlabCancelReport(const std::string matId)
{
	try
	{
		m_log << "PrepareL3SlabCancelReport - started, matId:" << matId.c_str() << end_l;
		try
		{
			mes_l2_msg_define::MLL304 ml304;
			this->SetMessageHeader(ml304.header, "0152", "MLL304");
			memcpy(ml304.GENERATETIME, uni_box::time_tools::getCurrentTime("%Y%m%d%H%M%S", false).c_str(), sizeof(ml304.GENERATETIME));


			auto quer_sql = fmt::format("select ID,SLAB_ID,ROLLING_SCHEDULE_ID,SLAB_CALC_WEIGHT,SUBSTATE from TB_PDI where COIL_ID = '{0}'", matId);

			m_log << "执行: " << quer_sql.c_str() << end_l;

			auto res = DB::OracleDB::OracleDML::executeQuery(quer_sql);
			if (!res.rs_.Next())
			{
				throw std::logic_error(fmt::format("Production response '{0}' not found!", matId));
			}

			auto slabId = res.rs_.Get<std::string>("SLAB_ID");
			auto rolling_schedule_id = res.rs_.Get<std::string>("ROLLING_SCHEDULE_ID");

			memcpy(ml304.COIL_ID, uni_box::utils::PadRight(matId, sizeof(ml304.COIL_ID)).c_str(), sizeof(ml304.COIL_ID));
			memcpy(ml304.SLAB_ID, uni_box::utils::PadRight(slabId, sizeof(ml304.SLAB_ID)).c_str(), sizeof(ml304.SLAB_ID));
			memcpy(ml304.ROLLING_SCHED_ID, uni_box::utils::PadRight(rolling_schedule_id, sizeof(ml304.ROLLING_SCHED_ID)).c_str(), sizeof(ml304.ROLLING_SCHED_ID));

			std::shared_ptr<ActualResponseFlyw> act_;

			// 直接将 int 赋值给 char 有问题
			ml304.REJECT_LOCATION = uni_box::utils::Int2Char(res.rs_.Get<int>("SUBSTATE") < 5 ? 0 : 1);
			m_log << "REJECT_LOCATION: " << ml304.REJECT_LOCATION << end_l;


			if (act_ = ActualResponseFlyw::FindOne(res.rs_.Get<shared_define::ID_TYPE>("ID"), shared_define::EquipNames::REJ_DATA, shared_define::PropNames::REJECT_ZONE, 0))
			{
				memcpy(ml304.TAKE_OFF_PLACE, uni_box::utils::PadRight(act_->tValue_, sizeof(ml304.TAKE_OFF_PLACE)).c_str(), sizeof(ml304.TAKE_OFF_PLACE));
				m_log << "REJECT_ZONE: " << act_->tValue_.c_str() << end_l;
			}
			else
			{
				m_log << "查询 REJECT_ZONE 无此记录,赋默认值" << end_l;
				memcpy(ml304.TAKE_OFF_PLACE, std::string(sizeof(ml304.TAKE_OFF_PLACE), ' ').c_str(), sizeof(ml304.TAKE_OFF_PLACE));
			}

			if (act_ = ActualResponseFlyw::FindOne(res.rs_.Get<shared_define::ID_TYPE>("ID"), shared_define::EquipNames::FCE_ENTRY, shared_define::PropNames::SLAB_WEIGHT_ACT, 0))
			{
				memcpy(ml304.SLAB_WEIGHT, uni_box::utils::parseNumberToString(act_->nValue_, "000000").c_str(), sizeof(ml304.SLAB_WEIGHT));
			}
			else
			{
				auto pdi_wei = res.rs_.Get<int>("SLAB_CALC_WEIGHT");
				m_log << "查询 SLAB_WEIGHT_ACT 无此记录,赋PDI值 :" << pdi_wei << end_l;
				memcpy(ml304.SLAB_WEIGHT, uni_box::utils::parseNumberToString(pdi_wei, "000000").c_str(), sizeof(ml304.SLAB_WEIGHT));
			}

			ml304.REJECT_REASON = ' ';
			ml304.SCRAP_OR_TRFBAR = ' ';
			memcpy(ml304.REJECT_TIME, uni_box::time_tools::getCurrentTime("%Y%m%d%H%M%S").c_str(), sizeof(ml304.REJECT_TIME));
			memcpy(ml304.OPERATOR, std::string(sizeof(ml304.OPERATOR), ' ').c_str(), sizeof(ml304.OPERATOR));
			memcpy(ml304.TRANSFER_BAR_THICKN, std::string(sizeof(ml304.TRANSFER_BAR_THICKN), '0').c_str(), sizeof(ml304.TRANSFER_BAR_THICKN));
			memcpy(ml304.TRANSFER_BAR_WIDTH, std::string(sizeof(ml304.TRANSFER_BAR_WIDTH), '0').c_str(), sizeof(ml304.TRANSFER_BAR_WIDTH));
			memcpy(ml304.TRANSFER_BAR_LENGTH, std::string(sizeof(ml304.TRANSFER_BAR_LENGTH), '0').c_str(), sizeof(ml304.TRANSFER_BAR_LENGTH));

			auto shiftinfo = CrewMgtHelper::GetCurrentShiftInfo();
			ml304.SHIFT_NO = shiftinfo._crewName.at(0);
			ml304.SHIFT_TEAM = shiftinfo._shiftName.at(0);

			int status1 = 0;
#ifdef TEST_CAST
			ChannelStatus("SendErp", &status1);
			if (status1 == HW_CHNL_WORKING)
			{
				SendData("SendErp", &ml304, sizeof(ml304));
			}
			else
				ALARM(AL_ERROR, 6113, "与L3通道 %s 未建立连接,不向其发送数据！", "SendErp");
#else

			ChannelStatus(shared_define::L3Net::SEND_L3_CHANNEL, &status1);
			if (status1 == HW_CHNL_WORKING)
			{
				SendData(shared_define::L3Net::SEND_L3_CHANNEL, &ml304, sizeof(ml304));
			}
			else
				ALARM(AL_ERROR, 6114, "与L3通道 %s 未建立连接,不向其发送数据！", shared_define::L3Net::SEND_L3_CHANNEL);
#endif 

			ALARM(AL_INFO, 6115, "向L3 发送 MLL304板坯吊销报告成功!");

		}
		catch (const std::exception& ex)
		{
			//TODO:  失败了,不会执行下面的删除操作!
			ALARM(AL_ERROR, 6116, "准备MLL304报告数据失败:%s", ex.what());
			throw ex;
		}



		//删除记录
		{
			auto sql_del = fmt::format("delete from TB_PDI where COIL_ID = '{0}'", matId);
			m_log << "执行SQL:" << sql_del.c_str() << end_l;

			auto affect = DB::OracleDB::OracleDML::execute(sql_del);

			if (affect < 1)
			{
				ALARM(AL_ERROR, 6117, "删除失败！卷号=%s", matId.c_str());
			}

			m_log << "检测到删除操作,删除TB_PDI 中数据,卷号：" << matId.c_str() << end_l;
		}
		m_log << "PrepareL3SlabCancelReport - end" << end_l;

	}
	catch (const std::exception& e)
	{
		ALARM(AL_ERROR, 6118, "向L3发送MLL304报告失败:%s", e.what());
	}
}

void ERPServices::PrepareL3ProductReport(const std::string matId)
{
	m_log << fmt::format("PrepareL3ProductReport Start: Item '{0}'", matId).c_str() << end_l;

	try
	{
		auto query_305 = fmt::format("select * from v_mill305@lk_pri where Matid = '{0}'", matId);

		m_log << "执行SQL查询V_MLL305： " << query_305.c_str() << end_l;

		auto res = DB::OracleDB::OracleDML::executeQuery(query_305);
		if (!res.rs_.Next())
		{
			ALARM(AL_ERROR, 6119, "查询v_mill305失败,无此记录:matId:%s", matId.c_str());
			throw std::logic_error(fmt::format("v_mill305无此纪录:{0}", query_305));
		}

#pragma region 赋值
		mes_l2_msg_define::MLL305 mll305;
		memset(&mll305, 0x00, sizeof(mll305));
		this->SetMessageHeader(mll305.header, "0264", "MLL305");
		mll305.end_character = 0x0a;
		memcpy(mll305.GENERATETIME, uni_box::time_tools::getCurrentTime("%Y%m%d%H%M%S", false).c_str(), sizeof(mll305.GENERATETIME));

		auto slabId = res.rs_.Get<std::string>("SLAB_ID");
		auto rolling_schedule_id = res.rs_.Get<std::string>("ROLLING_SCHEDULE_ID");

		memcpy(mll305.COIL_ID, uni_box::utils::PadRight(matId, sizeof(mll305.COIL_ID)).c_str(), sizeof(mll305.COIL_ID));
		memcpy(mll305.SLAB_ID, uni_box::utils::PadRight(slabId, sizeof(mll305.SLAB_ID)).c_str(), sizeof(mll305.SLAB_ID));
		memcpy(mll305.ROLLING_SCHED_ID, uni_box::utils::PadRight(rolling_schedule_id, sizeof(mll305.ROLLING_SCHED_ID)).c_str(), sizeof(mll305.ROLLING_SCHED_ID));

		std::string rolling_start_time = (res.rs_.Get<ocilib::Date>("RM_START_TIME").IsValid() ? res.rs_.Get<ocilib::Date>("RM_START_TIME").ToString(DB::OracleDB::default_out_format) : res.rs_.Get<ocilib::Date>("FM_START_TIME").IsValid() ? res.rs_.Get<ocilib::Date>("FM_START_TIME").ToString(DB::OracleDB::default_out_format) : "99999999999999");

		memcpy(mll305.ROLLING_START_TIME, rolling_start_time.substr(0, sizeof(mll305.ROLLING_START_TIME)).c_str(), sizeof(mll305.ROLLING_START_TIME));

		std::string rolling_end_time = (res.rs_.Get<ocilib::Date>("DC_OFF_TIME").IsValid() ? res.rs_.Get<ocilib::Date>("DC_OFF_TIME").ToString(DB::OracleDB::default_out_format) : "99999999999999");
		memcpy(mll305.ROLLING_END_TIME, rolling_end_time.substr(0, sizeof(mll305.ROLLING_END_TIME)).c_str(), sizeof(mll305.ROLLING_END_TIME));

		auto shift_info = CrewMgtHelper::GetCurrentShiftInfo();
		mll305.SHIFT_NO = shift_info._crewName.at(0);
		mll305.SHIFT_TEAM = shift_info._shiftName.at(0);


		if ((res.rs_.Get<int>("PROD_REQ_TEMPLATE") == (int)shared_define::mes_message::ReqTemplateEnum::Plate) ||
			(res.rs_.Get<int>("PROD_REQ_TEMPLATE") == (int)shared_define::mes_message::ReqTemplateEnum::Strip))
		{
#pragma region  Plate Order AND default values for strip orders

			memcpy(mll305.RM_EXIT_SLAB_THICKN, "999999", sizeof(mll305.RM_EXIT_SLAB_THICKN));
			memcpy(mll305.RM_EXIT_SLAB_WIDTH, "99999", sizeof(mll305.RM_EXIT_SLAB_WIDTH));
			memcpy(mll305.RM_EXIT_SLAB_LENGTH, "99999", sizeof(mll305.RM_EXIT_SLAB_LENGTH));
			memcpy(mll305.RM_EXIT_SLAB_TEMP, "9999", sizeof(mll305.RM_EXIT_SLAB_TEMP));

			memcpy(mll305.FM_EXIT_THICKN_AVG, "999999", sizeof(mll305.FM_EXIT_THICKN_AVG));
			memcpy(mll305.FM_EXIT_THICKN_MAX, "999999", sizeof(mll305.FM_EXIT_THICKN_MAX));
			memcpy(mll305.FM_EXIT_THICKN_MIN, "999999", sizeof(mll305.FM_EXIT_THICKN_MIN));
			memcpy(mll305.FM_EXIT_WIDTH_AVG, "99999", sizeof(mll305.FM_EXIT_WIDTH_AVG));
			memcpy(mll305.FM_EXIT_WIDTH_MAX, "99999", sizeof(mll305.FM_EXIT_WIDTH_MAX));
			memcpy(mll305.FM_EXIT_WIDTH_MIN, "99999", sizeof(mll305.FM_EXIT_WIDTH_MIN));
			memcpy(mll305.FM_EXIT_LENGTH, "99999", sizeof(mll305.FM_EXIT_LENGTH));
			memcpy(mll305.COIL_OUTER_DIA, "9999", sizeof(mll305.COIL_OUTER_DIA));
			memcpy(mll305.COIL_WEIGHT_CALC, "999999", sizeof(mll305.COIL_WEIGHT_CALC));
			memcpy(mll305.FM_ENTRY_TEMP_AVG, "9999", sizeof(mll305.FM_ENTRY_TEMP_AVG));
			memcpy(mll305.FM_EXIT_TEMP_AVG, "9999", sizeof(mll305.FM_EXIT_TEMP_AVG));
			memcpy(mll305.COILING_TEMP_AVG, "9999", sizeof(mll305.COILING_TEMP_AVG));
			memcpy(mll305.CROWN_AVG, "99999999", sizeof(mll305.CROWN_AVG));
			memcpy(mll305.CROWN_MAX, "99999999", sizeof(mll305.CROWN_MAX));
			memcpy(mll305.CROWN_MIN, "99999999", sizeof(mll305.CROWN_MIN));
			memcpy(mll305.FLATNESS_AVG, "99999999", sizeof(mll305.FLATNESS_AVG));
			memcpy(mll305.FLATNESS_MAX, "99999999", sizeof(mll305.FLATNESS_MAX));
			memcpy(mll305.FLATNESS_MIN, "99999999", sizeof(mll305.FLATNESS_MIN));
			memcpy(mll305.WEDGE_AVG, "99999999", sizeof(mll305.WEDGE_AVG));
			memcpy(mll305.WEDGE_MAX, "99999999", sizeof(mll305.WEDGE_MAX));
			memcpy(mll305.WEDGE_MIN, "99999999", sizeof(mll305.WEDGE_MIN));

			mll305.COILER_ID = '9';
#pragma endregion


			if (res.rs_.Get<int>("PROD_REQ_TEMPLATE") == (int)shared_define::mes_message::ReqTemplateEnum::Strip)
			{
				try
				{
					mll305.COILER_ID = uni_box::utils::parseNumberToString(res.rs_.Get<int>("DC_NO"), "0").at(0);

					memcpy(mll305.RM_EXIT_SLAB_THICKN, uni_box::utils::parseNumberToString(res.rs_.Get<float>("RM_EXIT_SLAB_THICKN"), "000000").c_str(), sizeof(mll305.RM_EXIT_SLAB_THICKN));

					memcpy(mll305.RM_EXIT_SLAB_WIDTH, uni_box::utils::parseNumberToString(res.rs_.Get<float>("RM_EXIT_SLAB_WIDTH"), "00000").c_str(), sizeof(mll305.RM_EXIT_SLAB_WIDTH));

					memcpy(mll305.RM_EXIT_SLAB_LENGTH, uni_box::utils::parseNumberToString(res.rs_.Get<float>("RM_EXIT_SLAB_LENGTH"), "00000").c_str(), sizeof(mll305.RM_EXIT_SLAB_LENGTH));

					memcpy(mll305.RM_EXIT_SLAB_TEMP, uni_box::utils::parseNumberToString(res.rs_.Get<int>("RM_EXIT_SLAB_TEMP"), "0000").c_str(), sizeof(mll305.RM_EXIT_SLAB_TEMP));

					memcpy(mll305.FM_EXIT_THICKN_AVG, uni_box::utils::parseNumberToString(res.rs_.Get<float>("FM_EXIT_THICKN_AVG"), "000000").c_str(), sizeof(mll305.FM_EXIT_THICKN_AVG));

					memcpy(mll305.FM_EXIT_THICKN_MAX, uni_box::utils::parseNumberToString(res.rs_.Get<float>("FM_EXIT_THICKN_MAX"), "000000").c_str(), sizeof(mll305.FM_EXIT_THICKN_MAX));

					memcpy(mll305.FM_EXIT_THICKN_MIN, uni_box::utils::parseNumberToString(res.rs_.Get<float>("FM_EXIT_THICKN_MIN"), "000000").c_str(), sizeof(mll305.FM_EXIT_THICKN_MIN));

					memcpy(mll305.FM_EXIT_WIDTH_AVG, uni_box::utils::parseNumberToString(res.rs_.Get<float>("FM_EXIT_WIDTH_AVG"), "00000").c_str(), sizeof(mll305.FM_EXIT_WIDTH_AVG));

					memcpy(mll305.FM_EXIT_WIDTH_MAX, uni_box::utils::parseNumberToString(res.rs_.Get<float>("FM_EXIT_WIDTH_MAX"), "00000").c_str(), sizeof(mll305.FM_EXIT_WIDTH_MAX));

					memcpy(mll305.FM_EXIT_WIDTH_MIN, uni_box::utils::parseNumberToString(res.rs_.Get<float>("FM_EXIT_WIDTH_MIN"), "00000").c_str(), sizeof(mll305.FM_EXIT_WIDTH_MIN));

					memcpy(mll305.FM_EXIT_LENGTH, uni_box::utils::parseNumberToString(res.rs_.Get<float>("FM_EXIT_LENGTH"), "00000").c_str(), sizeof(mll305.FM_EXIT_LENGTH));

					std::shared_ptr<ActualResponseFlyw> act_;
					if (act_ = ActualResponseFlyw::FindOne(res.rs_.Get<shared_define::ID_TYPE>("ID"), shared_define::EquipNames::DC, shared_define::PropNames::COIL_OUTER_DIAMETER, 0))
					{
						memcpy(mll305.COIL_OUTER_DIA, uni_box::utils::parseNumberToString(static_cast<int>(act_->nValue_), "0000").c_str(), sizeof(mll305.COIL_OUTER_DIA));
					}
					else
					{
						ALARM(AL_WARNING, 6120, "ActualResponseFlyw 中没有 COIL_OUTER_DIA 记录,无法为COIL_OUTER_DIA赋值，使用默认NonValue!");
						//memcpy(mll305.COIL_OUTER_DIA, uni_box::utils::parseNumberToString(res.rs_.Get<int>("COIL_OUTER_DIA"), "0000").c_str(), sizeof(mll305.COIL_OUTER_DIA));
					}

					// Material density from model not reliable. Always send NON-VALUE per customer request
					//memcpy(mll305.COIL_WEIGHT_CALC, uni_box::utils::parseNumberToString(res.rs_.Get<int>("COIL_WEIGHT_CALC"), "000000").c_str(), sizeof(mll305.COIL_WEIGHT_CALC));

					memcpy(mll305.FM_ENTRY_TEMP_AVG, uni_box::utils::parseNumberToString(res.rs_.Get<int>("FM_ENTRY_TEMP_AVG"), "0000").c_str(), sizeof(mll305.FM_ENTRY_TEMP_AVG));

					memcpy(mll305.FM_EXIT_TEMP_AVG, uni_box::utils::parseNumberToString(res.rs_.Get<int>("FM_EXIT_TEMP_AVG"), "0000").c_str(), sizeof(mll305.FM_EXIT_TEMP_AVG));

					memcpy(mll305.COILING_TEMP_AVG, uni_box::utils::parseNumberToString(res.rs_.Get<int>("COILING_TEMP_AVG"), "0000").c_str(), sizeof(mll305.COILING_TEMP_AVG));

					memcpy(mll305.CROWN_AVG, uni_box::utils::parseNumberToString(res.rs_.Get<float>("CROWN_AVG"), "00000000").c_str(), sizeof(mll305.CROWN_AVG));

					memcpy(mll305.CROWN_MAX, uni_box::utils::parseNumberToString(res.rs_.Get<float>("CROWN_MAX"), "00000000").c_str(), sizeof(mll305.CROWN_MAX));

					memcpy(mll305.CROWN_MIN, uni_box::utils::parseNumberToString(res.rs_.Get<float>("CROWN_MIN"), "00000000").c_str(), sizeof(mll305.CROWN_MIN));

					memcpy(mll305.FLATNESS_AVG, uni_box::utils::parseNumberToString(res.rs_.Get<float>("FLATNESS_AVG"), "00000000").c_str(), sizeof(mll305.FLATNESS_AVG));

					memcpy(mll305.FLATNESS_MAX, uni_box::utils::parseNumberToString(res.rs_.Get<float>("FLATNESS_MAX"), "00000000").c_str(), sizeof(mll305.FLATNESS_MAX));

					memcpy(mll305.FLATNESS_MIN, uni_box::utils::parseNumberToString(res.rs_.Get<float>("FLATNESS_MIN"), "00000000").c_str(), sizeof(mll305.FLATNESS_MIN));


					memcpy(mll305.WEDGE_AVG, uni_box::utils::parseNumberToString(res.rs_.Get<float>("WEDGE_AVG"), "00000000").c_str(), sizeof(mll305.WEDGE_AVG));

					memcpy(mll305.WEDGE_MAX, uni_box::utils::parseNumberToString(res.rs_.Get<float>("WEDGE_MAX"), "00000000").c_str(), sizeof(mll305.WEDGE_MAX));

					memcpy(mll305.WEDGE_MIN, uni_box::utils::parseNumberToString(res.rs_.Get<float>("WEDGE_MIN"), "00000000").c_str(), sizeof(mll305.WEDGE_MIN));

				}
				catch (const std::exception& ex)
				{
					ALARM(AL_ERROR, 6121, "向MLL305赋值时出错:%s", ex.what());
					throw std::logic_error(fmt::format("向MLL305赋值时出错:{}", ex.what()));
				}
			}

		}


#pragma endregion

		int status1 = 0;
#ifdef TEST_CAST
		ChannelStatus("SendErp", &status1);
		if (status1 == HW_CHNL_WORKING)
		{
			SendData("SendErp", &mll305, sizeof(mll305));
		}
		else
			ALARM(AL_ERROR, 6122, "与L3通道 %s 未建立连接,不向其发送数据！", "SendErp");
#else

		ChannelStatus(shared_define::L3Net::SEND_L3_CHANNEL, &status1);
		if (status1 == HW_CHNL_WORKING)
		{
			SendData(shared_define::L3Net::SEND_L3_CHANNEL, &mll305, sizeof(mll305));
		}
		else
			ALARM(AL_ERROR, 6123, "与L3通道 %s 未建立连接,不向其发送数据！", shared_define::L3Net::SEND_L3_CHANNEL);
#endif 

		ALARM(AL_INFO, 6124, "向L3 发送 MLL305产品报告成功!");
	}
	catch (const std::exception& e)
	{
		ALARM(AL_ERROR, 6125, "向L3 发送 MLL305产品报告时出错:%s", e.what());
	}

	m_log << fmt::format("PrepareL3ProductReport End: Item '{0}'", matId).c_str() << end_l;
}

void ERPServices::PrepareL3ChargeReport(std::string itemName)
{
	try
	{
		m_log << fmt::format("PrepareL3ChargeReport Start: Item '{0}'", itemName).c_str() << end_l;


		shared_define::ID_TYPE pdi_id = 0;
		std::string matId;
		std::string slabId;
		std::string rolling_schedule_id;
		std::string target_charge_date;
		std::string slab_calc_weight;

		mes_l2_msg_define::MLL302 mll302;
		memset(&mll302, 0x00, sizeof(mll302));
		this->SetMessageHeader(mll302.header, "0108", "MLL302");
		mll302.end_character = 0x0a;
		try
		{
			auto query_sql = fmt::format("select ID,COIL_ID,SLAB_ID,ROLLING_SCHEDULE_ID,TARGET_CHARGE_DATE,SLAB_CALC_WEIGHT from tb_pdi where COIL_ID='{}'", itemName);
			auto res = DB::OracleDB::OracleDML::executeQuery(query_sql);


			if (res.rs_.Next())
			{
				pdi_id = res.rs_.Get<shared_define::ID_TYPE>("ID");
				matId = res.rs_.Get<std::string>("COIL_ID");
				slabId = res.rs_.Get<std::string>("SLAB_ID");
				rolling_schedule_id = res.rs_.Get<std::string>("ROLLING_SCHEDULE_ID");
				target_charge_date = res.rs_.Get<ocilib::Date>("TARGET_CHARGE_DATE").ToString(DB::OracleDB::default_out_format);
				slab_calc_weight = std::to_string(res.rs_.Get<int>("SLAB_CALC_WEIGHT"));


				memcpy(mll302.COIL_ID, uni_box::utils::PadRight(matId, sizeof(mll302.COIL_ID)).c_str(), sizeof(mll302.COIL_ID));
				memcpy(mll302.SLAB_ID, uni_box::utils::PadRight(slabId, sizeof(mll302.SLAB_ID)).c_str(), sizeof(mll302.SLAB_ID));
				memcpy(mll302.ROLLING_SCHED_ID, uni_box::utils::PadRight(rolling_schedule_id, sizeof(mll302.ROLLING_SCHED_ID)).c_str(), sizeof(mll302.ROLLING_SCHED_ID));
				memcpy(mll302.GENERATETIME, uni_box::time_tools::getCurrentTime("%Y%m%d%H%M%S", false).c_str(), sizeof(mll302.GENERATETIME));

				m_log << fmt::format("查询TB_PDI记录:pdi_id:{0},matId:{1},slabId:{2},rolling_schedule_id:{3}", pdi_id, matId, slabId, rolling_schedule_id).c_str() << end_l;

			}
		}
		catch (std::exception& ex)
		{
			throw std::logic_error(fmt::format("读取TB_PDI时发生错误:{}", ex.what()));
		}

		try
		{
			std::shared_ptr<ActualResponseFlyw> act_;
			if ((act_ = ActualResponseFlyw::FindOne(pdi_id, shared_define::EquipNames::FCE, shared_define::PropNames::FCE_FURNACE_NO, 0)) != nullptr)
			{
				mll302.FURNACE_NO = uni_box::utils::Int2Char(static_cast<int>(act_->nValue_));
				mll302.SHIFT_NO = act_->shift_.at(0);
				mll302.SHIFT_TEAM = act_->crew_.at(0);
			}
			else
			{
				ALARM(AL_WARNING, 6126, "ACTUAL_RESPONSES 中没有 FCE_FURNACE_NO 记录!");
				mll302.FURNACE_NO = '1';
				mll302.SHIFT_NO = '1';
				mll302.SHIFT_TEAM = '2';
			}

			if ((act_ = ActualResponseFlyw::FindOne(pdi_id, shared_define::EquipNames::FCE, shared_define::PropNames::FCE_CHARGE_TIME, 0)) != nullptr)
			{
				memcpy(mll302.CHARGE_TIME, act_->dTValue_.c_str(), act_->dTValue_.size());
			}
			else
			{
				ALARM(AL_WARNING, 6127, "ACTUAL_RESPONSES 中没有 FCE_CHARGE_TIME 记录!");
				memcpy(mll302.CHARGE_TIME, target_charge_date.c_str(), sizeof(mll302.CHARGE_TIME));

			}

			if ((act_ = ActualResponseFlyw::FindOne(pdi_id, shared_define::EquipNames::FCE, shared_define::PropNames::FCE_CHARGE_TEMP, 0)) != nullptr)
			{
				memcpy(mll302.CHARGE_TEMP, uni_box::utils::parseNumberToString(act_->nValue_, "0000").c_str(), sizeof(mll302.CHARGE_TEMP));
			}
			else
			{
				ALARM(AL_WARNING, 6128, "ACTUAL_RESPONSES 中没有 FCE_CHARGE_TEMP 记录!");
				memcpy(mll302.CHARGE_TEMP, "1200", sizeof(mll302.CHARGE_TEMP));
			}

			if ((act_ = ActualResponseFlyw::FindOne(pdi_id, shared_define::EquipNames::FCE_ENTRY, shared_define::PropNames::SLAB_WEIGHT_ACT, 0)) != nullptr)
			{
				memcpy(mll302.SLAB_WEIGHT_ACT, uni_box::utils::parseNumberToString(act_->nValue_, "000000").c_str(), sizeof(mll302.SLAB_WEIGHT_ACT));
			}
			else
			{
				ALARM(AL_WARNING, 6129, "ACTUAL_RESPONSES 中没有 SLAB_WEIGHT_ACT 记录!");
				memcpy(mll302.SLAB_WEIGHT_ACT, slab_calc_weight.c_str(), sizeof(mll302.SLAB_WEIGHT_ACT));
			}

		}
		catch (const std::exception& ex1)
		{
			throw std::logic_error(fmt::format("读取ACTUAL_RESPONSES时发生错误:{}", ex1.what()));
		}


		try
		{
			int status1 = 0;

#ifdef TEST_CAST
			ChannelStatus("SendErp", &status1);
			if (status1 == HW_CHNL_WORKING)
			{
				SendData("SendErp", &mll302, sizeof(mll302));
			}
			else
				ALARM(AL_ERROR, 6130, "与L3通道 %s 未建立连接,不向其发送数据！", "SendErp");
#else
			ChannelStatus(shared_define::L3Net::SEND_L3_CHANNEL, &status1);
			if (status1 == HW_CHNL_WORKING)
			{
				SendData(shared_define::L3Net::SEND_L3_CHANNEL, &mll302, sizeof(mll302));
			}
			else
				ALARM(AL_ERROR, 6131, "与L3通道 %s 未建立连接,不向其发送数据！", shared_define::L3Net::SEND_L3_CHANNEL);
#endif // TEST_CAST

		}
		catch (const std::exception& ex2)
		{
			ALARM(AL_ERROR, 6132, "向L3发送MLL302失败:%s", ex2.what());
		}

		m_log << fmt::format("PrepareL3ChargeReport End: Item '{0}'", itemName).c_str() << end_l;

	}
	catch (const std::exception& e)
	{
		std::string err = fmt::format("准备Charge Report 出错 matId;{0} ,reason:{1}", itemName, e.what()).c_str();
		ALARM(AL_ERROR, 6133, err.c_str());
		m_log << err.c_str() << end_l;
	}
}

void ERPServices::PrepareL3SampleReport(const std::string matId, const std::string sampleTime)
{
	m_log << fmt::format("PrepareL3SampleReport End: matId '{0}', sampleTime:{1}", matId, sampleTime).c_str() << end_l;
	try
	{
		mes_l2_msg_define::MLL306 mll306;
		memset(&mll306, 0x00, sizeof(mll306));
		mll306.end_character = 0x0a;

		this->SetMessageHeader(mll306.header, "0072", "MLL306");
		memcpy(mll306.GENERATETIME, uni_box::time_tools::getCurrentTime("%Y%m%d%H%M%S", false).c_str(), sizeof(mll306.GENERATETIME));
		memcpy(mll306.COIL_ID, uni_box::utils::PadRight(matId, sizeof(mll306.COIL_ID), ' ').c_str(), sizeof(mll306.COIL_ID));
		memcpy(mll306.SAMPLE_TIME, uni_box::utils::PadRight(sampleTime, sizeof(mll306.SAMPLE_TIME), ' ').c_str(), sizeof(mll306.SAMPLE_TIME));

		int status1 = 0;
#ifdef TEST_CAST
		ChannelStatus("SendErp", &status1);
		if (status1 == HW_CHNL_WORKING)
		{
			SendData("SendErp", &mll306, sizeof(mll306));
		}
		else
			ALARM(AL_ERROR, 6134, "与L3通道 %s 未建立连接,不向其发送数据！", "SendErp");
#else

		ChannelStatus(shared_define::L3Net::SEND_L3_CHANNEL, &status1);
		if (status1 == HW_CHNL_WORKING)
		{
			SendData(shared_define::L3Net::SEND_L3_CHANNEL, &mll306, sizeof(mll306));
		}
		else
			ALARM(AL_ERROR, 6135, "与L3通道 %s 未建立连接,不向其发送数据！", shared_define::L3Net::SEND_L3_CHANNEL);
#endif 
		m_log << fmt::format("PrepareL3SampleReport Start: matId '{0}', sampleTime:{1}", matId, sampleTime).c_str() << end_l;

	}
	catch (const std::exception& e)
	{
		ALARM(AL_ERROR, 6136, "The Error in PrepareL3SampleReport :%s", e.what());
	}
}

void ERPServices::PrepareL3WeightReport(const std::string matId, float coilWeight, const std::string weighTime)
{

	try
	{
		m_log << fmt::format("PrepareL3WeightReport Start: matId '{0}', weighTime:{1}, coilWeight:{2} ", matId, weighTime, coilWeight).c_str() << end_l;

		mes_l2_msg_define::MLL307 mll307;
		memset(&mll307, 0x00, sizeof(mll307));
		mll307.end_character = 0x0a;

		memcpy(mll307.GENERATETIME, uni_box::time_tools::getCurrentTime("%Y%m%d%H%M%S", false).c_str(), sizeof(mll307.GENERATETIME));
		this->SetMessageHeader(mll307.header, "0078", "MLL307");

		memcpy(mll307.COIL_ID, uni_box::utils::PadRight(matId, sizeof(mll307.COIL_ID), ' ').c_str(), sizeof(mll307.COIL_ID));

		memcpy(mll307.WEIGHING_TIME, ocilib::Date(weighTime, DB::OracleDB::default_format).ToString(DB::OracleDB::default_out_format).c_str(), sizeof(mll307.WEIGHING_TIME));
		memcpy(mll307.COIL_WEIGHT, uni_box::utils::parseNumberToString(coilWeight, "000000").c_str(), sizeof(mll307.COIL_WEIGHT));


		int status1 = 0;
#ifdef TEST_CAST
		ChannelStatus("SendErp", &status1);
		if (status1 == HW_CHNL_WORKING)
		{
			SendData("SendErp", &mll307, sizeof(mll307));
		}
		else
			ALARM(AL_ERROR, 6137, "与L3通道 %s 未建立连接,不向其发送数据！", "SendErp");
#else

		ChannelStatus(shared_define::L3Net::SEND_L3_CHANNEL, &status1);
		if (status1 == HW_CHNL_WORKING)
		{
			SendData(shared_define::L3Net::SEND_L3_CHANNEL, &mll307, sizeof(mll307));
		}
		else
			ALARM(AL_ERROR, 6138, "与L3通道 %s 未建立连接,不向其发送数据！", shared_define::L3Net::SEND_L3_CHANNEL);
#endif 

		m_log << fmt::format("PrepareL3WeightReport End: matId '{0}', weighTime:{1}, coilWeight:{2} ", matId, weighTime, coilWeight).c_str() << end_l;
	}
	catch (const std::exception& e)
	{
		ALARM(AL_ERROR, 6139, "The error in PrepareL3WeightReport:%s", e.what());
	}
}

void ERPServices::PrepareL3RollChangeReport(void* datas)
{
	try
	{
		ROLL_CHANGE_REPORT roll_datas;
		memset(&roll_datas, 0x00, sizeof(roll_datas));
		memcpy(&roll_datas, datas, sizeof(roll_datas));

		std::string rollId;
		uni_box::utils::CharsToString(roll_datas.roll_id, rollId, sizeof(roll_datas.roll_id));

		m_log << fmt::format("PrepareL3RollChangeReport Start: rollId: {0} ", rollId).c_str() << end_l;

		mes_l2_msg_define::MLL309 mll309;
		memset(&mll309, 0x00, sizeof(mll309));
		mll309.end_character = 0x0a;

		this->SetMessageHeader(mll309.header, "0107", "MLL309");
		memcpy(mll309.GENERATETIME, uni_box::time_tools::getCurrentTime("%Y%m%d%H%M%S", false).c_str(), sizeof(mll309.GENERATETIME));
		memcpy(mll309.ROLL_SET_ID, "          ", sizeof(mll309.ROLL_SET_ID));
		memcpy(mll309.ROLL_TYPE, "  ", sizeof(mll309.ROLL_TYPE));

		try
		{
			mll309.ROLL_KIND = roll_datas.kind;
			memcpy(mll309.ROLL_LOCATION, roll_datas.loc, sizeof(mll309.ROLL_LOCATION));

			memcpy(mll309.ROLL_CHANGE_TIME, roll_datas.charge_time, sizeof(mll309.ROLL_CHANGE_TIME));

			memcpy(mll309.ROLLED_TONNAGE, roll_datas.roll_tons, sizeof(mll309.ROLLED_TONNAGE));
			memcpy(mll309.ROLLED_LENGTH, roll_datas.roll_lens, sizeof(mll309.ROLLED_LENGTH));

			memcpy(mll309.ROLL_ID, roll_datas.roll_id, sizeof(mll309.ROLL_ID));

			int status1 = 0;
#ifdef TEST_CAST
			ChannelStatus("SendErp", &status1);
			if (status1 == HW_CHNL_WORKING)
			{
				SendData("SendErp", &mll309, sizeof(mll309));
			}
			else
				ALARM(AL_ERROR, 6140, "与L3通道 %s 未建立连接,不向其发送数据！", "SendErp");
#else

			ChannelStatus(shared_define::L3Net::SEND_L3_CHANNEL, &status1);
			if (status1 == HW_CHNL_WORKING)
			{
				SendData(shared_define::L3Net::SEND_L3_CHANNEL, &mll309, sizeof(mll309));
			}
			else
				ALARM(AL_ERROR, 6141, "与L3通道 %s 未建立连接,不向其发送数据！", shared_define::L3Net::SEND_L3_CHANNEL);
#endif 
		}
		catch (const std::exception& ex)
		{
			ALARM(AL_ERROR, 6142, "向L3发送MLL309失败:%s", ex.what());
		}



		m_log << fmt::format("PrepareL3RollChangeReport End: rollId '{0}' ", rollId).c_str() << end_l;
	}
	catch (const std::exception& e)
	{
		ALARM(AL_ERROR, 6143, "The error in PrepareL3RollChangeReport:%s", e.what());
	}
}

void ERPServices::HandleProdReqChanged(const std::string& matId, int opType)
{
	try
	{
		m_log << "ERPServices::HandleProdReqChanged " << matId.c_str() << " - start" << end_l;
		auto sql_ = fmt::format("select STATENAME,IN_STATE, ID from TB_PDI where COIL_ID = '{0}'", matId);
		m_log << "执行SQL:" << end_l;
		m_log << sql_.c_str() << end_l;

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
						, matId);


					m_log << "ERPServices::HandleProdReqChanged::InsertCmd 执行更新状态：" << end_l;
					m_log << sql_update.c_str() << end_l;

					auto affect = DB::OracleDB::OracleDML::execute(sql_update);

					if (!affect)
					{
						ALARM(AL_ERROR, 6144, "更新失败！卷号=%s", matId.c_str());
					}


					//触发信号给TM，PRStateChangeOccurred
					::Message sendMsg;
					memset(&sendMsg, 0x00, sizeof(sendMsg));
					sendMsg.SetId(EVENT_STATE_CHANGE_OCCURED);
					sendMsg.AddParam("TB_PDI_ID", id);
					sendMsg.Send("TM");
					ALARM(AL_INFO, 6145, "向TM发送状态改变事件！卷号=%s", matId.c_str());
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
							, matId);


						m_log << "ERPServices::HandleProdReqChanged::UpdateCmd 执行更新状态：" << end_l;
						m_log << sql_update.c_str() << end_l;

						auto affect = DB::OracleDB::OracleDML::execute(sql_update);

						if (!affect)
						{
							ALARM(AL_ERROR, 6146, "更新失败！卷号=%s", matId.c_str());
						}
						//触发信号给TM，PRStateChangeOccurred
						Message sendMsg;
						memset(&sendMsg, 0x00, sizeof(sendMsg));

						sendMsg.SetId(EVENT_STATE_CHANGE_OCCURED);
						sendMsg.AddParam("TB_PDI_ID", id);
						sendMsg.Send("TM");
						ALARM(AL_INFO, 6147, "向TM发送状态改变事件！卷号=%s", matId.c_str());
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
					ALARM(AL_INFO, 6148, "向TM发送数据改变事件！卷号=%s", matId.c_str());
					sendMsg.Send("Model");
					ALARM(AL_INFO, 6149, "向Model发送数据改变事件！卷号=%s", matId.c_str());
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
					ALARM(AL_INFO, 6150, "向TM发送数据改变事件！卷号=%s", matId.c_str());

					//:确认是否可以将一份消息发送给多个进程
					sendMsg.Send("Model");
					ALARM(AL_INFO, 6151, "向Model发送数据改变事件！卷号=%s", matId.c_str());

					m_log << "检测到删除操作,移至TMService中延迟删除,卷号:" << matId.c_str() << end_l;
				}

			}
			break;

			case (int)shared_define::mes_message::OperationTypeEnum::L2DeleteCmd: //3
			case (int)shared_define::mes_message::OperationTypeEnum::SchedCancelCmd: //4
			{
				m_log << "处理L2DeleteCmd 或 SchedCancelCmd 操作..." << end_l;

				if (statename == "RLS" || (statename == "DSPT") || (statename == "DRAFT"))
				{
					// Notify system that the order data has changed
					Message sendMsg;
					memset(&sendMsg, 0x00, sizeof(sendMsg));
					sendMsg.SetId(EVENT_DATA_CHANGE_OCCURED);
					sendMsg.AddParam("TB_PDI_ID", (long)id);
					sendMsg.AddParam("opType", (long)opType);
					sendMsg.Send("TM");
					ALARM(AL_INFO, 6152, "向TM发送数据改变事件！卷号=%s", matId.c_str());
					sendMsg.Send("Model");
					ALARM(AL_INFO, 6153, "向Model发送数据改变事件！卷号=%s", matId.c_str());
				}
				else
				{
					throw std::invalid_argument(fmt::format("matID: {} 不符合 ('RLS', 'DRAFT', 'DSPT') 状态，不予吊销!", matId));
				}
			}
			break;

			default:
				break;
			}
		}
		else
		{
			ALARM(AL_ERROR, 6154, "TB_PDI 中无此记录： matId=%s", matId.c_str());
			throw std::invalid_argument(fmt::format("TB_PDI 中不存在此卷号: {}", matId));
		}
		m_log << "ERPServices::HandleProdReqChanged  - end" << end_l;
	}
	catch (const std::exception& e)
	{
		ALARM(AL_ERROR, 6155, "ERPServices::HandleProdReqChanged 发生错误:%s", e.what());
		throw e;
	}
}

void ERPServices::ProdScheduleCancel(std::vector<std::string>&& matIds, const std::string& ticket, Records& reply)
{

	for (decltype(matIds.size()) i = 0; i < matIds.size(); ++i)
	{
		m_log << "Handling HSI cancel schedule request, matID: " << matIds[i].c_str() << "- started" << end_l;
		try
		{
			this->HandleProdReqChanged(matIds[i], shared_define::mes_message::OperationTypeEnum::SchedCancelCmd);
		}
		catch (const std::exception& e)
		{
			ALARM(AL_ERROR, 6156, "Failed to handle deletion of '{%s}'!", e.what());
			reply[0]["status_code"] = 0;
			reply[0]["msg"] = e.what();
		}

		m_log << "Handling HSI cancel schedule request - end" << end_l;
	}

}

void ERPServices::ProdReqUpdated(const std::string matId, const std::string& ticket, Records& reply)
{
	try
	{
		m_log << "Handling HSI update request request - started" << end_l;
		this->HandleProdReqChanged(matId, shared_define::mes_message::OperationTypeEnum::UpdateCmd);
		m_log << "Handling HSI update request request - end" << end_l;
	}
	catch (const std::exception& e)
	{
		ALARM(AL_ERROR, 6157, "Failed to handle update of '{%s}'!", e.what());
		reply[0]["status_code"] = 0;
		reply[0]["msg"] = e.what();
	}
}

void ERPServices::ProdReqCreated(const std::string matId, const std::string& ticket, Records& reply)
{
	try
	{
		m_log << "Handling HSI create request request - started" << end_l;
		this->HandleProdReqChanged(matId, shared_define::mes_message::OperationTypeEnum::InsertCmd);
		m_log << "Handling HSI create request request - end" << end_l;
	}
	catch (const std::exception& e)
	{
		ALARM(AL_ERROR, 6158, "Failed to handle update of '{%s}'!", e.what());
		reply[0]["status_code"] = 0;
		reply[0]["msg"] = e.what();
	}
}

void ERPServices::SendMESAliveL3()
{

	try
	{
		mes_l2_msg_define::heart_beat heartMsg;
		memcpy(heartMsg.header.msg_len, "0030", sizeof(heartMsg.header.msg_len));
		memcpy(heartMsg.header.msg_id, "999999", sizeof(heartMsg.header.msg_id));
		memcpy(heartMsg.header.msg_send_date, uni_box::time_tools::getCurrentTime("%Y%m%d").c_str(), shared_define::mes_message::DATESEND_LEN);
		memcpy(heartMsg.header.msg_send_time, uni_box::time_tools::getCurrentTime("%H%M%S").c_str(), shared_define::mes_message::TIMESEND_LEN);
		//memcpy(heartMsg.header.send_code, "BO", sizeof(heartMsg.header.send_code));
		memcpy(heartMsg.header.send_code, "ML", sizeof(heartMsg.header.send_code));
		memcpy(heartMsg.header.recv_code, "L3", sizeof(heartMsg.header.recv_code));
		heartMsg.header.flag = 'C';
		heartMsg.end_character = 10;

		int status1 = 0;
#ifdef TEST_CAST
		ChannelStatus("SendErp", &status1);
		if (status1 == HW_CHNL_WORKING)
		{
			SendData("SendErp", &heartMsg, sizeof(heartMsg));
		}
		else
			ALARM(AL_ERROR, 6159, "与L3通道 %s 未建立连接,不向其发送数据！", "SendErp");
#else

		ChannelStatus(shared_define::L3Net::SEND_L3_CHANNEL, &status1);
		if (status1 == HW_CHNL_WORKING)
		{
			SendData(shared_define::L3Net::SEND_L3_CHANNEL, &heartMsg, sizeof(heartMsg));
		}
		else
			ALARM(AL_ERROR, 6160, "与L3通道 %s 未建立连接,不向其发送数据！", shared_define::L3Net::SEND_L3_CHANNEL);
#endif 
	}
	catch (const std::exception& e)
	{
		ALARM(AL_ERROR, 6161, "向L3发送 999999 失败:%s", e.what());

	}
}



