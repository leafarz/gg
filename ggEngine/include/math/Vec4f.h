#ifndef		GG_VEC4F_H
#define		GG_VEC4F_H
#pragma once
#include <iomanip>

namespace gg
{
	namespace Math
	{
		struct Vec4f
		{
		public:
			/* The x of the vector. */
			float x;
			/* The x of the vector. */
			float y;
			/* The z of the vector. */
			float z;
			/* The w of the vector. */
			float w;

			/* Creates vector with x,y,z,w as 0. */
			Vec4f(void);
			/* Creates vector with defined x,y,z,w. */
			Vec4f(float c);
			/* Creates vector with defined x,y,z,w values. */
			Vec4f(float x, float y, float z, float w);

			friend Vec4f operator+(const Vec4f& A, const Vec4f& B);
			Vec4f operator-(void) const;
			friend Vec4f operator-(const Vec4f& A, const Vec4f& B);
			friend Vec4f operator*(const Vec4f& A, float c);
			friend Vec4f operator*(float c, const Vec4f& A);
			friend Vec4f operator/(const Vec4f& A, float c);

			Vec4f& operator+=(const Vec4f& A);
			Vec4f& operator+=(float c);
			Vec4f& operator-=(const Vec4f& A);
			Vec4f& operator-=(float c);

			friend bool operator==(const Vec4f& A, const Vec4f& B);
			friend bool operator!=(const Vec4f& A, const Vec4f& B);

			friend std::ostream& operator<<(std::ostream& out, const Vec4f& A);

			/* Sets x,y,z,w values to c and returns the result vector. */
			Vec4f& set(float c);
			/* Sets defined x,y,z,w values and returns the result vector. */
			Vec4f& set(float x, float y, float z, float w);
			/* Sets defined x,y,z,w values and returns the result vector. */
			Vec4f& set(const Vec4f& A);

			/* Sets x value only and returns the result vector. */
			Vec4f& setX(float x);
			/* Sets y value only and returns the result vector. */
			Vec4f& setY(float y);
			/* Sets z value only and returns the result vector. */
			Vec4f& setZ(float z);
			/* Sets w value only and returns the result vector. */
			Vec4f& setW(float w);

			/* Returns the component with the highest value. */
			float max(void) const;

			/* Returns the component with the lowest value. */
			float min(void) const;

			/* Returns the length of the vector.
			* (Same as getMagnitude function)
			*/
			float length(void) const;
			/* Returns the square of length of the vector.
			* (Same as getSqrMagnitude function)
			*/
			float sqrLength(void) const;
			/* Returns the magnitude of the vector.
			* (Same as getLength function)
			*/
			float magnitude(void) const;
			/* Returns the square of magnitude of the vector.
			* (Same as getSqrLength function)
			*/
			float sqrMagnitude(void) const;

			/* Returns the normalized vector. */
			Vec4f normal(void) const;
			/* Normalize the current vector. */
			Vec4f& normalize(void);

			/* Returns the absolute value of the vector. */
			Vec4f abs(void);

			/* Computes the dot product of the current vector to the param. */
			float Vec4f::dot(const Vec4f& A) const;
			/* Computes the dot product of 2 vectors. */
			static float dot(const Vec4f& A, const Vec4f& B);

			/* Gets the lerped vector between 2 vectors. */
			static Vec4f lerp(const Vec4f& from, const Vec4f& to, float p);
		};// struct vec4f
	}// namespace Math
}// namespace gg
#endif