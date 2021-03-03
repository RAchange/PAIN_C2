#pragma once
#include <Windows.h>
#include <tchar.h>
#include <atlimage.h>

namespace BmpCImage 
{
	BOOL SaveBmp(HBITMAP hBmp, TCHAR* pszFileName);
	BOOL ConverPicture(TCHAR* pszSrcImage, TCHAR* pszDstImage);
}
