#pragma once
#include <stdio.h>
#include "exif.h"
#include <iostream>
#include "GeoPoint.h"
//jpg с геоданными
class ImgPoint: public GeoPoint {
	std::string path;
public:
	std::string getData();
	ImgPoint() {};
	//Конструтор класса использует сторонний класс EXIFInfo для получений данных из метаданных
	ImgPoint(std::string path) ;
};