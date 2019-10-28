#include "fileop.h"
#include <vector>
#include <direct.h>
#include <windows.h>
#include <io.h>
#include <algorithm>

// 从path获取文件名称（有后缀）.
Str getFileName(StrRef path) {
	const char *h = path.c_str(), *p = h + path.length();
	while (p != h && *p != '\\' && *p != '/') --p;
	return p == h ? p : p + 1;
}

// 从path获取文件名称（无后缀）.
Str getFileNameNoPostfix(StrRef path) {
	char buf[_MAX_PATH], *p = buf + path.length();
	strcpy_s(buf, path.c_str());
	while (p != buf && *p != '\\' && *p != '/'&& *p != '.') --p;
	if (*p == '.') {
		*p = 0;
		while (p != buf && *p != '\\' && *p != '/') --p;
	}
	return p == buf ? p : p + 1;
}

// 从path获取文件目录名称.
Str getFileDirName(StrRef path) {
	char buf[_MAX_PATH], *p = buf + path.length();
	strcpy_s(buf, path.c_str());
	while (p != buf && *p != '\\' && *p != '/') --p;
	if (p != buf) {
		*p = 0;
		while (p != buf && *p != '\\' && *p != '/') --p;
	}
	return p == buf ? p : p + 1;
}

// 从path获取文件目录路径.
Str getFileDirPath(StrRef  path)
{
	char buf[_MAX_PATH], *p = buf + path.length();
	strcpy_s(buf, path.c_str());
	while (p != buf && *p != '\\' && *p != '/') --p;
	if (p != buf) {
		*p = 0;
	}
	return buf;
}

// 从小到大排序.字典顺序.
bool comp(StrRef i, StrRef j) { return (i < j); }

// 获取指定目录下的文件.
bool listFiles(FileList &ret, StrRef dir, StrRef typ, bool recursive)
{
	bool result = false;
	//文件句柄
	intptr_t hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	Str p;
	try
	{
		Str filter = "\\*" + typ;
		if ((hFile = _findfirst(p.assign(dir).append(filter).c_str(), &fileinfo)) != -1) {
			do {
				if (0 == strcmp(fileinfo.name, ".") || 0 == strcmp(fileinfo.name, ".."))
					continue;
				Str child = dir + "\\" + fileinfo.name;
				if (FILE_ATTRIBUTE_DIRECTORY & fileinfo.attrib)
				{
					if (listFiles(ret, child, typ, recursive)) {
						printf("列举\"%s\"失败.\n", child.c_str());
					}
					continue;
				}
				else {
					ret.push_back(child);
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
			result = true;
		}
	}
	catch (std::exception e) { if (hFile) _findclose(hFile); }

	return result;
}

// 获取指定目录下的文件.
FileList getFilesByDir(StrRef dir, StrRef typ, bool recursive)
{
	FileList ret;
	if (listFiles(ret, dir, typ, recursive))
	{
		std::sort(ret.begin(), ret.end(), comp);
	}

	return ret;
}

// 递归删除目录.
bool deleteFiles(StrRef folder_path, bool recursive)
{
	bool ret = true;
	//文件句柄
	intptr_t hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	Str p;
	try
	{
		if ((hFile = _findfirst(p.assign(folder_path).append("\\*.*").c_str(), &fileinfo)) != -1)
		{
			do {
				if (0 == strcmp(fileinfo.name, ".") || 0 == strcmp(fileinfo.name, ".."))
					continue;
				Str child = folder_path + "\\" + fileinfo.name;
				if (FILE_ATTRIBUTE_DIRECTORY & fileinfo.attrib)
				{
					if (!recursive) continue;
					if (deleteFiles(child, recursive)) {
						BOOL b = RemoveDirectoryA(child.c_str());
						if (FALSE == b) ret = false;
						printf("删除\"%s\"%s.\n", child.c_str(), b ? "成功" : "失败");
					}
					else ret = false;
				}
				else
				{
					if (!DeleteFileA(child.c_str())) {
						ret = false;
						printf("删除\"%s\"失败.\n", child.c_str());
					}
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
	}
	catch (std::exception e) { if (hFile) _findclose(hFile); }

	return ret;
}

// 删除目录.
bool removeDir(StrRef folder_path) {
	return deleteFiles(folder_path, true);
}

// 检查目录以'\\'或'/'结尾.
void checkDir(Str &dir)
{
	char n = dir.at(dir.length()-1);
	if(n != '\\'&& n != '/')
		dir.append("\\");
}
