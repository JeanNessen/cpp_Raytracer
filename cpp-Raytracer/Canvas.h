#pragma once

#include <vector>
#include <string>


//Forward declarations
class Color;

class Canvas
{
//Methods
private:
public:
    Canvas(int width, int height);
	
	[[nodiscard]] Color PixelAt(int x, int y) const;
	void WritePixel(int x, int y, Color col);
	std::string ToPPM();

    Canvas operator+(const Canvas& other);
    Canvas& operator+=(const Canvas& other);
    Canvas operator/(const double& other);
    bool operator==(const Canvas& other) const;
    bool operator!=(const Canvas& other) const;

//Members
private:
	const int width;
	const int height;

	std::vector<std::vector<Color>> grid;

public:

};

