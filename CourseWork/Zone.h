#pragma once
#include <string>
#include "Point.h"

//Класс, представляюший зону
//mins - точка, обозначаюшия нижнюю границу долготы и нижнюю границу долготы
//maxs - точка, обозначаюшия верхнюю границу долготы и верхнюю границу долготы
class Zone {
	char* name;
	Point mins;
	Point maxs;
public:
	char *  getName() {
		return name;
	};
	Zone(std::string name, Point mins, Point maxs) : mins(mins), maxs(maxs) {
		//Есть ли способ элегантнее?
		this->name = new char[name.length()];
		const char * temp = name.c_str();
		strcpy(this->name, temp);
	}
	//метод, которой определяет, попадает ли точкав это зону
	bool belongsToThis(Point p) {
		return p.getX() <= maxs.getX() && p.getX() >= mins.getX() && p.getY() <= maxs.getY() && p.getY() >= mins.getY();
	}
};