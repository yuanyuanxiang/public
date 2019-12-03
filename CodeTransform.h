/** 
* @file CodeTransform.h
* @brief 转换数据编码，仅适用于 Windows 平台(MFC)
* @date 2016/8/24 建立此文档
* @author yuanyuanxiang
*/

#ifdef _WIN32

#include <atlstr.h>

#pragma once

// 将Unicode编码转换成ANSI编码(需要手动delete转换结果)
char* UnicodeConvert2ANSI(LPCWCH strEncodeData, int &ncLength);

// 将ANSI编码转换成Unicode编码
CString ANSIConvert2Unicode(const char *strANSI, int &ncLength);

// 将Unicode编码转换成UTF-8编码(需要手动delete转换结果)
char* UnicodeConvert2UTF8(LPCWCH strUnicode, int &ncLength);

// 将utf-8编码转换成Unicode编码
CString UTF8Convert2Unicode(const char* strUtf8, int &ncLength);

// 将ANSI编码转换成UTF-8编码(需要手动delete转换结果)
char* ANSIConvert2UTF8(const char* strANSI, int &ncLength);

// 将UTF8编码转换成ANSI编码(需要手动delete转换结果)
char* UTF8Convert2ANSI(const char* strUtf8, int &ncLength);

#endif
