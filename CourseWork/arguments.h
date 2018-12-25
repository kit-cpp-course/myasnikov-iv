#pragma once
#include "configs.h"

//Класс для работы с аргументами командной строки
namespace cmd {
	class arguments {
		size_t count;
		char ** argument;
	protected:
		//Является ли данная строка ключем
		bool isKey(size_t index) const;
		//Поиск аргумента по ключу
		std::string find(const std::string & name, std::string & def) const;
	public:
		arguments(size_t count, char ** arguments);
		//Установка конфигируции на основе консольных аргументов
		void apply(config & cfg) const;
	};
}