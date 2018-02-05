#include "math/Vec4f.h"

#include <math.h>
#include "math/MathUtil.h"

#include "math/Vec2f.h"
#include "math/Vec3f.h"
namespace gg
{
	namespace Math
	{
		Vec4f::Vec4f(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w)
		{ }

		Vec4f::Vec4f(Vec2f& A, float z, float w)
			: x(A.x), y(A.y), z(z), w(w)
		{ }

		Vec4f::Vec4f(Vec3f & A, float w)
			: x(A.x), y(A.y), z(A.z), w(w)
		{ }

		Vec4f operator+(const Vec4f& A, const Vec4f& B)
		{
			return Vec4f(A.x + B.x, A.y + B.y, A.z + B.z, A.w + B.w);
		}

		Vec4f Vec4f::operator-(void) const
		{
			return Vec4f(-this->x, -this->y, -this->z, -this->w);
		}

		Vec4f operator-(const Vec4f& A, const Vec4f& B)
		{
			return Vec4f(A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w);
		}

		Vec4f operator*(const Vec4f& A, float c)
		{
			return Vec4f(A.x * c, A.y * c, A.z * c, A.w * c);
		}

		Vec4f operator*(float c, const Vec4f& A)
		{
			return Vec4f(A.x * c, A.y * c, A.z * c, A.w * c);
		}

		Vec4f operator/(const Vec4f& A, float c)
		{
			float _invC = 1 / c;
			return Vec4f(A.x * _invC, A.y * _invC, A.z * _invC, A.w * _invC);
		}

		Vec4f& Vec4f::operator+=(const Vec4f& B)
		{
			this->x += B.x;
			this->y += B.y;
			this->z += B.z;
			this->w += B.w;
			return *this;
		}

		Vec4f& Vec4f::operator+=(float c)
		{
			this->x += c;
			this->y += c;
			this->z += c;
			this->w += c;
			return *this;
		}

		Vec4f& Vec4f::operator-=(const Vec4f& A)
		{
			this->x -= A.x;
			this->y -= A.y;
			this->z -= A.z;
			this->w -= A.w;
			return *this;
		}

		Vec4f& Vec4f::operator-=(float c)
		{
			this->x -= c;
			this->y -= c;
			this->z -= c;
			this->w -= c;
			return *this;
		}

		Vec4f& Vec4f::operator*=(float c)
		{
			this->x *= c;
			this->y *= c;
			this->z *= c;
			this->w *= c;
			return *this;
		}

		Vec4f& Vec4f::operator/=(float c)
		{
			this->x /= c;
			this->y /= c;
			this->z /= c;
			this->w /= c;
			return *this;
		}

		bool operator==(const Vec4f& A, const Vec4f& B)
		{
			return
				floatCmp(A.x, B.x) &&
				floatCmp(A.y, B.y) &&
				floatCmp(A.z, B.z) &&
				floatCmp(A.w, B.w);
		}

		bool operator!=(const Vec4f& A, const Vec4f& B)
		{
			return
				!floatCmp(A.x, B.x) ||
				!floatCmp(A.y, B.y) ||
				!floatCmp(A.z, B.z) ||
				!floatCmp(A.w, B.w);
		}

		std::ostream& operator<<(std::ostream& out, const Vec4f& A)
		{
			return
				out << std::fixed << std::setprecision(2) <<
				'(' << A.x << ", " << A.y << ", " << A.z <<
				", " << A.w << ')';
		}

		Vec2f Vec4f::xy(void) const { return Vec2f(x, y); }
		Vec2f Vec4f::xz(void) const { return Vec2f(x, z); }
		Vec2f Vec4f::xw(void) const { return Vec2f(x, w); }

		Vec2f Vec4f::yx(void) const { return Vec2f(y, x); }
		Vec2f Vec4f::yz(void) const { return Vec2f(y, z); }
		Vec2f Vec4f::yw(void) const { return Vec2f(y, w); }

		Vec2f Vec4f::zx(void) const { return Vec2f(z, x); }
		Vec2f Vec4f::zy(void) const { return Vec2f(z, y); }
		Vec2f Vec4f::zw(void) const { return Vec2f(z, w); }

		Vec2f Vec4f::wx(void) const { return Vec2f(w, x); }
		Vec2f Vec4f::wy(void) const { return Vec2f(w, y); }
		Vec2f Vec4f::wz(void) const { return Vec2f(w, z); }

		Vec3f Vec4f::xyz(void) const { return Vec3f(x, y, z); }
		Vec3f Vec4f::xzy(void) const { return Vec3f(x, z, y); }
		Vec3f Vec4f::xyw(void) const { return Vec3f(x, y, w); }
		Vec3f Vec4f::xwy(void) const { return Vec3f(x, w, y); }
		Vec3f Vec4f::xzw(void) const { return Vec3f(x, z, w); }
		Vec3f Vec4f::xwz(void) const { return Vec3f(x, w, z); }

		Vec3f Vec4f::yxz(void) const { return Vec3f(y, x, z); }
		Vec3f Vec4f::yzx(void) const { return Vec3f(y, z, x); }
		Vec3f Vec4f::yxw(void) const { return Vec3f(y, x, w); }
		Vec3f Vec4f::ywx(void) const { return Vec3f(y, w, x); }
		Vec3f Vec4f::yzw(void) const { return Vec3f(y, z, w); }
		Vec3f Vec4f::ywz(void) const { return Vec3f(y, w, z); }

		Vec3f Vec4f::zxy(void) const { return Vec3f(z, x, y); }
		Vec3f Vec4f::zyx(void) const { return Vec3f(z, y, x); }
		Vec3f Vec4f::zxw(void) const { return Vec3f(z, x, w); }
		Vec3f Vec4f::zwx(void) const { return Vec3f(z, w, x); }
		Vec3f Vec4f::zyw(void) const { return Vec3f(z, y, w); }
		Vec3f Vec4f::zwy(void) const { return Vec3f(z, w, y); }

		Vec3f Vec4f::wxy(void) const { return Vec3f(w, x, y); }
		Vec3f Vec4f::wyx(void) const { return Vec3f(w, y, x); }
		Vec3f Vec4f::wxz(void) const { return Vec3f(w, x, z); }
		Vec3f Vec4f::wzx(void) const { return Vec3f(w, z, x); }
		Vec3f Vec4f::wyz(void) const { return Vec3f(w, y, z); }
		Vec3f Vec4f::wzy(void) const { return Vec3f(w, z, y); }

		Vec4f& Vec4f::set(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
			return *this;
		}

		Vec4f& Vec4f::set(const Vec4f& A)
		{
			this->x = A.x;
			this->y = A.y;
			this->z = A.z;
			this->w = A.w;
			return *this;
		}

		Vec4f& Vec4f::setX(float x) { this->x = x; return *this; }
		Vec4f& Vec4f::setY(float y) { this->y = y; return *this; }
		Vec4f& Vec4f::setZ(float z) { this->z = z; return *this; }
		Vec4f& Vec4f::setW(float w) { this->w = w; return *this; }

		float Vec4f::max(void) const
		{
			return fmaxf(fmaxf(this->x, this->y), fmaxf(this->z, this->w));
		}

		float Vec4f::min(void) const
		{
			return fminf(fminf(this->x, this->y), fminf(this->z, this->w));
		}

		float Vec4f::length(void) const
		{
			return sqrt(
				this->x * this->x +
				this->y * this->y +
				this->z * this->z +
				this->w * this->w
			);
		}

		float Vec4f::sqrLength(void) const
		{
			return
				this->x * this->x +
				this->y * this->y +
				this->z * this->z +
				this->w * this->w;
		}

		float Vec4f::magnitude(void) const
		{
			return sqrt(
				this->x * this->x +
				this->y * this->y +
				this->z * this->z +
				this->w * this->w
			);
		}

		float Vec4f::sqrMagnitude(void) const
		{
			return
				this->x * this->x +
				this->y * this->y +
				this->z * this->z +
				this->w * this->w;
		}

		Vec4f Vec4f::normal(void) const
		{
			return *this / length();
		}

		Vec4f& Vec4f::normalize(void)
		{
			float _invLength = 1 / length();
			this->x *= _invLength;
			this->y *= _invLength;
			this->z *= _invLength;
			this->w *= _invLength;
			return *this;
		}

		Vec4f Vec4f::abs(void)
		{
			return Vec4f(
				std::abs(this->x),
				std::abs(this->y),
				std::abs(this->z),
				std::abs(this->w)
			);
		}

		float Vec4f::dot(const Vec4f& A) const
		{
			return
				this->x * A.x +
				this->y * A.y +
				this->z * A.z +
				this->w * A.w;
		}

		float Vec4f::dot(const Vec4f& A, const Vec4f& B)
		{
			return
				A.x * B.x +
				A.y * B.y +
				A.z * B.z +
				A.w * B.w;
		}

		Vec4f Vec4f::lerp(const Vec4f& from, const Vec4f& to, float p)
		{
			return from + (to - from) * p;
		}
	}// namespace Math
}// namespace gg
