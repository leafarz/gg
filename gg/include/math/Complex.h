#ifndef		GG_COMPLEX_H
#define		GG_COMPLEX_H
#pragma once
#include <math.h>
#include <iomanip>

namespace gg { namespace math {
	struct Complex
	{
	public:
		/* The real of the complex. */
		double re;
		/* The imaginary of the complex. */
		double im;

		/* Creates complex with re,im as 0. */
		Complex();
		/* Creates complex with defined re,im values. */
		Complex(double re, double im);

		friend Complex operator+(const Complex& A, const Complex& B);
		Complex& operator-(void);
		friend Complex operator-(const Complex& A, const Complex& B);
		friend Complex operator*(const Complex& A, const Complex& B);
		friend Complex operator*(const Complex& A, double c);
		friend Complex operator*(double c, const Complex& A);
		friend Complex operator/(const Complex& A, double c);
		friend Complex operator/(const Complex& A, const Complex& c);

		Complex& operator+=(const Complex& A);
		Complex& operator+=(double c);
		Complex& operator-=(const Complex& A);
		Complex& operator-=(double c);

		friend bool operator==(const Complex& A, const Complex& B);
		friend bool operator!=(const Complex& A, const Complex& B);

		friend std::ostream& operator<<(std::ostream& out, const Complex& A);

		/* Sets defined re,im values and returns the result complex. */
		Complex& set(double re, double im);
		/* Sets defined re,im values and returns the result complex. */
		Complex& set(const Complex& A);

		/* Sets defined real and returns the result complex. */
		Complex& setReal(double re);
		/* Sets defined imaginary and returns the result complex. */
		Complex& setImag(double im);

		/* Returns the length of the complex.
		* (Same as getMagnitude function)
		*/
		double getLength(void) const;
		/* Returns the square of length of the complex.
		* (Same as getSqrMagnitude function)
		*/
		double getSqrLength(void) const;
		/* Returns the magnitude of the complex.
		* (Same as getLength function)
		*/
		double getMagnitude(void) const;
		/* Returns the square of magnitude of the complex.
		* (Same as getSqrLength function)
		*/
		double getSqrMagnitude(void) const;
	};// struct complex
}/*namespace math*/ }// namespace gg
#endif