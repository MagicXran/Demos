
///****************************************************************************
/// @author  : Renaissance
/// @date    : 
/// @file    : 
/// @brief   :报警号范围: 6201~6300
///----------------------------------------------------------------------------
///                           Change History
///----------------------------------------------------------------------------
///
///****************************************************************************

#pragma once
#include "DBOraclePool.hpp"
#include "stdafx.h"
#include "ERPStrategy.h"


class ERPAckConcreteStrategy :
	public ERPStrategy
{

private:
	Trace  m_log;

public:
	ERPAckConcreteStrategy();
	~ERPAckConcreteStrategy() = default;
public:

	/// <summary>
	/// 报警号范围: 6201~6209
	/// </summary>
	/// <param name="type"></param>
	virtual void EventHandler(std::shared_ptr<msg::Message>& data) override;


	/// <summary>
	/// 报警号范围: 6220~6230
	/// </summary>
	/// <param name="nack_ack_flag">电文传输是否成功标志</param>
	/// <param name="msg_id">电文号 L3ML01</param>
	/// <param name="descr">描述</param>
	virtual void ReplyMsg(std::shared_ptr<msg::Message>& data, const char nack_ack_flag, const char* descr) override;


	virtual void Dispatcher(void* data, const char* sender) override;

	virtual void Send(const char* ChannelName, const void* Buffer, const long Size) override;

};

