
///****************************************************************************
/// @author  : Renaissance
/// @date    : 
/// @file    : 工厂模式: 生产不同类型策略(算法)的抽象工厂,具体工厂需要继承此类
/// @brief   :
///----------------------------------------------------------------------------
///                           Change History
///----------------------------------------------------------------------------
///
///****************************************************************************

#pragma once
#include "ERPStrategy.h"

class ERPStrategyFactory
{
public:
	virtual ~ERPStrategyFactory() = default;

	/// <summary>
	/// 生产具体策略类型
	/// </summary>
	/// <returns></returns>
	virtual std::shared_ptr<ERPStrategy> createEPRConcreteStrategy() = 0;

};

