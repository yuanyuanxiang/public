#include "fileop.h"
#include <vector>
#include <direct.h>
#include <windows.h>
#include <io.h>
#include <algorithm>

// ��path��ȡ�ļ����ƣ��к�׺��.
Str getFileName(StrRef path) {
	const char *h = path.c_str(), *p = h + path.length();
	while (p != h && *p != '\\' && *p != '/') --p;
	return p == h ? p : p + 1;
}

// ��path��ȡ�ļ����ƣ��޺�׺��.
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

// ��path��ȡ�ļ�Ŀ¼����.
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

// ��path��ȡ�ļ�Ŀ¼·��.
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

// ��С��������.�ֵ�˳��.
bool comp(StrRef i, StrRef j) { return (i < j); }

// ��ȡָ��Ŀ¼�µ��ļ�.
bool listFiles(FileList &ret, StrRef dir, StrRef typ, bool recursive)
{
	bool result = false;
	//�ļ����
	intptr_t hFile = 0;
	//�ļ���Ϣ  
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
						printf("�о�\"%s\"ʧ��.\n", child.c_str());
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

// ��ȡָ��Ŀ¼�µ��ļ�.
FileList getFilesByDir(StrRef dir, StrRef typ, bool recursive)
{
	FileList ret;
	if (listFiles(ret, dir, typ, recursive))
	{
		std::sort(ret.begin(), ret.end(), comp);
	}

	return ret;
}

// �ݹ�ɾ��Ŀ¼.
bool deleteFiles(StrRef folder_path, bool recursive)
{
	bool ret = true;
	//�ļ����
	intptr_t hFile = 0;
	//�ļ���Ϣ  
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
						printf("ɾ��\"%s\"%s.\n", child.c_str(), b ? "�ɹ�" : "ʧ��");
					}
					else ret = false;
				}
				else
				{
					if (!DeleteFileA(child.c_str())) {
						ret = false;
						printf("ɾ��\"%s\"ʧ��.\n", child.c_str());
					}
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
	}
	catch (std::exception e) { if (hFile) _findclose(hFile); }

	return ret;
}

// ɾ��Ŀ¼.
bool removeDir(StrRef folder_path) {
	return deleteFiles(folder_path, true);
}

// ���Ŀ¼��'\\'��'/'��β.
void checkDir(Str &dir)
{
	char n = dir.at(dir.length()-1);
	if(n != '\\'&& n != '/')
		dir.append("\\");
}
