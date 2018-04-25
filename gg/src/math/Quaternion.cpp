#include "math/Quaternion.h"

#include <math.h>
#include "math/MathUtil.h"
#include "math/Mat4f.h"
#include "math/Vec2f.h"
#include "math/Vec3f.h"

namespace gg { namespace math {
	const Quaternion Quaternion::identity = Quaternion(0,0,0,1);

	Quaternion::Quaternion(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{ }

	Quaternion::Quaternion(const Vec3f& axis, float deg)
	{
		float _sinHalfAngle = sinf(deg * static_cast<float>(DEG_TO_RAD_HALF));
		float _cosHalfAngle = cosf(deg * static_cast<float>(DEG_TO_RAD_HALF));

		this->x = axis.x * _sinHalfAngle;
		this->y = axis.y * _sinHalfAngle;
		this->z = axis.z * _sinHalfAngle;
		this->w = _cosHalfAngle;
	}

	Quaternion::Quaternion(const Vec3f& eulerd)
	{
		*this = fromEulerd(eulerd);
	}

	Quaternion Quaternion::operator-(void)
	{
		this->x = -this->x;
		this->y = -this->y;
		this->z = -this->z;
		this->w = -this->w;
		return *this;
	}

	Quaternion operator+(const Quaternion& A, const Quaternion& B)
	{
		return Quaternion(A.x + B.x, A.y + B.y, A.z + B.z, A.w + B.w);
	}

	Quaternion operator-(const Quaternion& A, const Quaternion& B)
	{
		return Quaternion(A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w);
	}

	Quaternion operator*(const Quaternion& A, const Quaternion& B)
	{
		return Quaternion(
			(A.x * B.w) + (A.w * B.x) + (A.y * B.z) - (A.z * B.y),
			(A.y * B.w) + (A.w * B.y) + (A.z * B.x) - (A.x * B.z),
			(A.z * B.w) + (A.w * B.z) + (A.x * B.y) - (A.y * B.x),
			(A.w * B.w) - (A.x * B.x) - (A.y * B.y) - (A.z * B.z)
		);
	}

	Quaternion operator*(const Quaternion& A, float c)
	{
		return Quaternion(A.x * c, A.y * c, A.z * c, A.w * c);
	}

	Quaternion operator*(float c, const Quaternion& A)
	{
		return Quaternion(A.x * c, A.y * c, A.z * c, A.w * c);
	}

	Vec3f operator*(const Quaternion& A, const Vec3f& B)
	{
		// nVidia SDK implementation

		Vec3f uv, uuv;
		Vec3f qvec(A.x, A.y, A.z);
		uv = qvec.cross(B);
		uuv = qvec.cross(uv);
		uv *= (2.0f * A.w);
		uuv *= 2.0f;

		return B + uv + uuv;
	}

	Quaternion operator/(const Quaternion& A, float c)
	{
		const float _invC = 1 / c;
		return Quaternion(A.x * _invC, A.y * _invC, A.z * _invC, A.w * _invC);
	}

	bool operator==(const Quaternion& A, const Quaternion& B)
	{
		return
			floatCmp(A.x, B.x) &&
			floatCmp(A.y, B.y) &&
			floatCmp(A.z, B.z) &&
			floatCmp(A.w, B.w);
	}

	bool operator!=(const Quaternion& A, const Quaternion& B)
	{
		return
			!floatCmp(A.x, B.x) ||
			!floatCmp(A.y, B.y) ||
			!floatCmp(A.z, B.z) ||
			!floatCmp(A.w, B.w);
	}

	std::ostream& operator<<(std::ostream& out, const Quaternion& A)
	{
		return
			out << std::fixed << std::setprecision(2) <<
			"(" << A.x << ", " << A.y << ", " << A.z <<
			", " << A.w << ")";
	}

	Vec3f Quaternion::getForward(void)	const { return (*this * Vec3f::forward); }
	Vec3f Quaternion::getBack(void)		const { return (*this * Vec3f::back); }
	Vec3f Quaternion::getUp(void)		const { return (*this * Vec3f::up); }
	Vec3f Quaternion::getDown(void)		const { return (*this * Vec3f::down); }
	Vec3f Quaternion::getRight(void)	const { return (*this * Vec3f::right); }
	Vec3f Quaternion::getLeft(void)		const { return (*this * Vec3f::left); }

	Vec2f Quaternion::xy(void) const { return Vec2f(x, y); }
	Vec2f Quaternion::xz(void) const { return Vec2f(x, z); }
	Vec2f Quaternion::xw(void) const { return Vec2f(x, w); }

	Vec2f Quaternion::yx(void) const { return Vec2f(y, x); }
	Vec2f Quaternion::yz(void) const { return Vec2f(y, z); }
	Vec2f Quaternion::yw(void) const { return Vec2f(y, w); }

	Vec2f Quaternion::zx(void) const { return Vec2f(z, x); }
	Vec2f Quaternion::zy(void) const { return Vec2f(z, y); }
	Vec2f Quaternion::zw(void) const { return Vec2f(z, w); }

	Vec2f Quaternion::wx(void) const { return Vec2f(w, x); }
	Vec2f Quaternion::wy(void) const { return Vec2f(w, y); }
	Vec2f Quaternion::wz(void) const { return Vec2f(w, z); }

	Vec3f Quaternion::xyz(void) const { return Vec3f(x, y, z); }
	Vec3f Quaternion::xzy(void) const { return Vec3f(x, z, y); }
	Vec3f Quaternion::xyw(void) const { return Vec3f(x, y, w); }
	Vec3f Quaternion::xwy(void) const { return Vec3f(x, w, y); }
	Vec3f Quaternion::xzw(void) const { return Vec3f(x, z, w); }
	Vec3f Quaternion::xwz(void) const { return Vec3f(x, w, z); }

	Vec3f Quaternion::yxz(void) const { return Vec3f(y, x, z); }
	Vec3f Quaternion::yzx(void) const { return Vec3f(y, z, x); }
	Vec3f Quaternion::yxw(void) const { return Vec3f(y, x, w); }
	Vec3f Quaternion::ywx(void) const { return Vec3f(y, w, x); }
	Vec3f Quaternion::yzw(void) const { return Vec3f(y, z, w); }
	Vec3f Quaternion::ywz(void) const { return Vec3f(y, w, z); }

	Vec3f Quaternion::zxy(void) const { return Vec3f(z, x, y); }
	Vec3f Quaternion::zyx(void) const { return Vec3f(z, y, x); }
	Vec3f Quaternion::zxw(void) const { return Vec3f(z, x, w); }
	Vec3f Quaternion::zwx(void) const { return Vec3f(z, w, x); }
	Vec3f Quaternion::zyw(void) const { return Vec3f(z, y, w); }
	Vec3f Quaternion::zwy(void) const { return Vec3f(z, w, y); }

	Vec3f Quaternion::wxy(void) const { return Vec3f(w, x, y); }
	Vec3f Quaternion::wyx(void) const { return Vec3f(w, y, x); }
	Vec3f Quaternion::wxz(void) const { return Vec3f(w, x, z); }
	Vec3f Quaternion::wzx(void) const { return Vec3f(w, z, x); }
	Vec3f Quaternion::wyz(void) const { return Vec3f(w, y, z); }
	Vec3f Quaternion::wzy(void) const { return Vec3f(w, z, y); }

	Quaternion& Quaternion::set(float c)
	{
		this->x = c;
		this->y = c;
		this->z = c;
		this->w = c;
		return *this;
	}

	Quaternion& Quaternion::set(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
		return *this;
	}

	Quaternion& Quaternion::set(const Quaternion& A)
	{
		this->x = A.x;
		this->y = A.y;
		this->z = A.z;
		this->w = A.w;
		return *this;
	}

	Quaternion& Quaternion::set(Vec3f axis, float deg)
	{
		float _sinHalfAngle = sinf(deg * static_cast<float>(DEG_TO_RAD_HALF));
		float _cosHalfAngle = cosf(deg * static_cast<float>(DEG_TO_RAD_HALF));

		this->x = axis.x * _sinHalfAngle;
		this->y = axis.y * _sinHalfAngle;
		this->z = axis.z * _sinHalfAngle;
		this->w = _cosHalfAngle;

		return *this;
	}

	Quaternion& Quaternion::setX(float x) { this->x = x; return *this; }
	Quaternion& Quaternion::setY(float y) { this->y = y; return *this; }
	Quaternion& Quaternion::setZ(float z) { this->z = z; return *this; }
	Quaternion& Quaternion::setW(float w) { this->w = w; return *this; }

	float Quaternion::length(void) const
	{
		return sqrt(
			this->x * this->x +
			this->y * this->y +
			this->z * this->z +
			this->w * this->w
		);
	}

	float Quaternion::sqrLength(void) const
	{
		return
			this->x * this->x +
			this->y * this->y +
			this->z * this->z +
			this->w * this->w;
	}

	float Quaternion::magnitude(void) const
	{
		return sqrt(
			this->x * this->x +
			this->y * this->y +
			this->z * this->z +
			this->w * this->w
		);
	}

	float Quaternion::sqrMagnitude(void) const
	{
		return
			this->x * this->x +
			this->y * this->y +
			this->z * this->z +
			this->w * this->w;
	}

	Quaternion Quaternion::normal(void) const
	{
		return (*this) / length();
	}

	Quaternion& Quaternion::normalize(void)
	{
		const float _invLength = length();
		this->x *= _invLength;
		this->y *= _invLength;
		this->z *= _invLength;
		this->w *= _invLength;
		return *this;
	}

	Quaternion Quaternion::conjugate(void) const
	{
		return Quaternion(-this->x, -this->y, -this->z, this->w);
	}

	Quaternion Quaternion::conjugate(const Quaternion& A)
	{
		return Quaternion(-A.x, -A.y, -A.z, A.w);
	}

	Vec3f Quaternion::toEulerr(void) const
	{
		return Vec3f(
			asinf(2 *  (this->w * this->x - this->z * this->y)),
			atan2f(2 * (this->w * this->y + this->x * this->z), 1 - 2 * (powf(this->y, 2) + powf(this->x, 2))),
			atan2f(2 * (this->w * this->z + this->y * this->x), 1 - 2 * (powf(this->x, 2) + powf(this->z, 2)))
		);
	}

	Vec3f Quaternion::toEulerd(void) const
	{
		return Vec3f(
			asinf(2 * (this->w * this->x - this->z * this->y)),
			atan2f(2 * (this->w * this->y + this->x * this->z), 1 - 2 * (powf(this->y, 2) + powf(this->x, 2))),
			atan2f(2 * (this->w * this->z + this->y * this->x), 1 - 2 * (powf(this->x, 2) + powf(this->z, 2)))
		) * static_cast<float>(RAD_TO_DEG);
	}

	Mat4f Quaternion::toRotationMatrix(void) const
	{
		return Mat4f::rotationMatrix(*this);
	}

	float Quaternion::dot(const Quaternion& A) const
	{
		return
			this->x * A.x +
			this->y * A.y +
			this->z * A.z +
			this->w * A.w;
	}

	float Quaternion::dot(const Quaternion& A, const Quaternion& B)
	{
		return
			A.x * B.x +
			A.x * B.y +
			A.x * B.z +
			A.x * B.w;
	}

	Quaternion Quaternion::lookRotation(const Vec3f& forward)
	{
		float _dot = Vec3f::dot(Vec3f::forward, forward);

		if (abs(_dot - (-1.0f)) < FLT_EPSILON) { return Quaternion(Vec3f::up, static_cast<float>(math::PI)); }
		if (abs(_dot - ( 1.0f)) < FLT_EPSILON) { return identity; }

		float _angle = (float)acos(_dot);
		Vec3f _axis = Vec3f::cross(Vec3f::forward, forward).normal();

		return Quaternion(_axis, _angle * static_cast<float>(RAD_TO_DEG));
	}

	Quaternion Quaternion::fromEulerd(const Vec3f & eulerd)
	{
		Quaternion _q;

		float cy = cosf(eulerd.z * static_cast<float>(DEG_TO_RAD_HALF));	// yaw
		float sy = sinf(eulerd.z * static_cast<float>(DEG_TO_RAD_HALF));	// yaw
		float cr = cosf(eulerd.x * static_cast<float>(DEG_TO_RAD_HALF));	// roll
		float sr = sinf(eulerd.x * static_cast<float>(DEG_TO_RAD_HALF));	// roll
		float cp = cosf(eulerd.y * static_cast<float>(DEG_TO_RAD_HALF));	// pitch
		float sp = sinf(eulerd.y * static_cast<float>(DEG_TO_RAD_HALF));	// pitch

		_q.w = cy * cr * cp + sy * sr * sp;
		_q.x = cy * sr * cp - sy * cr * sp;
		_q.y = cy * cr * sp + sy * sr * cp;
		_q.z = sy * cr * cp - cy * sr * sp;
		return _q;
	}
}/*namespace math*/ }// namespace gg
