#include "SquareMap.h"
#include "Zone.h"
#include "FileSystemTools.h"
#include "ImgPoint.h"
#include "UI.h"

#include <codecvt>
#include <locale>
#include <vector>
int main()
{
	setlocale(LC_ALL, "Russian");		
	const size_t zoneCount = 5;
	Zone** zones = new Zone*[zoneCount];
	//Создадим известные зоны
	zones[0] = &Zone("St.Petersburg", Point(59.784857, 29.939072), Point(60.1059280, 30.6244484));
	zones[1] = &Zone("Moscow", Point(55.551461, 37.304680), Point(55.926738, 37.895120));
	zones[2] = &Zone("Englang", Point(49.727877, -6.160674), Point(55.766276, 1.908676));
	zones[3] = &Zone("Antarctica", Point(-90, -180), Point(-62, 180));
	zones[4] = &Zone("Penrhyn", Point(-9.113082, -158.078312), Point(-8.892594, -157.889655));
	//Пользователь вводит необходимые данные: путь к jpg файлам
	string pathToData = UI::getDataPath();
	if (pathToData == "0") {
		return 0;
	}
	//Для кадждого найденого файла создается объект ImgPoint
	vector<string> jpgs = FileSystemTools::findAllJpgs(pathToData);
	size_t n = jpgs.size();
	ImgPoint** imgPoints =new ImgPoint*[n];
	for (size_t i = 0; i < n;i++) {
		imgPoints[i] = new ImgPoint(jpgs[i]);
	}
	//Пользователь вводит необходимые данные: Путь где будет происходить катологизация
	string PathToMap = UI::getPathToMap();
	if (PathToMap == "0") {
		return 0;
	}
	//Создание каталога для каждой Zone
	if (PathToMap.back() != '\\') PathToMap += "\\";
	std::wstring zonePaths[zoneCount];
	for (size_t i = 0; i < zoneCount;i++) {
		zonePaths[i] = UI::converter.from_bytes(PathToMap + zones[i]->getName());
		if (!FileSystemTools::createFolder(&zonePaths[i])) {
			UI::errorMessage();
			return -1;
		}
	}
	//Разбиение jpg файлов по каталогам
	std::wstring unknownLocationPath;
	for (size_t i = 0; i < n; i++) {
		bool zoneFound = false; //Маркер, показываюший, нашласи ли Zone для данного ImgPoint
		std::wstring path = UI::converter.from_bytes(imgPoints[i]->getData());
		for (size_t j = 0; j < zoneCount;j++) {
			if (zones[j]->belongsToThis(*imgPoints[i])) {
				if (!FileSystemTools::copyFile(&path,&zonePaths[j])) {
					UI::errorMessage();
					return -1;
				}
				zoneFound = true;
				break;
			};
		}
		if (!zoneFound) {
			if ((imgPoints[i]->getX() != 0 || imgPoints[i]->getY() != 0)&& imgPoints[i]->getData() !="") {
				//Если директория для ImgPoint из неизвестных зон еще не создана создадим ее
				if (unknownLocationPath.empty()) {
					unknownLocationPath = UI::converter.from_bytes(PathToMap + "Unknown Location");
					if (!FileSystemTools::createFolder(&unknownLocationPath)) {
						UI::errorMessage();
							return -1;
					}
				}
				if (!FileSystemTools::copyFile(&path, &unknownLocationPath)) {
					UI::errorMessage();
					return -1;
				}
			}
		}
	}
	UI::endMessage(PathToMap);
	return 0;
}