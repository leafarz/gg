#ifndef		GG_MATRIX4F_H
#define		GG_MATRIX4F_H
#pragma once

#include <iomanip>
#include "math/Vec4f.h"

namespace gg { namespace math { struct Vec3f; struct Quaternion; } }

namespace gg { namespace math {
	struct Mat4f
	{
	public:
		union
		{
			float elements[16];
			Vec4f columns[4];
		};

		/* The identity matrix. */
		static const Mat4f identity;

		/* Creates 4x4 matrix with all indices as 0. */
		Mat4f(void);

		/* Creates 4x4 matrix with all indices as c. */
		Mat4f(float c);

		/* Creates 4x4 matrix with defined values. */
		Mat4f(
			float c00, float c01, float c02, float c03,
			float c10, float c11, float c12, float c13,
			float c20, float c21, float c22, float c23,
			float c30, float c31, float c32, float c33
		);

		/* Gets the translation matrix from the given vector. */
		static Mat4f translationMatrix(const Vec3f& translation);
		/* Gets the translation matrix from the given values. */
		static Mat4f translationMatrix(float x, float y, float z);

		/* Gets the rotation matrix (in degrees) from the given vector. */
		static Mat4f rotationMatrixd(const Vec3f& eulerAngles);
		/* Gets the rotation matrix (in radians) from the given vector. */
		static Mat4f rotationMatrixr(const Vec3f& eulerAngles);
		/* Gets the rotation matrix from the given values. */
		static Mat4f rotationMatrix(float x, float y, float z);
		/* Gets the rotation matrix from the vectors. */
		static Mat4f rotationMatrix(const Vec3f& forward, const Vec3f& up);
		/* Gets the rotation matrix from the vectors. */
		static Mat4f rotationMatrix(const Vec3f& forward, const Vec3f& up, const Vec3f& right);
		/* Gets the rotation matrix from quaternion. */
		static Mat4f rotationMatrix(const Quaternion& rot);

		/* Gets the projection matrix from the given parameters. */
		static Mat4f perspectiveMatrix(float fovDeg, float aspectRatio, float zNear, float zFar);

		/* Gets the orthographic matrix from the given parameters. */
		static Mat4f orthographicMatrix(float left, float right, float bottom, float top, float near, float far);

		/* Gets the rotation matrix from the given float. */
		static Mat4f scaleMatrix(float c);
		/* Gets the rotation matrix from the given vector. */
		static Mat4f scaleMatrix(const Vec3f& scale);
		/* Gets the rotation matrix from the given values. */
		static Mat4f scaleMatrix(float x, float y, float z);

		float& operator[] (int idx);

		friend Mat4f operator+(const Mat4f& A, const Mat4f& B);
		Mat4f operator-(void);
		friend Mat4f operator-(const Mat4f& A, const Mat4f& B);
		friend Mat4f operator*(const Mat4f& A, float c);
		friend Mat4f operator*(float c, const Mat4f& A);
		friend Mat4f operator*(const Mat4f& A, const Mat4f& B);
		friend Vec4f operator*(const Mat4f& A, const Vec4f& B);
		friend Mat4f operator/(const Mat4f& A, float c);

		Mat4f& operator+=(const Mat4f& A);
		Mat4f& operator+=(float c);	
		Mat4f& operator-=(const Mat4f& A);
		Mat4f& operator-=(float c);
		Mat4f& operator*=(const Mat4f& A);
		Mat4f& operator*=(float c);
		Mat4f& operator/=(float c);

		friend std::ostream& operator<<(std::ostream& out, const Mat4f& A);

		/* Gets the float array of the matrix. */
		const float* getMatrix(void) const;

		/* Gets the value of a specific cell from the matrix. */
		float get(int idx) const;
		/* Gets the value of a specific cell from the matrix. */
		float get(int m, int n) const;

		/* Sets the value of a specific cell from the matrix
			* and returns the result matrix.
			*/
		Mat4f& set(int idx, float c);
		/* Sets the value of a specific cell from the matrix
			* and returns the result matrix.
			*/
		Mat4f& set(int m, int n, float c);
		/* Sets the value of a each individual element of the matrix */
		Mat4f& set(
			float c00, float c01, float c02, float c03,
			float c10, float c11, float c12, float c13,
			float c20, float c21, float c22, float c23,
			float c30, float c31, float c32, float c33
		);

		/* Sets the diagonal of this matrix with c. */
		Mat4f& setDiagonal(float c);

		/* Gets the transpose of the current matrix. */
		Mat4f getTranspose(void);
		/* Does transpose operation to the current matrix. */
		Mat4f& transpose(void);
		/* Static function for getting transpose of the matrix M. */
		static Mat4f getTranspose(const Mat4f& M);

		Vec3f getTransform(Vec3f A);
	};// struct Mat4f
}/*namespace math*/ }// namespace gg
#endif