#include "Canvas.h"
#include <fstream>

Canvas::Canvas(int width, int height):
	width(width),
	height(height)
{
	for (int i = 0; i < height; i++)
	{
		grid.push_back(std::vector<Color>(width, Color{0,0,0}));
	}
}

Color Canvas::pixel_at(int x, int y)
{
	return grid[y][x];
}

void Canvas::write_pixel(int x, int y, Color col)
{
	grid[y][x] = col;
}

std::string Canvas::to_ppm()
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
			int red = pixel_at(x, y).RGBRed();
			int green = pixel_at(x, y).RGBGreen();
			int blue = pixel_at(x, y).RGBBlue();
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
