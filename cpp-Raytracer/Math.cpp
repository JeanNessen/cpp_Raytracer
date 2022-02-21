#include "Math.h"
#include <cmath>
#include <iostream>

Matrix4 Math::identiy_matrix = Matrix4{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
};

bool Math::Equal(const float a, const float b)
{
	float epsilon = 0.0001;

	if (std::abs(a - b) < epsilon)
	{
		return true;
	}
	return false;
}

bool Math::Equal(const Tuple a, const Tuple b)
{
	return Equal(a.x, b.x) && Equal(a.y, b.y) && Equal(a.z, b.z) && Equal(a.w, b.w);
}

float Math::Dot(const Vector & a, const Vector & b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

Vector Math::Cross(const Vector & a, const Vector & b)
{
	Vector crossProduct = Vector(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
	return crossProduct;
}

Matrix4 Math::Identity4()
{
	return Matrix4{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
}

Matrix2 Math::Submatrix(const Matrix3& input, const int row, const int column)
{
	Matrix2 submatrix;
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

Matrix3 Math::Submatrix(const Matrix4& input, const int row, const int column)
{
	Matrix3 submatrix;
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

Matrix4 Math::Translation(const float x, const float y, const float z)
{
	Matrix4 transform{
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};
	return transform;
}

Matrix4 Math::Scaling(const float x, const float y, const float z)
{
	Matrix4 transform{
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	};
	return transform;
}

Matrix4 Math::Rotation_X(const float r)
{
	Matrix4 rotation{
		1, 0, 0, 0,
		0, std::cos(r), -std::sin(r), 0,
		0, std::sin(r), std::cos(r), 0,
		0, 0, 0, 1
	};
	return rotation;
}

Matrix4 Math::Rotation_Y(const float r)
{
	Matrix4 rotation{
		std::cos(r), 0, std::sin(r), 0,
		0, 1, 0, 0,
		-std::sin(r), 0, std::cos(r), 0,
		0, 0, 0, 1
	};
	return rotation;
}

Matrix4 Math::Rotation_Z(const float r)
{
	Matrix4 rotation{
		std::cos(r), -std::sin(r), 0, 0,
		std::sin(r), std::cos(r), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	return rotation;
}

Matrix4 Math::Shearing(const int x_y, const int x_z, const int y_x, const int y_z, const int z_x, const int z_y)
{
	Matrix4 transform{
		1, float(x_y), float(x_z), 0,
		float(y_x), 1, float(y_z), 0,
		float(z_x), float(z_y), 1, 0,
		0, 0, 0, 1
	};
	return transform;
}

Matrix4 Math::ViewTransform(Point from, Point to, Vector up) {
    Vector forward = Vector(to-from).normalized();
    Vector left = Math::Cross(forward, up.normalized());
    Vector true_up = Math::Cross(left, forward);

    Matrix4 orientation{
        left.x, left.y, left.z, 0,
        true_up.x, true_up.y, true_up.z, 0,
        -forward.x, -forward.y, -forward.z, 0,
        0, 0, 0, 1
    };

    return orientation * Math::Translation(-from.x, -from.y, -from.z);
}

Tuple::Tuple(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;

}

Tuple::Tuple(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

bool Tuple::operator==(const Tuple& other) const
{
    //return (Math::Equal(x, other.x) && Math::Equal(y, other.y), Math::Equal(z, other.z));
	return (x == other.x && y == other.y && z == other.z && w == other.w);
}

Tuple Tuple::operator+(const Tuple& other) const
{
	Tuple sum{ x + other.x, y + other.y, z + other.z, w + other.w };
	return sum;
}

Tuple Tuple::operator-(const Tuple& other) const
{
	Tuple diff{ x - other.x, y - other.y, z - other.z, w - other.w };
	return diff;
}

Tuple Tuple::operator*(const float& other) const
{
	Tuple product{ x * other, y * other, z * other, w * other };
	return product;
}

float Tuple::magnitude() const
{
	return std::sqrt(std::pow(x, 2)+std::pow(y, 2) + std::pow(z, 2) + std::pow(w, 2));
}

Tuple Tuple::operator-() {
    Tuple negative{-x, -y, -z, -w};
    return negative;
}

std::ostream &operator<<(std::ostream &os, const Tuple &t) {
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

Matrix4::Matrix4(
	float n00, float n01, float n02, float n03, 
	float n10, float n11, float n12, float n13, 
	float n20, float n21, float n22, float n23, 
	float n30, float n31, float n32, float n33)
{
	//This Matrix representation uses column-major storage
	n[0][0] = n00; n[0][1] = n10; n[0][2] = n20; n[0][3] = n30;
	n[1][0] = n01; n[1][1] = n11; n[1][2] = n21; n[1][3] = n31;
	n[2][0] = n02; n[2][1] = n12; n[2][2] = n22; n[2][3] = n32;
	n[3][0] = n03; n[3][1] = n13; n[3][2] = n23; n[3][3] = n33;
}

bool Matrix4::operator==(const Matrix4& other) const
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

bool Matrix4::operator!=(const Matrix4& other) const
{
	return !(*this==other);
}

Matrix4 Matrix4::operator*(const Matrix4& other) const
{
	Matrix4 output{
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

Tuple Matrix4::operator*(const Tuple& b) const
{
	Tuple product;
	product.x = (*this)(0, 0) * b.x + (*this)(0, 1) * b.y + (*this)(0, 2) * b.z + (*this)(0, 3) * b.w;
	product.y = (*this)(1, 0) * b.x + (*this)(1, 1) * b.y + (*this)(1, 2) * b.z + (*this)(1, 3) * b.w;
	product.z = (*this)(2, 0) * b.x + (*this)(2, 1) * b.y + (*this)(2, 2) * b.z + (*this)(2, 3) * b.w;
	product.w = (*this)(3, 0) * b.x + (*this)(3, 1) * b.y + (*this)(3, 2) * b.z + (*this)(3, 3) * b.w;
	return product;
}

Matrix4 Matrix4::Transposed()
{
	Matrix4 T{
		(*this)(0,0), (*this)(1,0), (*this)(2,0), (*this)(3,0),
		(*this)(0,1), (*this)(1,1), (*this)(2,1), (*this)(3,1),
		(*this)(0,2), (*this)(1,2), (*this)(2,2), (*this)(3,2),
		(*this)(0,3), (*this)(1,3), (*this)(2,3), (*this)(3,3)
	};
	return T;
}

Matrix4 Matrix4::Inversed()
{
	Matrix4 output;
	float det = Determinant();
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			float c = Cofactor(row, col);
			output(col, row) = c / det;
		}
	}
	return output;
}

float Matrix4::Determinant()
{
	float det =
		(*this)(0, 0) * this->Cofactor(0, 0) +
		(*this)(0, 1) * this->Cofactor(0, 1) +
		(*this)(0, 2) * this->Cofactor(0, 2) +
		(*this)(0, 3) * this->Cofactor(0, 3);
	return det;
}

float Matrix4::Minor(const int row, const int column)
{
	Matrix3 submatrix = Math::Submatrix((*this), row, column);
	float sub_det = submatrix.Determinant();
	return sub_det;
}

float Matrix4::Cofactor(const int row, const int column)
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

bool Matrix4::IsInvertible()
{
	if (this->Determinant() == 0)
	{
		return false;
	}
	else {
		return true;
	}

}

void Matrix4::Print()
{
	std::cout << "|" << (*this)(0, 0) << "|" << (*this)(0, 1) << "|" << (*this)(0, 2) << "|" << (*this)(0, 3) << "|\n";
	std::cout << "|" << (*this)(1, 0) << "|" << (*this)(1, 1) << "|" << (*this)(1, 2) << "|" << (*this)(1, 3) << "|\n";
	std::cout << "|" << (*this)(2, 0) << "|" << (*this)(2, 1) << "|" << (*this)(2, 2) << "|" << (*this)(2, 3) << "|\n";
	std::cout << "|" << (*this)(3, 0) << "|" << (*this)(3, 1) << "|" << (*this)(3, 2) << "|" << (*this)(3, 3) << "|\n";
}



Matrix2::Matrix2(
	float n00, float n01, 
	float n10, float n11)
{
	n[0][0] = n00; n[0][1] = n10;
	n[1][0] = n01; n[1][1] = n11;
}

float Matrix2::Determinant()
{
	float determinant = n[0][0] * n[1][1] - n[0][1] * n[1][0];
	return determinant;
}

bool Matrix2::operator==(const Matrix2& other) const
{
	if (!Math::Equal((*this)(0, 0), other(0, 0))) return false;
	if (!Math::Equal((*this)(0, 1), other(0, 1))) return false;

	if (!Math::Equal((*this)(1, 0), other(1, 0))) return false;
	if (!Math::Equal((*this)(1, 1), other(1, 1))) return false;

	return true;
}

bool Matrix2::operator!=(const Matrix2& other) const
{
	return !(*this == other);
}

Matrix3::Matrix3(
	float n00, float n01, float n02, 
	float n10, float n11, float n12, 
	float n20, float n21, float n22)
{
	n[0][0] = n00; n[0][1] = n10; n[0][2] = n20;
	n[1][0] = n01; n[1][1] = n11; n[1][2] = n21;
	n[2][0] = n02; n[2][1] = n12; n[2][2] = n22;
}

bool Matrix3::operator==(const Matrix3& other) const
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

bool Matrix3::operator!=(const Matrix3& other) const
{
	return !(*this == other);
}

float Matrix3::Determinant()
{
	float det = 
		(*this)(0, 0) * this->Cofactor(0, 0) + 
		(*this)(0, 1) * this->Cofactor(0, 1) + 
		(*this)(0, 2) * this->Cofactor(0, 2);
	return det;
}

float Matrix3::Minor(const int row, const int column)
{
	Matrix2 submatrix = Math::Submatrix((*this), row, column);
	float sub_det = submatrix.Determinant();
	return sub_det;
}

float Matrix3::Cofactor(const int row, const int column)
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

Point::Point()
{
	x = 0;
	y = 0;
	z = 0;
	w = 1;
}

Point::Point(float x, float y, float z):
	Tuple(x, y, z)
{
	w = 1;
}

Point::Point(Tuple t) {
    x = t.x;
    y = t.y;
    z = t.z;
    w = 1;
}

Vector::Vector()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector::Vector(float x, float y, float z):
	Tuple(x, y, z)
{
	w = 0;
}

Vector::Vector(Tuple t)
{
    x = t.x;
    y = t.y;
    z = t.z;
    w = 0;
}

Vector Vector::normalized() const
{
	Vector norm;
	norm.x = x / magnitude();
	norm.y = y / magnitude();
	norm.z = z / magnitude();
	norm.w = w / magnitude();
	return norm;
}

Vector Vector::Reflect(Vector normal) const {
    Vector in = *this;
    return Vector{in - normal * 2 * Math::Dot(in, normal)};
}
