#pragma once
#include "stdafx.h"

namespace VTManager
{
	template<typename T> inline T vfunc(void *base, int index)
	{
		QWORD *vTabella = *(QWORD**)base;
		return (T)vTabella[index];
	}
}
