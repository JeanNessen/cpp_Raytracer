#pragma once
#include "Math.h"
struct Color
{
	float red;
	float green;
	float blue;

	Color() = default;
	Color(float red, float green, float blue);

	bool operator==(const Color& other) const;
	Color operator+(const Color& other) const;
	Color operator-(const Color& other) const;
	Color operator*(const Color& other) const;
	Color operator*(const float& other) const;

	int RGBRed() { return ConvertFloatToIntInRange(red); }
	int RGBGreen() { return ConvertFloatToIntInRange(green); }
	int RGBBlue() { return ConvertFloatToIntInRange(blue); }

private:

	int ConvertFloatToIntInRange(float num);
};

