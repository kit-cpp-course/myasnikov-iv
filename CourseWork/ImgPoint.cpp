#include "ImgPoint.h"

std::string ImgPoint::getData() {
	return path;
}
ImgPoint::ImgPoint(std::string path) {
	this->path = path;
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
	this->GeoPoint::GeoPoint(result.GeoLocation.Latitude, result.GeoLocation.Longitude);
}
