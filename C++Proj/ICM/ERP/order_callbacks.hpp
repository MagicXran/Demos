///****************************************************************************
/// @author  : Renaissance                                                        
/// @date    :                                                                 
/// @file    :                                                                 
/// @brief   :  用于处理L3回调函数类                                                               
///----------------------------------------------------------------------------
///                           Change History                                   
///----------------------------------------------------------------------------
///                              
///****************************************************************************
#pragma once
#include "DBOraclePool.hpp"
#include "universal_toolbox.hpp"
#include "common.hpp"



namespace mes_callback
{
	/// <summary>
	/// 保存L3下发的订单数据
	/// </summary>
	/// <param name="rs"></param>
	/// <returns></returns>
	inline bool saveOrder(const ocilib::Resultset& rs)
	{

		return true;
	}
}
