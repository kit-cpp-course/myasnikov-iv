
#pragma once
#include <stdio.h>
#include "exif.h"

#include <iostream>
#include "Point.h"

class ImgPoint: public Point {
	std::string path;
public:
	std::string getData() {
		return path;
	}
	ImgPoint() {};
	//Конструтор класса использует сторонний класс EXIFInfo для получений данных из метаданных
	ImgPoint(std::string path): path(path){
		FILE *fp = fopen(path.c_str(), "rb");
		if (!fp) {
			std::cout << "Can't open file " << path << std::endl;
			this->~ImgPoint();
			return;
		}
		fseek(fp, 0, SEEK_END);
		unsigned long fsize = ftell(fp);
		rewind(fp);
		unsigned char *buf = new unsigned char[fsize];
		if (fread(buf, 1, fsize, fp) != fsize) {
			std::cout << "Cant read file " << path << std::endl;
			delete[] buf;
			this->~ImgPoint();
			return;
		}
		fclose(fp);
		easyexif::EXIFInfo result;
		int code = result.parseFrom(buf, fsize);
		delete[] buf;
		if (code) {
			std::cout << "Error parsing EXIF " << path << ": code " << code << std::endl;
			this->~ImgPoint();
			return;
		};
		//Пересоздание точки с получинным координатами
		this->Point::Point(result.GeoLocation.Latitude, result.GeoLocation.Longitude);
	}
};