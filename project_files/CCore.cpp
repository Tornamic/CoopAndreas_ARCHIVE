#include "stdafx.h"
#include "CCrashLog.h"
#include "Commands/CCustomCommandRegistrar.h"
#include "CDiscordRPC.h"

WNDPROC prevWndProc;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CChat::WndProc(hWnd, message, wParam, lParam);
	return CallWindowProcW(prevWndProc, hWnd, message, wParam, lParam);
}

void InitWndProc()
{
	HWND hWnd = *(HWND*)0xC97C1C;

	SetWindowTextW(hWnd, L"CoopAndreas");
	RsGlobal.appName = "CoopAndreas";

	if (hWnd) 
	{
		prevWndProc = (WNDPROC)GetWindowLongW(hWnd, GWL_WNDPROC);
		SetWindowLongW(hWnd, GWL_WNDPROC, (LONG)WindowProc);
		return;
	}
}

void CCore::Init()
{
#ifdef _DEV
	CCore::AllocateConsole();
#endif
	CPatch::ApplyPatches();
	CHook::Init();
	CCustomCommandRegistrar::Register();
	CDXFont::Init();
	CLaunchManager::CollectCommandLineArgs();
	CDiscordRPC::Init();
	//SetUnhandledExceptionFilter(CCrashLog::ExceptionHandler);
	Events::initGameEvent.after += []
	{
		// init CNetworking async
		CreateThread(NULL, NULL, CNetwork::InitAsync, NULL, NULL, NULL);
		InitWndProc();
	};
	Events::initRwEvent += []
	{
		CPatch::PatchFramerate();
	};
	Events::initScriptsEvent.after += []
	{
		CPatch::TemporaryPatches();
	};
	gameShutdownEvent.before += []
	{
		// disconnect from server
		CNetwork::Disconnect();
	};
}

void CCore::AllocateConsole()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
}
