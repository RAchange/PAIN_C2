#include "PipeCmd.h"

PipeCmd::PipeCmd()
{
	hReadPipe = NULL;
	hWritePipe = NULL;
}

BOOL PipeCmd::execute(LPCTSTR pszCmd, LPTSTR pszResultBuffer, DWORD dwResultBufferSize)
{
	hReadPipe = NULL;
	hWritePipe = NULL;
	SECURITY_ATTRIBUTES securityAttributes = { 0 };
	BOOL bRet = FALSE;
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	securityAttributes.bInheritHandle = TRUE;
	securityAttributes.nLength = sizeof(securityAttributes);
	securityAttributes.lpSecurityDescriptor = NULL;
	bRet = CreatePipe(&hReadPipe, &hWritePipe, &securityAttributes, 0);
	if (bRet == FALSE)
	{
		MessageBox(NULL, _T("CreatePipe"), _T("Failed"), MB_OK);
		return FALSE;
	}
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.wShowWindow = SW_HIDE;
	si.hStdError = hWritePipe;
	si.hStdOutput = hWritePipe;
	bRet = CreateProcess(NULL, (LPTSTR)pszCmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	if (bRet == FALSE)
	{
		MessageBox(NULL, _T("CreateProcess"), _T("Failed"), MB_OK);
	}
	WaitForSingleObject(pi.hThread, INFINITE);
	WaitForSingleObject(pi.hProcess, INFINITE);
	
	RtlZeroMemory(pszResultBuffer, dwResultBufferSize);
	ReadFile(hReadPipe, pszResultBuffer, dwResultBufferSize, NULL, NULL);
	
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	CloseHandle(hWritePipe);
	CloseHandle(hReadPipe);

	return TRUE;
}

PipeCmd::~PipeCmd()
{
}