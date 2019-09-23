// stdafx.h: 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 项目特定的包含文件
//

#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
//////////////////////////////////////////////////////////
//*
//*     功能: 头文件
//*
//////////////////////////////////////////////////////////
#include <windows.h>
#include <TlHelp32.h> 
#include <D3D11.h>
#include <Shlwapi.h>

#define Exit() TerminateProcess(GetCurrentProcess(),0)
#define ValidPointer( pointer ) ( pointer != NULL && (DWORD_PTR)pointer >= 0x10000 && (DWORD_PTR)pointer < 0x000F000000000000)
#define QWORD unsigned __int64
