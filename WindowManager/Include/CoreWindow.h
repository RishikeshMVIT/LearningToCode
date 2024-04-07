#pragma once

#define WIN32_LEAN_AND_MEAN

#include "Windows.h"	

class CoreWindow
{
public:
	CoreWindow();
	~CoreWindow();

	bool Initialize(int width, int height)
	{
		WNDCLASSEXW wcex = {};
		wcex.cbSize = sizeof(WNDCLASSEXW);
		wcex.style = CS_OWNDC;
		wcex.lpfnWndProc = nullptr;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = GetModuleHandleW(nullptr);
		wcex.hIcon = LoadIconW(IDI_APPLICATION);
		wcex.hCursor = LoadCursorW(IDC_ARROW);
		wcex.hbrBackground = nullptr;
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = "CoreWindow";
		wcex.hIconSm = LoadIconW(IDI_APPLICATION);

		m_windowClass = RegisterClassExW(&wcex);

		if (!m_windowClass)
			return false;

		m_windowHandle = CreateWindowExW(
			WS_EX_OVERLAPPEDWINDOW,
			LPCWSTR(m_windowClass),
			L"Core Window",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			width, height,
			nullptr,
			nullptr,
			GetModuleHandleW(nullptr),
			nullptr
		);

		if (!m_windowClass)
			return false;

		ShowWindow(m_windowHandle, SW_SHOW);

		return true;
	}
	
	void Shutdown()
	{
		if (m_windowHandle)
			DestroyWindow(m_windowHandle);

		if (m_windowClass)
			UnregisterClassW((LPCWSTR)m_windowClass, nullptr);
	}

private:
	int width, height;
	HWND m_windowHandle;
	ATOM m_windowClass;
};

enum WindowType
{
	COREWINDOW,,
	PANEL,
	TOOLTIP,
	LOADINGSCREEN,
	SPLASHSCREEN
};
