#pragma once
#include <string>



// ласс, представл¤юший географическую точку

class GeoPoint {
	//Ўирота
	double longitude;
	//ƒолгота
	double latitude;
public:
	double getLon() const;;
	double getLat() const;;
	GeoPoint() {};
	GeoPoint(double x, double y);;
	
};