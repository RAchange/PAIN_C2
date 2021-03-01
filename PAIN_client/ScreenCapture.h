#pragma once
#include <Windows.h>
#include <tchar.h>
#include "BmpCImage.h"

class ScreenCapture
{
	HWND hDesktopWnd;
	HDC hdc, mdc;
	HBITMAP bmp;
	SYSTEMTIME now;
	DWORD dwScreenWidth, dwScreenHeight;
	
public:
	ScreenCapture();
	~ScreenCapture();
	BOOL say_cheese();
	BOOL export_image();
	void clear();

private:
	BOOL paint_mouse();
};

