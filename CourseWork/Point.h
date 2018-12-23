#pragma once
#include <string>

// ласс, представл€юший точку

class Point {
	float x;
	float y;
public:
	float getX() const {
		return x;
	};
	float getY() const {
		return y;
	};
	Point() {};
	Point(float x, float y) : x(x), y(y) {};
	
};