#include "stdafx.h"
#include "Hooks.h"
#include "Hooker.h"
#include "Data.h"
#include "Interface.h"
#include "imgui/imgui.h"
#include "imgui/examples/imgui_impl_dx11.h"
#include "imgui/examples/imgui_impl_win32.h"

namespace Hooker
{
	tD3D11Present oPresent;
	WNDPROC oWndProc;

	IDXGISwapChain* pSwapChain;
	ID3D11Device* pDevice;
	ID3D11DeviceContext* pContext;
}

bool g_InitUI_Finished;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Hooker
{
	HRESULT hkD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		if (!g_InitUI_Finished)
		{
			Hooker::pSwapChain = pSwapChain;

			if (!SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void **)&Hooker::pDevice))) 
				Exit();

			pSwapChain->GetDevice(__uuidof(Hooker::pDevice), (void**)&Hooker::pDevice);

			Hooker::pDevice->GetImmediateContext(&Hooker::pContext);

			IMGUI_CHECKVERSION();

			ImGui::CreateContext();

			ImGuiIO& io = ImGui::GetIO();

			ImGui::StyleColorsDark();

			ImGui_ImplWin32_Init(WindowInfo_ImGui::hWnd);

			ImGui_ImplDX11_Init(Hooker::pDevice, Hooker::pContext);

			ImFont* font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 15.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());

			if (font == NULL)
			{
				MessageBoxA(WindowInfo_ImGui::hWnd, "Font not found.", "Error: ", MB_ICONHAND);
				Exit();
			}

			g_InitUI_Finished = true;

			Hooks::HookMessage();
		}
		 
		bool InitializaedpRenderTargetView = false;
		ID3D11RenderTargetView* pRenderTargetView = nullptr;
		ID3D11Texture2D* renderTargetTexture = nullptr;

		if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&renderTargetTexture))))
		{
			if (SUCCEEDED(Hooker::pDevice->CreateRenderTargetView(renderTargetTexture, NULL, &pRenderTargetView)))
			{
				InitializaedpRenderTargetView = true;
			}
			renderTargetTexture->Release();
		}

		Interface::Draw(InitializaedpRenderTargetView, pRenderTargetView);

		HRESULT result = Hooker::oPresent(pSwapChain, SyncInterval, Flags);

		if (InitializaedpRenderTargetView)
			pRenderTargetView->Release();

		return result;
	}

	LRESULT CALLBACK hkWndProc(HWND hWnd, UINT Msg, WPARAM wp, LPARAM lp)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, Msg, wp, lp);
		return Hooker::oWndProc(hWnd, Msg, wp, lp);
	}
}