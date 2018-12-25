#pragma once

#include <string>
#include <vector>
#include "ImgPoint.h"


//Географическая зона
//mins - точка, обозначаюшия нижнюю границу долготы и нижнюю границу долготы
//maxs - точка, обозначаюшия верхнюю границу долготы и верхнюю границу долготы
//pointsInside - jpg с геоданными соответствующие этой зоне
class Zone {
	char* name;
	GeoPoint mins;
	GeoPoint maxs;
	std::vector<ImgPoint*> pointsInside;
public:
	char *  getName() {
		return name;
	};
	Zone(std::string name, GeoPoint mins, GeoPoint maxs);
	//Определяет попадает ли точка p с эту зону, если попадает, добавляет p в pointInside
	bool addImgPoint(ImgPoint* p);
	//Возвращает точку из pointsInside по индексу
	ImgPoint * getImgPoint(size_t index);
	//Размер pointsInside
	size_t getImgPointsCount();
};