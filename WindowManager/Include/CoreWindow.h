#pragma once

#define WIN32_LEAN_AND_MEAN

#include "Windows.h"	

class CoreWindow
{
public:


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
