#pragma once
#include <iostream>
#include <fstream>
#include <codecvt>
#include <locale>
//Средство взаимодействия с пользователем
namespace UI{
	static void endMessage(string path) {
		std::cout << "Done! Check the folder " << path << std::endl;
		system("PAUSE");
	}
	static void errorMessage(){
		std::cout << "Something went wrong :(" << std::endl;
	}
};
