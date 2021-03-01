#include "ScreenCapture.h"

ScreenCapture::ScreenCapture()
{
	dwScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	dwScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	hDesktopWnd = NULL;
	bmp = NULL;
	hdc = mdc = NULL;
}

BOOL ScreenCapture::say_cheese()
{
	hDesktopWnd = GetDesktopWindow();
	hdc = GetDC(hDesktopWnd);
	mdc = CreateCompatibleDC(hdc);
	if (!mdc)
	{
		MessageBox(NULL, _T("CreateCompatibleDC has failed"), _T("Failed"), MB_OK);
		return FALSE;
	}

	bmp = CreateCompatibleBitmap(hdc, dwScreenWidth, dwScreenHeight);
	if (!bmp)
	{
		MessageBox(NULL, _T("CreateCompatibleBitmap Failed"), _T("Failed"), MB_OK);
		return FALSE;
	}
	
	HBITMAP holdbmp = (HBITMAP)SelectObject(mdc, bmp);

	if (!BitBlt(mdc, 0, 0, dwScreenWidth, dwScreenHeight, hdc, 0, 0, SRCCOPY))
	{
		MessageBox(NULL, _T("BitBlt has failed"), _T("Failed"), MB_OK);
		return FALSE;
	}	

	paint_mouse();

	GetSystemTime(&now);

	return TRUE;
}

BOOL ScreenCapture::export_image()
{
	if (!bmp)
	{
		MessageBox(NULL, _T("There are no data in buffer. Pls call say_cheese first."), _T("Export Image Failed"), MB_OK);
		return FALSE;
	}
	
	LPTSTR pszTime = new TCHAR[MAX_PATH];
	_stprintf(pszTime, _T("%d%d%d%d%d%d%d"), now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond, now.wMilliseconds);
	if (!BmpCImage::SaveBmp(bmp, pszTime))
	{
		MessageBox(NULL, _T(""), _T("Save Image Failed"), MB_OK);
		return FALSE;
	}

	clear();
	return TRUE;
}

VOID ScreenCapture::clear()
{
	if (bmp != NULL)
		DeleteObject(bmp);
	if (mdc != NULL)
		DeleteObject(mdc);
	if (hdc != NULL)
		ReleaseDC(hDesktopWnd, hdc);

	mdc = hdc = NULL;
	bmp = NULL;
}

BOOL ScreenCapture::paint_mouse()
{
	HDC bufdc = NULL;
	CURSORINFO cursorInfo = { 0 };
	ICONINFO iconInfo = { 0 };
	HBITMAP bmpOldMask = NULL;

	bufdc = ::CreateCompatibleDC(mdc);
	RtlZeroMemory(&iconInfo, sizeof(iconInfo));
	cursorInfo.cbSize = sizeof(cursorInfo);

	GetCursorInfo(&cursorInfo);

	GetIconInfo(cursorInfo.hCursor, &iconInfo);

	bmpOldMask = (HBITMAP)::SelectObject(bufdc, iconInfo.hbmMask);
	BitBlt(mdc, cursorInfo.ptScreenPos.x, cursorInfo.ptScreenPos.y, 20, 20,
		bufdc, 0, 0, SRCAND);

	SelectObject(bufdc, iconInfo.hbmColor);
	BitBlt(mdc, cursorInfo.ptScreenPos.x, cursorInfo.ptScreenPos.y, 20, 20,
		bufdc, 0, 0, SRCPAINT);

	SelectObject(bufdc, bmpOldMask);
	DeleteObject(iconInfo.hbmColor);
	DeleteObject(iconInfo.hbmMask);
	DeleteDC(bufdc);
	return TRUE;
}

ScreenCapture::~ScreenCapture()
{
	hDesktopWnd = NULL;
	clear();
}