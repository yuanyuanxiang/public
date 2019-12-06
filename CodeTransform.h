/** 
* @file CodeTransform.h
* @brief ת�����ݱ��룬�������� Windows ƽ̨(MFC)
* @date 2016/8/24 �������ĵ�
* @author yuanyuanxiang
*/

#ifdef _WIN32

#ifndef _WINDOWS // MFC
#include <atlstr.h>
using namespace ATL;
#else
#include <afx.h>
#endif

#pragma once

// ��Unicode����ת����ANSI����(��Ҫ�ֶ�deleteת�����)
char* UnicodeConvert2ANSI(LPCWCH strEncodeData, int &ncLength);

// ��ANSI����ת����Unicode����
CString ANSIConvert2Unicode(const char *strANSI, int &ncLength);

// ��Unicode����ת����UTF-8����(��Ҫ�ֶ�deleteת�����)
char* UnicodeConvert2UTF8(LPCWCH strUnicode, int &ncLength);

// ��utf-8����ת����Unicode����
CString UTF8Convert2Unicode(const char* strUtf8, int &ncLength);

// ��ANSI����ת����UTF-8����(��Ҫ�ֶ�deleteת�����)
char* ANSIConvert2UTF8(const char* strANSI, int &ncLength);

// ��UTF8����ת����ANSI����(��Ҫ�ֶ�deleteת�����)
char* UTF8Convert2ANSI(const char* strUtf8, int &ncLength);

#endif
