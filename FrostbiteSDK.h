#pragma once
#include "VFTManager.h"
#include "Data.h"

class DxDisplaySettings {};

struct RenderScreenInfo
{
	unsigned int width; //0x0000 
	unsigned int height; //0x0004 
	unsigned int windowWidth; //0x0008 
	unsigned int windowHeight; //0x000C
};//Size=0x0010

class SwapChainClass
{
public:
	char pad_0x0[0x10];
	IDXGISwapChain* m_pSwapChain; //this+0x10
};

class Screen
{
public:
	char _0x0000[0x68];
	RenderScreenInfo m_ScreenInfo; //0x0068 
	char _0x0078[0x288];
	SwapChainClass* m_ptrSwapChain; //0x0300
	char _0x0308[0x30];
	class Dx11RenderTargetView* m_pDefaultRenderView; //0x0338 [=> https://www.unknowncheats.me/forum/1817135-post1239.html ]
};

class DxRenderer
{
public:
	char pad_0x0[0x910];
	Screen* m_pScreen; //this+0x910
	char pad_0x918[0x70];
	ID3D11Device* m_pDevice; //this+0x988
	ID3D11DeviceContext* m_pContext; //this+0x990
public:
	POINT GetClientRect()
	{
		Screen* pScreen = GetScreenByNumber(NULL);
		if (ValidPointer(pScreen))
		{
			return *(POINT*)&pScreen->m_ScreenInfo.width;
		}
		return { 0,0 };
	}
	Screen* GetScreenByNumber(unsigned int ScreenNbr) //用屏幕编号获取Screen* 感觉已经无效
	{
		return  (Screen*)((DWORD_PTR)((DWORD_PTR)this->getScreenInfo(ScreenNbr) - (DWORD_PTR)0x68));
	}
	unsigned int GetNumberOfScreens() // index: 13   获取屏幕编号
	{
		return VTManager::vfunc<unsigned int(__thiscall *)(void*)>(this, 13)(this);
	}
	RenderScreenInfo* getScreenInfo(unsigned int ScreenNbr) // index: 14   获取屏幕信息
	{
		return VTManager::vfunc<RenderScreenInfo*(__thiscall *)(void*, unsigned int)>(this, 14)(this, ScreenNbr);
	}

	DxDisplaySettings* getDxDisplaySettings()
	{
		return VTManager::vfunc<DxDisplaySettings*(__thiscall *)(void*)>(this, 53)(this);
	}

	static DxRenderer* GetInstance()
	{
		DxRenderer** ppDxRenderer = reinterpret_cast<DxRenderer**>(DATA::OFFSET_DXRENDERER);
		if (!ValidPointer(ppDxRenderer)) return NULL;
		return *(DxRenderer**)(ppDxRenderer);
	}
};