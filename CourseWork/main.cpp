#include "Zone.h"
#include "FileSystemTools.h"
#include "ImgPoint.h"
#include "ImgMap.h"
#include "UI.h"
#include "arguments.h"
#include "ZoneParser.h"

#include <codecvt>
#include <locale>
#include <vector>

int main(size_t count, char * args[])
{
	ZoneParser input("ZoneData.txt");

	if (!input.isReady()) {
		UI::errorMessage();
		return -1;
	}
	vector<Zone *> zones = input.parse();
	config & cfg = config::instance();
	if (count<3) {
		UI::errorMessage();
		return -1;
	}
	cmd::arguments arg(count,  args);
	arg.apply(cfg);
	if (!cfg.isValid()) {
		UI::errorMessage();
		return -1;
	}
	const size_t zoneCount = zones.size();
	
	string pathToData = cfg.input();
	vector<string> jpgs = FileSystemTools::findAllJpgs(pathToData);
	size_t n = jpgs.size();

	string pathToMap = cfg.output();

	ImgMap map;
	for (size_t i = 0; i < zoneCount;i++) {
		map.addZone(zones[i]);
	}
	for (size_t i = 0; i < n; i++) {
		ImgPoint* point =new ImgPoint(jpgs[i]);
		map.addImgPoint(point);
	}
	if (!map.mapToFileSystem(pathToMap)) {
		UI::errorMessage();
		return -1;
	};
	UI::endMessage(pathToMap);
	return 0;
}