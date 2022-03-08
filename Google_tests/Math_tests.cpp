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

TEST(Tuples, ReflectingVectorAt45)
{
    Vector v{1, -1, 0};
    Vector n{0, 1, 0};

    Vector r = v.Reflect(n);

    EXPECT_TRUE(Math::Equal(r, Vector(1, 1, 0)));
}

TEST(Tuples, ReflectingVectorOffSlant)
{
    Vector v{0, -1, 0};
    Vector n{static_cast<float>(std::sqrt(2)/2), static_cast<float>(std::sqrt(2)/2), 0};

    Vector r = v.Reflect(n);

    EXPECT_TRUE(Math::Equal(r, Vector(1, 0, 0)));
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

TEST(Matricies, Matrix4ScalarMultiplication)
{
    Matrix4 A{
        1, 1, 1, 1,
        2, 2, 2, 2,
        3, 3, 3, 3,
        4, 4, 4, 4
    };

    double b = 2;

    Matrix4 target{
        2, 2, 2, 2,
        4, 4, 4, 4,
        6, 6, 6, 6,
        8, 8, 8, 8
    };

    //EXPECT_EQ(A * b, target);
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
    EXPECT_TRUE(Math::Equal(A.Minor(1, 0), 25));
    EXPECT_TRUE(Math::Equal(A.Cofactor(1, 0), -25));
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

TEST(Matricies, Matrix4Invertible)
{
    Matrix4 A{
            6, 4, 4, 4,
            5, 5, 7, 6,
            4, -9, 3, -7,
            9, 1, 7, -6
    };

    EXPECT_TRUE(Math::Equal(A.Determinant(), -2120));
    EXPECT_TRUE(A.IsInvertible());
}

TEST(Matricies, Matrix4NonInvertible)
{
    Matrix4 A{
            -4, 2, -2, -3,
            9, 6, 2, 6,
            0, -5, 1, -5,
            0, 0, 0, 0
    };

    EXPECT_TRUE(Math::Equal(A.Determinant(), 0));
    EXPECT_FALSE(A.IsInvertible());
}

TEST(Matricies, Matrix4Inversion01)
{
    Matrix4 A{
            -5, 2, 6, -8,
            1, -5, 1, 8,
            7, 7, -6, -7,
            1, -3, 7, 4
    };
    Matrix4 B = A.Inversed();

    Matrix4 Target{
            0.21805, 0.45113, 0.24060, -0.04511,
            -0.80827, -1.45677, -0.44361, 0.52068,
            -0.07895, -0.22368, -0.05263, 0.19737,
            -0.52256, -0.81391, -0.30075, 0.30639
    };

    EXPECT_TRUE(Math::Equal(A.Determinant(), 532));

    EXPECT_TRUE(Math::Equal(A.Cofactor(2, 3), -160));
    EXPECT_TRUE(Math::Equal(B(3, 2), -160.0f/532.0f));

    EXPECT_TRUE(Math::Equal(A.Cofactor(3, 2), 105));
    EXPECT_TRUE(Math::Equal(B(2, 3), 105.0f/532.0f));

    EXPECT_EQ(B, Target);
}

TEST(Matricies, Matrix4Inversion02)
{
    Matrix4 A{
            8, -5, 9, 2,
            7, 5, 6, 1,
            -6, 0, 9, 6,
            -3, 0, -9, -4
    };


    Matrix4 target{
            -0.15385, -0.15385, -0.28205, -0.53846,
            -0.07692, 0.12308, 0.02564, 0.03077,
            0.35897, 0.35897, 0.43590, 0.92308,
            -0.69231, -0.69231, -0.76923, -1.92308
    };

    EXPECT_EQ(A.Inversed(), target);
}

TEST(Matricies, Matrix4Inversion03)
{
    Matrix4 A{
            9, 3, 0, 9,
            -5, -2, -6, -3,
            -4, 9, 6, 4,
            -7, 6, 6, 2
    };

    Matrix4 target{
            -0.04074, -0.07778, 0.14444, -0.22222,
            -0.07778, 0.03333, 0.36667, -0.33333,
            -0.02901, -0.14630, -0.10926, 0.12963,
            0.17778, 0.06667, -0.26667, 0.33333
    };

    EXPECT_EQ(A.Inversed(), target);
}

TEST(Matricies, MultiplyMatrix4ProductByInverse)
{
    Matrix4 A{
            3, - 9, 7, 3,
            3, -8, 2, -9,
            -4, 4, 4, 1,
            -6, 5, -1, 1
    };

    Matrix4 B{
            8, 2, 2, 2,
            3, -1, 7, 0,
            7, 0, 5, 4,
            6, -2, 0, 5
    };

    Matrix4 C = A * B;

    EXPECT_EQ(C*B.Inversed(), A);
}

TEST(Matricies, MultiplyByTranslationMatrix)
{
    Matrix4 transform = Math::Translation(5, -3, 2);
    Point p{ -3, 4, 5 };
    Point target{2, 1, 7};

    EXPECT_EQ(transform * p, target);
}

TEST(Matricies, MultiplyByInverseOfTranslationMatrix)
{
    Matrix4 transform = Math::Translation(5, -3, 2);
    Matrix4 inv = transform.Inversed();
    Point p{ -3, 4, 5 };
    Point target{-8, 7, 3};

    EXPECT_EQ(inv * p, target);
}

TEST(Matricies, TranslationDoesNotAffectVectors)
{
    Matrix4 transform = Math::Translation(5, -3, 2);
    Vector v{ -3, 4, 5 };

    EXPECT_EQ(transform * v, v);
}

TEST(Matricies, ScalingMatrixAppliedToAPoint)
{
    Matrix4 transform = Math::Scaling(2, 3, 4);
    Point p{ -4, 6, 8 };
    Point target{-8, 18, 32};

    EXPECT_EQ(transform * p, target);
}

TEST(Matricies, ScalingMatrixAppliedToAVector)
{
    Matrix4 transform = Math::Scaling(2, 3, 4);
    Vector v{ -4, 6, 8 };
    Vector target{-8, 18, 32};

    EXPECT_EQ(transform * v, target);
}

TEST(Matricies, MultiplyingByInverseOfScalingMatrix)
{
    Matrix4 transform = Math::Scaling(2, 3, 4);
    Matrix4 inv = transform.Inversed();
    Vector v{ -4, 6, 8 };
    Vector target{-2, 2, 2};

    EXPECT_EQ(inv * v, target);
}

TEST(Matricies, ReflectionIsScalingByNegativeValue)
{
    Matrix4 transform = Math::Scaling(-1, 1, 1);
    Point p{ 2, 3, 4 };
    Point target{-2, 3, 4};

    EXPECT_EQ(transform * p, target);
}

TEST(Matricies, RotatingAPointAroundXAxis)
{
    Point p{ 0, 1, 0 };
    Matrix4 half_quater = Math::Rotation_X(M_PI / 4);
    Matrix4 full_quater = Math::Rotation_X(M_PI / 2);
    Point target1{0,static_cast<float>(std::sqrt(2)/2), static_cast<float>(std::sqrt(2)/2)};
    Point target2{0, 0, 1};

    EXPECT_TRUE(Math::Equal(half_quater * p, target1));
    EXPECT_TRUE(Math::Equal(full_quater * p, target2));
}

TEST(Matricies, InverseOfXRotation)
{
    Point p{ 0,1,0 };
    Matrix4 half_quater = Math::Rotation_X(M_PI / 4);
    Matrix4 inverse = half_quater.Inversed();
    Point target{0, static_cast<float>(std::sqrt(2)/2), static_cast<float>(-(std::sqrt(2)/2))};

    EXPECT_TRUE(Math::Equal(inverse * p, target));
}

TEST(Matricies, RotatingAPointAroundYAxis)
{
    Point p{ 0,0,1 };
    Matrix4 half_quater = Math::Rotation_Y(M_PI / 4);
    Matrix4 full_quater = Math::Rotation_Y(M_PI / 2);
    Point target1{static_cast<float>(std::sqrt(2) / 2), 0, static_cast<float>(std::sqrt(2) / 2)};
    Point target2{1, 0, 0};

    EXPECT_TRUE(Math::Equal(half_quater * p, target1));
    EXPECT_TRUE(Math::Equal(full_quater * p, target2));
}

TEST(Matricies, RotatingAPointAroundZAxis)
{
    Point p{ 0,1,0 };
    Matrix4 half_quater = Math::Rotation_Z(M_PI / 4);
    Matrix4 full_quater = Math::Rotation_Z(M_PI / 2);
    Point target1{static_cast<float>(-std::sqrt(2) / 2), static_cast<float>(std::sqrt(2) / 2), 0};
    Point target2{-1, 0, 0};

    EXPECT_TRUE(Math::Equal(half_quater * p, target1));
    EXPECT_TRUE(Math::Equal(full_quater * p, target2));
}

TEST(Matricies, ShearingXToY)
{
    Matrix4 transform = Math::Shearing(1, 0, 0, 0, 0, 0);
    Point p{ 2, 3, 4 };
    Point target{5, 3, 4};

    EXPECT_TRUE(Math::Equal(transform *p, target));
}

TEST(Matricies, ShearingXToZ)
{
    Matrix4 transform = Math::Shearing(0, 1, 0, 0, 0, 0);
    Point p{ 2, 3, 4 };
    Point target{6, 3, 4};
    EXPECT_TRUE(Math::Equal(transform *p, target));
}

TEST(Matricies, ShearingYToX)
{
    Matrix4 transform = Math::Shearing(0, 0, 1, 0, 0, 0);
    Point p{ 2, 3, 4 };
    Point target{2, 5, 4};
    EXPECT_TRUE(Math::Equal(transform *p, target));
}

TEST(Matricies, ShearingYToZ)
{
    Matrix4 transform = Math::Shearing(0, 0, 0, 1, 0, 0);
    Point p{ 2, 3, 4 };
    Point target{2, 7, 4};
    EXPECT_TRUE(Math::Equal(transform *p, target));
}

TEST(Matricies, ShearingZToX)
{
    Matrix4 transform = Math::Shearing(0, 0, 0, 0, 1, 0);
    Point p{ 2, 3, 4 };
    Point target{2, 3, 6};
    EXPECT_TRUE(Math::Equal(transform *p, target));
}

TEST(Matricies, ShearingZToY)
{
    Matrix4 transform = Math::Shearing(0, 0, 0, 0, 0, 1);
    Point p{ 2, 3, 4 };
    Point target{2, 3, 7};
    EXPECT_TRUE(Math::Equal(transform *p, target));
}

TEST(Matricies, IndividualTransformations)
{
    Point p{ 1, 0, 1 };
    Matrix4 A = Math::Rotation_X(M_PI / 2);
    Matrix4 B = Math::Scaling(5, 5, 5);
    Matrix4 C = Math::Translation(10, 5, 7);

    Tuple p2 = A * p;
    Tuple p3 = B * p2;
    Tuple p4 = C * p3;

    Point target2{1, -1, 0};
    Point target3{5, -5, 0};
    Point target4{15, 0, 7};

    EXPECT_TRUE(Math::Equal(p2, target2));
    EXPECT_TRUE(Math::Equal(p3, target3));
    EXPECT_TRUE(Math::Equal(p4, target4));
}

TEST(Matricies, ChainedTransformations)
{
    Point p{ 1, 0, 1 };
    Matrix4 A = Math::Rotation_X(M_PI / 2);
    Matrix4 B = Math::Scaling(5, 5, 5);
    Matrix4 C = Math::Translation(10, 5, 7);

    Matrix4 T = C * B * A;

    Point target{15, 0, 7};

    EXPECT_TRUE(Math::Equal(T * p, target));
}

TEST(Matricies, TransformationMatrixForDefaultorientation)
{
    Point from{0, 0, 0};
    Point to{0, 0, -1};
    Vector up{0, 1, 0};

    Matrix4 t = Math::ViewTransform(from, to, up);

    EXPECT_EQ(t, Math::identiy_matrix);
}

TEST(Matricies, TransformationMatrixLookingInPositiveDirection)
{
    Point from{0, 0, 0};
    Point to{0, 0, 1};
    Vector up{0, 1, 0};

    Matrix4 t = Math::ViewTransform(from, to, up);

    EXPECT_EQ(t, Math::Scaling(-1, 1, -1));
}

TEST(Matricies, TransfomationMovesTheWorld)
{
    Point from{0, 0, 8};
    Point to{0, 0, 0};
    Vector up{0, 1, 0};

    Matrix4 t = Math::ViewTransform(from, to, up);

    EXPECT_EQ(t, Math::Translation(0, 0, -8));
}

TEST(Matricies, ArbitraryViewTransformation)
{
    Point from{1, 3, 2};
    Point to{4, -2, 8};
    Vector up{1, 1, 0};

    Matrix4 t = Math::ViewTransform(from, to, up);

    Matrix4 target {
        -0.50709, 0.50709, 0.67612, -2.36643,
        0.76772, 0.60609, 0.12122, -2.82843,
        -0.35857, 0.59761, -0.71714, 0.00000,
        0.00000, 0.00000, 0.00000, 1.00000
    };

    EXPECT_EQ(t, target);
}