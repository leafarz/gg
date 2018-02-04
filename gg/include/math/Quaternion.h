#ifndef		GG_QUATERNION_H
#define		GG_QUATERNION_H
#pragma once
#include <iomanip>

// TODO: check if we need to remove default value for
// up param in lookRotation function to avoid circular
// dependency and remove include
#include "Vec3f.h"

// TODO: x rotation is counter cw
namespace gg
{
	namespace Math
	{
		struct Vec2f;
		struct Mat4f;
		struct Quaternion
		{
			/* The x of the quaternion. */
			float x;
			/* The y of the quaternion. */
			float y;
			/* The z of the quaternion. */
			float z;
			/* The w of the quaternion. */
			float w;

			/* Creates quaternion with default x,y,z=0 unless defined. */
			Quaternion(float x = 0, float y = 0, float z = 0, float w = 1);
			/* Creates quaternion from rotation parameters. */
			Quaternion(const Vec3f& axis, float deg);
			/* Create quaternion from forward and up vectors. */
			Quaternion(const Vec3f& forward, const Vec3f& up);
			/* Create quaternion from euler angles in degrees. */
			Quaternion(const Vec3f& eulerd);


			friend Quaternion operator+(const Quaternion& A, const Quaternion& B);
			friend Quaternion operator-(const Quaternion& A, const Quaternion& B);
			Quaternion operator-(void);
			friend Quaternion operator*(const Quaternion& A, const Quaternion& B);
			friend Quaternion operator*(const Quaternion& A, float c);
			friend Vec3f operator*(const Quaternion& A, const Vec3f& B);
			friend Quaternion operator*(float c, const Quaternion& A);
			friend Quaternion operator/(const Quaternion& A, float c);

			friend bool operator==(const Quaternion& A, const Quaternion& B);
			friend bool operator!=(const Quaternion& A, const Quaternion& B);

			friend std::ostream& operator<<(std::ostream& out, const Quaternion& A);

			/* Gets forward vector from the current quaternion. */
			Vec3f getForward(void) const;
			/* Gets back vector from the current quaternion. */
			Vec3f getBack(void) const;
			/* Gets up vector from the current quaternion. */
			Vec3f getUp(void) const;
			/* Gets down vector from the current quaternion. */
			Vec3f getDown(void) const;
			/* Gets right vector from the current quaternion. */
			Vec3f getRight(void) const;
			/* Gets left vector from the current quaternion. */
			Vec3f getLeft(void) const;

			/* Gets the x,y values in Vec2f form. */
			Vec2f xy(void) const;
			/* Gets the x,z values in Vec2f form. */
			Vec2f xz(void) const;
			/* Gets the x,w values in Vec2f form. */
			Vec2f xw(void) const;

			/* Gets the y,x values in Vec2f form. */
			Vec2f yx(void) const;
			/* Gets the y,z values in Vec2f form. */
			Vec2f yz(void) const;
			/* Gets the y,w values in Vec2f form. */
			Vec2f yw(void) const;

			/* Gets the z,x values in Vec2f form. */
			Vec2f zx(void) const;
			/* Gets the z,y values in Vec2f form. */
			Vec2f zy(void) const;
			/* Gets the z,w values in Vec2f form. */
			Vec2f zw(void) const;

			/* Gets the w,x values in Vec2f form. */
			Vec2f wx(void) const;
			/* Gets the w,y values in Vec2f form. */
			Vec2f wy(void) const;
			/* Gets the w,z values in Vec2f form. */
			Vec2f wz(void) const;

			/* Gets the x,y,z values in Vec3f form. */
			Vec3f xyz(void) const;
			/* Gets the x,z,y values in Vec3f form. */
			Vec3f xzy(void) const;
			/* Gets the x,y,w values in Vec3f form. */
			Vec3f xyw(void) const;
			/* Gets the x,w,y values in Vec3f form. */
			Vec3f xwy(void) const;
			/* Gets the x,z,w values in Vec3f form. */
			Vec3f xzw(void) const;
			/* Gets the x,w,z values in Vec3f form. */
			Vec3f xwz(void) const;

			/* Gets the y,x,z values in Vec3f form. */
			Vec3f yxz(void) const;
			/* Gets the y,z,x values in Vec3f form. */
			Vec3f yzx(void) const;
			/* Gets the y,x,w values in Vec3f form. */
			Vec3f yxw(void) const;
			/* Gets the y,w,x values in Vec3f form. */
			Vec3f ywx(void) const;
			/* Gets the y,z,w values in Vec3f form. */
			Vec3f yzw(void) const;
			/* Gets the y,w,z values in Vec3f form. */
			Vec3f ywz(void) const;

			/* Gets the z,x,y values in Vec3f form. */
			Vec3f zxy(void) const;
			/* Gets the z,y,x values in Vec3f form. */
			Vec3f zyx(void) const;
			/* Gets the z,x,w values in Vec3f form. */
			Vec3f zxw(void) const;
			/* Gets the z,w,x values in Vec3f form. */
			Vec3f zwx(void) const;
			/* Gets the z,y,w values in Vec3f form. */
			Vec3f zyw(void) const;
			/* Gets the z,w,y values in Vec3f form. */
			Vec3f zwy(void) const;

			/* Gets the w,x,y values in Vec3f form. */
			Vec3f wxy(void) const;
			/* Gets the w,y,x values in Vec3f form. */
			Vec3f wyx(void) const;
			/* Gets the w,x,z values in Vec3f form. */
			Vec3f wxz(void) const;
			/* Gets the w,z,x values in Vec3f form. */
			Vec3f wzx(void) const;
			/* Gets the w,y,z values in Vec3f form. */
			Vec3f wyz(void) const;
			/* Gets the w,z,y values in Vec3f form. */
			Vec3f wzy(void) const;

			/* Sets x,y,z,w values to c and returns the result quaternion. */
			Quaternion& set(float c);
			/* Sets defined x,y,z,w values and returns the result quaternion. */
			Quaternion& set(float x, float y, float z, float w);
			/* Sets defined x,y,z,w values and returns the result quaternion. */
			Quaternion& set(const Quaternion& A);
			/* Set quaternion from rotation parameters. */
			Quaternion& set(Vec3f axis, float deg);

			/* Sets x value only and returns the result quaternion. */
			Quaternion& setX(float x);
			/* Sets y value only and returns the result quaternion. */
			Quaternion& setY(float y);
			/* Sets z value only and returns the result quaternion. */
			Quaternion& setZ(float z);
			/* Sets w value only and returns the result quaternion. */
			Quaternion& setW(float w);

			/* Returns the length of the quaternion.
			*  (Same as getMagnitude function)
			*/
			float length(void) const;
			/* Returns the square of length of the quaternion.
			*  (Same as getSqrMagnitude function)
			*/
			float sqrLength(void) const;
			/* Returns the magnitude of the quaternion.
			*  (Same as getLength function)
			*/
			float magnitude(void) const;
			/* Returns the square of magnitude of the quaternion.
			*  (Same as getSqrLength function)
			*/
			float sqrMagnitude(void) const;

			/* Returns the normalized quaternion. */
			Quaternion normal(void) const;
			/* Normalize the current quaternion. */
			Quaternion& normalize(void);

			/* Returns the conjugate of the current quaternion. */
			Quaternion conjugate(void) const;
			/* Returns the conjugate of the quaternion. */
			static Quaternion conjugate(const Quaternion& A);

			/* Returns the converted euler angles from the current quaternion in radians. */
			Vec3f toEulerr(void) const;
			/* Returns the converted euler angles from the current quaternion in degrees. */
			Vec3f toEulerd(void) const;

			/* Returns the equivalent rotation matrix of the current quaternion. */
			Mat4f toRotationMatrix(void) const;

			/* Computes the dot product of the current quaternion to the param. */
			float dot(const Quaternion& A) const;
			/* Computes the dot product of 2 quaternions. */
			static float dot(const Quaternion& A, const Quaternion& B);

			/* Gets the quaternion from forward and up vectors. */
			static Quaternion lookRotation(const Vec3f& forward, const Vec3f& up = Vec3f::up);

			static Quaternion fromEulerd(const Vec3f& eulerd);

		};// struct Quaternion
	}// namespace Math
}// namespace gg
#endif