///****************************************************************************
/// @author  : Renaissance                                                        
/// @date    :                                                                 
/// @file    :                                                                 
/// @brief   :  定义与L3级通信电文基类                                                               
///----------------------------------------------------------------------------
///                           Change History                                   
///----------------------------------------------------------------------------
///                              
///****************************************************************************

#pragma once
#include "messagedef.h"

namespace msg
{
	class ERPMessage :
		public Message
	{

	public:
		/// <summary>
		/// 构造函数:缓存数据
		/// </summary>
		/// <param name="data"></param>
		ERPMessage(const void* data);
		~ERPMessage();
	private:
		/// <summary>
		/// 解析电文头
		/// </summary>
		virtual void ParseMessage() override;

	};
}


