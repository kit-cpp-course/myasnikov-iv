#include "ImgMap.h"

void ImgMap::addZone(Zone * zone) {
	this->zones.push_back(zone);
}

void ImgMap::addImgPoint(ImgPoint * img) {
	bool zoneFound = false; //Маркер, показываюший, нашлась ли Zone для данного ImgPoint
	for (size_t j = 0; j < zones.size();j++) {
		if (zones[j]->addImgPoint(img)) {
			zoneFound = true;
			break;
		};
	}
	//Если для ImgPoint не нашлась Zone, То кладем ее в неизвестную зону
	if (!zoneFound && (img->getLon() != 0 || img->getLat() != 0) && img->getData() != "") {
		unknown.push_back(img);
	}
}

bool ImgMap::mapToFileSystem(std::string path) {
	if (path.back() != '\\') path += "\\";
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wpath = converter.from_bytes(path);
	for (size_t i = 0; i < zones.size();i++) {
		std::wstring zonePath = wpath + converter.from_bytes(zones[i]->getName());
		if (FileSystemTools::createFolder(&zonePath)) {
			for (size_t j = 0; j < zones[i]->getImgPointsCount();j++) {
				std::wstring pathToImg = converter.from_bytes(zones[i]->getImgPoint(j)->getData());
				if (!FileSystemTools::copyFile(&pathToImg, &zonePath)) {
					return false;
				}
			}
		}
	}
	if (unknown.size() != 0) {
		std::wstring unkPath = wpath + L"Unknown Location";
		if (FileSystemTools::createFolder(&unkPath)) {
			for (size_t i = 0; i < unknown.size(); i++) {
				std::wstring pathToImg = converter.from_bytes(unknown[i]->getData());
				if (!FileSystemTools::copyFile(&pathToImg, &unkPath)) {
					return false;
				}
			}
		}
	}
}
