#include <iostream>
#pragma once

struct color
{

private:
	[[nodiscard]] int convert_double_to_int_in_range(double pNum) const;

public:

    color() = default;
	color(double pRed, double pGreen, double pBlue);

	bool operator==(const color& pOther) const;
	color operator+(const color& pOther) const;
	color operator-(const color& pOther) const;
	color operator*(const color& pOther) const;
	color operator*(const double& pOther) const;
    color operator/(const double& pOther) const;

    [[nodiscard]] int rgb_red() const { return convert_double_to_int_in_range(red); }
    [[nodiscard]] int rgb_green() const { return convert_double_to_int_in_range(green); }
    [[nodiscard]] int rgb_blue() const { return convert_double_to_int_in_range(blue); }

    // ReSharper disable once CppInconsistentNaming
    friend std::ostream& operator<<(std::ostream& os, const color& pC);

    double red;
    double green;
    double blue;
};

namespace colors{
    const color black{0, 0, 0};
    const color white{1, 1, 1};
    const color blue{0, 0, 1};
    const color red{1, 0, 0};
    const color green{0, 1, 0};

}