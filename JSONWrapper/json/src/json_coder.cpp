#include "stdafx.h"
#include <string>
#if defined(_MSC_VER)
#include <Windows.h>
#define CP_UTF8                   65001       // UTF-8 translation
#define INTERNAL_CODING           CP_UTF8
#endif
namespace Json {
#if defined(_MSC_VER)
    /// Converts a UTF-8 code-point to unicode.
    std::wstring UTF8ToUnicode(const std::string szCodePage)
    {
        if (szCodePage.empty())
        {
            return std::wstring(L"");
        }
        const char *pchar = szCodePage.c_str();
        int nLen = szCodePage.size();
        int nSize = MultiByteToWideChar(INTERNAL_CODING, 0, (LPCSTR)pchar, nLen, 0, 0);
        if(nSize <= 0) return NULL;
        WCHAR *pwszDst = new WCHAR[nSize+1];
        if( NULL == pwszDst) return NULL;
        MultiByteToWideChar(INTERNAL_CODING, 0,(LPCSTR)pchar, nLen, pwszDst, nSize);
        pwszDst[nSize] = 0;
        if( pwszDst[0] == 0xFEFF ) // skip Oxfeff
        {
            for(int i = 0; i < nSize; i ++)
            {
                pwszDst[i] = pwszDst[i+1];
            }
        }
        std::wstring wcharString(pwszDst);
        delete pwszDst;
        return wcharString;
    }

    /// Converts a unicode code-point to UTF-8.
    std::string UnicodeToUTF8(const std::wstring szUnicode)
    {
        if (szUnicode.empty())
        {
            return std::string("");
        }
        const wchar_t* pwchar = szUnicode.c_str();
        int nLen = WideCharToMultiByte(INTERNAL_CODING, 0, pwchar, -1, NULL, 0, NULL, NULL);
        if (nLen<= 0) return std::string("");
        char* pszDst = new char[nLen];
        if (NULL == pszDst) return std::string("");
        WideCharToMultiByte(INTERNAL_CODING, 0, pwchar, -1, pszDst, nLen, NULL, NULL);
        pszDst[nLen -1] = 0;
        std::string strTemp(pszDst);
        delete [] pszDst;
        return strTemp;
    }
#endif
}
