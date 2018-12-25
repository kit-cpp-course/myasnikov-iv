#include "configs.h"

config config::m_instance = config();

const std::string & config::input() const {
	return m_input;
}

const std::string & config::output() const {
	return m_output;
}

config & config::instance() {
	return m_instance;
}

bool config::isValid() {
	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring winput = converter.from_bytes(m_input);
	std::wstring woutput = converter.from_bytes(m_output);
	return FileSystemTools::isFolder(&winput) && FileSystemTools::createFolder(&woutput);
}
