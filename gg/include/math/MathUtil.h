#ifndef		GG_MATHUTIL_H
#define		GG_MATHUTIL_H
#pragma once
#include <math.h>
#include "math/Vec3f.h"

namespace gg { namespace Math {
		static const double PI = 3.14159265358979323846;

		static const double RAD_TO_DEG		= static_cast<double>(180.0 / PI);
		static const double DEG_TO_RAD		= static_cast<double>(PI / 180.0);
		static const double RAD_TO_DEG_HALF	= static_cast<double>(90.0 / PI);
		static const double DEG_TO_RAD_HALF	= static_cast<double>(PI / 360.0);

		/* Compares floats within FLT_EPSILON value */
		bool floatCmp(float a, float b, float threshold = FLT_EPSILON);

		/* Compares doubles within DBL_EPSILON value */
		bool doubleCmp(double a, double b, float threshold = DBL_EPSILON);

		/* Keeps value within [min, max].
		 * Default min is 0.
		 * Default max is 0.
		 */
		float clamp(float val, float min = 0, float max = 1);

		/* Lerp function. Returns the value ranging from
		 * [from] to [to] at percent [p].
		 * p: range is [0,1]
		 */
		float lerp(float from, float to, float p);

		/* Lerp function. Returns the value ranging from
		 * [from] to [to] at percent [p].
		 * p: range is [0,1]
		 */
		float lerp(double from, double to, double p);

		Vec3f bezier(Vec3f p0, Vec3f p1, Vec3f p2, float t);
}/*namespace Math*/ }// namespace gg
#endif