#pragma once
#include <vector>
#include "Color.h"
#include <string>


class Canvas
{
public:
	
	Canvas(int width, int height);
	Color pixel_at(int x, int y);
	void write_pixel(int x, int y, Color col);
	std::string to_ppm();


private:
	const int width;
	const int height;

	std::vector<std::vector<Color>> grid;

};

