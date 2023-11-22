#pragma once

///****************************************************************************
/// @author  : Renaissance
/// @date    : 
/// @file    : 
/// @brief   : 处理与EPR通信全句柄
///				L3级业务逻辑类:
///				包含了缓存数据,解析头部信息,分发处理;
///				报警范围：6100-6200
///----------------------------------------------------------------------------
///                           Change History
///----------------------------------------------------------------------------
///
///****************************************************************************

#include "stdafx.h"
#include "messagedef.h"
#include "ERPStrategyFactory.h"
#include "mes_l2_struct.h"
#include "ipc_message.h"

class ERPServices
{

#pragma region 属性
private:

	// Log tracker
	Trace m_log;

	// data pointer
	std::shared_ptr<msg::Message> m_data;
	//策略指针
	std::shared_ptr<ERPStrategy> m_strategy;

#pragma endregion


#pragma region 构造析构
public:

	ERPServices();

	ERPServices(std::shared_ptr<msg::Message>&& data);
	ERPServices(std::shared_ptr<ERPStrategyFactory>&& strategy, std::shared_ptr<msg::Message>&& data);
	~ERPServices();
#pragma endregion


#pragma region 公共方法
public:

	/// <summary>
	/// 赋值通用头部信息
	/// </summary>
	/// <param name="header"></param>
	/// <param name="len"></param>
	/// <param name="id_"></param>
	void SetMessageHeader(mes_l2_msg_define::common_header& header, const char* len, const char* id_);

	/// <summary>
	/// 事件处理程序,全部电文由此中转
	/// 报警号:6030~6039
	/// </summary>
	/// <param name="type">电文类型</param>
	/// <param name="data">数据</param>
	void  EPRSrvEventHandler();

	/// <summary>
	/// 设置指定策略
	/// 报警号:6060~6070
	/// </summary>
	/// <param name="strategy"></param>
	//void setStrategy(std::shared_ptr<ERPStrategyFactory>& strategy);

	/// <summary>
	/// 校验电文基本信息,过滤电文
	/// 报警号:6040~6050
	/// </summary>
	bool checkMessage();

	/// <summary>
	/// Preparation method of L3 coil transport report
	/// </summary>
	/// <param name="itemName">coil_id</param>
	/// <param name="exitAreaNo">Number of the coil exit area the coil is transfered to</param>
	void PrepareL3CoilTransportReport(std::string itemName, int exitAreaNo);

	/// <summary>
	/// 于RM1中准备数据
	/// </summary>
	/// <param name="datas"></param>
	void PrepareL3DischargeReport(mes_l2_msg_define::MLL303* datas);


	void ReceiveSlabCancelNotify(const shared_define::ID_TYPE prodReqId);

	void PrepareL3SlabCancelReport(const std::string matId);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="datas"></param>
	void PrepareL3ProductReport(const std::string matId);

	/// <summary>
	/// Preparation method of L3 charge report
	/// 报警号:6071~6080
	/// </summary>
	/// <param name="itemName">卷号</param>
	void PrepareL3ChargeReport(std::string itemName);


	void PrepareL3SampleReport(const std::string matId, const std::string sampleTime);


	void PrepareL3WeightReport(const std::string matId, float coilWeight, const std::string weighTime);


	/// <summary>
	/// 整理MLL309信息
	/// </summary>
	/// <param name="startRollId">换辊起始id</param>
	/// <param name="rollNum">换辊个数</param>
	void PrepareL3RollChangeReport(void* datas);



#pragma region HMI Interface


	void HandleProdReqChanged(const std::string& matId, int opType);


	/// <summary>
	/// HMI 传来一组板坯吊销事件
	/// 注意:HMI 保证 待吊销板坯状态必须位于{RLS", "DRAFT", "DSPT"}才可吊销.
	/// </summary>
	/// <param name="matIds"></param>
	void ProdScheduleCancel(std::vector<std::string>&& matIds, const std::string& ticket, Records& reply);


	void ProdReqUpdated(const std::string matId, const std::string& ticket, Records& reply);
	void ProdReqCreated(const std::string matId, const std::string& ticket, Records& reply);
#pragma endregion

	/// <summary>
	/// 发送心跳给L3,每分钟
	/// </summary>
	static void SendMESAliveL3();
#pragma endregion


};

