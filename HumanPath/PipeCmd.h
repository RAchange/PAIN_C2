#pragma once
#include <Windows.h>
#include <tchar.h>

class PipeCmd
{
	HANDLE hReadPipe;
	HANDLE hWritePipe;
public:
	PipeCmd();
	BOOL execute(LPCTSTR pszCmd, LPTSTR pszResultBuffer, DWORD dwResultBufferSize);
	~PipeCmd();
};

