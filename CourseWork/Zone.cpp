#include "Zone.h"

Zone::Zone(std::string name, GeoPoint mins, GeoPoint maxs) : mins(mins), maxs(maxs) {
	//Есть ли способ элегантнее?
	this->name = new char[name.length()];
	const char * temp = name.c_str();
	strcpy(this->name, temp);
}

//метод, которой определяет, попадает ли точка в этe зону и если попадает, кладет ссылку на нее внутрь себя

bool Zone::addImgPoint(ImgPoint * p) {
	if (p->getLon() <= maxs.getLon() && p->getLon() >= mins.getLon() && p->getLat() <= maxs.getLat() && p->getLat() >= mins.getLat()) {
		pointsInside.push_back(p);
		return true;
	}
	return false;
}

ImgPoint * Zone::getImgPoint(size_t index) {
	return pointsInside[index];
}
size_t Zone::getImgPointsCount() {
	return pointsInside.size();
}

//метод, которой определяет, попадает ли точка в этe зону и если попадает, кладет ссылку на нее внутрь себя

