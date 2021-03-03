#pragma once
#include <Windows.h>
#include <tchar.h>
#include <list>
#include <vector>
#include <iostream>

typedef struct FileObj {
	DWORD dwAttr;
	TCHAR fileName[MAX_PATH];
	std::vector<FileObj> childs;
} FileObj, *PFileObj;

class SearchFile
{
	HANDLE hFile;
	LPTSTR pszFileName, pszDirectory;
	std::vector<FileObj> childs;
public:
	SearchFile(LPCTSTR);
	~SearchFile();
	BOOL update_tree();
	std::vector<FileObj> get_tree();
};

std::ostream& operator<<(std::ostream&, const FileObj&);