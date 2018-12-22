#pragma once
#include <iostream>
#include <fstream>
#include <codecvt>
#include <locale>
//Средство взаимодействия с пользователем
namespace UI{
	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	static void endMessage(string path) {
		std::cout << "Done! Check the folder " << path << std::endl;
		system("PAUSE");
	}
	static string getPathToMap() {
		std::cout << "Enter path to the folder to put data in" << std::endl;
		string str;
		getline(cin, str);
		std::wstring wstr = converter.from_bytes(str);
		while (!FileSystemTools::createFolder(&wstr)) {
			if (str == "0") {
				return "0";
			}
			std::cout << "Invalid path, try again (to exit type\"0\")" << std::endl;
			getline(cin, str);
			wstr = converter.from_bytes(str);
		}
		return str;
	}
	static void errorMessage(){
		std::cout << "Something went wrong :(" << std::endl;
	}
	static string getDataPath() {
		std::cout << "Enter path to .jpg files" << std::endl;
		string str;
		getline(cin, str);
		std::wstring wstr = converter.from_bytes(str);
		while (!FileSystemTools::isFolder(&wstr)) {
			if (str == "0") {
				return "0";
			}
			std::cout << "Path does not lead to folder, try again  (to exit type\"0\")" << std::endl;
			getline(cin, str);
			wstr = converter.from_bytes(str);
		}
		return str;
	}
};
