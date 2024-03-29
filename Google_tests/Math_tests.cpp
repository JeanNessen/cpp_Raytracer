//
// Created by jeanl on 08/01/2022.
//

#include "gtest/gtest.h"
#include "../cpp-Raytracer/Math.h"
#include "../cpp-Raytracer/Math.cpp"

TEST(Tuples, CreatePoint)
{
    point p = point(4, -4, 3);
    tuple target = tuple(4, -4, 3, 1);

    EXPECT_EQ(p, target);
}

TEST(Tuples, CreateVector)
{
    vector v = vector(4, -4, 3);
    tuple target{ 4, -4, 3, 0 };
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
    tuple a{ 1, 2, 3, 4 };
    tuple b{ 1, 2, 3, 4.01 };
    tuple c{ 1, 2 ,3, 4.00001 };

    EXPECT_FALSE(Math::Equal(a, b));
    EXPECT_TRUE(Math::Equal(a, c));
}

TEST(Tuples, TupleAddition)
{
    tuple a1{ 3, -2, 5, 1 };
    tuple a2{ -2, 3, 1, 0 };
    tuple target{ 1, 1, 6, 1 };

    EXPECT_EQ(a1+a2, target);
}

TEST(Tuples, PointMinusPoint)
{
    point p1 = point(3, 2, 1);
    point p2 = point(5, 6, 7);
    vector target = vector(-2, -4, -6);

    EXPECT_EQ(p1-p2, target);
}

TEST(Tuples, PointMinusVector)
{
    point p = point(3, 2, 1);
    vector v = vector(5, 6, 7);
    point target = point(-2, -4, -6);

    EXPECT_EQ(p-v, target);
}

TEST(Tuples, VectorMinusVector)
{
    vector v1 = vector(3, 2, 1);
    vector v2 = vector(5, 6, 7);
    vector target = vector(-2, -4, -6);

    EXPECT_EQ(v1-v2, target);
}
TEST(Tuples, TupleNegation)
{
    tuple a{ 1, -2, 3, -4 };
    tuple target{ -1, 2, -3, 4 };

    EXPECT_EQ(-a, target);
}

TEST(Tuples, TupleScalarMultiplicaiton)
{
    tuple a{ 1, -2, 3, -4 };
    tuple target{ 3.5, -7, 10.5, -14 };

    EXPECT_EQ(a*3.5, target);
}

TEST(Tuples, TupleFractionMultiplication)
{
    tuple a{ 1, -2, 3, -4 };
    tuple target{ 0.5, -1, 1.5, -2 };

    EXPECT_EQ(a*0.5, target);
}

TEST(Tuples, VectorMagnitude01)
{
    vector v = vector(1, 0 , 0);

    EXPECT_TRUE(Math::Equal(v.magnitude(), 1));
}

TEST(Tuples, VectorMagnitude02)
{
    vector v = vector(0, 1 , 0);

    EXPECT_TRUE(Math::Equal(v.magnitude(), 1));
}
TEST(Tuples, VectorMagnitude03)
{
    vector v = vector(0, 0 , 1);

    EXPECT_TRUE(Math::Equal(v.magnitude(), 1));
}
TEST(Tuples, VectorMagnitude04)
{
    vector v = vector(1, 2 , 3);

    EXPECT_TRUE(Math::Equal(v.magnitude(), std::sqrt(14)));
}

TEST(Tuples, NormalizeVector01)
{
    vector v = vector(4, 0, 0);
    vector target = vector(1, 0, 0);

    EXPECT_TRUE(Math::Equal(v.normalized(), target));
}

TEST(Tuples, NormalizeVector02)
{
    vector v = vector(1, 2, 3);
    vector target = vector(1 / std::sqrt(14), 2 / std::sqrt(14), 3 / std::sqrt(14));

    EXPECT_TRUE(Math::Equal(v.normalized(), target));
}

TEST(Tuples, NormalizedVectorMagnitude)
{
    vector v = vector(1, 2, 3);
    vector norm = v.normalized();

    EXPECT_TRUE(Math::Equal(norm.magnitude(), 1));
}

TEST(Tuples, DotProductVectors)
{
    vector v1 = vector(1, 2, 3);
    vector v2 = vector(2, 3, 4);

    EXPECT_TRUE(Math::Equal(Math::Dot(v1, v2), 20));
}

TEST(Tuples, CrossProductVectors)
{
    vector v1 = vector(1, 2, 3);
    vector v2 = vector(2, 3, 4);
    vector target = vector(-1, 2, -1);

    EXPECT_TRUE(Math::Equal(Math::Cross(v1, v2), target));
}

TEST(Tuples, ReflectingVectorAt45)
{
    vector v{1, -1, 0};
    vector n{0, 1, 0};

    vector r = v.Reflect(n);

    EXPECT_TRUE(Math::Equal(r, vector(1, 1, 0)));
}

TEST(Tuples, ReflectingVectorOffSlant)
{
    vector v{0, -1, 0};
    vector n{static_cast<float>(std::sqrt(2)/2), static_cast<float>(std::sqrt(2)/2), 0};

    vector r = v.Reflect(n);

    EXPECT_TRUE(Math::Equal(r, vector(1, 0, 0)));
}

TEST(Matricies, ConstructionMatrix4)
{
    matrix4 M{	1,    2,    3,    4,
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
    matrix3 M{ -3,  5, 0,
               1, -2, -7,
               0,  1,  1};

    EXPECT_EQ(M(0,0), -3);
    EXPECT_EQ(M(1,1), -2);
    EXPECT_EQ(M(2,2), 1);
}

TEST(Matricies, ConstructionMatrix2)
{
    matrix2 M{ -3,  5,
               1, -2};

    EXPECT_EQ(M(0,0), -3);
    EXPECT_EQ(M(0,1), 5);
    EXPECT_EQ(M(1,0), 1);
    EXPECT_EQ(M(1,1), -2);
}

TEST(Matricies, Matrix2Comparison)
{
    matrix2 A{
            1, 2,
            3, 4
    };

    matrix2 B{
            1, 2,
            3, 4
    };

    matrix2 C{
            2, 1,
            4, 3
    };

    EXPECT_EQ(A, B);
    EXPECT_NE(A, C);
}

TEST(Matricies, Matrix3Comparison)
{
    matrix3 A{
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
    };

    matrix3 B{
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
    };

    matrix3 C{
            3, 2, 1,
            6, 5, 4,
            9, 8, 7
    };

    EXPECT_EQ(A, B);
    EXPECT_NE(A, C);
}

TEST(Matricies, Matrix4Comparison)
{
    matrix4 A{ 1, 2, 3, 4,
               5, 6, 7, 8,
               9, 8, 7, 6,
               5, 4, 3, 2 };

    matrix4 B{ 1, 2, 3, 4,
               5, 6, 7, 8,
               9, 8, 7, 6,
               5, 4, 3, 2 };

    matrix4 C{ 2, 3, 4, 5,
               6, 7, 8, 9,
               8, 7, 6, 5,
               4, 3, 2, 1 };

    EXPECT_EQ(A, B);
    EXPECT_NE(A, C);
}

TEST(Matricies, Matrix4Multiplication)
{
    matrix4 A{
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 8, 7, 6,
            5, 4, 3, 2
    };
    matrix4 B{
            -2, 1, 2, 3,
            3, 2, 1, -1,
            4, 3, 6, 5,
            1, 2, 7, 8
    };
    matrix4 Target{
            20, 22, 50, 48,
            44, 54, 114, 108,
            40, 58, 110, 102,
            16, 26, 46, 42
    };

    EXPECT_EQ(A*B, Target);
}

TEST(Matricies, Matrix4VectorMultiplication)
{
    matrix4 A{
            1, 2, 3, 4,
            2, 4, 4, 2,
            8, 6, 4, 1,
            0, 0, 0, 1
    };

    tuple b{ 1, 2, 3, 1 };

    tuple target{ 18, 24, 33, 1 };

    EXPECT_EQ(A*b, target);
}

TEST(Matricies, Matrix4ScalarMultiplication)
{
    matrix4 A{
        1, 1, 1, 1,
        2, 2, 2, 2,
        3, 3, 3, 3,
        4, 4, 4, 4
    };

    double b = 2;

    matrix4 target{
        2, 2, 2, 2,
        4, 4, 4, 4,
        6, 6, 6, 6,
        8, 8, 8, 8
    };

    EXPECT_EQ(A * b, target);
}

TEST(Matricies, Matrix4Identity)
{
    matrix4 A{
            1, 2, 3, 4,
            2, 4, 4, 2,
            8, 6, 4, 1,
            0, 0, 0, 1
    };

    EXPECT_EQ(A*Math::identiy_matrix, A);
}

TEST(Matricies, Matrix4Transpose)
{
    matrix4 M{
            0, 9, 3, 0,
            9, 8, 0, 8,
            1, 8, 5, 3,
            0, 0, 5, 8
    };

    matrix4 target{
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
    matrix2 A{
            1, 5,
            -3, 2
    };

    EXPECT_TRUE(Math::Equal(A.Determinant(), 17));
}

TEST(Matricies, Matrix3Submatrix)
{
    matrix3 A{
            1, 5, 0,
            -3, 2, 7,
            0, 6, -3
    };
    matrix2 target_submatrix{
            -3, 2,
            0, 6
    };

    EXPECT_EQ(Math::Submatrix(A, 0, 2), target_submatrix);
}

TEST(Matricies, Matrix4Submatrix)
{
    matrix4 A{
            -6, 1, 1, 6,
            -8, 5, 8, 6,
            -1, 0, 8, 2,
            -7, 1, -1, 1
    };

    matrix3 target_submatrix{
            -6, 1, 6,
            -8, 8, 6,
            -7, -1, 1
    };

    EXPECT_EQ(Math::Submatrix(A, 2, 1), target_submatrix);
}

TEST(Matricies, Matrix3Minor)
{
    matrix3 A{
            2, 5, 0,
            2, -1, -7,
            6, -1, 5
    };

    matrix2 B = Math::Submatrix(A, 1, 0);

    EXPECT_TRUE(Math::Equal(B.Determinant(), 25));
    EXPECT_TRUE(Math::Equal(A.Minor(1, 0), 25));
}

TEST(Matricies, Matrix3Cofactor)
{
    matrix3 A{
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
    matrix3 A{
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
    matrix4 A{
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
    matrix4 A{
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
    matrix4 A{
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
    matrix4 A{
            -5, 2, 6, -8,
            1, -5, 1, 8,
            7, 7, -6, -7,
            1, -3, 7, 4
    };
    matrix4 B = A.Inversed();

    matrix4 Target{
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
    matrix4 A{
            8, -5, 9, 2,
            7, 5, 6, 1,
            -6, 0, 9, 6,
            -3, 0, -9, -4
    };


    matrix4 target{
            -0.15385, -0.15385, -0.28205, -0.53846,
            -0.07692, 0.12308, 0.02564, 0.03077,
            0.35897, 0.35897, 0.43590, 0.92308,
            -0.69231, -0.69231, -0.76923, -1.92308
    };

    EXPECT_EQ(A.Inversed(), target);
}

TEST(Matricies, Matrix4Inversion03)
{
    matrix4 A{
            9, 3, 0, 9,
            -5, -2, -6, -3,
            -4, 9, 6, 4,
            -7, 6, 6, 2
    };

    matrix4 target{
            -0.04074, -0.07778, 0.14444, -0.22222,
            -0.07778, 0.03333, 0.36667, -0.33333,
            -0.02901, -0.14630, -0.10926, 0.12963,
            0.17778, 0.06667, -0.26667, 0.33333
    };

    EXPECT_EQ(A.Inversed(), target);
}

TEST(Matricies, MultiplyMatrix4ProductByInverse)
{
    matrix4 A{
            3, - 9, 7, 3,
            3, -8, 2, -9,
            -4, 4, 4, 1,
            -6, 5, -1, 1
    };

    matrix4 B{
            8, 2, 2, 2,
            3, -1, 7, 0,
            7, 0, 5, 4,
            6, -2, 0, 5
    };

    matrix4 C = A * B;

    EXPECT_EQ(C*B.Inversed(), A);
}

TEST(Matricies, MultiplyByTranslationMatrix)
{
    matrix4 transform = Math::Translation(5, -3, 2);
    point p{ -3, 4, 5 };
    point target{2, 1, 7};

    EXPECT_EQ(transform * p, target);
}

TEST(Matricies, MultiplyByInverseOfTranslationMatrix)
{
    matrix4 transform = Math::Translation(5, -3, 2);
    matrix4 inv = transform.Inversed();
    point p{ -3, 4, 5 };
    point target{-8, 7, 3};

    EXPECT_EQ(inv * p, target);
}

TEST(Matricies, TranslationDoesNotAffectVectors)
{
    matrix4 transform = Math::Translation(5, -3, 2);
    vector v{ -3, 4, 5 };

    EXPECT_EQ(transform * v, v);
}

TEST(Matricies, ScalingMatrixAppliedToAPoint)
{
    matrix4 transform = Math::Scaling(2, 3, 4);
    point p{ -4, 6, 8 };
    point target{-8, 18, 32};

    EXPECT_EQ(transform * p, target);
}

TEST(Matricies, ScalingMatrixAppliedToAVector)
{
    matrix4 transform = Math::Scaling(2, 3, 4);
    vector v{ -4, 6, 8 };
    vector target{-8, 18, 32};

    EXPECT_EQ(transform * v, target);
}

TEST(Matricies, MultiplyingByInverseOfScalingMatrix)
{
    matrix4 transform = Math::Scaling(2, 3, 4);
    matrix4 inv = transform.Inversed();
    vector v{ -4, 6, 8 };
    vector target{-2, 2, 2};

    EXPECT_EQ(inv * v, target);
}

TEST(Matricies, ReflectionIsScalingByNegativeValue)
{
    matrix4 transform = Math::Scaling(-1, 1, 1);
    point p{ 2, 3, 4 };
    point target{-2, 3, 4};

    EXPECT_EQ(transform * p, target);
}

TEST(Matricies, RotatingAPointAroundXAxis)
{
    point p{ 0, 1, 0 };
    matrix4 half_quater = Math::Rotation_X(M_PI / 4);
    matrix4 full_quater = Math::Rotation_X(M_PI / 2);
    point target1{0,static_cast<float>(std::sqrt(2)/2), static_cast<float>(std::sqrt(2)/2)};
    point target2{0, 0, 1};

    EXPECT_TRUE(Math::Equal(half_quater * p, target1));
    EXPECT_TRUE(Math::Equal(full_quater * p, target2));
}

TEST(Matricies, InverseOfXRotation)
{
    point p{ 0,1,0 };
    matrix4 half_quater = Math::Rotation_X(M_PI / 4);
    matrix4 inverse = half_quater.Inversed();
    point target{0, static_cast<float>(std::sqrt(2)/2), static_cast<float>(-(std::sqrt(2)/2))};

    EXPECT_TRUE(Math::Equal(inverse * p, target));
}

TEST(Matricies, RotatingAPointAroundYAxis)
{
    point p{ 0,0,1 };
    matrix4 half_quater = Math::Rotation_Y(M_PI / 4);
    matrix4 full_quater = Math::Rotation_Y(M_PI / 2);
    point target1{static_cast<float>(std::sqrt(2) / 2), 0, static_cast<float>(std::sqrt(2) / 2)};
    point target2{1, 0, 0};

    EXPECT_TRUE(Math::Equal(half_quater * p, target1));
    EXPECT_TRUE(Math::Equal(full_quater * p, target2));
}

TEST(Matricies, RotatingAPointAroundZAxis)
{
    point p{ 0,1,0 };
    matrix4 half_quater = Math::Rotation_Z(M_PI / 4);
    matrix4 full_quater = Math::Rotation_Z(M_PI / 2);
    point target1{static_cast<float>(-std::sqrt(2) / 2), static_cast<float>(std::sqrt(2) / 2), 0};
    point target2{-1, 0, 0};

    EXPECT_TRUE(Math::Equal(half_quater * p, target1));
    EXPECT_TRUE(Math::Equal(full_quater * p, target2));
}

TEST(Matricies, ShearingXToY)
{
    matrix4 transform = Math::Shearing(1, 0, 0, 0, 0, 0);
    point p{ 2, 3, 4 };
    point target{5, 3, 4};

    EXPECT_TRUE(Math::Equal(transform *p, target));
}

TEST(Matricies, ShearingXToZ)
{
    matrix4 transform = Math::Shearing(0, 1, 0, 0, 0, 0);
    point p{ 2, 3, 4 };
    point target{6, 3, 4};
    EXPECT_TRUE(Math::Equal(transform *p, target));
}

TEST(Matricies, ShearingYToX)
{
    matrix4 transform = Math::Shearing(0, 0, 1, 0, 0, 0);
    point p{ 2, 3, 4 };
    point target{2, 5, 4};
    EXPECT_TRUE(Math::Equal(transform *p, target));
}

TEST(Matricies, ShearingYToZ)
{
    matrix4 transform = Math::Shearing(0, 0, 0, 1, 0, 0);
    point p{ 2, 3, 4 };
    point target{2, 7, 4};
    EXPECT_TRUE(Math::Equal(transform *p, target));
}

TEST(Matricies, ShearingZToX)
{
    matrix4 transform = Math::Shearing(0, 0, 0, 0, 1, 0);
    point p{ 2, 3, 4 };
    point target{2, 3, 6};
    EXPECT_TRUE(Math::Equal(transform *p, target));
}

TEST(Matricies, ShearingZToY)
{
    matrix4 transform = Math::Shearing(0, 0, 0, 0, 0, 1);
    point p{ 2, 3, 4 };
    point target{2, 3, 7};
    EXPECT_TRUE(Math::Equal(transform *p, target));
}

TEST(Matricies, IndividualTransformations)
{
    point p{ 1, 0, 1 };
    matrix4 A = Math::Rotation_X(M_PI / 2);
    matrix4 B = Math::Scaling(5, 5, 5);
    matrix4 C = Math::Translation(10, 5, 7);

    tuple p2 = A * p;
    tuple p3 = B * p2;
    tuple p4 = C * p3;

    point target2{1, -1, 0};
    point target3{5, -5, 0};
    point target4{15, 0, 7};

    EXPECT_TRUE(Math::Equal(p2, target2));
    EXPECT_TRUE(Math::Equal(p3, target3));
    EXPECT_TRUE(Math::Equal(p4, target4));
}

TEST(Matricies, ChainedTransformations)
{
    point p{ 1, 0, 1 };
    matrix4 A = Math::Rotation_X(M_PI / 2);
    matrix4 B = Math::Scaling(5, 5, 5);
    matrix4 C = Math::Translation(10, 5, 7);

    matrix4 T = C * B * A;

    point target{15, 0, 7};

    EXPECT_TRUE(Math::Equal(T * p, target));
}

TEST(Matricies, TransformationMatrixForDefaultorientation)
{
    point from{0, 0, 0};
    point to{0, 0, -1};
    vector up{0, 1, 0};

    matrix4 t = Math::ViewTransform(from, to, up);

    EXPECT_EQ(t, Math::identiy_matrix);
}

TEST(Matricies, TransformationMatrixLookingInPositiveDirection)
{
    point from{0, 0, 0};
    point to{0, 0, 1};
    vector up{0, 1, 0};

    matrix4 t = Math::ViewTransform(from, to, up);

    EXPECT_EQ(t, Math::Scaling(-1, 1, -1));
}

TEST(Matricies, TransfomationMovesTheWorld)
{
    point from{0, 0, 8};
    point to{0, 0, 0};
    vector up{0, 1, 0};

    matrix4 t = Math::ViewTransform(from, to, up);

    EXPECT_EQ(t, Math::Translation(0, 0, -8));
}

TEST(Matricies, ArbitraryViewTransformation)
{
    point from{1, 3, 2};
    point to{4, -2, 8};
    vector up{1, 1, 0};

    matrix4 t = Math::ViewTransform(from, to, up);

    matrix4 target {
        -0.50709, 0.50709, 0.67612, -2.36643,
        0.76772, 0.60609, 0.12122, -2.82843,
        -0.35857, 0.59761, -0.71714, 0.00000,
        0.00000, 0.00000, 0.00000, 1.00000
    };

    EXPECT_EQ(t, target);
}