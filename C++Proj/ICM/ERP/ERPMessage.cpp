#include "ERPMessage.h"
#include "fmt/core.h"
#include <iostream>
msg::ERPMessage::ERPMessage(const void* data)
{
	try
	{
		m_length.assign(static_cast<const char*>(data) + shared_define::mes_message::LENGTH_POS, shared_define::mes_message::LENGTH_LEN);

		memcpy(m_buffer, data, std::stoi(m_length));
		if (!data)
		{
			throw std::invalid_argument("data of receive is nullptr in ERPMessage(data)~");
		}

		// 解析电文头
		this->ParseMessage();
	}
	catch (const std::exception& e)
	{
		std::logic_error(fmt::format("解析消息时出错：{0}", e.what()));
	}
}

msg::ERPMessage::~ERPMessage()
{
}

void msg::ERPMessage::ParseMessage()
{
	try
	{
		////解析电文号
		//memset(m_identity, 0x00, shared_define::mes_message::IDENTITY_LEN + 1);
		//strncpy(m_identity, m_buffer + shared_define::mes_message::IDENTITY_POS, shared_define::mes_message::IDENTITY_LEN);
		////解析长度
		//memset(m_length, 0x00, shared_define::mes_message::LENGTH_LEN + 1);
		//strncpy(m_length, m_buffer + shared_define::mes_message::LENGTH_POS, shared_define::mes_message::LENGTH_LEN);
		////解析发送端
		//memset(m_sender, 0x00, shared_define::mes_message::SENDER_LEN + 1);
		//strncpy(m_sender, m_buffer + shared_define::mes_message::SENDER_POS, shared_define::mes_message::SENDER_LEN);
		////解析接收端
		//memset(m_recver, 0x00, shared_define::mes_message::RECEIVER_LEN + 1);
		//strncpy(m_recver, m_buffer + shared_define::mes_message::RECEIVER_POS, shared_define::mes_message::RECEIVER_LEN);

		////解析日期
		//memset(m_date, 0x00, shared_define::mes_message::DATESEND_LEN + 1);
		//strncpy(m_date, m_buffer + shared_define::mes_message::DATESEND_POS, shared_define::mes_message::DATESEND_LEN);

		////解析时间
		//memset(m_time, 0x00, shared_define::mes_message::TIMESEND_LEN + 1);
		//strncpy(m_time, m_buffer + shared_define::mes_message::TIMESEND_POS, shared_define::mes_message::TIMESEND_LEN);

		////解析功能码
		////memset(m_funccode, 0x00, shared_define::mes_message::FUNCCODE_LEN + 1);
		//strncpy(&m_funccode, m_buffer + shared_define::mes_message::FUNCCODE_POS, shared_define::mes_message::FUNCCODE_LEN);
		////解析尾部结束符
		////memcpy(&m_endcode, m_buffer + ,);
		//m_endcode = m_buffer[std::stoi(m_length) - 1];


		m_identity.assign(m_buffer, shared_define::mes_message::IDENTITY_POS, shared_define::mes_message::IDENTITY_LEN);

		m_sender.assign(m_buffer + shared_define::mes_message::SENDER_POS, shared_define::mes_message::SENDER_LEN);
		m_recver.assign(m_buffer + shared_define::mes_message::RECEIVER_POS, shared_define::mes_message::RECEIVER_LEN);
		m_date.assign(m_buffer + shared_define::mes_message::DATESEND_POS, shared_define::mes_message::DATESEND_LEN);
		m_time.assign(m_buffer + shared_define::mes_message::TIMESEND_POS, shared_define::mes_message::TIMESEND_LEN);

		strncpy(&m_funccode, m_buffer + shared_define::mes_message::FUNCCODE_POS, shared_define::mes_message::FUNCCODE_LEN);
		m_endcode = m_buffer[std::stoi(m_length) - 1];
	}
	catch (const std::exception& e)
	{
		throw std::logic_error(fmt::format("解析电文时出错:reason:{0}", e.what()));
	}

}

