//
// Created by jeanl on 09/01/2022.
//

#include "gtest/gtest.h"

#include "../cpp-Raytracer/Color.h"
#include "../cpp-Raytracer/Color.cpp"

#include "../cpp-Raytracer/Canvas.h"
#include "../cpp-Raytracer/Canvas.cpp"

TEST(Color, ColorCreation)
{
    Color c1{ -0.5f, 0.4f, 1.7f };

    EXPECT_EQ(c1.red, -0.5f);
    EXPECT_EQ(c1.green, 0.4f);
    EXPECT_EQ(c1.blue, 1.7f);
}

TEST(Color, ColorPlusColor)
{
    Color c1{ 0.9f, 0.6f, 0.75f };
    Color c2{ 0.7f, 0.1f, 0.25f };
    Color target{ 1.6f, 0.7f, 1.0f };

    EXPECT_EQ(c1 + c2, target);
}

TEST(Color, ColorMinusColor)
{
    Color c1{ 0.9f, 0.6f, 0.75f };
    Color c2{ 0.7f, 0.1f, 0.25f };
    Color target{ 0.2f, 0.5f, 0.5f };

    EXPECT_EQ(c1 - c2, target);
}

TEST(Color, ColorTimesScalar)
{
    Color c{ 0.2f, 0.3f, 0.4f };
    Color target{ 0.4f, 0.6f, 0.8f };

    EXPECT_EQ(c * 2, target);
}

TEST(Color, ColorTimesColor)
{
    Color c1{ 1.0f, 0.2f, 0.4f };
    Color c2{ 0.9f, 1.0f, 0.1f };
    Color target{ 0.9f, 0.2f, 0.04f };

    EXPECT_EQ(c1 * c2, target);
}

TEST(Color, RGBOutput)
{
    Color c1{ 1.0f, 0.5f, 0.0f };
    Color c2{ 1.5f, 0, -0.5f };

    EXPECT_EQ(c1.RGBRed(), 255);
    EXPECT_EQ(c1.RGBGreen(), 128);
    EXPECT_EQ(c1.RGBBlue(), 0);

    EXPECT_EQ(c2.RGBRed(), 255);
    EXPECT_EQ(c2.RGBBlue(), 0);
}

TEST(Canvas, CanvasCreation)
{
    Canvas c{ 10, 20 };
    Color red{ 1.0f, 0, 0 };
    c.WritePixel(2, 3, red);

    EXPECT_EQ(c.PixelAt(2, 3), red);
}

TEST(Canvas, PPMHeader)
{
    Canvas c{ 5, 3 };
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
    Canvas c{ 5, 3 };
    Color c1{ 1.5, 0, 0 };
    Color c2{ 0, 0.5, 0 };
    Color c3{ -0.5, 0, 1 };

    c.WritePixel(0, 0, c1);
    c.WritePixel(2, 1, c2);
    c.WritePixel(4, 2, c3);

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
    Canvas c1{2, 2};
    c1.WritePixel(0, 0, Color(1, 1, 1));
    c1.WritePixel(1, 1, Color(0.5, 0.5, 0.5));

    Canvas c2{2, 2};
    c2.WritePixel(0, 0, Color(0.75, 0.75, 0.75));

    Canvas c3 = c1 + c2;

    EXPECT_EQ(c3.PixelAt(0, 0), Color(1.75, 1.75, 1.75));
    EXPECT_EQ(c3.PixelAt(1, 1), Color(0.5, 0.5, 0.5));
}

TEST(Canvas, ComparingTwoCanvases)
{
    Canvas c1{2, 2};
    c1.WritePixel(0, 0, Color(1, 1, 1));
    c1.WritePixel(1, 1, Color(0.5, 0.5, 0.5));

    Canvas c2{2, 2};
    c2.WritePixel(0, 0, Color(0.75, 0.75, 0.75));

    Canvas c3 = c1;

    EXPECT_EQ(c1, c3);
    EXPECT_NE(c1, c2);
}

TEST(Color, WhiteAndBlackGlobalColors)
{
    Color black = color::black;
    Color white = color::white;

    EXPECT_EQ(black, Color(0, 0, 0));
    EXPECT_EQ(white, Color(1, 1, 1));
}