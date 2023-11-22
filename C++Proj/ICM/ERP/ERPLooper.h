///****************************************************************************
/// @author  : Renaissance                                                        
/// @date    :                                                                 
/// @file    :                                                                 
/// @brief   : L3通信进程;
/// @note	 : 报警号:6000~6100
///----------------------------------------------------------------------------
///                           Change History                                   
///----------------------------------------------------------------------------
///                              
///****************************************************************************

#pragma once
#include "DBOraclePool.hpp"
#include "MDWlib.h"

class ERPLooper : public MsgLooper
{

private:
	Trace			m_log;

public:

	ERPLooper();
	~ERPLooper();

	/// <summary>
	/// </summary>
	/// <param name="RevMsg"></param>
	void Dispatcher(const Message& RevMsg);

	/// <summary>
	/// </summary>
	/// <param name="Timer"></param>
	void Cycle(WORD Timer);
};


