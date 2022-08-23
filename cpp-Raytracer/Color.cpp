#include "color.h"
#include "Math.h"


color::color(const double pRed, const double pGreen, const double pBlue)
{
	this->red = pRed;
	this->green = pGreen;
	this->blue = pBlue;
}

bool color::operator==(const color& pOther) const
{

	return Math::Equal(red, pOther.red) && Math::Equal(green, pOther.green) && Math::Equal(blue, pOther.blue);
}

color color::operator+(const color& pOther) const
{
	const color sum{ red + pOther.red, green + pOther.green, blue + pOther.blue };
	return sum;
}

color color::operator-(const color& pOther) const
{
	const color difference{ red - pOther.red, green - pOther.green, blue - pOther.blue };
	return difference;
}

color color::operator*(const color& pOther) const
{
	const color product{ red * pOther.red, green * pOther.green, blue * pOther.blue };
	return product;
}

color color::operator*(const double& pOther) const
{
	const color product{ red * pOther, green * pOther, blue * pOther };
	return product;
}

//Converts a color in the range 0.0f-1.0f to one from the range 0-255
int color::convert_double_to_int_in_range(const double pNum) const
{
	int result;
	if (pNum < 0)
	{
		result = 0;
	}
	else if (pNum > 1)
	{
		result = 255;
	}
	else
	{
		double tempResult = 255 * pNum;
		tempResult = std::round(tempResult);
		result = static_cast<int>(tempResult);
	}
	return result;
}

// ReSharper disable once CppInconsistentNaming
std::ostream &operator<<(std::ostream &os, const color &pC) {
    os << "c(" << pC.red << ", " << pC.green << ", " << pC.blue << ")";
    return os;
}

color color::operator/(const double &pOther) const {
    return {red / pOther, green / pOther, blue / pOther};
}


