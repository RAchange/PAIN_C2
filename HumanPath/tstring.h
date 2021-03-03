#pragma once
#include <tchar.h>
#include <string>
#include <fstream>
#include <sstream>

#ifdef _UNICODE
#define tstring wstring
#else
#define tstring string
#endif

namespace std
{
    typedef basic_string<TCHAR> tstring;

    typedef basic_ostream<TCHAR>    tostream;
    typedef basic_istream<TCHAR>    tistream;
    typedef basic_iostream<TCHAR>   tiostream;

    typedef basic_ifstream<TCHAR>   tifstream;
    typedef basic_ofstream<TCHAR>   tofstream;
    typedef basic_fstream<TCHAR>    tfstream;

    typedef basic_stringstream<TCHAR>   tstringstream;
}