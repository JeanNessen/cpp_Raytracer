#pragma once

#include <vector>
#include <string>
#include "Color.h"

class canvas
{
//Methods
private:
public:
    canvas(int pWidth, int pHeight);
	
	[[nodiscard]] color pixel_at(int pX, int pY) const;
	void write_pixel(int pX, int pY, color pCol);
	[[nodiscard]] std::string to_ppm() const;

    canvas operator+(const canvas& pOther) const;
    canvas& operator+=(const canvas& pOther);
    canvas operator/(const double& pOther) const;
    bool operator==(const canvas& pOther) const;
    bool operator!=(const canvas& pOther) const;

//Members
private:
	const int m_width;
	const int m_height;

	std::vector<std::vector<color>> m_grid;

public:

};

