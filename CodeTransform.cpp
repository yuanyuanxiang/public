/**
* @file 
* @brief �ַ���ת����ʵ��
*/

#include "CodeTransform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) if((p) != NULL){ delete [] (p); (p) = NULL; }/**< ��ȫɾ��ָ��p */
#endif

/// ��Unicode����ת����ANSI����(��Ҫ�ֶ�deleteת�����)
char* UnicodeConvert2ANSI(LPCWCH strUnicode, int &ncLength)
{
	ncLength = WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, NULL, 0, NULL, NULL);
	char *strANSI = new char[ncLength];
	ncLength = WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, strANSI, ncLength, NULL, NULL);
	strANSI[ncLength - 1] = 0;
	return strANSI;
}


/// ��ANSI����ת����Unicode����
CString ANSIConvert2Unicode(const char *strANSI, int &ncLength)
{
	ncLength = MultiByteToWideChar(CP_ACP, 0, strANSI, -1, NULL, 0);
	wchar_t *strUnicode = new wchar_t[ncLength];
	ncLength = MultiByteToWideChar(CP_ACP, 0, strANSI, -1, strUnicode, ncLength * sizeof(wchar_t));
	CString strDst(strUnicode);
	SAFE_DELETE(strUnicode);
	return strDst;
}


/// ��Unicode����ת����UTF-8����(��Ҫ�ֶ�deleteת�����)
char* UnicodeConvert2UTF8(LPCWCH strUnicode, int &ncLength)
{
	ncLength = WideCharToMultiByte(CP_UTF8, 0, strUnicode, -1, NULL, 0, NULL, NULL);
	// ��û�������ַ�
	if (ncLength == 1)
		return NULL;
	char *strUtf8 = new char[ncLength];
	ncLength = WideCharToMultiByte(CP_UTF8, 0, strUnicode, -1, strUtf8, ncLength, NULL, NULL);
	strUtf8[ncLength - 1] = 0;
	return strUtf8;
}


/// ��utf-8����ת����Unicode����
CString UTF8Convert2Unicode(const char* strUtf8, int &ncLength)
{
	ncLength = MultiByteToWideChar(CP_UTF8, 0, strUtf8, -1, NULL, 0);
	WCHAR *strUnicode = new WCHAR[ncLength];
	ncLength = MultiByteToWideChar(CP_UTF8, 0, strUtf8, -1, strUnicode, ncLength);
	CString strDst(strUnicode);
	SAFE_DELETE(strUnicode);
	return strDst;
}


/// ��ANSI����ת����UTF-8����
char* ANSIConvert2UTF8(const char* strANSI, int &ncLength)
{
	CString strUnicode = ANSIConvert2Unicode(strANSI, ncLength);
	char *strUtf8 = UnicodeConvert2UTF8(strUnicode, ncLength);
	return strUtf8;
}


/// ��UTF8����ת����ANSI����
char* UTF8Convert2ANSI(const char* strUtf8, int &ncLength)
{
	CString strUnicode = UTF8Convert2Unicode(strUtf8, ncLength);
	char *strANSI = UnicodeConvert2ANSI(strUnicode, ncLength);
	return strANSI;
}
