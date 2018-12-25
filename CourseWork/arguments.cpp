#include "arguments.h"

bool cmd::arguments::isKey(size_t index) const {
	return (argument[index][0] == '/' && (argument[index][1] == 'i' || argument[index][1] == 'o'));
}

std::string cmd::arguments::find(const std::string & name, std::string & def) const {
	for (size_t i = 0; i < count - 1; i++) {
		if (isKey(i) && !isKey(i + 1) && strcmp(argument[i], name.data()) == 0) {
			return argument[i + 1];
		}
	}
	return def;
}

cmd::arguments::arguments(size_t count, char ** arguments)
	: count(count), argument(arguments) {}

void cmd::arguments::apply(config & cfg) const {
	cfg.m_input = find("/i", cfg.m_input);
	cfg.m_output = find("/o", cfg.m_output);
}
