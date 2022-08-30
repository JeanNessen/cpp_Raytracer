#include "Math.h"
#include <cmath>
#include <iostream>
#include <random>
#include <thread>

matrix4 Math::identiy_matrix = matrix4{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
};

bool Math::Equal(const double a, const double b)
{
	double epsilon = 0.0001;

	if (std::abs(a - b) < epsilon)
	{
		return true;
	}
	return false;
}

bool Math::Equal(const tuple a, const tuple b)
{
	return Equal(a.x, b.x) && Equal(a.y, b.y) && Equal(a.z, b.z) && Equal(a.w, b.w);
}

double Math::Dot(const vector & a, const vector & b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

vector Math::Cross(const vector & a, const vector & b)
{
	vector crossProduct = vector(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
	return crossProduct;
}

matrix4 Math::Identity4()
{
	return matrix4{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
}

matrix2 Math::Submatrix(const matrix3& input, const int row, const int column)
{
	matrix2 submatrix;
	int sub_x = 0;
	int sub_y = 0;
	for (int x = 0; x < 3; x++)
	{
		if (x == row)
		{
			continue;
		}
		sub_y = 0;
		for (int y = 0; y < 3; y++)
		{
			if (y == column)
			{
				continue;
			}
			submatrix(sub_x, sub_y) = input(x, y);
			sub_y++;
		}
		sub_x++;
	}
	return submatrix;
}

matrix3 Math::Submatrix(const matrix4& input, const int row, const int column)
{
	matrix3 submatrix;
	int sub_x = 0;
	int sub_y = 0;
	for (int x = 0; x < 4; x++)
	{
		if (x == row)
		{
			continue;
		}
		sub_y = 0;
		for (int y = 0; y < 4; y++)
		{
			if (y == column)
			{
				continue;
			}
			submatrix(sub_x, sub_y) = input(x, y);
			sub_y++;
		}
		sub_x++;
	}
	return submatrix;
}

matrix4 Math::Translation(const double x, const double y, const double z)
{
	matrix4 transform{
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};
	return transform;
}

matrix4 Math::Scaling(const double x, const double y, const double z)
{
	matrix4 transform{
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	};
	return transform;
}

matrix4 Math::Rotation_X(const double r)
{
	matrix4 rotation{
		1, 0, 0, 0,
		0, std::cos(r), -std::sin(r), 0,
		0, std::sin(r), std::cos(r), 0,
		0, 0, 0, 1
	};
	return rotation;
}

matrix4 Math::Rotation_Y(const double r)
{
	matrix4 rotation{
		std::cos(r), 0, std::sin(r), 0,
		0, 1, 0, 0,
		-std::sin(r), 0, std::cos(r), 0,
		0, 0, 0, 1
	};
	return rotation;
}

matrix4 Math::Rotation_Z(const double r)
{
	matrix4 rotation{
		std::cos(r), -std::sin(r), 0, 0,
		std::sin(r), std::cos(r), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	return rotation;
}

matrix4 Math::Shearing(const int x_y, const int x_z, const int y_x, const int y_z, const int z_x, const int z_y)
{
	matrix4 transform{
		1, double(x_y), double(x_z), 0,
		double(y_x), 1, double(y_z), 0,
		double(z_x), double(z_y), 1, 0,
		0, 0, 0, 1
	};
	return transform;
}

matrix4 Math::ViewTransform(point from, point to, vector up) {
    vector forward = vector(to-from).normalized();
    vector left = Math::Cross(forward, up.normalized());
    vector true_up = Math::Cross(left, forward);

    matrix4 orientation{
        left.x, left.y, left.z, 0,
        true_up.x, true_up.y, true_up.z, 0,
        -forward.x, -forward.y, -forward.z, 0,
        0, 0, 0, 1
    };

    return orientation * Math::Translation(-from.x, -from.y, -from.z);
}

matrix4 Math::Scaling(const double s) {
    return Scaling(s, s, s);
}

double Math::GetRandomDouble(double min, double max) {
    //Faster random number generator is used, as distribution is not important here.
    //https://cboard.cprogramming.com/c-programming/3264-best-way-generate-random-double.html
    //return ( ( double )rand() * ( max - min ) ) / ( double )RAND_MAX + min;

	//Using the thread id to seed the random generator to make sure each thread produces numbers indipendend from the others.
	auto seed = std::hash<std::thread::id>()(std::this_thread::get_id());

	static thread_local std::mt19937 generator(seed);
	std::uniform_real_distribution<double> distribution(min, max);
	return distribution(generator);
}

tuple::tuple(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;

}

tuple::tuple(double x, double y, double z, double w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

bool tuple::operator==(const tuple& other) const
{
    //return (Math::Equal(x, other.x) && Math::Equal(y, other.y), Math::Equal(z, other.z));
	return (x == other.x && y == other.y && z == other.z && w == other.w);
}

tuple tuple::operator+(const tuple& other) const
{
	tuple sum{ x + other.x, y + other.y, z + other.z, w + other.w };
	return sum;
}

tuple tuple::operator-(const tuple& other) const
{
	tuple diff{ x - other.x, y - other.y, z - other.z, w - other.w };
	return diff;
}

tuple tuple::operator*(const double& other) const
{
	tuple product{ x * other, y * other, z * other, w * other };
	return product;
}

double tuple::magnitude() const
{
	return std::sqrt(std::pow(x, 2)+std::pow(y, 2) + std::pow(z, 2) + std::pow(w, 2));
}

tuple tuple::operator-() {
    tuple negative{-x, -y, -z, -w};
    return negative;
}

std::ostream &operator<<(std::ostream &os, const tuple &t) {
    if(t.w == 0)
    {
        os << "v(" << t.x << ", " << t.y << ", " << t.z << ")";
    }
    else
    {
        os << "p(" << t.x << ", " << t.y << ", " << t.z << ")";
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const matrix4& c)
{
	os << "|" << c(0, 0) << ", " << c(0, 1) << ", " << c(0, 2) << ", " << c(0, 3) << "|\n" <<
		"|" << c(1, 0) << ", " << c(1, 1) << ", " << c(1, 2) << ", " << c(1, 3) << "|\n" <<
		"|" << c(2, 0) << ", " << c(2, 1) << ", " << c(2, 2) << ", " << c(2, 3) << "|\n" <<
		"|" << c(3, 0) << ", " << c(3, 1) << ", " << c(3, 2) << ", " << c(3, 3) << "|\n";

	return os;
}

bool tuple::operator!=(const tuple &other) const {
    return !(*this == other);
}

tuple tuple::operator-(const double &other) const {
    return {x-other, y-other, z-other, w};
}

matrix4::matrix4(
	double n00, double n01, double n02, double n03,
	double n10, double n11, double n12, double n13,
	double n20, double n21, double n22, double n23,
	double n30, double n31, double n32, double n33)
{
	//This Matrix representation uses column-major storage
	n[0][0] = n00; n[0][1] = n10; n[0][2] = n20; n[0][3] = n30;
	n[1][0] = n01; n[1][1] = n11; n[1][2] = n21; n[1][3] = n31;
	n[2][0] = n02; n[2][1] = n12; n[2][2] = n22; n[2][3] = n32;
	n[3][0] = n03; n[3][1] = n13; n[3][2] = n23; n[3][3] = n33;
}

bool matrix4::operator==(const matrix4& other) const
{
	if (!Math::Equal((*this)(0, 0), other(0, 0))) return false;
	if (!Math::Equal((*this)(1, 0), other(1, 0))) return false;
	if (!Math::Equal((*this)(2, 0), other(2, 0))) return false;
	if (!Math::Equal((*this)(3, 0), other(3, 0))) return false;
	
	if (!Math::Equal((*this)(0, 1), other(0, 1))) return false;
	if (!Math::Equal((*this)(1, 1), other(1, 1))) return false;
	if (!Math::Equal((*this)(2, 1), other(2, 1))) return false;
	if (!Math::Equal((*this)(3, 1), other(3, 1))) return false;

	if (!Math::Equal((*this)(0, 2), other(0, 2))) return false;
	if (!Math::Equal((*this)(1, 2), other(1, 2))) return false;
	if (!Math::Equal((*this)(2, 2), other(2, 2))) return false;
	if (!Math::Equal((*this)(3, 2), other(3, 2))) return false;

	if (!Math::Equal((*this)(0, 3), other(0, 3))) return false;
	if (!Math::Equal((*this)(1, 3), other(1, 3))) return false;
	if (!Math::Equal((*this)(2, 3), other(2, 3))) return false;
	if (!Math::Equal((*this)(3, 3), other(3, 3))) return false;

	return true;
}

bool matrix4::operator!=(const matrix4& other) const
{
	return !(*this==other);
}

matrix4 matrix4::operator*(const matrix4& other) const
{
	matrix4 output{
		(*this)(0,0) * other(0,0) + (*this)(0,1) * other(1,0) + (*this)(0,2) * other(2,0) + (*this)(0,3) * other(3,0),
		(*this)(0,0) * other(0,1) + (*this)(0,1) * other(1,1) + (*this)(0,2) * other(2,1) + (*this)(0,3) * other(3,1),
		(*this)(0,0) * other(0,2) + (*this)(0,1) * other(1,2) + (*this)(0,2) * other(2,2) + (*this)(0,3) * other(3,2),
		(*this)(0,0) * other(0,3) + (*this)(0,1) * other(1,3) + (*this)(0,2) * other(2,3) + (*this)(0,3) * other(3,3),

		(*this)(1,0) * other(0,0) + (*this)(1,1) * other(1,0) + (*this)(1,2) * other(2,0) + (*this)(1,3) * other(3,0),
		(*this)(1,0) * other(0,1) + (*this)(1,1) * other(1,1) + (*this)(1,2) * other(2,1) + (*this)(1,3) * other(3,1),
		(*this)(1,0) * other(0,2) + (*this)(1,1) * other(1,2) + (*this)(1,2) * other(2,2) + (*this)(1,3) * other(3,2),
		(*this)(1,0) * other(0,3) + (*this)(1,1) * other(1,3) + (*this)(1,2) * other(2,3) + (*this)(1,3) * other(3,3),

		(*this)(2,0) * other(0,0) + (*this)(2,1) * other(1,0) + (*this)(2,2) * other(2,0) + (*this)(2,3) * other(3,0),
		(*this)(2,0) * other(0,1) + (*this)(2,1) * other(1,1) + (*this)(2,2) * other(2,1) + (*this)(2,3) * other(3,1),
		(*this)(2,0) * other(0,2) + (*this)(2,1) * other(1,2) + (*this)(2,2) * other(2,2) + (*this)(2,3) * other(3,2),
		(*this)(2,0) * other(0,3) + (*this)(2,1) * other(1,3) + (*this)(2,2) * other(2,3) + (*this)(2,3) * other(3,3),

		(*this)(3,0) * other(0,0) + (*this)(3,1) * other(1,0) + (*this)(3,2) * other(2,0) + (*this)(3,3) * other(3,0),
		(*this)(3,0) * other(0,1) + (*this)(3,1) * other(1,1) + (*this)(3,2) * other(2,1) + (*this)(3,3) * other(3,1),
		(*this)(3,0) * other(0,2) + (*this)(3,1) * other(1,2) + (*this)(3,2) * other(2,2) + (*this)(3,3) * other(3,2),
		(*this)(3,0) * other(0,3) + (*this)(3,1) * other(1,3) + (*this)(3,2) * other(2,3) + (*this)(3,3) * other(3,3)
	};
	return output;
}

tuple matrix4::operator*(const tuple& b) const
{
	tuple product;
	product.x = (*this)(0, 0) * b.x + (*this)(0, 1) * b.y + (*this)(0, 2) * b.z + (*this)(0, 3) * b.w;
	product.y = (*this)(1, 0) * b.x + (*this)(1, 1) * b.y + (*this)(1, 2) * b.z + (*this)(1, 3) * b.w;
	product.z = (*this)(2, 0) * b.x + (*this)(2, 1) * b.y + (*this)(2, 2) * b.z + (*this)(2, 3) * b.w;
	product.w = (*this)(3, 0) * b.x + (*this)(3, 1) * b.y + (*this)(3, 2) * b.z + (*this)(3, 3) * b.w;
	return product;
}

matrix4 matrix4::operator*(const double& b) const
{
	matrix4 output{
		(*this)(0,0)* b, (*this)(0,1)* b, (*this)(0,2)* b, (*this)(0,3)* b,
		(*this)(1,0)* b, (*this)(1,1)* b, (*this)(1,2)* b, (*this)(1,3)* b,
		(*this)(2,0)* b, (*this)(2,1)* b, (*this)(2,2)* b, (*this)(2,3)* b,
		(*this)(3,0)* b, (*this)(3,1)* b, (*this)(3,2)* b, (*this)(3,3)* b,
	};
	return output;
	
}

matrix4 matrix4::Transposed()
{
	matrix4 T{
		(*this)(0,0), (*this)(1,0), (*this)(2,0), (*this)(3,0),
		(*this)(0,1), (*this)(1,1), (*this)(2,1), (*this)(3,1),
		(*this)(0,2), (*this)(1,2), (*this)(2,2), (*this)(3,2),
		(*this)(0,3), (*this)(1,3), (*this)(2,3), (*this)(3,3)
	};
	return T;
}

matrix4 matrix4::Inversed() const {
	//http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html

	double out_00 = n[1][1] * n[2][2] * n[3][3] + n[2][1] * n[3][2] * n[1][3] + n[3][1] * n[1][2] * n[2][3] -
                    n[1][1] * n[3][2] * n[2][3] - n[2][1] * n[1][2] * n[3][3] - n[3][1] * n[2][2] * n[1][3];

    double out_01 = n[1][0] * n[3][2] * n[2][3] + n[2][0] * n[1][2] * n[3][3] + n[3][0] * n[2][2] * n[1][3] -
                    n[1][0] * n[2][2] * n[3][3] - n[2][0] * n[3][2] * n[1][3] - n[3][0] * n[1][2] * n[2][3];

	double out_02 = n[1][0] * n[2][1] * n[3][3] + n[2][0] * n[3][1] * n[1][3] + n[3][0] * n[1][1] * n[2][3] -
                    n[1][0] * n[3][1] * n[2][3] - n[2][0] * n[1][1] * n[3][3] - n[3][0] * n[2][1] * n[1][3];

	double out_03 = n[1][0] * n[3][1] * n[2][2] + n[2][0] * n[1][1] * n[3][2] + n[3][0] * n[2][1] * n[1][2] -
                    n[1][0] * n[2][1] * n[3][2] - n[2][0] * n[3][1] * n[1][2] - n[3][0] * n[1][1] * n[2][2];


	double out_10 = n[0][1] * n[3][2] * n[2][3] + n[2][1] * n[0][2] * n[3][3] + n[3][1] * n[2][2] * n[0][3] -
                    n[0][1] * n[2][2] * n[3][3] - n[2][1] * n[3][2] * n[0][3] - n[3][1] * n[0][2] * n[2][3];

	double out_11 = n[0][0] * n[2][2] * n[3][3] + n[2][0] * n[3][2] * n[0][3] + n[3][0] * n[0][2] * n[2][3] -
                    n[0][0] * n[3][2] * n[2][3] - n[2][0] * n[0][2] * n[3][3] - n[3][0] * n[2][2] * n[0][3];

	double out_12 = n[0][0] * n[3][1] * n[2][3] + n[2][0] * n[0][1] * n[3][3] + n[3][0] * n[2][1] * n[0][3] -
                    n[0][0] * n[2][1] * n[3][3] - n[2][0] * n[3][1] * n[0][3] - n[3][0] * n[0][1] * n[2][3];

	double out_13 = n[0][0] * n[2][1] * n[3][2] + n[2][0] * n[3][1] * n[0][2] + n[3][0] * n[0][1] * n[2][2] -
                    n[0][0] * n[3][1] * n[2][2] - n[2][0] * n[0][1] * n[3][2] - n[3][0] * n[2][1] * n[0][2];


	double out_20 = n[0][1] * n[1][2] * n[3][3] + n[1][1] * n[3][2] * n[0][3] + n[3][1] * n[0][2] * n[1][3] -
                    n[0][1] * n[3][2] * n[1][3] - n[1][1] * n[0][2] * n[3][3] - n[3][1] * n[1][2] * n[0][3];

	double out_21 = n[0][0] * n[3][2] * n[1][3] + n[1][0] * n[0][2] * n[3][3] + n[3][0] * n[1][2] * n[0][3] -
					n[0][0] * n[1][2] * n[3][3] - n[1][0] * n[3][2] * n[0][3] - n[3][0] * n[0][2] * n[1][3];

	double out_22 = n[0][0] * n[1][1] * n[3][3] + n[1][0] * n[3][1] * n[0][3] + n[3][0] * n[0][1] * n[1][3] -
					n[0][0] * n[3][1] * n[1][3] - n[1][0] * n[0][1] * n[3][3] - n[3][0] * n[1][1] * n[0][3];

	double out_23 = n[0][0] * n[3][1] * n[1][2] + n[1][0] * n[0][1] * n[3][2] + n[3][0] * n[1][1] * n[0][2] -
					n[0][0] * n[1][1] * n[3][2] - n[1][0] * n[3][1] * n[0][2] - n[3][0] * n[0][1] * n[1][2];


	double out_30 = n[0][1] * n[2][2] * n[1][3] + n[1][1] * n[0][2] * n[2][3] + n[2][1] * n[1][2] * n[0][3] -
					n[0][1] * n[1][2] * n[2][3] - n[1][1] * n[2][2] * n[0][3] - n[2][1] * n[0][2] * n[1][3];

	double out_31 = n[0][0] * n[1][2] * n[2][3] + n[1][0] * n[2][2] * n[0][3] + n[2][0] * n[0][2] * n[1][3] -
					n[0][0] * n[2][2] * n[1][3] - n[1][0] * n[0][2] * n[2][3] - n[2][0] * n[1][2] * n[0][3];

	double out_32 = n[0][0] * n[2][1] * n[1][3] + n[1][0] * n[0][1] * n[2][3] + n[2][0] * n[1][1] * n[0][3] -
					n[0][0] * n[1][1] * n[2][3] - n[1][0] * n[2][1] * n[0][3] - n[2][0] * n[0][1] * n[1][3];

	double out_33 = n[0][0] * n[1][1] * n[2][2] + n[1][0] * n[2][1] * n[0][2] + n[2][0] * n[0][1] * n[1][2] -
					n[0][0] * n[2][1] * n[1][2] - n[1][0] * n[0][1] * n[2][2] - n[2][0] * n[1][1] * n[0][2];

	matrix4 A{
		out_00, out_01, out_02, out_03,
		out_10, out_11, out_12, out_13,
		out_20, out_21, out_22, out_23,
		out_30, out_31, out_32, out_33
	};
	matrix4 output = A * (1 / Determinant());


//	matrix4 output{};
//	double det = Determinant();
//	for (int row = 0; row < 4; row++)
//	{
//		for (int col = 0; col < 4; col++)
//		{
//			double c = Cofactor(row, col);
//			output(col, row) = c / det;
//		}
//	}
	return output;
}

double matrix4::Determinant() const {
//determinant calculation from http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html
    double determinant =    n[0][0] * n[1][1] * n[2][2] * n[3][3] + n[0][0] * n[2][1] * n[3][2] * n[1][3] + n[0][0] * n[3][1] * n[1][2] * n[2][3] +

                            n[1][0] * n[0][1] * n[3][2] * n[2][3] + n[1][0] * n[2][1] * n[0][2] * n[3][3] + n[1][0] * n[3][1] * n[2][2] * n[0][3] +

                            n[2][0] * n[0][1] * n[1][2] * n[3][3] + n[2][0] * n[1][1] * n[3][2] * n[0][3] + n[2][0] * n[3][1] * n[0][2] * n[1][3] +

                            n[3][0] * n[0][1] * n[2][2] * n[1][3] + n[3][0] * n[1][1] * n[0][2] * n[2][3] + n[3][0] * n[2][1] * n[1][2] * n[0][3] -

                            n[0][0] * n[1][1] * n[3][2] * n[2][3] - n[0][0] * n[2][1] * n[1][2] * n[3][3] - n[0][0] * n[3][1] * n[2][2] * n[1][3] -

                            n[1][0] * n[0][1] * n[2][2] * n[3][3] - n[1][0] * n[2][1] * n[3][2] * n[0][3] - n[1][0] * n[3][1] * n[0][2] * n[2][3] -

                            n[2][0] * n[0][1] * n[3][2] * n[1][3] - n[2][0] * n[1][1] * n[0][2] * n[3][3] - n[2][0] * n[3][1] * n[1][2] * n[0][3] -

                            n[3][0] * n[0][1] * n[1][2] * n[2][3] - n[3][0] * n[1][1] * n[2][2] * n[0][3] - n[3][0] * n[2][1] * n[0][2] * n[1][3];



////
//    double first = (*this)(0, 0) * this->Cofactor(0, 0);
//    double second = (*this)(0, 1) * this->Cofactor(0, 1);
//    double third = (*this)(0, 2) * this->Cofactor(0, 2);
//    double fourth = (*this)(0, 3) * this->Cofactor(0, 3);
//
//    double determinant = first + second + third + fourth;
	return determinant;
}

double matrix4::Minor(const int row, const int column) const
{
	matrix3 submatrix = Math::Submatrix((*this), row, column);
	double sub_det = submatrix.Determinant();
	return sub_det;
}

double matrix4::Cofactor(const int row, const int column) const {
	if ((row + column) % 2 == 0)
	{
		return this->Minor(row, column);
	}
	else
	{
		return -(this->Minor(row, column));
	}
}

bool matrix4::IsInvertible()
{
	if (this->Determinant() == 0)
	{
		return false;
	}
	else {
		return true;
	}

}

void matrix4::Print()
{
	std::cout << "|" << (*this)(0, 0) << "|" << (*this)(0, 1) << "|" << (*this)(0, 2) << "|" << (*this)(0, 3) << "|\n";
	std::cout << "|" << (*this)(1, 0) << "|" << (*this)(1, 1) << "|" << (*this)(1, 2) << "|" << (*this)(1, 3) << "|\n";
	std::cout << "|" << (*this)(2, 0) << "|" << (*this)(2, 1) << "|" << (*this)(2, 2) << "|" << (*this)(2, 3) << "|\n";
	std::cout << "|" << (*this)(3, 0) << "|" << (*this)(3, 1) << "|" << (*this)(3, 2) << "|" << (*this)(3, 3) << "|\n";
}



matrix2::matrix2(
	double n00, double n01,
	double n10, double n11)
{
	n[0][0] = n00; n[0][1] = n10;
	n[1][0] = n01; n[1][1] = n11;
}

double matrix2::Determinant()
{
	double determinant = n[0][0] * n[1][1] - n[0][1] * n[1][0];
	return determinant;
}

bool matrix2::operator==(const matrix2& other) const
{
	if (!Math::Equal((*this)(0, 0), other(0, 0))) return false;
	if (!Math::Equal((*this)(0, 1), other(0, 1))) return false;

	if (!Math::Equal((*this)(1, 0), other(1, 0))) return false;
	if (!Math::Equal((*this)(1, 1), other(1, 1))) return false;

	return true;
}

bool matrix2::operator!=(const matrix2& other) const
{
	return !(*this == other);
}

matrix3::matrix3(
	double n00, double n01, double n02,
	double n10, double n11, double n12,
	double n20, double n21, double n22)
{
	n[0][0] = n00; n[0][1] = n10; n[0][2] = n20;
	n[1][0] = n01; n[1][1] = n11; n[1][2] = n21;
	n[2][0] = n02; n[2][1] = n12; n[2][2] = n22;
}

bool matrix3::operator==(const matrix3& other) const
{
	if (!Math::Equal((*this)(0, 0), other(0, 0))) return false;
	if (!Math::Equal((*this)(0, 1), other(0, 1))) return false;
	if (!Math::Equal((*this)(0, 2), other(0, 2))) return false;

	if (!Math::Equal((*this)(1, 0), other(1, 0))) return false;
	if (!Math::Equal((*this)(1, 1), other(1, 1))) return false;
	if (!Math::Equal((*this)(1, 2), other(1, 2))) return false;

	if (!Math::Equal((*this)(2, 0), other(2, 0))) return false;
	if (!Math::Equal((*this)(2, 1), other(2, 1))) return false;
	if (!Math::Equal((*this)(2, 2), other(2, 2))) return false;

	return true;
}

bool matrix3::operator!=(const matrix3& other) const
{
	return !(*this == other);
}

double matrix3::Determinant()
{
	double det =
		(*this)(0, 0) * this->Cofactor(0, 0) + 
		(*this)(0, 1) * this->Cofactor(0, 1) + 
		(*this)(0, 2) * this->Cofactor(0, 2);
	return det;
}

double matrix3::Minor(const int row, const int column)
{
	matrix2 submatrix = Math::Submatrix((*this), row, column);
	double sub_det = submatrix.Determinant();
	return sub_det;
}

double matrix3::Cofactor(const int row, const int column)
{
	if ((row + column) % 2 == 0)
	{
		return this->Minor(row, column);
	}
	else
	{
		return -(this->Minor(row, column));
	}
}

point::point()
{
	x = 0;
	y = 0;
	z = 0;
	w = 1;
}

point::point(double x, double y, double z):
	tuple(x, y, z)
{
	w = 1;
}

point::point(tuple t) {
    x = t.x;
    y = t.y;
    z = t.z;
    w = 1;
}

vector::vector()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

vector::vector(double x, double y, double z):
	tuple(x, y, z)
{
	w = 0;
}

vector::vector(tuple t)
{
    x = t.x;
    y = t.y;
    z = t.z;
    w = 0;
}

vector vector::normalized() const
{
	vector norm;
	norm.x = x / magnitude();
	norm.y = y / magnitude();
	norm.z = z / magnitude();
	norm.w = w / magnitude();
	return norm;
}

vector vector::Reflect(vector normal) const {
    vector in = *this;
    return vector{in - normal * 2 * Math::Dot(in, normal)};
}
