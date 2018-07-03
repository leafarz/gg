#ifndef		GG_MATRIX3F_H
#define		GG_MATRIX3F_H
#pragma once

#include <iomanip>
#include "math/Vec3f.h"

namespace gg { namespace math {
	struct Mat3f
	{
	public:
		union
		{
			float elements[9];
			Vec3f columns[3];
		};

		/* The identity matrix. */
		static const Mat3f identity;

		/* Creates 4x4 matrix with all indices as 0. */
		Mat3f(void);

		/* Creates 4x4 matrix with all indices as c. */
		Mat3f(float c);

		/* Creates 4x4 matrix with defined values. */
		Mat3f(
			float c00, float c01, float c02,
			float c10, float c11, float c12,
			float c20, float c21, float c22
		);

		float& operator[] (int idx);

		friend Mat3f operator+(const Mat3f& A, const Mat3f& B);
		Mat3f operator-(void);
		friend Mat3f operator-(const Mat3f& A, const Mat3f& B);
		friend Mat3f operator*(const Mat3f& A, float c);
		friend Mat3f operator*(float c, const Mat3f& A);
		friend Mat3f operator*(const Mat3f& A, const Mat3f& B);
		friend Vec3f operator*(const Mat3f& A, const Vec3f& B);
		friend Mat3f operator/(const Mat3f& A, float c);

		Mat3f& operator+=(const Mat3f& A);
		Mat3f& operator+=(float c);	
		Mat3f& operator-=(const Mat3f& A);
		Mat3f& operator-=(float c);
		Mat3f& operator*=(const Mat3f& A);
		Mat3f& operator*=(float c);
		Mat3f& operator/=(float c);

		friend std::ostream& operator<<(std::ostream& out, const Mat3f& A);

		/* Gets the float array of the matrix. */
		inline const float* getMatrix(void) const { return this->elements; }

		/* Gets the value of a specific cell from the matrix. */
		inline float get(int idx) { return this->elements[idx]; }
		/* Gets the value of a specific cell from the matrix. */
		inline float get(int m, int n) const { return this->elements[m * 3 + n]; }

		/* Sets the value of a specific cell from the matrix
		 * and returns the result matrix.
		 */
		Mat3f& set(int idx, float c);
		/* Sets the value of a specific cell from the matrix
		 * and returns the result matrix.
		 */
		Mat3f& set(int m, int n, float c);

		Mat3f& setDiagonal(float c);

		/* Gets the transpose of the current matrix. */
		Mat3f getTranspose(void);
		/* Does transpose operation to the current matrix. */
		Mat3f& transpose(void);
		/* Static function for getting transpose of the matrix M. */
		static Mat3f getTranspose(const Mat3f& M);
	};// struct Mat3f
}/*namespace math*/ }// namespace gg
#endif