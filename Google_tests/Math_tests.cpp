//
// Created by jeanl on 08/01/2022.
//

#include "gtest/gtest.h"
#include "../cpp-Raytracer/Math.h"
#include "../cpp-Raytracer/Math.cpp"

TEST(Tuples, CreatePoint)
{
    Point p = Point(4, -4, 3);
    Tuple target = Tuple(4, -4, 3, 1);

    EXPECT_EQ(p, target);
}

TEST(Tuples, CreateVector)
{
    Vector v = Vector(4, -4, 3);
    Tuple target{ 4, -4, 3, 0 };
    EXPECT_EQ(v, target);
}

TEST(GeneralMath, FloatComparison)
{
    float a = 4;
    float b = 4.001;
    float c = 4.000001;

    EXPECT_FALSE(Math::Equal(a, b));
    EXPECT_TRUE(Math::Equal(a, c));
}

TEST(GeneralMath, TupleComparison)
{
    Tuple a{ 1, 2, 3, 4 };
    Tuple b{ 1, 2, 3, 4.01 };
    Tuple c{ 1, 2 ,3, 4.00001 };

    EXPECT_FALSE(Math::Equal(a, b));
    EXPECT_TRUE(Math::Equal(a, c));
}

TEST(Tuples, TupleAddition)
{
    Tuple a1{ 3, -2, 5, 1 };
    Tuple a2{ -2, 3, 1, 0 };
    Tuple target{ 1, 1, 6, 1 };

    EXPECT_EQ(a1+a2, target);
}

TEST(Tuples, PointMinusPoint)
{
    Point p1 = Point(3, 2, 1);
    Point p2 = Point(5, 6, 7);
    Vector target = Vector(-2, -4, -6);

    EXPECT_EQ(p1-p2, target);
}

TEST(Tuples, PointMinusVector)
{
    Point p = Point(3, 2, 1);
    Vector v = Vector(5, 6, 7);
    Point target = Point(-2, -4, -6);

    EXPECT_EQ(p-v, target);
}

TEST(Tuples, VectorMinusVector)
{
    Vector v1 = Vector(3, 2, 1);
    Vector v2 = Vector(5, 6, 7);
    Vector target = Vector(-2, -4, -6);

    EXPECT_EQ(v1-v2, target);
}
TEST(Tuples, TupleNegation)
{
    Tuple a{ 1, -2, 3, -4 };
    Tuple target{ -1, 2, -3, 4 };

    EXPECT_EQ(-a, target);
}

TEST(Tuples, TupleScalarMultiplicaiton)
{
    Tuple a{ 1, -2, 3, -4 };
    Tuple target{ 3.5, -7, 10.5, -14 };

    EXPECT_EQ(a*3.5, target);
}

TEST(Tuples, TupleFractionMultiplication)
{
    Tuple a{ 1, -2, 3, -4 };
    Tuple target{ 0.5, -1, 1.5, -2 };

    EXPECT_EQ(a*0.5, target);
}

TEST(Tuples, VectorMagnitude01)
{
    Vector v = Vector(1, 0 , 0);

    EXPECT_TRUE(Math::Equal(v.magnitude(), 1));
}

TEST(Tuples, VectorMagnitude02)
{
    Vector v = Vector(0, 1 , 0);

    EXPECT_TRUE(Math::Equal(v.magnitude(), 1));
}
TEST(Tuples, VectorMagnitude03)
{
    Vector v = Vector(0, 0 , 1);

    EXPECT_TRUE(Math::Equal(v.magnitude(), 1));
}
TEST(Tuples, VectorMagnitude04)
{
    Vector v = Vector(1, 2 , 3);

    EXPECT_TRUE(Math::Equal(v.magnitude(), std::sqrt(14)));
}

TEST(Tuples, NormalizeVector01)
{
    Vector v = Vector(4, 0, 0);
    Vector target = Vector(1, 0, 0);

    EXPECT_TRUE(Math::Equal(v.normalized(), target));
}

TEST(Tuples, NormalizeVector02)
{
    Vector v = Vector(1, 2, 3);
    Vector target = Vector(1 / std::sqrt(14), 2 / std::sqrt(14), 3 / std::sqrt(14));

    EXPECT_TRUE(Math::Equal(v.normalized(), target));
}

TEST(Tuples, NormalizedVectorMagnitude)
{
    Vector v = Vector(1, 2, 3);
    Vector norm = v.normalized();

    EXPECT_TRUE(Math::Equal(norm.magnitude(), 1));
}

TEST(Tuples, DotProductVectors)
{
    Vector v1 = Vector(1, 2, 3);
    Vector v2 = Vector(2, 3, 4);

    EXPECT_TRUE(Math::Equal(Math::Dot(v1, v2), 20));
}

TEST(Tuples, CrossProductVectors)
{
    Vector v1 = Vector(1, 2, 3);
    Vector v2 = Vector(2, 3, 4);
    Vector target = Vector(-1, 2, -1);

    EXPECT_TRUE(Math::Equal(Math::Cross(v1, v2), target));
}

TEST(Matricies, ConstructionMatrix4)
{
    Matrix4 M{	1,    2,    3,    4,
                  5.5,  6.5,  7.5,  8.5,
                  9,    10,   11,   12,
                  13.5, 14.5, 15.5, 16.5 };

    EXPECT_EQ(M(0,0), 1);
    EXPECT_EQ(M(0,3), 4);
    EXPECT_EQ(M(1,0), 5.5);
    EXPECT_EQ(M(1,2), 7.5);
    EXPECT_EQ(M(2,2), 11);
    EXPECT_EQ(M(3,0), 13.5);
    EXPECT_EQ(M(3,2), 15.5);
}

TEST(Matricies, ConstructionMatrix3)
{
    Matrix3 M{ -3,  5, 0,
               1, -2, -7,
               0,  1,  1};

    EXPECT_EQ(M(0,0), -3);
    EXPECT_EQ(M(1,1), -2);
    EXPECT_EQ(M(2,2), 1);
}

TEST(Matricies, ConstructionMatrix2)
{
    Matrix2 M{ -3,  5,
               1, -2};

    EXPECT_EQ(M(0,0), -3);
    EXPECT_EQ(M(0,1), 5);
    EXPECT_EQ(M(1,0), 1);
    EXPECT_EQ(M(1,1), -2);
}

TEST(Matricies, Matrix2Comparison)
{
    Matrix2 A{
            1, 2,
            3, 4
    };

    Matrix2 B{
            1, 2,
            3, 4
    };

    Matrix2 C{
            2, 1,
            4, 3
    };

    EXPECT_EQ(A, B);
    EXPECT_NE(A, C);
}

TEST(Matricies, Matrix3Comparison)
{
    Matrix3 A{
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
    };

    Matrix3 B{
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
    };

    Matrix3 C{
            3, 2, 1,
            6, 5, 4,
            9, 8, 7
    };

    EXPECT_EQ(A, B);
    EXPECT_NE(A, C);
}

TEST(Matricies, Matrix4Comparison)
{
    Matrix4 A{ 1, 2, 3, 4,
               5, 6, 7, 8,
               9, 8, 7, 6,
               5, 4, 3, 2 };

    Matrix4 B{ 1, 2, 3, 4,
               5, 6, 7, 8,
               9, 8, 7, 6,
               5, 4, 3, 2 };

    Matrix4 C{ 2, 3, 4, 5,
               6, 7, 8, 9,
               8, 7, 6, 5,
               4, 3, 2, 1 };

    EXPECT_EQ(A, B);
    EXPECT_NE(A, C);
}

TEST(Matricies, Matrix4Multiplication)
{
    Matrix4 A{
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 8, 7, 6,
            5, 4, 3, 2
    };
    Matrix4 B{
            -2, 1, 2, 3,
            3, 2, 1, -1,
            4, 3, 6, 5,
            1, 2, 7, 8
    };
    Matrix4 Target{
            20, 22, 50, 48,
            44, 54, 114, 108,
            40, 58, 110, 102,
            16, 26, 46, 42
    };

    EXPECT_EQ(A*B, Target);
}

TEST(Matricies, Matrix4VectorMultiplication)
{
    Matrix4 A{
            1, 2, 3, 4,
            2, 4, 4, 2,
            8, 6, 4, 1,
            0, 0, 0, 1
    };

    Tuple b{ 1, 2, 3, 1 };

    Tuple target{ 18, 24, 33, 1 };

    EXPECT_EQ(A*b, target);
}

TEST(Matricies, Matrix4Identity)
{
    Matrix4 A{
            1, 2, 3, 4,
            2, 4, 4, 2,
            8, 6, 4, 1,
            0, 0, 0, 1
    };

    EXPECT_EQ(A*Math::identiy_matrix, A);
}

TEST(Matricies, Matrix4Transpose)
{
    Matrix4 M{
            0, 9, 3, 0,
            9, 8, 0, 8,
            1, 8, 5, 3,
            0, 0, 5, 8
    };

    Matrix4 target{
            0, 9, 1, 0,
            9, 8, 8, 0,
            3, 0, 5, 5,
            0, 8, 3, 8
    };

    EXPECT_EQ(M.Transposed(), target);
    EXPECT_EQ(Math::identiy_matrix.Transposed(), Math::identiy_matrix);
}

TEST(Matricies, Matrix2Determinant)
{
    Matrix2 A{
            1, 5,
            -3, 2
    };

    EXPECT_TRUE(Math::Equal(A.Determinant(), 17));
}

TEST(Matricies, Matrix3Submatrix)
{
    Matrix3 A{
            1, 5, 0,
            -3, 2, 7,
            0, 6, -3
    };
    Matrix2 target_submatrix{
            -3, 2,
            0, 6
    };

    EXPECT_EQ(Math::Submatrix(A, 0, 2), target_submatrix);
}

TEST(Matricies, Matrix4Submatrix)
{
    Matrix4 A{
            -6, 1, 1, 6,
            -8, 5, 8, 6,
            -1, 0, 8, 2,
            -7, 1, -1, 1
    };

    Matrix3 target_submatrix{
            -6, 1, 6,
            -8, 8, 6,
            -7, -1, 1
    };

    EXPECT_EQ(Math::Submatrix(A, 2, 1), target_submatrix);
}

TEST(Matricies, Matrix3Minor)
{
    Matrix3 A{
            2, 5, 0,
            2, -1, -7,
            6, -1, 5
    };

    Matrix2 B = Math::Submatrix(A, 1, 0);

    EXPECT_TRUE(Math::Equal(B.Determinant(), 25));
    EXPECT_TRUE(Math::Equal(A.Minor(1, 0), 25));
}

TEST(Matricies, Matrix3Cofactor)
{
    Matrix3 A{
            3, 5, 0,
            2, -1, -7,
            6, -1, 5
    };

    EXPECT_TRUE(Math::Equal(A.Minor(0, 0), -12));
    EXPECT_TRUE(Math::Equal(A.Cofactor(0, 0), -12));
    EXPECT_TRUE(Math::Equal(A.Minor(0, 1), 25));
    EXPECT_TRUE(Math::Equal(A.Minor(0, 2), -25));
}

TEST(Matricies, Matrix3Determinant)
{
    Matrix3 A{
            1, 2, 6,
            -5, 8, -4,
            2, 6, 4
    };

    EXPECT_TRUE(Math::Equal(A.Cofactor(0, 0), 56));
    EXPECT_TRUE(Math::Equal(A.Cofactor(0, 1), 12));
    EXPECT_TRUE(Math::Equal(A.Cofactor(0, 2), -46));

    EXPECT_TRUE(Math::Equal(A.Determinant(), -196));
}

TEST(Matricies, Matrix4Determinant)
{
    Matrix4 A{
            -2, -8, 3, 5,
            -3, 1, 7, 3,
            1, 2, -9, 6,
            -6, 7, 7, -9
    };

    EXPECT_TRUE(Math::Equal(A.Cofactor(0, 0), 690));
    EXPECT_TRUE(Math::Equal(A.Cofactor(0, 1), 447));
    EXPECT_TRUE(Math::Equal(A.Cofactor(0, 2), 210));
    EXPECT_TRUE(Math::Equal(A.Cofactor(0, 3), 51));

    EXPECT_TRUE(Math::Equal(A.Determinant(), -4071));
}

