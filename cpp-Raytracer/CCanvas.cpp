#include "CCanvas.h"
#include <fstream>

CCanvas::CCanvas(int width, int height):
	width(width),
	height(height)
{
	for (int i = 0; i < height; i++)
	{
		grid.push_back(std::vector<CColor>(width, CColor{0,0,0}));
	}
}

CColor CCanvas::PixelAt(int x, int y) const
{
	return grid[y][x];
}

void CCanvas::WritePixel(int x, int y, CColor col)
{
	grid[y][x] = col;
}

std::string CCanvas::to_ppm()
{
	std::remove("output.ppm");
	std::string line1 = "P3\n";
	std::string line2 = std::to_string(width) + " " + std::to_string(height) + "\n";
	std::string line3 = "255\n";

	std::string header = line1 + line2 + line3;

	std::ofstream out("output.ppm", std::ofstream::app);
	out << header;

	std::string body;
	for (int y = 0; y < height; ++y)
	{
		std::string line;
		for (int x = 0; x < width; ++x)
		{
			int red = PixelAt(x, y).RGBRed();
			int green = PixelAt(x, y).RGBGreen();
			int blue = PixelAt(x, y).RGBBlue();
			std::string colorString = std::to_string(red) + " " + std::to_string(green) + " " + std::to_string(blue);
			if (x != width - 1)
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

CCanvas CCanvas::operator+(const CCanvas &other) {
    CCanvas sum{width, height};
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            CColor color_sum = PixelAt(x, y) + other.PixelAt(x, y);
            sum.WritePixel(x, y, color_sum);
        }
    }
    return sum;
}

CCanvas& CCanvas::operator+=(const CCanvas &other) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            CColor color_sum = PixelAt(x, y) + other.PixelAt(x, y);
            WritePixel(x, y, color_sum);
        }
    }
    return *this;
}

CCanvas CCanvas::operator/(const double& other) {
    CCanvas quotient{width, height};
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            CColor color_quotient = PixelAt(x, y) / other;
            quotient.WritePixel(x, y, color_quotient);
        }
    }
    return quotient;
}

bool CCanvas::operator==(const CCanvas &other) const {

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (PixelAt(x, y) != other.PixelAt(x, y))
            {
                return false;
            }
        }
    }
    return true;
}

bool CCanvas::operator!=(const CCanvas &other) const {
    return !(*this == other);
}
