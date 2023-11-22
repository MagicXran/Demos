
///****************************************************************************
/// @author  : Renaissance
/// @date    : 
/// @file    : 心跳策略生产工厂
/// @brief   :
///----------------------------------------------------------------------------
///                           Change History
///----------------------------------------------------------------------------
///
///****************************************************************************


#pragma once
#include "ERPStrategyFactory.h"
#include "ERPHeartConcreteStrategy.h"

class ERPAckStrategyFactory :public ERPStrategyFactory
{
public:
	/// <summary>
	/// 生产心跳策略的工厂
	/// </summary>
	/// <returns></returns>
	virtual std::shared_ptr<ERPStrategy> createEPRConcreteStrategy() override;
};


inline std::shared_ptr<ERPStrategy> ERPAckStrategyFactory::createEPRConcreteStrategy()
{
	return std::make_shared<ERPHeartConcreteStrategy>();
}
