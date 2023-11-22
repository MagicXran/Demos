#include "ERPAckConcreteStrategy.h"
#include "mes_l2_struct.h"
#include "universal_toolbox.hpp"

ERPAckConcreteStrategy::ERPAckConcreteStrategy() :m_log(__FUNCTION__)
{
}

void ERPAckConcreteStrategy::EventHandler(std::shared_ptr<msg::Message>& data)
{
	try
	{
		//copy data
		mes_l2_msg_define::L3ML03 ack_data;
		memset(&ack_data, 0x00, sizeof(mes_l2_msg_define::L3ML03));
		memcpy(&ack_data, data->m_buffer, sizeof(mes_l2_msg_define::L3ML03));

		std::string msgid;
		msgid.resize(20);

		std::string roll_id;
		roll_id.resize(20);

		std::string RejectReason;
		RejectReason.resize(25);

		int status = 0;
		uni_box::utils::CharsToString(ack_data.MESSAGE_ID, msgid, sizeof(ack_data.MESSAGE_ID));
		uni_box::utils::CharsToString(ack_data.MATERIAL_ID, roll_id, sizeof(ack_data.MATERIAL_ID));
		uni_box::utils::CharsToString(ack_data.REJECT_REASON, RejectReason, sizeof(ack_data.REJECT_REASON));

		if (ack_data.CONFIRM_FLAG == 'Y')
		{
			status = (int)shared_define::SendReportStatus::Acknowledged;
		}
		else
		{
			status = (int)shared_define::SendReportStatus::Rejected;
		}

		//处理 ML309 电文
		if (msgid == "MLL309")
		{
			std::string query_sql = uni_box::utils::string_format("select ID from ROLL_CHANGES where ROLL_ID='%s',STATUS=%d order by ROLL_CHANGE_TIME desc "
				, roll_id.c_str(), (int)shared_define::SendReportStatus::Acknowledged);

			m_log << "执行查询SQL：" << end_l;
			m_log << query_sql.c_str() << end_l;
			m_log << end_t;

			auto res = DB::OracleDB::OracleDML::executeQuery(query_sql);
			if (res.rs_.Next())
			{
				auto id = res.rs_.Get<shared_define::ID_TYPE>("ID");
				std::string upd_sql = uni_box::utils::string_format("update ROLL_CHANGES set STATUS=%d where ID=%lu", status, id);

				m_log << "执行查询SQL：" << end_l;
				m_log << upd_sql.c_str() << end_l;
				m_log << end_t;

				DB::OracleDB::OracleDML::execute(upd_sql);
				ALARM(AL_INFO, 6201, "更新 ROLL_CHANGES 中记录： ID=%d , roll_id=%s", id, roll_id.c_str());
			}
			else
			{
				// Either the roll does not exist or it has already been acknowledged.
				// No action.
			}

		}

		m_log << uni_box::utils::format("HandleAcknowledge End  : MsgId '{%s}', ItemID '{%s}', Flag '{%d}', RejectReason '{%s}'"
			, msgid.c_str(), roll_id.c_str(), ack_data.CONFIRM_FLAG, RejectReason.c_str()).c_str() << end_l;
		m_log << end_t;

	}
	catch (const std::exception& e)
	{
		ALARM(AL_ERROR, 6202, "Error: ", e.what());
	}
}

void ERPAckConcreteStrategy::ReplyMsg(std::shared_ptr<msg::Message>& data, const char nack_ack_flag, const char* descr)
{
}

void ERPAckConcreteStrategy::Dispatcher(void* data, const char* sender)
{
}

void ERPAckConcreteStrategy::Send(const char* ChannelName, const void* Buffer, const long Size)
{
}
