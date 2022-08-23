#include "Canvas.h"
#include <fstream>
#include "color.h"

canvas::canvas(const int pWidth, const int pHeight):
	m_width(pWidth),
	m_height(pHeight)
{
	for (int i = 0; i < pHeight; i++)
	{
		m_grid.push_back(std::vector<color>(pWidth, color{0,0,0}));
	}
}

color canvas::pixel_at(const int pX, const int pY) const
{
	return m_grid[pY][pX];
}

void canvas::write_pixel(const int pX, const int pY, const color pCol)
{
	m_grid[pY][pX] = pCol;
}

std::string canvas::to_ppm() const
{
	std::remove("output.ppm");
	std::string line1 = "P3\n";
	std::string line2 = std::to_string(m_width) + " " + std::to_string(m_height) + "\n";
	std::string line3 = "255\n";

	std::string header = line1 + line2 + line3;

	std::ofstream out("output.ppm", std::ofstream::app);
	out << header;

	std::string body;
	for (int y = 0; y < m_height; ++y)
	{
		std::string line;
		for (int x = 0; x < m_width; ++x)
		{
			int red = pixel_at(x, y).rgb_red();
			int green = pixel_at(x, y).rgb_green();
			int blue = pixel_at(x, y).rgb_blue();
			std::string colorString = std::to_string(red) + " " + std::to_string(green) + " " + std::to_string(blue);
			if (x != m_width - 1)
			{
				colorString += " ";
			}
			line += colorString;
		}
		line += "\n";
		body += line;
	}
	out << body;
	out.close();

	

	return header + body;
}

canvas canvas::operator+(const canvas &pOther) const
{
    canvas sum{m_width, m_height};
    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
	        const color colorSum = pixel_at(x, y) + pOther.pixel_at(x, y);
            sum.write_pixel(x, y, colorSum);
        }
    }
    return sum;
}

canvas& canvas::operator+=(const canvas &pOther)
{
    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
	        const color colorSum = pixel_at(x, y) + pOther.pixel_at(x, y);
            write_pixel(x, y, colorSum);
        }
    }
    return *this;
}

canvas canvas::operator/(const double& pOther) const
{
    canvas quotient{m_width, m_height};
    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
	        const color colorQuotient = pixel_at(x, y) / pOther;
            quotient.write_pixel(x, y, colorQuotient);
        }
    }
    return quotient;
}

bool canvas::operator==(const canvas &pOther) const
{

    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
            if (pixel_at(x, y) != pOther.pixel_at(x, y))
            {
                return false;
            }
        }
    }
    return true;
}

bool canvas::operator!=(const canvas &pOther) const
{
    return !(*this == pOther);
}
