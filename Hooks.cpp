#include "stdafx.h"
#include "FrostbiteSDK.h"
#include "Hooker.h"

namespace Hooks
{
	void HookD3D11()
	{
		DxRenderer* pDxRenderer = DxRenderer::GetInstance();

		if (!ValidPointer(pDxRenderer))
			Exit();

		DxDisplaySettings* pDxDisplaySettings = pDxRenderer->getDxDisplaySettings();

		if (!ValidPointer(pDxDisplaySettings))
			Exit();

		Screen* pScreen = pDxRenderer->GetScreenByNumber(NULL);

		if (!ValidPointer(pScreen))
			Exit();

		IDXGISwapChain* sc = pScreen->m_ptrSwapChain->m_pSwapChain;

		if (!ValidPointer(sc))
			Exit();

		QWORD* EngineSwapChainVT = *(QWORD**)(sc);

		if (!ValidPointer(EngineSwapChainVT))
			Exit();

		DWORD old;
		Hooker::oPresent = reinterpret_cast<tD3D11Present>((BYTE*)EngineSwapChainVT[8]);
		if (VirtualProtect(&EngineSwapChainVT[8], sizeof(__int64), PAGE_EXECUTE_READWRITE, &old))
		{
			EngineSwapChainVT[8] = (QWORD)Hooker::hkD3D11Present;
			if (!VirtualProtect(&EngineSwapChainVT[8], sizeof(__int64), old, &old))
				Exit();
		}
	}

	void HookMessage()
	{
		Hooker::oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(WindowInfo_ImGui::hWnd, GWLP_WNDPROC, (QWORD)Hooker::hkWndProc));
	}
} 