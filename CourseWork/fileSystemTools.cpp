#include "FileSystemTools.h"
#include <iostream>

// подготовка пути для работы программы 
const wchar_t* FileSystemTools::prepare(wstring path)
{
	wstring result = ( path);
	wchar_t* resstr = new wchar_t[result.length() + 1];
	const wchar_t *cstr = result.c_str();
	memcpy(resstr, cstr, (result.length() + 1) * sizeof(wchar_t));
	return resstr;
}

// проврека на существование файла или папки 
bool FileSystemTools::exists(wstring* const path)
{
	DWORD attrs = GetFileAttributesW(prepare(*path));
	DWORD error = GetLastError();
	if (attrs == INVALID_FILE_ATTRIBUTES && (error == ERROR_FILE_NOT_FOUND || error == ERROR_PATH_NOT_FOUND)) {
		return false;
	}
	return true;
}

// папка или файл
bool FileSystemTools::isFolder(wstring* const path)
{
	DWORD attrs = GetFileAttributesW(prepare(*path));
	DWORD error = GetLastError();
	if (attrs == INVALID_FILE_ATTRIBUTES && error == ERROR_FILE_NOT_FOUND) return false;
	return attrs & FILE_ATTRIBUTE_DIRECTORY;
}
bool FileSystemTools::isFile(wstring* const path)
{
	DWORD attrs = GetFileAttributesW(prepare(*path));
	DWORD error = GetLastError();
	if (attrs == INVALID_FILE_ATTRIBUTES && error == ERROR_FILE_NOT_FOUND) return false;
	return !(attrs & FILE_ATTRIBUTE_DIRECTORY);
}

// создание папки 
bool FileSystemTools::createFolder(wstring* const path)
{
	const wchar_t* cpath = prepare(*path);
	DWORD result = CreateDirectoryW(cpath, NULL);
	if (result == 0) {
		DWORD error = GetLastError();
		if (error == ERROR_ALREADY_EXISTS) {
			return true;
		}
		else if (error == ERROR_PATH_NOT_FOUND) {

			unsigned int steps = 0;
			size_t index = -1;
			wstring newPath;
			do {
				index = path->find_first_of('\\', index + 1);
				newPath = path->substr(0, index + 1);
				bool ex = exists(&newPath);
				if (ex && !isFolder(&newPath)) {
					return false;
				}
				else if (!ex && steps) {
					createFolder(&newPath);
				}
				else if (!ex && !steps) {
					return false;
				}
				steps++;
			} while (index != wstring::npos);
		}
	}
	return true;
}

// копирование файла в новую категорию 
bool FileSystemTools::copyFile(wstring* const from, wstring* const to)
{
	if (!isFile(from)) return false;
	if (to->back() != '\\') to->push_back(L'\\');
	const wchar_t* cfrom = prepare(*from);
	size_t index = from->find_last_of('\\');
	std::wstring fileName = from->substr(index + 1, from->length() - index - 1);
	const wchar_t* cto = prepare(*to+fileName);
	DWORD result = CopyFileW(cfrom, cto, true);
	return CopyFileW(cfrom, cto, true) != 0 || GetLastError() == ERROR_FILE_EXISTS;
}
vector<string> FileSystemTools::findAllJpgs(string path)
{
	WIN32_FIND_DATA FindFileData;
	if(path.back() != '\\') path += "\\";
	string a = path + "*.*";
	const char* cpath = &a[0];
	HANDLE h_fd = FindFirstFile(cpath, &FindFileData);
	vector<string> jpgs;
	if (h_fd == INVALID_HANDLE_VALUE) {
		DWORD err = GetLastError();
		cout << path << endl;
		return jpgs ;
	}

	while (FindNextFile(h_fd, &FindFileData)) {
		string name= FindFileData.cFileName;
		size_t n = name.size();
		if (n > 4 && name.substr(name.size() - 4, 4) == ".jpg")
			jpgs.push_back(path + name);
		
	}
	return jpgs;
}


