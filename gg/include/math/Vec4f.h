#ifndef		GG_VEC4F_H
#define		GG_VEC4F_H
#pragma once

#include <iomanip>

namespace gg { namespace Math {
	struct Vec2f;
	struct Vec3f;
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

		/* Creates vector with default x,y,z,w=0 unless defined. */
		Vec4f(float x = 0, float y = 0, float z = 0, float w = 0);
		/* Creates vector with any pointer (must have 4 floats).
		 * Void pointer will be converted to float pointer and will get the
		 * 1st, 2nd, 3rd and 4th indices, otherwise Vec4f will have unexpected values.
		 */
		Vec4f(void* vec);
		/* Creates vector from x,y values of Vec2f and z,w value 0 as default unless defined.*/
		Vec4f(const Vec2f& A, float z = 0, float w = 0);
		/* Creates vector from x,y,z values of Vec3f and w value 0 as default unless defined.*/
		Vec4f(const Vec3f& A, float w = 0);

		friend Vec4f operator+(const Vec4f& A, const Vec4f& B);
		Vec4f operator-(void) const;
		friend Vec4f operator-(const Vec4f& A, const Vec4f& B);
		friend Vec4f operator*(const Vec4f& A, float c);
		friend Vec4f operator*(float c, const Vec4f& A);
		friend Vec4f operator/(const Vec4f& A, float c);

		/* Adds Vec4f to this vector. */
		Vec4f& operator+=(const Vec4f& A);
		/* Adds c to x,y,z,w values of this vector. */
		Vec4f& operator+=(float c);
		/* Subtracts Vec4f to this vector. */
		Vec4f& operator-=(const Vec4f& A);
		/* Subtracts c to x,y,z,w values of this vector. */
		Vec4f& operator-=(float c);
		/* Multiplies c to x,y,z,w values of this vector. */
		Vec4f& operator*=(float c);
		/* Divides c to x,y,z,w values of this vector. */
		Vec4f& operator/=(float c);

		friend bool operator==(const Vec4f& A, const Vec4f& B);
		friend bool operator!=(const Vec4f& A, const Vec4f& B);

		friend std::ostream& operator<<(std::ostream& out, const Vec4f& A);

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

	// swizzle functions
	public:
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

		/* Gets the x,y,w,z values in Vec4f form. */
		Vec4f xywz(void) const;
		/* Gets the x,z,y,w values in Vec4f form. */
		Vec4f xzyw(void) const;
		/* Gets the x,z,w,y values in Vec4f form. */
		Vec4f xzwy(void) const;
		/* Gets the x,w,y,z values in Vec4f form. */
		Vec4f xwyz(void) const;
		/* Gets the x,w,z,y values in Vec4f form. */
		Vec4f xwzy(void) const;

		/* Gets the y,x,z,w values in Vec4f form. */
		Vec4f yxzw(void) const;
		/* Gets the y,x,w,z values in Vec4f form. */
		Vec4f yxwz(void) const;
		/* Gets the y,z,x,w values in Vec4f form. */
		Vec4f yzxw(void) const;
		/* Gets the y,z,w,x values in Vec4f form. */
		Vec4f yzwx(void) const;
		/* Gets the y,w,x,z values in Vec4f form. */
		Vec4f ywxz(void) const;
		/* Gets the y,w,x,z values in Vec4f form. */
		Vec4f ywzx(void) const;

		/* Gets the z,x,y,w values in Vec4f form. */
		Vec4f zxyw(void) const;
		/* Gets the z,x,w,y values in Vec4f form. */
		Vec4f zxwy(void) const;
		/* Gets the z,y,x,w values in Vec4f form. */
		Vec4f zyxw(void) const;
		/* Gets the z,y,w,x values in Vec4f form. */
		Vec4f zywx(void) const;
		/* Gets the z,w,x,y values in Vec4f form. */
		Vec4f zwxy(void) const;
		/* Gets the z,w,y,x values in Vec4f form. */
		Vec4f zwyx(void) const;

		/* Gets the w,x,y,z values in Vec4f form. */
		Vec4f wxyz(void) const;
		/* Gets the w,x,z,y values in Vec4f form. */
		Vec4f wxzy(void) const;
		/* Gets the w,y,x,z values in Vec4f form. */
		Vec4f wyxz(void) const;
		/* Gets the w,y,z,x values in Vec4f form. */
		Vec4f wyzx(void) const;
		/* Gets the w,z,x,y values in Vec4f form. */
		Vec4f wzxy(void) const;
		/* Gets the w,z,y,x values in Vec4f form. */
		Vec4f wzyx(void) const;
	};// struct vec4f
}/*namespace Math*/ }// namespace gg
#endif