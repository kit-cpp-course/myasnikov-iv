#include "SquareMap.h"


/*void SquareMap::SquareClasters(float a) {
	hSS = a;
	size_t xAm = ceil(x / 2 / a);
	size_t yAm = ceil(y / 2 / a);
	clasters = new Claster*[xAm];
	for (int i = 0; i < xAm; ++i)
	{
		clasters[i] = new Claster[yAm];
		for (int j = 0; j < yAm; ++j)
		{
			clasters[i][j] = Claster();
		}
	};
};
bool SquareMap::addData(Point* point) {
	float xP = point->getX();
	float yP = point->getY();
	if (xP > x || yP > y) {
		return false;
	}
	size_t xCor = (int)xP / 2 / hSS;
	size_t yCor = (int)yP / 2 / hSS;
	clasters[xCor][yCor].addPoint(point);
	return true;

};
bool SquareMap::mapToFileSystem(std::wstring folderPath) {
	if (FileSystemTools::createFolder(&folderPath)) {
		size_t xAm = ceil(x / 2 / hSS);
		size_t yAm = ceil(y / 2 / hSS);

		for (size_t i = 0; i < xAm; i++) {
			for (size_t j = 0; j < yAm; j++) {

				std::wstring addPath = L"\\" + std::to_wstring((int)(i * 2 * hSS)) + L"-" + std::to_wstring((int)(i + 1 == xAm ? x : (i + 1) * 2 * hSS)) + L" ";
				addPath = addPath + std::to_wstring((int)(j * 2 * hSS)) + L"-" + std::to_wstring((int)(j + 1 == yAm ? y : (j + 1) * 2 * hSS));
				std::wstring clastPath = folderPath + addPath;
				if (clasters[i][j].points.size() != 0) {
					if (FileSystemTools::createFolder(&clastPath)) {

						for (size_t k = 0; k < (size_t)clasters[i][j].points.size(); k++) {

							std::wstring path = clasters[i][j].points[k]->getData();
							if (FileSystemTools::isFile(&path)) {
								size_t index = path.find_last_of(L"\\");
								std::wstring newFilePath = clastPath + L"\\" + path.substr(index + 1, path.size() - index);
								if (!FileSystemTools::copyFile(&path, &newFilePath)) {
									return false;
								}
							}
							else {
								return false;
							}

						}
					}
					else
					{
						return false;
					}
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	};
}
SquareMap::~SquareMap() {
	size_t xAm = ceil(x / 2 / hSS);
	size_t yAm = ceil(y / 2 / hSS);

	for (size_t i = 0; i < xAm; i++) {
		delete[] clasters[i];
	};
	delete clasters;
}*/