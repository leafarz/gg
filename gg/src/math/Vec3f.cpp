#include "math/Vec3f.h"

#include <math.h>

#include "math/MathUtil.h"

#include "math/Quaternion.h"
#include "math/Vec2f.h"
#include "math/Vec4f.h"

namespace gg { namespace math {
	const Vec3f Vec3f::up		= Vec3f( 0,  1,  0);
	const Vec3f Vec3f::down		= Vec3f( 0, -1,  0);
	const Vec3f Vec3f::right	= Vec3f( 1,  0,  0);
	const Vec3f Vec3f::left		= Vec3f(-1,  0,  0);
	const Vec3f Vec3f::forward	= Vec3f( 0,  0,  1);
	const Vec3f Vec3f::back		= Vec3f( 0,  0, -1);
	const Vec3f Vec3f::zero		= Vec3f( 0,  0,  0);
	const Vec3f Vec3f::one		= Vec3f( 1,  1,  1);

	Vec3f::Vec3f(float x, float y, float z)
		: x(x), y(y), z(z)
	{ }

	Vec3f::Vec3f(void* vec)
		: x(((float*)(vec))[0]), y(((float*)(vec))[1]), z(((float*)(vec))[2])
	{ }

	Vec3f::Vec3f(const Vec2f& A, float z)
		: x(A.x), y(A.y), z(z)
	{ }

	Vec3f::Vec3f(const Vec4f& A)
		: x(A.x), y(A.y), z(A.z)
	{ }

	Vec3f::Vec3f(const Quaternion& Q)
		: x(asinf(2 * (Q.w * Q.x - Q.z * Q.y))),
		y(atan2f(2 * (Q.w * Q.y + Q.x * Q.z), 1 - 2 * (powf(Q.y, 2) + powf(Q.x, 2)))),
		z(atan2f(2 * (Q.w * Q.z + Q.y * Q.x), 1 - 2 * (powf(Q.x, 2) + powf(Q.z, 2))))
	{ }

	Vec3f operator+(const Vec3f& A, const Vec3f& B)
	{
		return Vec3f(A.x + B.x, A.y + B.y, A.z + B.z);
	}

	Vec3f Vec3f::operator-(void) const
	{
		return Vec3f(-this->x, -this->y, -this->z);
	}

	Vec3f operator-(const Vec3f& A, const Vec3f& B)
	{
		return Vec3f(A.x - B.x, A.y - B.y, A.z - B.z);
	}

	Vec3f operator*(const Vec3f& A, float c)
	{
		return Vec3f(A.x * c, A.y * c, A.z * c);
	}

	Vec3f operator*(float c, const Vec3f& A)
	{
		return Vec3f(A.x * c, A.y * c, A.z * c);
	}

	Vec3f operator/(const Vec3f& A, float c)
	{
		float _invC = 1 / c;
		return Vec3f(A.x * _invC, A.y * _invC, A.z * _invC);
	}

	Vec3f& Vec3f::operator+=(const Vec3f& A)
	{
		this->x += A.x;
		this->y += A.y;
		this->z += A.z;
		return *this;
	}

	Vec3f& Vec3f::operator+=(float c)
	{
		this->x += c;
		this->y += c;
		this->z += c;
		return *this;
	}

	Vec3f& Vec3f::operator-=(const Vec3f& A)
	{
		this->x -= A.x;
		this->y -= A.y;
		this->z -= A.z;
		return *this;
	}

	Vec3f& Vec3f::operator-=(float c)
	{
		this->x -= c;
		this->y -= c;
		this->z -= c;
		return *this;
	}

	Vec3f& Vec3f::operator*=(float c)
	{
		this->x *= c;
		this->y *= c;
		this->z *= c;
		return *this;
	}

	Vec3f& Vec3f::operator/=(float c)
	{
		this->x /= c;
		this->y /= c;
		this->z /= c;
		return *this;
	}

	bool operator==(const Vec3f& A, const Vec3f& B)
	{
		return
			floatCmp(A.x, B.x) &&
			floatCmp(A.y, B.y) &&
			floatCmp(A.z, B.z);
	}

	bool operator!=(const Vec3f& A, const Vec3f& B)
	{
		return
			!floatCmp(A.x, B.x) ||
			!floatCmp(A.y, B.y) ||
			!floatCmp(A.z, B.z);
	}

	std::ostream& operator<<(std::ostream& out, const Vec3f& A)
	{
		return
			out << std::fixed << std::setprecision(2) <<
			'(' << A.x << ", " << A.y << ", " << A.z << ')';
	}

	Vec3f& Vec3f::set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		return *this;
	}

	Vec3f& Vec3f::set(const Vec3f& A)
	{
		this->x = A.x;
		this->y = A.y;
		this->z = A.z;
		return *this;
	}

	Vec3f& Vec3f::set(const Vec4f& A)
	{
		this->x = A.x;
		this->y = A.y;
		this->z = A.z;
		return *this;
	}

	Vec3f& Vec3f::setX(float x) { this->x = x; return *this; }
	Vec3f& Vec3f::setY(float y) { this->y = y; return *this; }
	Vec3f& Vec3f::setZ(float z) { this->z = z; return *this; }

	float Vec3f::max(void) const
	{
		return fmaxf(this->x, fmaxf(this->y, this->z));
	}

	float Vec3f::min(void) const
	{
		return fminf(this->x, fminf(this->y, this->z));
	}

	float Vec3f::length(void) const
	{
		return sqrt(
			this->x * this->x +
			this->y * this->y +
			this->z * this->z
		);
	}

	float Vec3f::sqrLength(void) const
	{
		return
			x * x +
			y * y +
			z * z;
	}

	float Vec3f::magnitude(void) const
	{
		return sqrt(
			x * x +
			y * y +
			z * z
		);
	}

	float Vec3f::sqrMagnitude(void) const
	{
		return
			x * x +
			y * y +
			z * z;
	}

	Vec3f Vec3f::normal(void) const
	{
		return *this / length();
	}

	Vec3f& Vec3f::normalize(void)
	{
		float _invLength = 1 / length();
		x *= _invLength;
		y *= _invLength;
		z *= _invLength;
		return *this;
	}

	Vec3f Vec3f::abs(void) const
	{
		return Vec3f(
			std::abs(this->x),
			std::abs(this->y),
			std::abs(this->z)
		);
	}

	float Vec3f::dot(const Vec3f& A) const
	{
		return
			this->x * A.x +
			this->y * A.y +
			this->z * A.z;
	}

	float Vec3f::dot(const Vec3f& A, const Vec3f& B)
	{
		return
			A.x * B.x +
			A.y * B.y +
			A.z * B.z;
	}

	Vec3f Vec3f::cross(const Vec3f& B) const
	{
		return Vec3f(
			this->y * B.z - this->z * B.y,
			this->z * B.x - this->x * B.z,
			this->x * B.y - this->y * B.x
		);
	}

	Vec3f Vec3f::cross(const Vec3f& A, const Vec3f& B)
	{
		return Vec3f(
			A.y * B.z - A.z * B.y,
			A.z * B.x - A.x * B.z,
			A.x * B.y - A.y * B.x
		);
	}

	Vec3f Vec3f::lerp(const Vec3f& from, const Vec3f& to, float p)
	{
		return from + (to - from) * p;
	}

	Vec3f Vec3f::reflect(const Vec3f& normal) const
	{
		return Vec3f(*this - 2 * this->dot(normal) * normal);
	}

	Vec3f Vec3f::reflect(const Vec3f& A, const Vec3f& normal)
	{
		return 2 * (A.dot(normal)) * normal - A;
	}

	Vec3f Vec3f::rotater(const Vec3f& axis, float rad) const
	{
		float _sinAngle = sinf(-rad);
		float _cosAngle = cosf(-rad);

		return
			this->cross(axis * _sinAngle) +					// rot on local x
			(*this) * _cosAngle +							// rot on local z
			axis * (this->dot(axis * (1 - _cosAngle)));		// rot on local y
	}

	Vec3f Vec3f::rotater(const Vec3f& A, const Vec3f& axis, float rad)
	{
		return A.rotater(axis, rad);
	}

	Vec3f Vec3f::rotated(const Vec3f& axis, float deg) const
	{
		float _sinAngle = static_cast<float>(sin(-deg * DEG_TO_RAD));
		float _cosAngle = static_cast<float>(cos(-deg * DEG_TO_RAD));
			
		return this->cross(axis * _sinAngle) +				// rot on local x
			(*this) * _cosAngle +							// rot on local z
			axis * (this->dot(axis * (1 - _cosAngle)));		// rot on local y;
	}


	Vec3f Vec3f::rotated(const Vec3f& A, const Vec3f& axis, float deg)
	{
		return A.rotated(axis, deg);
	}

	Vec3f Vec3f::rotate(const Quaternion& rot) const
	{
		// nVidia SDK implementation

		Vec3f uv, uuv;
		Vec3f qvec(this->x, this->y, this->z);
		uv = qvec.cross(*this);
		uuv = qvec.cross(uv);
		uv *= (2.0f * rot.w);
		uuv *= 2.0f;

		return *this + uv + uuv;
	}

	void Vec3f::orthoNormalize(Vec3f& normal, Vec3f& tangent)
	{
		normal.normalize();
		Vec3f _perp = normal.cross(tangent);
		tangent = _perp.cross(normal).normal();
	}

	// swizzle functions
	Vec2f Vec3f::xy(void) const { return Vec2f(x, y); }
	Vec2f Vec3f::xz(void) const { return Vec2f(x, z); }

	Vec2f Vec3f::yx(void) const { return Vec2f(y, x); }
	Vec2f Vec3f::yz(void) const { return Vec2f(y, z); }

	Vec2f Vec3f::zx(void) const { return Vec2f(z, x); }
	Vec2f Vec3f::zy(void) const { return Vec2f(z, y); }

	Vec3f Vec3f::xzy(void) const { return Vec3f(x, z, y); }
	Vec3f Vec3f::yxz(void) const { return Vec3f(y, x, z); }
	Vec3f Vec3f::yzx(void) const { return Vec3f(y, z, x); }
	Vec3f Vec3f::zxy(void) const { return Vec3f(z, x, y); }
	Vec3f Vec3f::zyx(void) const { return Vec3f(z, y, x); }
} /*namespace math*/ }// namespace gg
