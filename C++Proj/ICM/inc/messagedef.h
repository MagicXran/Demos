///****************************************************************************
/// @author  : Renaissance                                                        
/// @date    :                                                                 
/// @file    :                                                                 
/// @brief   : 定义通信电文基类                                                      
///----------------------------------------------------------------------------
///                           Change History                                   
///----------------------------------------------------------------------------
///                              
///****************************************************************************

#pragma once
#include "project_shared.h"
namespace msg
{
	class Message
	{

	public:

		////	数据体缓存:去除电文头
		char	m_buffer[shared_define::mes_message::MAX_BYTES_ALLOWED];

		/// <summary>
		/// 整形电文id
		/// </summary>
		int  m_id;

		/// <summary>
		/// 电文长度
		/// </summary>
		int  m_len;

		/// <summary>
		/// 计数器
		/// </summary>
		int m_counter = 0;

		//	电文号
		std::string			m_identity ;
		//	电文长度
		std::string			m_length;
		//	date: 20230203
		std::string			m_date ;
		//	time: 121201
		std::string			m_time ;
		//	"发送端"
		std::string			m_sender ;
		//	"接收端"
		std::string			m_recver;
		//	"功能码"
		char				m_funccode;
		//	"结束符"
		int					m_endcode ;


	public:
		msg::Message() {
			memset(m_buffer, 0x00, shared_define::mes_message::MAX_BYTES_ALLOWED);
		};

		virtual ~Message() {
		};


	public:

		/// <summary>
		/// 解析电文头
		/// </summary>
		virtual void ParseMessage() = 0;

	};

	class Link
	{
	public:
		Link() = default;
		virtual ~Link() = default;

	public:
		virtual void Send(const void* Buffer, const long Size) = 0;
	private:

	};
}


