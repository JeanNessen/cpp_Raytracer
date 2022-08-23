//
// Created by jeanl on 09/01/2022.
//

#include "gtest/gtest.h"

#include "../cpp-Raytracer/color.h"
#include "../cpp-Raytracer/color.cpp"

#include "../cpp-Raytracer/Canvas.h"
#include "../cpp-Raytracer/Canvas.cpp"

TEST(Color, ColorCreation)
{
    color c1{ -0.5f, 0.4f, 1.7f };

    EXPECT_EQ(c1.red, -0.5f);
    EXPECT_EQ(c1.green, 0.4f);
    EXPECT_EQ(c1.blue, 1.7f);
}

TEST(Color, ColorPlusColor)
{
    color c1{ 0.9f, 0.6f, 0.75f };
    color c2{ 0.7f, 0.1f, 0.25f };
    color target{ 1.6f, 0.7f, 1.0f };

    EXPECT_EQ(c1 + c2, target);
}

TEST(Color, ColorMinusColor)
{
    color c1{ 0.9f, 0.6f, 0.75f };
    color c2{ 0.7f, 0.1f, 0.25f };
    color target{ 0.2f, 0.5f, 0.5f };

    EXPECT_EQ(c1 - c2, target);
}

TEST(Color, ColorTimesScalar)
{
    color c{ 0.2f, 0.3f, 0.4f };
    color target{ 0.4f, 0.6f, 0.8f };

    EXPECT_EQ(c * 2, target);
}

TEST(Color, ColorTimesColor)
{
    color c1{ 1.0f, 0.2f, 0.4f };
    color c2{ 0.9f, 1.0f, 0.1f };
    color target{ 0.9f, 0.2f, 0.04f };

    EXPECT_EQ(c1 * c2, target);
}

TEST(Color, RGBOutput)
{
    color c1{ 1.0f, 0.5f, 0.0f };
    color c2{ 1.5f, 0, -0.5f };

    EXPECT_EQ(c1.rgb_red(), 255);
    EXPECT_EQ(c1.rgb_green(), 128);
    EXPECT_EQ(c1.rgb_blue(), 0);

    EXPECT_EQ(c2.rgb_red(), 255);
    EXPECT_EQ(c2.rgb_blue(), 0);
}

TEST(Canvas, CanvasCreation)
{
    canvas c{10, 20 };
    color red{ 1.0f, 0, 0 };
    c.write_pixel(2, 3, red);

    EXPECT_EQ(c.pixel_at(2, 3), red);
}

TEST(Canvas, PPMHeader)
{
    canvas c{5, 3 };
    std::string ppm = c.to_ppm();
    std::stringstream ppmStream(ppm);
    std::string line1;
    std::getline(ppmStream, line1);
    std::string line2;
    std::getline(ppmStream, line2);
    std::string line3;
    std::getline(ppmStream, line3);

    EXPECT_EQ(line1, "P3");
    EXPECT_EQ(line2, "5 3");
    EXPECT_EQ(line3, "255");
}

TEST(Canvas, PPMPixelData)
{
    canvas c{5, 3 };
    color c1{ 1.5, 0, 0 };
    color c2{ 0, 0.5, 0 };
    color c3{ -0.5, 0, 1 };

    c.write_pixel(0, 0, c1);
    c.write_pixel(2, 1, c2);
    c.write_pixel(4, 2, c3);

    std::string ppm = c.to_ppm();
    std::stringstream ppmStream(ppm);

    //Remove the header from the stringstream
    std::string trash;
    std::getline(ppmStream, trash);
    std::getline(ppmStream, trash);
    std::getline(ppmStream, trash);



    std::string line1;
    std::getline(ppmStream, line1);
    std::string line2;
    std::getline(ppmStream, line2);
    std::string line3;
    std::getline(ppmStream, line3);

    EXPECT_EQ(line1, "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
    EXPECT_EQ(line2, "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0");
    EXPECT_EQ(line3, "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");
}

TEST(Canvas, AddingTwoCanvases)
{
    canvas c1{2, 2};
    c1.write_pixel(0, 0, color(1, 1, 1));
    c1.write_pixel(1, 1, color(0.5, 0.5, 0.5));

    canvas c2{2, 2};
    c2.write_pixel(0, 0, color(0.75, 0.75, 0.75));

    canvas c3 = c1 + c2;

    EXPECT_EQ(c3.pixel_at(0, 0), color(1.75, 1.75, 1.75));
    EXPECT_EQ(c3.pixel_at(1, 1), color(0.5, 0.5, 0.5));
}

TEST(Canvas, ComparingTwoCanvases)
{
    canvas c1{2, 2};
    c1.write_pixel(0, 0, color(1, 1, 1));
    c1.write_pixel(1, 1, color(0.5, 0.5, 0.5));

    canvas c2{2, 2};
    c2.write_pixel(0, 0, color(0.75, 0.75, 0.75));

    canvas c3 = c1;

    EXPECT_EQ(c1, c3);
    EXPECT_NE(c1, c2);
}

TEST(Color, WhiteAndBlackGlobalColors)
{
    color black = colors::black;
    color white = colors::white;

    EXPECT_EQ(black, color(0, 0, 0));
    EXPECT_EQ(white, color(1, 1, 1));
}