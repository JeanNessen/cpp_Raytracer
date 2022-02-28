#pragma once
#include <vector>
#include "Color.h"
#include <string>


class Canvas
{
public:
	
	Canvas(int width, int height);
	Color PixelAt(int x, int y) const;
	void WritePixel(int x, int y, Color col);
	std::string to_ppm();

    Canvas operator+(const Canvas& other);
    Canvas& operator+=(const Canvas& other);
    Canvas operator/(const double& other);
    bool operator==(const Canvas& other) const;
    bool operator!=(const Canvas& other) const;


private:
	const int width;
	const int height;

	std::vector<std::vector<Color>> grid;

};

