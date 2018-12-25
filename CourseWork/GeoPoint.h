#pragma once
#include <string>



// Класс, представл¤юший географическую точку

class GeoPoint {
	//Долгота
	double longitude;
	//Широта
	double latitude;
public:
	double getLon() const;;
	double getLat() const;;
	GeoPoint() {};
	GeoPoint(double x, double y);;
	
};
