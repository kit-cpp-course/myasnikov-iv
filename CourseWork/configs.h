#pragma once
#include <string>
#include <codecvt>
#include <locale>
#include "FileSystemTools.h"


namespace cmd {
	class arguments;
}
//Singleton класс, представл¤ющий конфигураци¤ дл¤ работы программы
class config {
	friend class cmd::arguments;
	static config m_instance;
	std::string m_input;
	std::string m_output = "output";
	config() {}
public:
	const std::string & input() const;
	const std::string & output() const;
	static config & instance();
	//явл¤етс¤ ли конфигураци¤ верной
	bool isValid();
};

