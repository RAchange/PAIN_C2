#include "EnumProcess.h"

EnumProcess::EnumProcess()
{
	update_list();
}

BOOL EnumProcess::update_list() {
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	processList.clear();

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		LPTSTR errorMessage = new TCHAR[100];
		_stprintf(errorMessage, _T("CreateToolhelp32Snapshot:%d"), GetLastError());
		MessageBox(NULL, _T("CreateToolhelp32Snapshot"), _T("EnumProcess Error"), MB_OK);
		delete[] errorMessage;
		return FALSE;
	}

	BOOL bRet = Process32First(hProcessSnap, &pe32);
	while (bRet)
	{
		processList.insert(std::pair<int, std::tstring>(pe32.th32ProcessID, std::tstring(pe32.szExeFile)));
		bRet = Process32Next(hProcessSnap, &pe32);
	}

	CloseHandle(hProcessSnap);

	return TRUE;
}


std::map<int, std::tstring> EnumProcess::get_list()
{
	return processList;
}

EnumProcess::~EnumProcess()
{
	if(hProcessSnap != INVALID_HANDLE_VALUE)
		CloseHandle(hProcessSnap);
}