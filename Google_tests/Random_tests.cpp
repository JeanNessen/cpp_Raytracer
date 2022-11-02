//
// Created by Jean-Luc von Nessen on 07.03.22.
//

#include <future>

#include "gtest/gtest.h"
#include "../cpp-Raytracer/Math.h"

TEST(RandomNumbers, RandomDoubleGivesDifferentNumberEveryTime){
    double n1 = Math::GetRandomDouble(0, 1);
    double n2 = Math::GetRandomDouble(0, 1);

    EXPECT_TRUE(n1 <= 1);
    EXPECT_TRUE(n2 <= 1);
    EXPECT_TRUE(n1 >= 0);
    EXPECT_TRUE(n2 >= 0);
    EXPECT_NE(n1, n2);
}

TEST(RandomNumbers, RandomDoublesOnMultipleThreads)
{
    std::vector<std::future<double>> futures;
    for(int i = 0; i < 100; ++i)
    {
        futures.push_back(std::async(&Math::GetRandomDouble, 0, 1));
    }

    std::vector<double> numbers;
    for(int i = 0; i < futures.size(); ++i)
    {
        futures[i].wait();
        numbers.push_back(futures[i].get());
    }

    for(int i = 0; i < numbers.size() - 1; ++i)
    {
        EXPECT_NE(numbers[i], numbers[i+1]);
    }
}

TEST(RandomVectors, RandomVector)
{
    vector random_vec = vector::random(0, 1);

    EXPECT_TRUE(random_vec.x <= 1);
    EXPECT_TRUE(random_vec.y <= 1);
    EXPECT_TRUE(random_vec.z <= 1);

    EXPECT_TRUE(random_vec.x >= 0);
    EXPECT_TRUE(random_vec.y >= 0);
    EXPECT_TRUE(random_vec.z >= 0);
    
}

TEST(RandomVectors, RandomVectorInUnitSphere)
{
    vector random_vec = vector::randomInUnitSphere();

    EXPECT_TRUE(random_vec.magnitude() <= 1);
    EXPECT_TRUE(random_vec.magnitude() > 0);

}