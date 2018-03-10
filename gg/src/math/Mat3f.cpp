#include "math/Mat3f.h"

#include <math.h>
#include <iostream>
#include "math/MathUtil.h"

namespace gg { namespace Math {
	const Mat3f Mat3f::identity = Mat3f(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	);

	Mat3f::Mat3f(void)
		: elements{ 1,0,0,
					0,1,0,
					0,0,1 }
	{ }

	Mat3f::Mat3f(float c)
		: elements{	c,0,0,
					0,c,0,
					0,0,c }
	{ }

	Mat3f::Mat3f(
		float c00, float c01, float c02,
		float c10, float c11, float c12,
		float c20, float c21, float c22
	)
		: elements{ c00, c01, c02,
					c10, c11, c12,
					c20, c21, c22 }
	{ }

	float& Mat3f::operator[] (int idx)
	{
		return elements[idx];
	}

	Mat3f operator+(const Mat3f& A, const Mat3f& B)
	{
		Mat3f _mat;
		for (int i = -1; ++i < 9; )
		{
			_mat.set(i, A.elements[i] + B.elements[i]);
		}
		return _mat;
	}

	Mat3f Mat3f::operator-(void)
	{
		for (int i = -1; ++i < 9; )
		{
			this->elements[i] = -this->elements[i];
		}
		return *this;
	}

	Mat3f operator-(const Mat3f& A, const Mat3f& B)
	{
		return Mat3f(
			A.elements[0] - B.elements[0],		A.elements[1] - B.elements[1],		A.elements[2] - B.elements[2],
			A.elements[3] - B.elements[3],		A.elements[4] - B.elements[4],		A.elements[5] - B.elements[5],
			A.elements[6] - B.elements[6],		A.elements[7] - B.elements[7],		A.elements[8] - B.elements[8]
		);
	}

	Mat3f operator*(const Mat3f& A, float c)
	{
		return Mat3f(
			A.elements[0] * c,		A.elements[1] * c,		A.elements[2] * c,
			A.elements[3] * c,		A.elements[4] * c,		A.elements[5] * c,
			A.elements[6] * c,		A.elements[7] * c,		A.elements[8] * c
		);
	}

	Mat3f operator*(float c, const Mat3f& A)
	{
		return Mat3f(
			c * A.elements[0], c * A.elements[1], c * A.elements[2],
			c * A.elements[3], c * A.elements[4], c * A.elements[5],
			c * A.elements[6], c * A.elements[7], c * A.elements[8]
		);
	}

	Mat3f operator*(const Mat3f& A, const Mat3f& B)
	{
		return Mat3f(
			A.elements[0] * B.elements[0] + A.elements[1] * B.elements[3] + A.elements[2] * B.elements[6],
			A.elements[0] * B.elements[1] + A.elements[1] * B.elements[4] + A.elements[2] * B.elements[7],
			A.elements[0] * B.elements[2] + A.elements[1] * B.elements[5] + A.elements[2] * B.elements[8],

			A.elements[4] * B.elements[0] + A.elements[5] * B.elements[3] + A.elements[6] * B.elements[6],
			A.elements[4] * B.elements[1] + A.elements[5] * B.elements[4] + A.elements[6] * B.elements[7],
			A.elements[4] * B.elements[2] + A.elements[5] * B.elements[5] + A.elements[6] * B.elements[8],

			A.elements[8] * B.elements[0] + A.elements[9] * B.elements[3] + A.elements[10] * B.elements[6],
			A.elements[8] * B.elements[1] + A.elements[9] * B.elements[4] + A.elements[10] * B.elements[7],
			A.elements[8] * B.elements[2] + A.elements[9] * B.elements[5] + A.elements[10] * B.elements[8]
		);
	}

	Vec3f operator*(const Mat3f& A, const Vec3f& B)
	{
		return Vec3f(
			A.elements[0] * B.x + A.elements[1] * B.y + A.elements[2] * B.z,
			A.elements[3] * B.x + A.elements[4] * B.y + A.elements[5] * B.z,
			A.elements[6] * B.x + A.elements[7] * B.y + A.elements[8] * B.z
		);
	}

	Mat3f operator/(const Mat3f& A, float c)
	{
		const float _invC = 1 / c;
		return Mat3f(
			A.elements[0] * c,	A.elements[1] * c,	A.elements[2] * c,
			A.elements[3] * c,	A.elements[4] * c,	A.elements[5] * c,
			A.elements[6] * c,	A.elements[7] * c,	A.elements[8] * c
		);
	}

	Mat3f& Mat3f::operator+=(const Mat3f& A)
	{
		for (int i = -1; ++i < 9; )
		{
			this->elements[i] += A.elements[i];
		}
		return *this;
	}

	Mat3f& Mat3f::operator+=(float c)
	{
		for (int i = -1; ++i < 9; )
		{
			this->elements[i] += c;
		}
		return *this;
	}

	Mat3f& Mat3f::operator-=(const Mat3f& A)
	{
		for (int i = -1; ++i < 9; )
		{
			this->elements[i] -= A.elements[i];
		}
		return *this;
	}

	Mat3f& Mat3f::operator-=(float c)
	{
		for (int i = -1; ++i < 9; )
		{
			this->elements[i] -= c;
		}
		return *this;
	}

	Mat3f& Mat3f::operator*=(const Mat3f& A)
	{
		for (int i = -1; ++i < 3; )
		{
			int _idx = i * 3;

			float _val0 =	this->elements[_idx]     * A.elements[0] +
							this->elements[_idx + 1] * A.elements[3] +
							this->elements[_idx + 2] * A.elements[6];

			float _val1 =	this->elements[_idx]     * A.elements[1] +
							this->elements[_idx + 1] * A.elements[4] +
							this->elements[_idx + 2] * A.elements[7];

			float _val2 =	this->elements[_idx]     * A.elements[2] +
							this->elements[_idx + 1] * A.elements[5] +
							this->elements[_idx + 2] * A.elements[8];

			this->elements[_idx] = _val0;
			this->elements[_idx + 1] = _val1;
			this->elements[_idx + 2] = _val2;
		}

		return *this;
	}

	Mat3f& Mat3f::operator*=(float c)
	{
		for (int i = -1; ++i < 9; )
		{
			this->elements[i] *= c;
		}
		return *this;
	}

	Mat3f& Mat3f::operator/=(float c)
	{
		const float _invC = 1 / c;
		for (int i = -1; ++i < 9; )
		{
			this->elements[i] *= _invC;
		}
		return *this;
	}

	std::ostream& operator<<(std::ostream& out, const Mat3f& A)
	{
		return
			out << std::fixed << std::setprecision(2) <<
			"\n| " << A.elements[0]  << ' ' << A.elements[1]  << ' ' << A.elements[2]  << " |" <<
			"\n| " << A.elements[3]  << ' ' << A.elements[4]  << ' ' << A.elements[5]  << " |" <<
			"\n| " << A.elements[6]  << ' ' << A.elements[7]  << ' ' << A.elements[8]  << " |" <<
			std::endl;
	}

	const float* Mat3f::getMatrix(void) const
	{
		return this->elements;
	}

	float Mat3f::get(int idx) const
	{
		return this->elements[idx];
	}

	float Mat3f::get(int m, int n) const
	{
		return this->elements[m * 3 + n];
	}

	Mat3f& Mat3f::set(int idx, float c)
	{
		this->elements[idx] = c;
		return *this;
	}

	Mat3f& Mat3f::set(int m, int n, float c)
	{
		this->elements[m * 3 + n] = c;
		return *this;
	}

	Mat3f& Mat3f::setDiagonal(float c)
	{
		this->elements[0] = c;
		this->elements[4] = c;
		this->elements[8] = c;
		return *this;
	}

	Mat3f Mat3f::getTranspose(void)
	{
		Mat3f _m = Mat3f(*this);
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

	Mat3f& Mat3f::transpose(void)
	{
		for (int i = -1; ++i < 2; )
		{
			for (int j = i; ++j < 3; )
			{
				short _index1 = i * 3 + j;
				short _index2 = j * 3 + i;
				float _dummy = elements[_index1];
				elements[_index1] = elements[_index2];
				elements[_index2] = _dummy;
			}
		}
		return *this;
	}

	Mat3f Mat3f::getTranspose(const Mat3f& M)
	{
		Mat3f _m = Mat3f(M);
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
}/*namespace Math*/ }// namespace gg
