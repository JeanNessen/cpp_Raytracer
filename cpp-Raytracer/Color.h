#pragma once

#include <iostream>

struct Color
{

private:
    int ConvertdoubleToIntInRange(double num);

public:

    Color() = default;
	Color(double red, double green, double blue);

	bool operator==(const Color& other) const;
	Color operator+(const Color& other) const;
	Color operator-(const Color& other) const;
	Color operator*(const Color& other) const;
	Color operator*(const double& other) const;
    Color operator/(const double& other) const;

    int RGBRed() { return ConvertdoubleToIntInRange(red); }
	int RGBGreen() { return ConvertdoubleToIntInRange(green); }
	int RGBBlue() { return ConvertdoubleToIntInRange(blue); }

    friend std::ostream& operator<<(std::ostream& os, const Color& c);

    double red;
    double green;
    double blue;
};

namespace color{
    const Color black{0, 0, 0};
    const Color white{1, 1, 1};
    const Color blue{0, 0, 1};
    const Color red{1, 0, 0};
    const Color green{0, 1, 0};

}