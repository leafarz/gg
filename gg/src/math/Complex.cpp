#include "math/Complex.h"

#include "Math/MathUtil.h"

namespace gg { namespace math {
	Complex::Complex()
		: re(0), im(0)
	{ }

	Complex::Complex(double re, double im)
		: re(re), im(im)
	{ }

	Complex operator+(const Complex& A, const Complex& B)
	{
		return Complex(A.re + B.re, A.im + B.im);
	}

	Complex& Complex::operator-(void)
	{
		this->re = -this->re;
		this->im = -this->im;
		return *this;
	}

	Complex operator-(const Complex& A, const Complex& B)
	{
		return Complex(A.re - B.re, A.im - B.im);
	}

	Complex operator*(const Complex& A, const Complex& B)
	{
		return Complex(
			A.re * B.re - A.im * B.im,
			A.re * B.im + B.re * A.im
		);
	}

	Complex operator*(const Complex& A, double c)
	{
		return Complex(A.re * c, A.im * c);
	}

	Complex operator*(double c, const Complex& A)
	{
		return Complex(A.re * c, A.im * c);
	}

	Complex operator/(const Complex& A, double c)
	{
		return Complex(A.re / c, A.im / c);
	}

	Complex operator/(const Complex& A, const Complex& B)
	{
		return Complex(
			(A.re * B.re + A.im * B.im) / (B.re * B.re + B.im * B.im),
			(B.re * A.im - A.re * B.im) / (B.re * B.re + B.im * B.im)
		);
	}

	Complex& Complex::operator+=(const Complex& A)
	{
		this->re += A.re;
		this->im += A.im;
		return *this;
	}

	Complex& Complex::operator+=(double c)
	{
		this->re += c;
		this->im += c;
		return *this;
	}

	Complex& Complex::operator-=(const Complex& A)
	{
		this->re -= A.re;
		this->im -= A.im;
		return *this;
	}

	Complex& Complex::operator-=(double c)
	{
		this->re -= c;
		this->im -= c;
		return *this;
	}

	bool operator==(const Complex& A, const Complex& B)
	{
		return doubleCmp(A.re, B.re) && doubleCmp(A.im, B.im);
	}

	bool operator!=(const Complex& A, const Complex& B)
	{
		return !doubleCmp(A.re, B.re) || !doubleCmp(A.im, B.im);
	}

	std::ostream& operator<<(std::ostream& out, const Complex& A)
	{
		return
			out << std::fixed << std::setprecision(7) <<
			"(" << A.re << "," << A.im << ")";
	}

	Complex& Complex::set(double re, double im)
	{
		this->re = re;
		this->im = im;
		return *this;
	}

	Complex& Complex::set(const Complex& A)
	{
		this->re = A.re;
		this->im = A.im;
		return *this;
	}

	Complex& Complex::setReal(double re)
	{
		this->re = re;
		return *this;
	}

	Complex& Complex::setImag(double im)
	{
		this->im = im;
		return *this;
	}

	double Complex::getLength(void) const
	{
		return sqrt(this->re * this->re + this->im * this->im);
	}

	double Complex::getSqrLength(void) const
	{
		return this->re * this->re + this->im * this->im;
	}

	double Complex::getMagnitude(void) const
	{
		return sqrt(this->re * this->re + this->im * this->im);
	}
	double Complex::getSqrMagnitude(void) const
	{
		return this->re * this->re + this->im * this->im;
	}
}/*namespace math*/ }// namespace gg
