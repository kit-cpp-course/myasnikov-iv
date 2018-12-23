#include "Zone.h"
#include "FileSystemTools.h"
#include "ImgPoint.h"
#include "UI.h"
#include "arguments.h"

#include <codecvt>
#include <locale>
#include <vector>
int main(size_t count, char * args[])
{
	config & cfg = config::instance();
	if (count<3) {
		UI::errorMessage();
		return -1;
	}
	cmd::arguments arg(count,  args);
	arg.apply(cfg);
	if (!cfg.isValid()) {
		UI::errorMessage();
		return -1;
	}
	const size_t zoneCount = 5;
	Zone** zones = new Zone*[zoneCount];
	//Создадим известные зоны
	zones[0] =new Zone("St.Petersburg", Point(59.784857f, 29.939072f), Point(60.1059280f, 30.6244484f));
	zones[1] =new Zone("Moscow", Point(55.551461f, 37.304680f), Point(55.926738f, 37.895120f));
	zones[2] =new Zone("Englang", Point(49.727877f, -6.160674f), Point(55.766276f, 1.908676f));
	zones[3] =new Zone("Antarctica", Point(-90.0f, -180.0f), Point(-62.0f, 180.0f));
	zones[4] =new Zone("Penrhyn", Point(-9.113082f, -158.078312f), Point(-8.892594f, -157.889655f));

	
	string pathToData = cfg.input();
	//Для кадждого найденого файла создается объект ImgPoint
	vector<string> jpgs = FileSystemTools::findAllJpgs(pathToData);
	size_t n = jpgs.size();
	ImgPoint** imgPoints =new ImgPoint*[n];
	for (size_t i = 0; i < n;i++) {
		imgPoints[i] = new ImgPoint(jpgs[i]);
	}
	//Пользователь вводит необходимые данные: Путь где будет происходить катологизация
	string PathToMap = cfg.output();
	static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	//Создание каталога для каждой Zone
	if (PathToMap.back() != '\\') PathToMap += "\\";
	std::wstring zonePaths[zoneCount];
	for (size_t i = 0; i < zoneCount;i++) {
		zonePaths[i] = converter.from_bytes(PathToMap + zones[i]->getName());
		if (!FileSystemTools::createFolder(&zonePaths[i])) {
			UI::errorMessage();
			return -1;
		}
	}
	//Разбиение jpg файлов по каталогам
	std::wstring unknownLocationPath;
	for (size_t i = 0; i < n; i++) {
		bool zoneFound = false; //Маркер, показываюший, нашласи ли Zone для данного ImgPoint
		std::wstring path = converter.from_bytes(imgPoints[i]->getData());
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
					unknownLocationPath = converter.from_bytes(PathToMap + "Unknown Location");
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