#pragma once
#include <fstream>
#include <string>

class ZoneParser {
	std::ifstream* input;
public:
	bool ready = false;
	ZoneParser(std::string path) {
		input = new std::ifstream(path);
		if (input->is_open()) {
			ready = true;
		};
	};
	vector<Zone *> parse() {
		double minLog, minLat, maxLog, maxLat;
		std::string name;
		vector<Zone *> res;
		while (*input >> minLog >> minLat >> maxLog >> maxLat && input->get() == ' ' && getline(*input, name)) {
			Zone* zone = new Zone(name, GeoPoint(minLog, minLat), GeoPoint(maxLog, maxLat));
			res.push_back(zone);
		}
		return res;
	}
	bool isReady() {
		return ready;
	}
};