///****************************************************************************
/// @author  : Renaissance
/// @date    : 
/// @file    : 
/// @brief   : 处理电文算法基类,根据不同类型电文,进行不同操作,使用策略模式
///----------------------------------------------------------------------------
///                           Change History
///----------------------------------------------------------------------------
///
///****************************************************************************
#pragma once
#include <memory>
#include "messagedef.h"
class ERPStrategy
{
public:
	virtual ~ERPStrategy() = default;

	/// <summary>
	/// 事件处理器
	/// </summary>
	virtual void EventHandler(std::shared_ptr<msg::Message>& data) = 0;

	/// <summary>
	/// 事件分发器
	/// </summary>
	/// <param name="data"></param>
	virtual void Dispatcher(void* data, const char* sender) = 0;


	/// <summary>
	/// 发送数据
	/// </summary>
	/// <param name="data"></param>
	virtual void Send(const char* ChannelName, const void* Buffer, const long Size) = 0;

	/// <summary>
	/// 应答电文
	/// </summary>
	/// <param name="data">电文数据</param>
	/// <param name="nack_ack_flag">响应表示</param>
	/// <param name="descr">描述</param>
	virtual void ReplyMsg(std::shared_ptr<msg::Message>& data, const char nack_ack_flag, const char* descr) = 0;
};

