//
// Created by jeanl on 09/01/2022.
//

#include "gtest/gtest.h"

#include "../cpp-Raytracer/CColor.h"
#include "../cpp-Raytracer/CColor.cpp"

#include "../cpp-Raytracer/CCanvas.h"
#include "../cpp-Raytracer/CCanvas.cpp"

TEST(Color, ColorCreation)
{
    CColor c1{ -0.5f, 0.4f, 1.7f };

    EXPECT_EQ(c1.red, -0.5f);
    EXPECT_EQ(c1.green, 0.4f);
    EXPECT_EQ(c1.blue, 1.7f);
}

TEST(Color, ColorPlusColor)
{
    CColor c1{ 0.9f, 0.6f, 0.75f };
    CColor c2{ 0.7f, 0.1f, 0.25f };
    CColor target{ 1.6f, 0.7f, 1.0f };

    EXPECT_EQ(c1 + c2, target);
}

TEST(Color, ColorMinusColor)
{
    CColor c1{ 0.9f, 0.6f, 0.75f };
    CColor c2{ 0.7f, 0.1f, 0.25f };
    CColor target{ 0.2f, 0.5f, 0.5f };

    EXPECT_EQ(c1 - c2, target);
}

TEST(Color, ColorTimesScalar)
{
    CColor c{ 0.2f, 0.3f, 0.4f };
    CColor target{ 0.4f, 0.6f, 0.8f };

    EXPECT_EQ(c * 2, target);
}

TEST(Color, ColorTimesColor)
{
    CColor c1{ 1.0f, 0.2f, 0.4f };
    CColor c2{ 0.9f, 1.0f, 0.1f };
    CColor target{ 0.9f, 0.2f, 0.04f };

    EXPECT_EQ(c1 * c2, target);
}

TEST(Color, RGBOutput)
{
    CColor c1{ 1.0f, 0.5f, 0.0f };
    CColor c2{ 1.5f, 0, -0.5f };

    EXPECT_EQ(c1.RGBRed(), 255);
    EXPECT_EQ(c1.RGBGreen(), 128);
    EXPECT_EQ(c1.RGBBlue(), 0);

    EXPECT_EQ(c2.RGBRed(), 255);
    EXPECT_EQ(c2.RGBBlue(), 0);
}

TEST(Canvas, CanvasCreation)
{
    CCanvas c{10, 20 };
    CColor red{ 1.0f, 0, 0 };
    c.WritePixel(2, 3, red);

    EXPECT_EQ(c.PixelAt(2, 3), red);
}

TEST(Canvas, PPMHeader)
{
    CCanvas c{5, 3 };
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
    CCanvas c{5, 3 };
    CColor c1{ 1.5, 0, 0 };
    CColor c2{ 0, 0.5, 0 };
    CColor c3{ -0.5, 0, 1 };

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
    CCanvas c1{2, 2};
    c1.WritePixel(0, 0, CColor(1, 1, 1));
    c1.WritePixel(1, 1, CColor(0.5, 0.5, 0.5));

    CCanvas c2{2, 2};
    c2.WritePixel(0, 0, CColor(0.75, 0.75, 0.75));

    CCanvas c3 = c1 + c2;

    EXPECT_EQ(c3.PixelAt(0, 0), CColor(1.75, 1.75, 1.75));
    EXPECT_EQ(c3.PixelAt(1, 1), CColor(0.5, 0.5, 0.5));
}

TEST(Canvas, ComparingTwoCanvases)
{
    CCanvas c1{2, 2};
    c1.WritePixel(0, 0, CColor(1, 1, 1));
    c1.WritePixel(1, 1, CColor(0.5, 0.5, 0.5));

    CCanvas c2{2, 2};
    c2.WritePixel(0, 0, CColor(0.75, 0.75, 0.75));

    CCanvas c3 = c1;

    EXPECT_EQ(c1, c3);
    EXPECT_NE(c1, c2);
}

TEST(Color, WhiteAndBlackGlobalColors)
{
    CColor black = color::black;
    CColor white = color::white;

    EXPECT_EQ(black, CColor(0, 0, 0));
    EXPECT_EQ(white, CColor(1, 1, 1));
}