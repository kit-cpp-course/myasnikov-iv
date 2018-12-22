
#pragma once
#include <string>
#include <vector>
#include "windows.h"
using namespace std;
	class FileSystemTools {
		static const wchar_t* prepare(wstring path);
	public:
		// проврека на существование файла или папки 
		static bool exists(wstring* const path);
		// папка или файл
		static bool isFolder(wstring* const path);
		static bool isFile(wstring* const path);
		// создание папки 
		static bool createFolder(wstring* const path);
		// копирование файла в новую категорию 
		static bool copyFile(wstring* const from, wstring* const to);
		// поиск всех файлов расширения jpeg в заданном каталоге
		// возвращает вектор путей к найденным файлам
		static vector<string> findAllJpgs(string path);
	};

