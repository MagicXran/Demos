
///****************************************************************************
/// @author  : Renaissance
/// @date    : 
/// @file    : 具体的接收L3下发计划的策略,其中有实际的动作;
///				 调用机理: ERPOrderStrategyFactory-->ERPStrategyFactory-->ERPStrategy-->ERPOrderConcreteStrategy
/// @brief   :
///				报警范围：6200-6300
///----------------------------------------------------------------------------
///                           Change History
///----------------------------------------------------------------------------
///
///****************************************************************************

#pragma once
#include <mutex>

#include "ERPStrategy.h"
#include "DBOraclePool.hpp"
#include "stdafx.h"
#include "mes_l2_struct.h"



class ERPOrderConcreteStrategy :
	public ERPStrategy
{
private:
	Trace  m_log;
	std::mutex m_mtx;
	int		m_opr_mode; //动作模式,
	//int		m_in_state; //状态

public:
	~ERPOrderConcreteStrategy();
	ERPOrderConcreteStrategy();

public:
	/// <summary>
	/// 管理L3下发的轧制计划处理器
	/// 报警号范围: 6101~6130
	/// </summary>
	virtual void EventHandler(std::shared_ptr<msg::Message>& data) override;

	/// <summary>
	/// 应答电文
	/// 报警号范围: 6131~6139
	/// </summary>
	/// <param name="nack_ack_flag">电文传输是否成功标志: A or B</param>
	/// <param name="msg_id">电文号 L3ML01</param>
	/// <param name="descr">描述</param>
	virtual void ReplyMsg(std::shared_ptr<msg::Message>& data, const char nack_ack_flag, const char* descr) override;


	/// <summary>
	/// 事件分发器,向其它进程分发事件
	/// 报警号范围: 6140~6750
	/// </summary>
	/// <param name="data">数据</param>
	[[deprecated("废弃不用")]]
	virtual void Dispatcher(void* data, const char* sender) override;


	/// <summary>
	/// send datas to Link
	/// 报警号范围: 6140~6149
	/// </summary>
	/// <param name="ChannelName"></param>
	/// <param name="Buffer"></param>
	/// <param name="Size"></param>
	virtual void Send(const char* ChannelName, const void* Buffer, const long Size) override;


public:

	/// <summary>
	/// 将L3下发计划存入数据库，准备发给TM数据
	/// 报警号范围: 6780~6800
	/// </summary>
	/// <param name="matId"></param>
	/// <param name="opCode"></param>
	[[deprecated("废弃")]]
	void PrepareTMPDIData(void* datas, int opCode, void* out_) {};

	/// <summary>
	/// PDI消息预处理，将L3下发计划存入数据库，准备发给TM数据
	/// note: 将L3下发的值原封不动存入TB_PDI中，其中若是需要用到二级本地工艺表，则根据下发的flag进行手动判断
	/// 报警号范围: 6150~6180
	/// </summary>
	/// <param name="matId"></param>
	/// <param name="opCode"></param>
	void PreProcessMsgData(void* datas, shared_define::mes_message::ReqTemplateEnum orderType);


	/// <summary>
	/// 请求转移分发
	/// 报警号范围: 6181~6199
	/// </summary>
	/// <param name="matId"></param>
	/// <param name="opCode"></param>
	void HandleProdReqChanged(const std::string& prodReqId, int opType);

};


