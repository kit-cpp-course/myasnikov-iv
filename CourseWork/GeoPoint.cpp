#include "GeoPoint.h"

double GeoPoint::getLon() const {
	return longitude;
}

double GeoPoint::getLat() const {
	return latitude;
}

GeoPoint::GeoPoint(double x, double y) : longitude(x), latitude(y) {}
