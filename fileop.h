/************************************************************************
* @brief 对文件进行操作的函数
* 2019-10-28
* https://github.com/yuanyuanxiang/public
************************************************************************/
#pragma once
#include <string>
#include <vector>

// path 指的是文件在磁盘上的路径

typedef std::string Str;
typedef const Str & StrRef;
typedef std::vector<Str> FileList;

// 从path获取文件名称（有后缀）
Str getFileName(StrRef path);

// 从path获取文件名称（无后缀）
Str getFileNameNoPostfix(StrRef path);

// 从path获取文件目录名称
Str getFileDirName(StrRef path);

// 从path获取文件目录路径
Str getFileDirPath(StrRef path);

// 获取指定目录下的文件
FileList getFilesByDir(StrRef dir, StrRef typ=".*", bool recursive=false);

// 递归删除目录.
bool removeDir(StrRef folder_path);

// 检查目录以'\\'或'/'结尾.
void checkDir(Str &dir);
