#pragma once
#include "Zone.h"
#include "ImgPoint.h"
#include "FileSystemTools.h"

#include <codecvt>
#include <vector>
//Карта изображений с геоданными, поделенных на зоны
class ImgMap {
	std::vector<Zone*> zones;
	std::vector<ImgPoint*> unknown;
public:
	ImgMap() {};
	//Добавление зоны на карту
	void addZone(Zone* zone);
	//Добавление изображения с геоданными на карту. Если она попадает в 1 из зон, то помещается в объект зоны
	//если ни одна зона не подходит, помешается в unknown
	void addImgPoint(ImgPoint* img);
	//Переносит себя в файловую систему по пути path: каждая зона и unknown это директории, содержание этих директорий - картинки, которые попали в данную зону
	bool mapToFileSystem(std::string path);
};