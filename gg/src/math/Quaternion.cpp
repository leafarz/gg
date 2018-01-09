#include "math/Quaternion.h"

#include <math.h>
#include "math/MathUtil.h"
#include "math/Mat4f.h"
#include "math/Vec3f.h"

namespace gg
{
	namespace Math
	{
		Quaternion::Quaternion(void)
			: x(0), y(0), z(0), w(1)
		{ }

		Quaternion::Quaternion(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w)
		{ }

		Quaternion::Quaternion(const Vec3f& axis, float deg)
		{
			float _sinHalfAngle = sinf(deg * DEG_TO_RAD_HALF);
			float _cosHalfAngle = cosf(deg * DEG_TO_RAD_HALF);

			this->x = axis.x * _sinHalfAngle;
			this->y = axis.y * _sinHalfAngle;
			this->z = axis.z * _sinHalfAngle;
			this->w = _cosHalfAngle;
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

		Quaternion operator*(const Quaternion& A, const Vec3f& B)
		{
			return Quaternion(
				 A.w * B.x + A.y * B.z - A.z * B.y,
				 A.w * B.y + A.z * B.x - A.x * B.z,
				 A.w * B.z + A.x * B.y - A.y * B.x,
				-A.x * B.x - A.y * B.y - A.z * B.z
			);
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

		Vec3f Quaternion::getForward(void)	const { return Vec3f::forward.rotate(*this); }
		Vec3f Quaternion::getBack(void)		const { return Vec3f::back.rotate(*this); }
		Vec3f Quaternion::getUp(void)		const { return Vec3f::up.rotate(*this); }
		Vec3f Quaternion::getDown(void)		const { return Vec3f::down.rotate(*this); }
		Vec3f Quaternion::getRight(void)	const { return Vec3f::right.rotate(*this); }
		Vec3f Quaternion::getLeft(void)		const { return Vec3f::left.rotate(*this); }

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
			float _sinHalfAngle = sinf(deg * DEG_TO_RAD_HALF);
			float _cosHalfAngle = cosf(deg * DEG_TO_RAD_HALF);

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
			) * RAD_TO_DEG;
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
	}// namespace Math
}// namespace gg
