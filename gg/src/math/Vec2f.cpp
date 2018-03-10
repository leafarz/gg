#include "math/Vec2f.h"

#include <math.h>
#include <iostream>

#include "math/MathUtil.h"

#include "math/Vec3f.h"
#include "math/Vec4f.h"

namespace gg { namespace Math {
	const Vec2f Vec2f::up		= Vec2f(0, 1);
	const Vec2f Vec2f::right	= Vec2f(1, 0);
	const Vec2f Vec2f::zero		= Vec2f(0, 0);
	const Vec2f Vec2f::one		= Vec2f(1, 1);

	Vec2f::Vec2f(float x, float y)
		: x(x), y(y)
	{ }

	Vec2f::Vec2f(const Vec3f & A)
		: x(A.x), y(A.y)
	{ }

	Vec2f::Vec2f(const Vec4f & A)
		: x(A.x), y(A.y)
	{ }

	Vec2f operator+(const Vec2f& A, const Vec2f& B)
	{
		return Vec2f(A.x + B.x, A.y + B.y);
	}

	Vec2f Vec2f::operator-(void) const
	{
		return Vec2f(-this->x, -this->y);
	}

	Vec2f operator-(const Vec2f& A, const Vec2f& B)
	{
		return Vec2f(A.x - B.x, A.y - B.y);
	}

	Vec2f operator*(const Vec2f& A, float c)
	{
		return Vec2f(A.x * c, A.y * c);
	}

	Vec2f operator*(float c, const Vec2f& A)
	{
		return Vec2f(A.x * c, A.y * c);
	}

	Vec2f operator/(const Vec2f& A, float c)
	{
		return Vec2f(A.x / c, A.y / c);
	}

	Vec2f& Vec2f::operator+=(const Vec2f& A)
	{
		this->x += A.x;
		this->y += A.y;
		return *this;
	}

	Vec2f& Vec2f::operator+=(float c)
	{
		this->x += c;
		this->y += c;
		return *this;
	}

	Vec2f& Vec2f::operator-=(const Vec2f& A)
	{
		this->x -= A.x;
		this->y -= A.y;
		return *this;
	}

	Vec2f& Vec2f::operator-=(float c)
	{
		this->x -= c;
		this->y -= c;
		return *this;
	}

	Vec2f& Vec2f::operator*=(float c)
	{
		this->x *= c;
		this->y *= c;
		return *this;
	}

	Vec2f& Vec2f::operator/=(float c)
	{
		this->x /= c;
		this->y /= c;
		return *this;
	}

	bool operator==(const Vec2f& A, const Vec2f& B)
	{
		return
			floatCmp(A.x, B.x) &&
			floatCmp(A.y, B.y);
	}

	bool operator!=(const Vec2f& A, const Vec2f& B)
	{
		return
			!floatCmp(A.x, B.x) ||
			!floatCmp(A.y, B.y);
	}

	std::ostream& operator<<(std::ostream& out, const Vec2f& A)
	{
		return
			out << std::fixed << std::setprecision(2) <<
			'(' << A.x << ", " << A.y << ')';
	}

	Vec2f& Vec2f::set(float x, float y)
	{
		this->x = x;
		this->y = y;
		return *this;
	}

	Vec2f& Vec2f::set(const Vec2f& A)
	{
		this->x = A.x;
		this->y = A.y;
		return *this;
	}

	Vec2f& Vec2f::setX(float x) { this->x = x; return *this; }
	Vec2f& Vec2f::setY(float y) { this->y = y; return *this; }

	float Vec2f::max(void) const
	{
		return fmaxf(this->x, this->y);
	}

	float Vec2f::min(void) const
	{
		return fminf(this->x, this->y);
	}

	float Vec2f::length(void) const
	{
		return sqrt(
			this->x * this->x +
			this->y * this->y
		);
	}

	float Vec2f::sqrLength(void) const
	{
		return
			this->x * this->x +
			this->y * this->y;
	}

	float Vec2f::magnitude(void) const
	{
		return sqrt(
			this->x * this->x +
			this->y * this->y
		);
	}

	float Vec2f::sqrMagnitude(void) const
	{
		return
			this->x * this->x +
			this->y * this->y;
	}

	Vec2f Vec2f::normal(void) const
	{
		return *this / length();
	}

	Vec2f& Vec2f::normalize(void)
	{
		float _invLength = 1 / length();
		this->x *= _invLength;
		this->y *= _invLength;
		return *this;
	}

	Vec2f Vec2f::abs() const
	{
		return Vec2f(
			std::abs(this->x),
			std::abs(this->y)
		);
	}

	float Vec2f::dot(const Vec2f& A) const
	{
		return this->x * A.x + this->y * A.y;
	}

	float Vec2f::dot(const Vec2f& A, const Vec2f& B)
	{
		return A.x * B.x + A.y * B.y;
	}

	Vec2f Vec2f::lerp(const Vec2f& from, const Vec2f& to, float p)
	{
		return from + (to - from) * p;
	}

	Vec2f Vec2f::reflect(const Vec2f& normal) const
	{
		return *this - 2 * (this->dot(normal)) * normal;
	}

	Vec2f Vec2f::reflect(const Vec2f& A, const Vec2f& normal)
	{
		return 2 * (A.dot(normal)) * normal - A;
	}

	Vec2f Vec2f::rotated(float degrees) const
	{
		float _rad = degrees * static_cast<float>(DEG_TO_RAD);
		float _cos = cosf(_rad);
		float _sin = sinf(_rad);

		return Vec2f(
			_cos * this->x - _sin * this->y,
			_sin * this->x + _cos * this->y
		);
	}

	Vec2f Vec2f::rotated(const Vec2f& A, float degrees)
	{
		float _rad = degrees * static_cast<float>(RAD_TO_DEG);
		float _cos = cosf(_rad);
		float _sin = sinf(_rad);
			
		return Vec2f(
			_cos * A.x - _sin * A.y,
			_sin * A.x + _cos * A.y
		);
	}

	Vec2f Vec2f::rotater(float rad) const
	{
		float _cos = cosf(rad);
		float _sin = sinf(rad);

		return Vec2f(
			_cos * this->x - _sin * this->y,
			_sin * this->x + _cos * this->y
		);
	}

	Vec2f Vec2f::rotater(const Vec2f& A, float rad)
	{
		float _cos = cosf(rad);
		float _sin = sinf(rad);
			
		return Vec2f(
			_cos * A.x - _sin * A.y,
			_sin * A.x + _cos * A.y
		);
	}

	float Vec2f::angle(const Vec2f& A) const
	{
		float _dot = this->dot(A);
		float _determinant = this->x * A.y - this->y * A.x;
		return atan2(_determinant, _dot);
	}

	float Vec2f::angle(const Vec2f& A, const Vec2f& B)
	{
		float _dot = A.dot(B);
		float _determinant = A.x * B.y - A.y * B.x;
		return atan2(_determinant, _dot);
	}
}/*namespace Math*/ }// namespace gg
