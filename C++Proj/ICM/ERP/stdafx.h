
#pragma once


#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif	


#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容

#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 1


#pragma warning(disable : 4146)


#include "MDWlib.h"
#include "HWapi.h"
#include "ipc_message.h"


#pragma  warning(disable : 4146)
#pragma  warning(disable : 4244)			//conversion from 'double' to 'float'

// 在此处引用程序需要的其他标头
