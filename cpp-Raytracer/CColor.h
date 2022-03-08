#pragma once
#include "Math.h"
#include <iostream>

struct CColor
{
	double red;
	double green;
	double blue;

	CColor() = default;
	CColor(double red, double green, double blue);

	bool operator==(const CColor& other) const;
	CColor operator+(const CColor& other) const;
	CColor operator-(const CColor& other) const;
	CColor operator*(const CColor& other) const;
	CColor operator*(const double& other) const;
    CColor operator/(const double& other) const;


	int RGBRed() { return ConvertdoubleToIntInRange(red); }
	int RGBGreen() { return ConvertdoubleToIntInRange(green); }
	int RGBBlue() { return ConvertdoubleToIntInRange(blue); }

    //Debug
    void Print() const;

    friend std::ostream& operator<<(std::ostream& os, const CColor& c);


private:

	int ConvertdoubleToIntInRange(double num);
};

namespace color{
    const CColor black{0, 0, 0};
    const CColor white{1, 1, 1};
    const CColor blue{0, 0, 1};
    const CColor red{1, 0, 0};
    const CColor green{0, 1, 0};

}