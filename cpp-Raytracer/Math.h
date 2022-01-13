#pragma once
#include <cmath>

# define M_PI           3.14159265358979323846  /* pi */

	struct Tuple
	{
		float x, y, z, w;

		Tuple() = default;
		Tuple(float x, float y, float z);
		Tuple(float x, float y, float z, float w);

		bool operator==(const Tuple& other) const;
		Tuple operator+(const Tuple& other) const;
		Tuple operator-(const Tuple& other) const;
		Tuple operator-() const;
		Tuple operator*(const float& other) const;

		float magnitude() const;

	};

	struct Point : public Tuple
	{
		Point();
		Point(float x, float y, float z);
        explicit Point(Tuple t);
	};

	struct Vector : public Tuple
	{
		Vector();
		Vector(float x, float y, float z);
        explicit Vector(Tuple t);

		Vector normalized() const;

        Vector Reflect(Vector normal) const;
	};

	class Matrix2
	{
	private:
		float n[2][2];
	public:
		Matrix2() = default;

		Matrix2(float n00, float n01,
			float n10, float n11);

		float Determinant();

		float& operator()(int i, int j) { return n[j][i]; }
		const float& operator()(int i, int j) const { return n[j][i]; }

		bool operator==(const Matrix2& other) const;
		bool operator!=(const Matrix2& other) const;

	};

	class Matrix3
	{
	private:
		float n[3][3];
	public:

		Matrix3() = default;

		Matrix3(float n00, float n01, float n02,
			float n10, float n11, float n12,
			float n20, float n21, float n22);

		float& operator()(int i, int j) { return (n[j][i]); }
		const float& operator()(int i, int j) const { return (n[j][i]); }

		bool operator==(const Matrix3& other) const;
		bool operator!=(const Matrix3& other) const;

		float Determinant();
		float Minor(const int row ,const int column);
		float Cofactor(const int row, const int column);


	};

	class Matrix4
	{
	private:
		float n[4][4];
	public:

		Matrix4() = default;

		Matrix4(float n00, float n01, float n02, float n03,
			float n10, float n11, float n12, float n13,
			float n20, float n21, float n22, float n23,
			float n30, float n31, float n32, float n33);

		float& operator()(int i, int j) { return (n[j][i]); }
		const float& operator()(int i, int j) const { return (n[j][i]); }

		bool operator==(const Matrix4& other) const;
		bool operator!=(const Matrix4& other) const;

		Matrix4 operator*(const Matrix4& A) const;
		Tuple operator*(const Tuple& b) const;

		Matrix4 Transposed();
		Matrix4 Inversed();

		float Determinant();
		float Minor(const int row, const int column);
		float Cofactor(const int row, const int column);

		bool IsInvertible();

		//Debug method to print the matrix to the console
		void Print();

	};

	namespace Math {
		bool Equal(const float a, const float b);
		bool Equal(const Tuple a, const Tuple b);

		float Dot(const Vector& a, const Vector& b);
		Vector Cross(const Vector& a, const Vector& b);

		//Returns the identity Matrix
		Matrix4 Identity4();

		//Creates a submatrix that is one smaller than the input Matrix, the specified row and column are removed
		Matrix2 Submatrix(const Matrix3& input, const int row, const int column);
		Matrix3 Submatrix(const Matrix4& input, const int row, const int column);

		//Translates a Point in space, does not affect Vectors
		Matrix4 Translation(const float x, const float y, const float z);

		//Scales a Point or Vector in Space
		Matrix4 Scaling(const float x, const float y, const float z);

		//Rotates a Point around the given Axis
		Matrix4 Rotation_X(const float r);
		Matrix4 Rotation_Y(const float r);
		Matrix4 Rotation_Z(const float r);

		//Shearing
		//(1, 0, 0, 0, 0, 0) X in proportion to Y
		//(0, 1, 0, 0, 0, 0) X in proportion to Z
		//(0, 0, 1, 0, 0, 0) Y in porportion to X
		//(0, 0, 0, 1, 0, 0) Y in proportion to Z
		//(0, 0, 0, 0, 1, 0) Z in proportion to X
		//(0, 0, 0, 0, 0, 1) Z in proportion to Y

		Matrix4 Shearing(const int x_y, const int x_z, const int y_x, const int y_z, const int z_x, const int z_y);

		extern Matrix4 identiy_matrix;
	}