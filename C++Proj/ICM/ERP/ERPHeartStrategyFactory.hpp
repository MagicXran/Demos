
///****************************************************************************
/// @author  : Renaissance
/// @date    : 
/// @file    : ����������������
/// @brief   :
///----------------------------------------------------------------------------
///                           Change History
///----------------------------------------------------------------------------
///
///****************************************************************************


#pragma once
#include "ERPStrategyFactory.h"
#include "ERPHeartConcreteStrategy.h"

class ERPHeartStrategyFactory :public ERPStrategyFactory
{
public:
	/// <summary>
	/// �����������ԵĹ���
	/// </summary>
	/// <returns></returns>
	virtual std::shared_ptr<ERPStrategy> createEPRConcreteStrategy() override;
};


inline std::shared_ptr<ERPStrategy> ERPHeartStrategyFactory::createEPRConcreteStrategy()
{
	return std::make_shared<ERPHeartConcreteStrategy>();
}
