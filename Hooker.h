#pragma once
#include "stdafx.h"

typedef HRESULT(__stdcall* tD3D11Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

namespace Hooker
{
	extern tD3D11Present oPresent;
	extern WNDPROC oWndProc;

	extern IDXGISwapChain* pSwapChain;
	extern ID3D11Device* pDevice;
	extern ID3D11DeviceContext* pContext;
}

namespace Hooker
{
	HRESULT hkD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	LRESULT CALLBACK hkWndProc(HWND, UINT, WPARAM, LPARAM);
}