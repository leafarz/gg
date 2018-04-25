#include "math/Mat4f.h"

#include <math.h>
#include <iostream>
#include "math/MathUtil.h"
#include "math/Vec3f.h"
#include "math/Quaternion.h"

namespace gg { namespace math {
	const Mat4f Mat4f::identity = Mat4f(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);

	Mat4f::Mat4f(void)
		: elements{ 1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1 }
	{ }

	Mat4f::Mat4f(float c)
		: elements{	c,0,0,0,
				0,c,0,0,
				0,0,c,0,
				0,0,0,c }
	{ }

	Mat4f::Mat4f(
		float c00, float c01, float c02, float c03,
		float c10, float c11, float c12, float c13,
		float c20, float c21, float c22, float c23,
		float c30, float c31, float c32, float c33
	)
		: elements{ c00, c01, c02, c03,
				c10, c11, c12, c13,
				c20, c21, c22, c23,
				c30, c31, c32, c33 }
	{ }

	Mat4f Mat4f::translationMatrix(const Vec3f& translation)
	{
		return Mat4f(
			1, 0, 0, translation.x,
			0, 1, 0, translation.y,
			0, 0, 1, translation.z,
			0, 0, 0, 1
		);
	}

	Mat4f Mat4f::translationMatrix(float x, float y, float z)
	{
		return Mat4f(
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1
		);
	}

	Mat4f Mat4f::rotationMatrixr(const Vec3f& eulerAngles)
	{
		const float _x = eulerAngles.x;
		const float _y = eulerAngles.y;
		const float _z = eulerAngles.z;

		Mat4f _rx = Mat4f(
			1,	0,			0,			0,
			0,	cosf(_x),	-sinf(_x),	0,
			0,	sinf(_x),	 cosf(_x),	0,
			0,	0,			0,			1
		);

		Mat4f _ry = Mat4f(
			cosf(_y),	0,	-sinf(_y),	0,
			0,			1,	0,			0,
			sinf(_y),	0,	 cosf(_y),	0,
			0,			0,	0,			1
		);

		Mat4f _rz = Mat4f(
			cosf(_z),	-sinf(_z),	0,	0,
			sinf(_z),	 cosf(_z),	0,	0,
			0,			0,			1,	0,
			0,			0,			0,	1
		);

		return _rz*_ry*_rx;
	}

	Mat4f Mat4f::rotationMatrixd(const Vec3f& eulerAngles)
	{
		const float _x = eulerAngles.x * static_cast<float>(DEG_TO_RAD);
		const float _y = eulerAngles.y * static_cast<float>(DEG_TO_RAD);
		const float _z = eulerAngles.z * static_cast<float>(DEG_TO_RAD);

		Mat4f _rx = Mat4f(
			1,	0,			0,			0,
			0,	cosf(_x),	-sinf(_x),	0,
			0,	sinf(_x),	 cosf(_x),	0,
			0,	0,			0,			1
		);

		Mat4f _ry = Mat4f(
			cosf(_y),	0,	-sinf(_y),	0,
			0,			1,	0,			0,
			sinf(_y),	0,	 cosf(_y),	0,
			0,			0,	0,			1
		);

		Mat4f _rz = Mat4f(
			cosf(_z),	-sinf(_z),	0,	0,
			sinf(_z),	 cosf(_z),	0,	0,
			0,			0,			1,	0,
			0,			0,			0,	1
		);

		return _rz*_ry*_rx;
	}

	Mat4f Mat4f::rotationMatrix(float x, float y, float z)
	{
		x *= static_cast<float>(DEG_TO_RAD);
		y *= static_cast<float>(DEG_TO_RAD);
		z *= static_cast<float>(DEG_TO_RAD);

		Mat4f _rx = Mat4f(
			1,	0,			0,			0,
			0,	cosf(x),	-sinf(x),	0,
			0,	sinf(x),	 cosf(x),	0,
			0,	0,			0,			1
		);

		Mat4f _ry = Mat4f(
			cosf(y),	0,	-sinf(y),	0,
			0,			1,	0,			0,
			sinf(y),	0,	 cosf(y),	0,
			0,			0,	0,			1
		);

		Mat4f _rz = Mat4f(
			cosf(z),	-sinf(z),	0,	0,
			sinf(z),	 cosf(z),	0,	0,
			0,			0,			1,	0,
			0,			0,			0,	1
		);

		return _rz*_ry*_rx;
	}

	Mat4f Mat4f::rotationMatrix(const Vec3f& forward, const Vec3f& up)
	{
		Vec3f _f = forward;
		Vec3f _r = up.cross(forward);
		Vec3f _u = up;

		return Mat4f(
			_r.x,	_r.y,	_r.z,	0,
			_u.x,	_u.y,	_u.z,	0,
			_f.x,	_f.y,	_f.z,	0,
			0,		0,		0,		1
		);
	}

	Mat4f Mat4f::rotationMatrix(const Vec3f& forward, const Vec3f& up, const Vec3f& right)
	{
		Vec3f _f = forward;
		Vec3f _r = right;
		Vec3f _u = up;

		return Mat4f(
			right.x,	right.y,	right.z,	0,
			up.x,		up.y,		up.z,		0,
			forward.x,	forward.y,	forward.z,	0,
			0,			0,			0,			1
		);
	}

	Mat4f Mat4f::rotationMatrix(const Quaternion& rot)
	{
		return Mat4f::rotationMatrix(
			Vec3f(
				2.0f * (rot.x * rot.z - rot.w * rot.y),
				2.0f * (rot.y * rot.z + rot.w * rot.x),
				1.0f - 2.0f * (rot.x * rot.x + rot.y * rot.y)
			),
			Vec3f(
				2.0f * (rot.x * rot.y + rot.w * rot.z),
				1.0f - 2.0f * (rot.x * rot.x + rot.z * rot.z),
				2.0f * (rot.y * rot.z - rot.w * rot.x)
			),
			Vec3f(
				1.0f - 2.0f * (rot.y * rot.y + rot.z * rot.z),
				2.0f * (rot.x * rot.y - rot.w * rot.z),
				2.0f * (rot.x * rot.z + rot.w * rot.y)
			)
		);
	}

	Mat4f Mat4f::perspectiveMatrix(float fovDeg, float aspectRatio, float zNear, float zFar)
	{
		zNear = clamp(zNear, 0.1f, zFar - 0.1f);

		float _tanHalfFOV = tan(fovDeg * static_cast<float>(DEG_TO_RAD_HALF));
		float _range = zNear - zFar;

		return Mat4f(
			1 / (aspectRatio * _tanHalfFOV),	0,					0,								0,
			0,									1 / _tanHalfFOV,	0,								0,
			0,									0,					-(zFar + zNear) / _range,		2 * zNear * zFar / _range,
			0,									0,					1,								0
		);
	}

	Mat4f Mat4f::orthographicMatrix(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		zNear = clamp(zNear, zNear, zFar - 0.1f);

		float _width = right - left;
		float _height = top - bottom;
		float _depth = zNear - zFar;

		return Mat4f(
			2 / _width,		0,				 0,				-(right + left) / _width,
			0,				2 / _height,	 0,				-(top + bottom) / _height,
			0,				0,				-2 / _depth,	 (zFar + zNear) / _depth,
			0,				0,				 0,				 1
		);
	}

	Mat4f Mat4f::scaleMatrix(float c)
	{
		return Mat4f(
			c, 0, 0, 0,
			0, c, 0, 0,
			0, 0, c, 0,
			0, 0, 0, 1
		);
	}

	Mat4f Mat4f::scaleMatrix(const Vec3f& vec)
	{
		return Mat4f(
			vec.x,	0,		0,		0,
			0,		vec.y,	0,		0,
			0,		0,		vec.z,	0,
			0,		0,		0,		1
		);
	}

	Mat4f Mat4f::scaleMatrix(float x, float y, float z)
	{
		return Mat4f(
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1
		);
	}

	float& Mat4f::operator[] (int idx)
	{
		return elements[idx];
	}

	Mat4f operator+(const Mat4f& A, const Mat4f& B)
	{
		Mat4f _mat;
		for (int i = -1; ++i < 16; )
		{
			_mat.set(i, A.elements[i] + B.elements[i]);
		}
		return _mat;
	}

	Mat4f Mat4f::operator-(void)
	{
		for (int i = -1; ++i < 16; )
		{
			this->elements[i] = -this->elements[i];
		}
		return *this;
	}

	Mat4f operator-(const Mat4f& A, const Mat4f& B)
	{
		return Mat4f(
			A.elements[0] - B.elements[0],		A.elements[1] - B.elements[1],		A.elements[2] - B.elements[2],		A.elements[3] - B.elements[3],
			A.elements[4] - B.elements[4],		A.elements[5] - B.elements[5],		A.elements[6] - B.elements[6],		A.elements[7] - B.elements[7],
			A.elements[8] - B.elements[8],		A.elements[9] - B.elements[9],		A.elements[10] - B.elements[10],	A.elements[11] - B.elements[11],
			A.elements[12] - B.elements[12],	A.elements[13] - B.elements[13],	A.elements[14] - B.elements[14],	A.elements[15] - B.elements[15]
		);
	}

	Mat4f operator*(const Mat4f& A, float c)
	{
		return Mat4f(
			A.elements[0] * c,	A.elements[1] * c,	A.elements[2] * c,	A.elements[3] * c,
			A.elements[4] * c,	A.elements[5] * c,	A.elements[6] * c,	A.elements[7] * c,
			A.elements[8] * c,	A.elements[9] * c,	A.elements[10] * c,	A.elements[11] * c,
			A.elements[12] * c,	A.elements[13] * c,	A.elements[14] * c,	A.elements[15] * c
		);
	}

	Mat4f operator*(float c, const Mat4f& A)
	{
		return Mat4f(
			c * A.elements[0] ,	c * A.elements[1],	c * A.elements[2],	c * A.elements[3],
			c * A.elements[4] ,	c * A.elements[5],	c * A.elements[6],	c * A.elements[7],
			c * A.elements[8] ,	c * A.elements[9],	c * A.elements[10],	c * A.elements[11],
			c * A.elements[12],	c * A.elements[13],	c * A.elements[14],	c * A.elements[15]
		);
	}

	Mat4f operator*(const Mat4f& A, const Mat4f& B)
	{
		return Mat4f(
			A.elements[0] * B.elements[0] + A.elements[1] * B.elements[4] + A.elements[2] * B.elements[8] + A.elements[3] * B.elements[12],
			A.elements[0] * B.elements[1] + A.elements[1] * B.elements[5] + A.elements[2] * B.elements[9] + A.elements[3] * B.elements[13],
			A.elements[0] * B.elements[2] + A.elements[1] * B.elements[6] + A.elements[2] * B.elements[10] + A.elements[3] * B.elements[14],
			A.elements[0] * B.elements[3] + A.elements[1] * B.elements[7] + A.elements[2] * B.elements[11] + A.elements[3] * B.elements[15],

			A.elements[4] * B.elements[0] + A.elements[5] * B.elements[4] + A.elements[6] * B.elements[8] + A.elements[7] * B.elements[12],
			A.elements[4] * B.elements[1] + A.elements[5] * B.elements[5] + A.elements[6] * B.elements[9] + A.elements[7] * B.elements[13],
			A.elements[4] * B.elements[2] + A.elements[5] * B.elements[6] + A.elements[6] * B.elements[10] + A.elements[7] * B.elements[14],
			A.elements[4] * B.elements[3] + A.elements[5] * B.elements[7] + A.elements[6] * B.elements[11] + A.elements[7] * B.elements[15],

			A.elements[8] * B.elements[0] + A.elements[9] * B.elements[4] + A.elements[10] * B.elements[8] + A.elements[11] * B.elements[12],
			A.elements[8] * B.elements[1] + A.elements[9] * B.elements[5] + A.elements[10] * B.elements[9] + A.elements[11] * B.elements[13],
			A.elements[8] * B.elements[2] + A.elements[9] * B.elements[6] + A.elements[10] * B.elements[10] + A.elements[11] * B.elements[14],
			A.elements[8] * B.elements[3] + A.elements[9] * B.elements[7] + A.elements[10] * B.elements[11] + A.elements[11] * B.elements[15],

			A.elements[12] * B.elements[0] + A.elements[13] * B.elements[4] + A.elements[14] * B.elements[8] + A.elements[15] * B.elements[12],
			A.elements[12] * B.elements[1] + A.elements[13] * B.elements[5] + A.elements[14] * B.elements[9] + A.elements[15] * B.elements[13],
			A.elements[12] * B.elements[2] + A.elements[13] * B.elements[6] + A.elements[14] * B.elements[10] + A.elements[15] * B.elements[14],
			A.elements[12] * B.elements[3] + A.elements[13] * B.elements[7] + A.elements[14] * B.elements[11] + A.elements[15] * B.elements[15]
		);
	}

	Vec4f operator*(const Mat4f& A, const Vec4f& B)
	{
		return Vec4f(
			A.elements[0] * B.x + A.elements[1] * B.y + A.elements[2] * B.z + A.elements[3] * B.w,
			A.elements[4] * B.x + A.elements[5] * B.y + A.elements[6] * B.z + A.elements[7] * B.w,
			A.elements[8] * B.x + A.elements[9] * B.y + A.elements[10] * B.z + A.elements[11] * B.w,
			A.elements[12] * B.x + A.elements[13] * B.y + A.elements[14] * B.z + A.elements[15] * B.w
		);
	}

	Mat4f operator/(const Mat4f& A, float c)
	{
		const float _invC = 1 / c;
		return Mat4f(
			A.elements[0] * c,	A.elements[1] * c,	A.elements[2] * c,	A.elements[3] * c,
			A.elements[4] * c,	A.elements[5] * c,	A.elements[6] * c,	A.elements[7] * c,
			A.elements[8] * c,	A.elements[9] * c,	A.elements[10] * c,	A.elements[11] * c,
			A.elements[12] * c,	A.elements[13] * c,	A.elements[14] * c,	A.elements[15] * c
		);
	}

	Mat4f& Mat4f::operator+=(const Mat4f& A)
	{
		for (int i = -1; ++i < 16; )
		{
			this->elements[i] += A.elements[i];
		}
		return *this;
	}

	Mat4f& Mat4f::operator+=(float c)
	{
		for (int i = -1; ++i < 16; )
		{
			this->elements[i] += c;
		}
		return *this;
	}

	Mat4f& Mat4f::operator-=(const Mat4f& A)
	{
		for (int i = -1; ++i < 16; )
		{
			this->elements[i] -= A.elements[i];
		}
		return *this;
	}

	Mat4f& Mat4f::operator-=(float c)
	{
		for (int i = -1; ++i < 16; )
		{
			this->elements[i] -= c;
		}
		return *this;
	}

	Mat4f& Mat4f::operator*=(const Mat4f& A)
	{
		for (int i = -1; ++i < 4; )
		{
			int _idx = i * 4;

			float _val0 =	this->elements[_idx]     * A.elements[0] +
							this->elements[_idx + 1] * A.elements[4] +
							this->elements[_idx + 2] * A.elements[8] +
							this->elements[_idx + 3] * A.elements[12];

			float _val1 =	this->elements[_idx]     * A.elements[1] +
							this->elements[_idx + 1] * A.elements[5] +
							this->elements[_idx + 2] * A.elements[9] +
							this->elements[_idx + 3] * A.elements[13];

			float _val2 =	this->elements[_idx]     * A.elements[2] +
							this->elements[_idx + 1] * A.elements[6] +
							this->elements[_idx + 2] * A.elements[10] +
							this->elements[_idx + 3] * A.elements[14];

			float _val3 =	this->elements[_idx]     * A.elements[3] +
							this->elements[_idx + 1] * A.elements[7] +
							this->elements[_idx + 2] * A.elements[11] +
							this->elements[_idx + 3] * A.elements[15];

			this->elements[_idx] = _val0;
			this->elements[_idx + 1] = _val1;
			this->elements[_idx + 2] = _val2;
			this->elements[_idx + 3] = _val3;
		}

		return *this;
	}

	Mat4f& Mat4f::operator*=(float c)
	{
		for (int i = -1; ++i < 16; )
		{
			this->elements[i] *= c;
		}
		return *this;
	}

	Mat4f& Mat4f::operator/=(float c)
	{
		const float _invC = 1 / c;
		for (int i = -1; ++i < 16; )
		{
			this->elements[i] *= _invC;
		}
		return *this;
	}

	std::ostream& operator<<(std::ostream& out, const Mat4f& A)
	{
		return
			out << std::fixed << std::setprecision(2) <<
			"\n| " << A.elements[0]  << ' ' << A.elements[1]  << ' ' << A.elements[2]  << ' ' << A.elements[3]  << " |" <<
			"\n| " << A.elements[4]  << ' ' << A.elements[5]  << ' ' << A.elements[6]  << ' ' << A.elements[7]  << " |" <<
			"\n| " << A.elements[8]  << ' ' << A.elements[9]  << ' ' << A.elements[10] << ' ' << A.elements[11] << " |" <<
			"\n| " << A.elements[12] << ' ' << A.elements[13] << ' ' << A.elements[14] << ' ' << A.elements[15] << " |" <<
			std::endl;
	}

	const float* Mat4f::getMatrix(void) const
	{
		return this->elements;
	}

	float Mat4f::get(int idx) const
	{
		return this->elements[idx];
	}

	float Mat4f::get(int m, int n) const
	{
		return this->elements[m * 4 + n];
	}

	Mat4f& Mat4f::set(int idx, float c)
	{
		this->elements[idx] = c;
		return *this;
	}

	Mat4f& Mat4f::set(int m, int n, float c)
	{
		this->elements[m * 4 + n] = c;
		return *this;
	}

	Mat4f& Mat4f::set(
		float c00, float c01, float c02, float c03,
		float c10, float c11, float c12, float c13,
		float c20, float c21, float c22, float c23,
		float c30, float c31, float c32, float c33
	)
	{
		this->elements[0]  = c00;	this->elements[1] =  c01;	this->elements[2]  = c02;	this->elements[3]  = c03;
		this->elements[4]  = c10;	this->elements[5] =  c11;	this->elements[6]  = c12;	this->elements[7]  = c13;
		this->elements[8]  = c20;	this->elements[9] =  c21;	this->elements[10] = c22;	this->elements[11] = c23;
		this->elements[12] = c30;	this->elements[13] = c31;	this->elements[14] = c32;	this->elements[15] = c33;
		return *this;
	}

	Mat4f& Mat4f::setDiagonal(float c)
	{
		this->elements[0] = c;
		this->elements[5] = c;
		this->elements[10] = c;
		this->elements[13] = c;
		return *this;
	}

	Mat4f Mat4f::getTranspose(void)
	{
		Mat4f _m = Mat4f(*this);
		for (int i = -1; ++i < 3; )
		{
			for (int j = i; ++j < 4; )
			{
				short _index1 = i * 4 + j;
				short _index2 = j * 4 + i;
				float _dummy = _m.elements[_index1];
				_m.set(_index1, _m.elements[_index2]);
				_m.set(_index2, _dummy);
			}
		}
		return _m;
	}

	Mat4f& Mat4f::transpose(void)
	{
		for (int i = -1; ++i < 3; )
		{
			for (int j = i; ++j < 4; )
			{
				short _index1 = i * 4 + j;
				short _index2 = j * 4 + i;
				float _dummy = elements[_index1];
				elements[_index1] = elements[_index2];
				elements[_index2] = _dummy;
			}
		}
		return *this;
	}

	Mat4f Mat4f::getTranspose(const Mat4f& M)
	{
		Mat4f _m = Mat4f(M);
		for (int i = -1; ++i < 3; )
		{
			for (int j = i; ++j < 4; )
			{
				short _index1 = i * 4 + j;
				short _index2 = j * 4 + i;
				float _dummy = _m.elements[_index1];
				_m.set(_index1, _m.elements[_index2]);
				_m.set(_index2, _dummy);
			}
		}
		return _m;
	}

	Vec3f Mat4f::getTransform(Vec3f A)
	{
		return Vec3f(
			this->elements[0] * A.x + this->elements[1] * A.y + this->elements[2] * A.z + this->elements[3],
			this->elements[4] * A.x + this->elements[5] * A.y + this->elements[6] * A.z + this->elements[7],
			this->elements[8] * A.x + this->elements[9] * A.y + this->elements[10] * A.z + this->elements[11]
		);
	}
}/*namespace math*/ }// namespace gg
