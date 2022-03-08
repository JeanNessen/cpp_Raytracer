#pragma once
#include <vector>
#include "CColor.h"
#include <string>


class CCanvas
{
public:
	
	CCanvas(int width, int height);
	CColor PixelAt(int x, int y) const;
	void WritePixel(int x, int y, CColor col);
	std::string to_ppm();

    CCanvas operator+(const CCanvas& other);
    CCanvas& operator+=(const CCanvas& other);
    CCanvas operator/(const double& other);
    bool operator==(const CCanvas& other) const;
    bool operator!=(const CCanvas& other) const;


private:
	const int width;
	const int height;

	std::vector<std::vector<CColor>> grid;

};

