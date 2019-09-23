#include "stdafx.h"
#include "Data.h"

namespace DATA
{
    QWORD OFFSET_DXRENDERER = 0x1447CF588;
}

namespace WindowInfo_ImGui
{
	HWND hWnd;

	BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lParam)
	{
		DWORD dwPid = 0;

		GetWindowThreadProcessId(hWnd, &dwPid);

		if (dwPid == lParam)
		{
			WindowInfo_ImGui::hWnd = hWnd;
			return FALSE;
		}

		return TRUE;
	}

	void GetProcessWindow()
	{
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(PROCESSENTRY32);
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (INVALID_HANDLE_VALUE == hSnapshot)
			Exit();

		if (!Process32First(hSnapshot, &pe))
			Exit();

		do
		{
			if (!Process32Next(hSnapshot, &pe))
				Exit();

		} while (StrCmpA(pe.szExeFile, "bfv.exe"));

		EnumWindows(WindowInfo_ImGui::EnumWindowCallBack, pe.th32ProcessID);

		if (WindowInfo_ImGui::hWnd == NULL)
			Exit();
	}
}