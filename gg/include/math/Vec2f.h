#ifndef		GG_VEC2F_H
#define		GG_VEC2F_H
#pragma once

#include <iomanip>

namespace gg
{
	namespace Math
	{
		struct Vec3f;
		struct Vec4f;
		struct Vec2f
		{
		public:
			/* The x of the vector. */
			float x;
			/* The y of the vector. */
			float y;

			/* The global up vector. */
			static const Vec2f up;
			/* The global right vector. */
			static const Vec2f right;
			/* Vector with 0 values. */
			static const Vec2f zero;
			/* Vector with 1 values. */
			static const Vec2f one;

			/* Creates vector with default x,y=0 unless defined. */
			Vec2f(float x = 0, float y = 0);
			/* Creates vector from x,y values of Vec3f. */
			Vec2f(const Vec3f& A);
			/* Creates vector from x,y values of Vec4f. */
			Vec2f(const Vec4f& A);

			friend Vec2f operator+(const Vec2f& A, const Vec2f& B);
			Vec2f operator-(void) const;
			friend Vec2f operator-(const Vec2f& A, const Vec2f& B);
			friend Vec2f operator*(const Vec2f& A, float c);
			friend Vec2f operator*(float c, const Vec2f& A);
			friend Vec2f operator/(const Vec2f& A, float c);

			/* Adds Vec2f to this vector. */
			Vec2f& operator+=(const Vec2f& A);
			/* Adds c to x,y values of this vector. */
			Vec2f& operator+=(float c);
			/* Subtracts Vec2f to this vector. */
			Vec2f& operator-=(const Vec2f& A);
			/* Subtracts c to x,y values of this vector. */
			Vec2f& operator-=(float c);
			/* Multiplies c to x,y values of this vector. */
			Vec2f& operator*=(float c);
			/* Divides c to x,y values of this vector. */
			Vec2f& operator/=(float c);

			friend bool operator==(const Vec2f& A, const Vec2f& B);
			friend bool operator!=(const Vec2f& A, const Vec2f& B);

			friend std::ostream& operator<<(std::ostream& out, const Vec2f& A);

			/* Sets defined x,y values and returns the result vector. */
			Vec2f& set(float x, float y);

			/* Sets defined x,y values and returns the result vector. */
			Vec2f& set(const Vec2f& A);

			/* Sets x value only and returns the result vector. */
			Vec2f& setX(float x);

			/* Sets y value only and returns the result vector. */
			Vec2f& setY(float y);

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
			Vec2f normal(void) const;

			/* Normalize the current vector. */
			Vec2f& normalize(void);

			/* Returns the absolute value of the vector. */
			Vec2f abs(void) const;

			/* Computes the dot product of the current vector to the param. */
			float dot(const Vec2f& A) const;
			/* Computes the dot product of 2 vectors. */
			static float dot(const Vec2f& A, const Vec2f& B);

			/* Gets the lerped vector between 2 vectors. */
			static Vec2f lerp(const Vec2f& from, const Vec2f& to, float p);

			/* Gets the reflection vector from current vector and normal. */
			Vec2f reflect(const Vec2f& normal) const;
			/* Gets the reflection vector from defined vector and normal. */
			static Vec2f reflect(const Vec2f& A, const Vec2f& normal);

			/* Gets the rotated vector of current vector by degrees. */
			Vec2f rotated(float degrees) const;
			/* Gets the rotated vector by degrees. */
			static Vec2f rotated(const Vec2f& A, float degrees);

			/* Gets the rotated vector of current vector by radians. */
			Vec2f rotater(float rad) const;
			/* Gets the rotated vector by radians. */
			static Vec2f rotater(const Vec2f& A, float rad);

			/* Gets the angle between the current vector and the param. */
			float angle(const Vec2f& A) const;
			/* Gets the angle between the 2 vector vectors. */
			static float angle(const Vec2f& A, const Vec2f& B);

		private:
			static Vec2f up_;
			static Vec2f right_;
			static Vec2f zero_;
			static Vec2f one_;

		};// struct vec2f
	}// namespace Math
}// namespace gg
#endif