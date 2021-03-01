#include "SearchFile.h"

SearchFile::SearchFile(LPCTSTR pszDirectory)
{
	pszFileName = new TCHAR[MAX_PATH];
	this->pszDirectory = new TCHAR[MAX_PATH];
	_stprintf(pszFileName, _T("%s\\*.*"), pszDirectory);
	_tcscpy(this->pszDirectory, pszDirectory);

	update_tree();
}

BOOL SearchFile::update_tree()
{
	childs.clear();

	WIN32_FIND_DATA FileData;
	FileData = { 0 };

	DWORD dwBufferSize = 2048;
	TCHAR* pTempSrc = NULL;

	BOOL bRet = FALSE;

	SearchFile* tmpSearchFile;

	pTempSrc = new TCHAR[dwBufferSize];
	
	hFile = FindFirstFile(pszFileName, &FileData);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		do {
			if (FileData.cFileName[0] == _T('.'))
			{
				continue;
			}

			_stprintf(pTempSrc, _T("%s\\%s"), pszDirectory, FileData.cFileName);

			PFileObj pTmpFileObj = new FileObj;
			pTmpFileObj->dwAttr = FileData.dwFileAttributes;
			_tcscpy(pTmpFileObj->fileName, pTempSrc);
			pTmpFileObj->childs.clear();
			
			if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				tmpSearchFile = new SearchFile(pTempSrc);
				pTmpFileObj->childs = tmpSearchFile->childs;
				delete tmpSearchFile;
			}
			
			childs.push_back(*pTmpFileObj);
			delete pTmpFileObj;
		} while (FindNextFile(hFile, &FileData));
		if (GetLastError() != ERROR_NO_MORE_FILES)
		{
			MessageBox(NULL, _T("Error"), _T("Error"), MB_OK);
		}
	}
	else 
	{
		return FALSE;
	}

	FindClose(hFile);

	delete[] pTempSrc;
	pTempSrc = NULL;
	return TRUE;
}

std::vector<FileObj> SearchFile::get_tree()
{
	return childs;
}

SearchFile::~SearchFile()
{
	if (pszFileName != NULL)
		delete[] pszFileName;
	pszFileName = NULL;
	if (pszDirectory != NULL)
		delete[] pszDirectory;
	pszDirectory = NULL;

	if (childs.size() != 0)
		childs.clear();
}	

std::ostream& operator<<(std::ostream& os, const FileObj& fo)
{
	os << fo.fileName << std::endl;
	for (FileObj child : fo.childs)
		os << child;
	return os;
}