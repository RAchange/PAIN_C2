#include "BmpCImage.h"


namespace BmpCImage
{
	enum IMAGE_EXT { BMP, JPG, PNG, GIF };
	CONST TCHAR ExtList[4][4] = { _T("bmp"), _T("jpg"), _T("png"), _T("gif") };

	BOOL SaveBmp(HBITMAP hBmp, TCHAR* pszFileName)
	{
		if (hBmp == NULL ||
			pszFileName == NULL ||
			_tcslen(pszFileName) == 0)
		{
			return FALSE;
		}

		CImage image;
		LPTSTR pszFullName = NULL;

		pszFullName = new TCHAR[MAX_PATH];

		_stprintf(pszFullName, _T("%s.jpg"), pszFileName);

		image.Attach(hBmp);
		if (image.Save(pszFullName) != S_OK)
			return FALSE;

		delete[] pszFullName;

		return TRUE;
	}


	BOOL ConverPicture(TCHAR* pszSrcImage, TCHAR* pszDstImage)
	{
		if (pszSrcImage == NULL ||
			_tcslen(pszSrcImage) == 0 ||
			pszDstImage == NULL ||
			_tcslen(pszDstImage) == 0)
		{
			return FALSE;
		}
		CImage image;

		if (image.Load(pszSrcImage) != S_OK)
			return FALSE;
		if (image.Save(pszDstImage) != S_OK)
			return FALSE;

		return TRUE;
	}
}
