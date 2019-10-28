/************************************************************************
* @brief ���ļ����в����ĺ���
* 2019-10-28
* https://github.com/yuanyuanxiang/public
************************************************************************/
#pragma once
#include <string>
#include <vector>

// path ָ�����ļ��ڴ����ϵ�·��

typedef std::string Str;
typedef const Str & StrRef;
typedef std::vector<Str> FileList;

// ��path��ȡ�ļ����ƣ��к�׺��
Str getFileName(StrRef path);

// ��path��ȡ�ļ����ƣ��޺�׺��
Str getFileNameNoPostfix(StrRef path);

// ��path��ȡ�ļ�Ŀ¼����
Str getFileDirName(StrRef path);

// ��path��ȡ�ļ�Ŀ¼·��
Str getFileDirPath(StrRef path);

// ��ȡָ��Ŀ¼�µ��ļ�
FileList getFilesByDir(StrRef dir, StrRef typ=".*", bool recursive=false);

// �ݹ�ɾ��Ŀ¼.
bool removeDir(StrRef folder_path);

// ���Ŀ¼��'\\'��'/'��β.
void checkDir(Str &dir);
