#pragma once
#include <Windows.h>
#include <tchar.h>
#include <tlhelp32.h>
#include <map>
#include <utility>
#include "tstring.h"


class EnumProcess
{
	HANDLE hProcessSnap;
	std::map<int, std::tstring> processList;
public:
	EnumProcess();
	~EnumProcess();
	BOOL update_list();
	std::map<int, std::tstring> get_list();
};

