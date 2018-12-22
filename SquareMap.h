#pragma once
#include <iostream>
#include <string>
#include <math.h>  
#include "FileSystemTools.h"

class SquareMap {
	//Claster** clasters;
	size_t y;
	size_t x;
	float hSS;
public:
	SquareMap(size_t x, size_t y) : x(x), y(y) {};
	void SquareClasters(float a);
	//bool addData(Point* point);
	bool mapToFileSystem(std::wstring folderPath);
	~SquareMap();
};