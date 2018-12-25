#pragma once

#include <string>
#include <vector>
#include "ImgPoint.h"


//�������������� ����
//mins - �����, ������������ ������ ������� ������� � ������ ������� �������
//maxs - �����, ������������ ������� ������� ������� � ������� ������� �������
//pointsInside - jpg � ���������� ��������������� ���� ����
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
	//���������� �������� �� ����� p � ��� ����, ���� ��������, ��������� p � pointInside
	bool addImgPoint(ImgPoint* p);
	//���������� ����� �� pointsInside �� �������
	ImgPoint * getImgPoint(size_t index);
	//������ pointsInside
	size_t getImgPointsCount();
};