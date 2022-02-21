#include "Color.h"


Color::Color(float red, float green, float blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

bool Color::operator==(const Color& other) const
{

	return Math::Equal(red, other.red) && Math::Equal(green, other.green) && Math::Equal(blue, other.blue);
}

Color Color::operator+(const Color& other) const
{
	Color sum{ red + other.red, green + other.green, blue + other.blue };
	return sum;
}

Color Color::operator-(const Color& other) const
{
	Color difference{ red - other.red, green - other.green, blue - other.blue };
	return difference;
}

Color Color::operator*(const Color& other) const
{
	Color product{ red * other.red, green * other.green, blue * other.blue };
	return product;
}

Color Color::operator*(const float& other) const
{
	Color product{ red * other, green * other, blue * other };
	return product;
}

//Converts a color in the range 0.0f-1.0f to one from the range 0-255
int Color::ConvertFloatToIntInRange(float num)
{
	int result;
	if (num < 0)
	{
		result = 0;
	}
	else if (num > 1)
	{
		result = 255;
	}
	else
	{
		float temp_result = 255 * num;
		temp_result = std::round(temp_result);
		result = int(temp_result);
	}
	return result;
}

void Color::Print() const {
    std::cout << "(" << red << ", " << green << ", " << blue << ")" << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Color &c) {
    os << "c(" << c.red << ", " << c.green << ", " << c.blue << ")";
    return os;
}


