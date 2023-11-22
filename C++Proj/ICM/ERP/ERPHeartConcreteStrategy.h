
///****************************************************************************
/// @author  : Renaissance
/// @date    : 
/// @file    : 
/// @brief   :
///----------------------------------------------------------------------------
///                           Change History
///----------------------------------------------------------------------------
///
///****************************************************************************

#pragma once
#include "stdafx.h"
#include "ERPStrategy.h"
class ERPHeartConcreteStrategy :
	public ERPStrategy
{
public:

	/// <summary>
	/// 具体的心跳策略
	/// </summary>
	/// <param name="type"></param>
	virtual void EventHandler(std::shared_ptr<msg::Message>& data) override;


	/// <summary>
	/// 应答电文
	/// </summary>
	/// <param name="nack_ack_flag">电文传输是否成功标志</param>
	/// <param name="msg_id">电文号 L3ML01</param>
	/// <param name="descr">描述</param>
	virtual void ReplyMsg(std::shared_ptr<msg::Message>& data, const char nack_ack_flag, const char* descr) override;


	// Inherited via ERPStrategy
	virtual void Dispatcher(void* data, const char* sender) override;

	virtual void Send(const char* ChannelName, const void* Buffer, const long Size) override;

};

