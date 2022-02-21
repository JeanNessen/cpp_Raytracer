#pragma once
#include "Math.h"
#include <iostream>
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

    //Debug
    void Print() const;

    friend std::ostream& operator<<(std::ostream& os, const Color& c);


private:

	int ConvertFloatToIntInRange(float num);
};

