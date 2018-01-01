#ifndef		GG_QUATERNION_H
#define		GG_QUATERNION_H
#pragma once
#include <iomanip>

namespace gg
{
	namespace Math
	{
		struct Vec3f;
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

			/* Creates quaternion with x,y,z,w as 0. */
			Quaternion(void);
			/* Creates quaternion with defined x,y,z, values. */
			Quaternion(float x, float y, float z, float w);
			/* Creates quaternion from rotation parameters. */
			Quaternion(const Vec3f& axis, float deg);

			friend Quaternion operator+(const Quaternion& A, const Quaternion& B);
			friend Quaternion operator-(const Quaternion& A, const Quaternion& B);
			Quaternion operator-(void);
			friend Quaternion operator*(const Quaternion& A, const Quaternion& B);
			friend Quaternion operator*(const Quaternion& A, float c);
			friend Quaternion operator*(const Quaternion& A, const Vec3f& B);
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

		};// struct Quaternion
	}// namespace Math
}// namespace gg
#endif