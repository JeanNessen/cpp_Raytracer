#pragma once
#include <cmath>
#include <iostream>

# define M_PI           3.14159265358979323846  /* pi */
# define EPSILON 0.00001

	struct tuple
	{
		double x, y, z, w;

		tuple() = default;
		tuple(double x, double y, double z);
		tuple(double x, double y, double z, double w);

		bool operator==(const tuple& other) const;
        bool operator!=(const tuple& other) const;
		tuple operator+(const tuple& other) const;
		tuple operator-(const tuple& other) const;

		tuple operator*(const double& other) const;
        tuple operator-(const double& other) const;

        tuple operator-();

		double magnitude() const;

        friend std::ostream& operator<<(std::ostream& os, const tuple& t);

	};

	struct point : public tuple
	{
		point();
		point(double x, double y, double z);
        explicit point(tuple t);
	};

	struct vector : public tuple
	{
		vector();
		vector(double x, double y, double z);
        explicit vector(tuple t);

		[[nodiscard]]vector normalized() const;

        vector Reflect(vector normal) const;
	};

	class Matrix2
	{
	private:
		double n[2][2];
	public:
		Matrix2() = default;

		Matrix2(double n00, double n01,
			double n10, double n11);

		double Determinant();

		double& operator()(int i, int j) { return n[j][i]; }
		const double& operator()(int i, int j) const { return n[j][i]; }

		bool operator==(const Matrix2& other) const;
		bool operator!=(const Matrix2& other) const;

	};

	class Matrix3
	{
	private:
		double n[3][3];
	public:

		Matrix3() = default;

		Matrix3(double n00, double n01, double n02,
			double n10, double n11, double n12,
			double n20, double n21, double n22);

		double& operator()(int i, int j) { return (n[j][i]); }
		const double& operator()(int i, int j) const { return (n[j][i]); }

		bool operator==(const Matrix3& other) const;
		bool operator!=(const Matrix3& other) const;

		double Determinant();
		double Minor(const int row ,const int column);
		double Cofactor(const int row, const int column);


	};

	class Matrix4
	{
	private:
		double n[4][4];
	public:

		Matrix4() = default;

		Matrix4(double n00, double n01, double n02, double n03,
			double n10, double n11, double n12, double n13,
			double n20, double n21, double n22, double n23,
			double n30, double n31, double n32, double n33);

		double& operator()(int i, int j) { return (n[j][i]); }
		const double& operator()(int i, int j) const { return (n[j][i]); }

		bool operator==(const Matrix4& other) const;
		bool operator!=(const Matrix4& other) const;

		Matrix4 operator*(const Matrix4& A) const;
		tuple operator*(const tuple& b) const;
		Matrix4 operator*(const double& b) const;

		friend std::ostream& operator<<(std::ostream& os, const Matrix4& c);

		Matrix4 Transposed();
		Matrix4 Inversed() const;

		double Determinant() const;
		double Minor(const int row, const int column) const;
		double Cofactor(const int row, const int column) const;

		bool IsInvertible();

		//Debug method to print the matrix to the console
		void Print();

	};

	namespace Math {
        double GetRandomDouble(double min, double max);

        bool Equal(const double a, const double b);
		bool Equal(const tuple a, const tuple b);

		double Dot(const vector& a, const vector& b);
		vector Cross(const vector& a, const vector& b);

		//Returns the identity Matrix
		Matrix4 Identity4();

		//Creates a submatrix that is one smaller than the input Matrix, the specified row and column are removed
		Matrix2 Submatrix(const Matrix3& input, const int row, const int column);
		Matrix3 Submatrix(const Matrix4& input, const int row, const int column);

		//Translates a point in space, does not affect Vectors
		Matrix4 Translation(const double x, const double y, const double z);

		//Scales a point or vector in Space
		Matrix4 Scaling(const double x, const double y, const double z);
        //Scales a point or vector uniformly in all dimensions
        Matrix4 Scaling(const double s);

		//Rotates a point around the given Axis
		Matrix4 Rotation_X(const double r);
		Matrix4 Rotation_Y(const double r);
		Matrix4 Rotation_Z(const double r);

		//Shearing
		//(1, 0, 0, 0, 0, 0) X in proportion to Y
		//(0, 1, 0, 0, 0, 0) X in proportion to Z
		//(0, 0, 1, 0, 0, 0) Y in porportion to X
		//(0, 0, 0, 1, 0, 0) Y in proportion to Z
		//(0, 0, 0, 0, 1, 0) Z in proportion to X
		//(0, 0, 0, 0, 0, 1) Z in proportion to Y

		Matrix4 Shearing(const int x_y, const int x_z, const int y_x, const int y_z, const int z_x, const int z_y);

        //From: Where should the eye be
        //To: Where should the eye be oriented towards
        //Up: What direction is up
        Matrix4 ViewTransform(point from, point to, vector up);

		extern Matrix4 identiy_matrix;
	}