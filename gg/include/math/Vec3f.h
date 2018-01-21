#ifndef		GG_VEC3F_H
#define		GG_VEC3F_H
#pragma once

#include <iomanip>

#include "Quaternion.h"
#include "Vec2f.h"
#include "Vec4f.h"

namespace gg
{
	namespace Math
	{
		struct Vec3f
		{
		public:
			/* The x of the vector. */
			float x;
			/* The y of the vector. */
			float y;
			/* The z of the vector. */
			float z;

			/* The global up vector. */
			static const Vec3f up;
			/* The global down vector. */
			static const Vec3f down;
			/* The global right vector. */
			static const Vec3f right;
			/* The global left vector. */
			static const Vec3f left;
			/* The global forward vector. */
			static const Vec3f forward;
			/* The global back vector. */
			static const Vec3f back;
			/* Vector with 0 values. */
			static const Vec3f zero;
			/* Vector with 1 values. */
			static const Vec3f one;

			/* Creates vector with default x,y,z=0 unless defined. */
			Vec3f(float x = 0, float y = 0, float z = 0);
			/* Creates vector from x,y values of Vec2f and z value 0 as default unless defined.*/
			Vec3f(const Vec2f& A, float z = 0);
			/* Creates vector from x,y,z values of Vec4f. */
			Vec3f(const Vec4f& A);
			/* Creates vector from quaternion. */
			Vec3f(const Quaternion& Q);

			friend Vec3f operator+(const Vec3f& A, const Vec3f& B);
			Vec3f operator-(void) const;
			friend Vec3f operator-(const Vec3f& A, const Vec3f& B);
			friend Vec3f operator*(const Vec3f& A, float c);
			friend Vec3f operator*(float c, const Vec3f& A);
			friend Vec3f operator/(const Vec3f& A, float c);

			/* Adds Vec3f to this vector. */
			Vec3f& operator+=(const Vec3f& A);
			/* Adds c to x,y,z values of this vector. */
			Vec3f& operator+=(float c);
			/* Subtracts Vec3f to this vector. */
			Vec3f& operator-=(const Vec3f& A);
			/* Subtracts c to x,y,z values of this vector. */
			Vec3f& operator-=(float c);
			/* Multiplies c to x,y,z values of this vector. */
			Vec3f& operator*=(float c);
			/* Divides c to x,y,z values of this vector. */
			Vec3f& operator/=(float c);

			friend bool operator==(const Vec3f& A, const Vec3f& B);
			friend bool operator!=(const Vec3f& A, const Vec3f& B);

			friend std::ostream& operator<<(std::ostream& out, const Vec3f& A);

			/* Gets the x,y values in Vec2f form. */
			Vec2f xy(void) const;
			/* Gets the x,z values in Vec2f form. */
			Vec2f xz(void) const;

			/* Gets the y,x values in Vec2f form. */
			Vec2f yx(void) const;
			/* Gets the y,z values in Vec2f form. */
			Vec2f yz(void) const;

			/* Gets the z,x values in Vec2f form. */
			Vec2f zx(void) const;
			/* Gets the z,y values in Vec2f form. */
			Vec2f zy(void) const;

			/* Sets defined x,y,z values and returns the result vector. */
			Vec3f& set(float x, float y, float z);
			/* Sets defined x,y,z values and returns the result vector. */
			Vec3f& set(const Vec3f& A);
			/* Sets defined x,y,z values and returns the result vector. */
			Vec3f& set(const Vec4f& A);

			/* Sets x value only and returns the result vector. */
			Vec3f& setX(float x);
			/* Sets y value only and returns the result vector. */
			Vec3f& setY(float y);
			/* Sets z value only and returns the result vector. */
			Vec3f& setZ(float z);

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
			*  (Same as getLength function)
			*/
			float magnitude(void) const;
			/* Returns the square of magnitude of the vector.
			*  (Same as getSqrLength function)
			*/
			float sqrMagnitude(void) const;

			/* Returns the normalized vector. */
			Vec3f normal(void) const;
			/* Normalize the current vector. */
			Vec3f& normalize(void);

			/* Returns the absolute value of the vector. */
			Vec3f abs(void) const;

			/* Computes the dot product of the current vector to the param. */
			float dot(const Vec3f& A) const;
			/* Computes the dot product of 2 vectors. */
			static float dot(const Vec3f& A, const Vec3f& B);

			/* Gets the cross product of the current vector to the param. */
			Vec3f cross(const Vec3f& A) const;
			/* Gets the cross product of 2 vectors. */
			static Vec3f cross(const Vec3f& A, const Vec3f& B);

			/* Gets the lerped vector between 2 vectors. */
			static Vec3f lerp(const Vec3f& from, const Vec3f& to, float p);

			/* Gets the reflection vector from current vector and normal. */
			Vec3f reflect(const Vec3f& normal) const;
			/* Gets the reflection vector from defined vector and normal. */
			static Vec3f reflect(const Vec3f& A, const Vec3f& normal);

			/* Gets the rotated vector of current vector along axis in radians. */
			Vec3f rotater(const Vec3f& axis, float rad) const;
			/* Gets the rotated vector along axis in radians. */
			static Vec3f rotater(const Vec3f& A, const Vec3f& axis, float rad);

			/* Gets the rotated vector of current vector along axis in degrees. */
			Vec3f rotated(const Vec3f& axis, float deg) const;
			/* Gets the rotated vector along axis in degrees. */
			static Vec3f rotated(const Vec3f& A, const Vec3f& axis, float deg);

			/* Gets the rotated vector of current vector from quaternion. */
			Vec3f rotate(const Quaternion& rot) const;
		};// struct vec3f

	}// namespace Math
}// namespace gg
#endif