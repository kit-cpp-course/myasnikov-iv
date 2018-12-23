#pragma once
#include <string>


namespace cmd {
	class arguments;
}

class config {
	friend class cmd::arguments;
	static config m_instance;
	std::string m_input;
	std::string m_output = "output";
	config() {}
public:
	const std::string & input() const {
		return m_input;
	}
	const std::string & output() const {
		return m_output;
	}
	static config & instance() {
		return m_instance;
	}
	bool isValid() {
		static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring winput = converter.from_bytes(m_input);
		std::wstring woutput = converter.from_bytes(m_output);
		return FileSystemTools::isFolder(&winput) && FileSystemTools::createFolder(&woutput);
	}
};

config config::m_instance = config();