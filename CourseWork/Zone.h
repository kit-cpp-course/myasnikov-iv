#pragma once
#include <string>
#include "Point.h"

//�����, �������������� ����
//mins - �����, ������������ ������ ������� ������� � ������ ������� �������
//maxs - �����, ������������ ������� ������� ������� � ������� ������� �������
class Zone {
	char* name;
	Point mins;
	Point maxs;
public:
	char *  getName() {
		return name;
	};
	Zone(std::string name, Point mins, Point maxs) : mins(mins), maxs(maxs) {
		//���� �� ������ ����������?
		this->name = new char[name.length()];
		const char * temp = name.c_str();
		strcpy(this->name, temp);
	}
	//�����, ������� ����������, �������� �� ������ ��� ����
	bool belongsToThis(Point p) {
		return p.getX() <= maxs.getX() && p.getX() >= mins.getX() && p.getY() <= maxs.getY() && p.getY() >= mins.getY();
	}
};