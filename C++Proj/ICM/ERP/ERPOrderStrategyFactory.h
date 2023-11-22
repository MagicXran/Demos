///****************************************************************************
/// @author  : Renaissance
/// @date    : 
/// @file    : 
/// @brief   : 订单类策略,主要用于生成处理接收L3下发轧制计划的类的工厂
///----------------------------------------------------------------------------
///                           Change History
///----------------------------------------------------------------------------
///
///****************************************************************************

#pragma once
#include "ERPStrategyFactory.h"
#include "ERPOrderConcreteStrategy.h"


class ERPOrderStrategyFactory :
	public ERPStrategyFactory
{
public:
	/// <summary>
	/// 生产订单策略的工厂
	/// </summary>
	/// <returns></returns>
	virtual std::shared_ptr<ERPStrategy> createEPRConcreteStrategy() override;
};

