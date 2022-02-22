#pragma once
#include "Math.h"
#include <iostream>
struct Color
{
	double red;
	double green;
	double blue;

	Color() = default;
	Color(double red, double green, double blue);

	bool operator==(const Color& other) const;
	Color operator+(const Color& other) const;
	Color operator-(const Color& other) const;
	Color operator*(const Color& other) const;
	Color operator*(const double& other) const;

	int RGBRed() { return ConvertdoubleToIntInRange(red); }
	int RGBGreen() { return ConvertdoubleToIntInRange(green); }
	int RGBBlue() { return ConvertdoubleToIntInRange(blue); }

    //Debug
    void Print() const;

    friend std::ostream& operator<<(std::ostream& os, const Color& c);


private:

	int ConvertdoubleToIntInRange(double num);
};

