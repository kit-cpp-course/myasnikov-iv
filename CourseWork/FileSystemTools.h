
#pragma once
#include <string>
#include <vector>
#include "windows.h"
using namespace std;
	class FileSystemTools {
		static const wchar_t* prepare(wstring path);
	public:
		// �������� �� ������������� ����� ��� ����� 
		static bool exists(wstring* const path);
		// ����� ��� ����
		static bool isFolder(wstring* const path);
		static bool isFile(wstring* const path);
		// �������� ����� 
		static bool createFolder(wstring* const path);
		// ����������� ����� � ����� ��������� 
		static bool copyFile(wstring* const from, wstring* const to);
		// ����� ���� ������ ���������� jpeg � �������� ��������
		// ���������� ������ ����� � ��������� ������
		static vector<string> findAllJpgs(string path);
	};

