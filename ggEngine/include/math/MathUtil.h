#ifndef		GGENGINE_MATHUTIL_H
#define		GGENGINE_MATHUTIL_H
#pragma once
#include <math.h>
#include "math/Vec3f.h"

namespace GGEngine
{
	namespace Math
	{
		static const double PI = 3.14159265358979323846;

		static const float RAD_TO_DEG		= static_cast<float>(180.0f / PI);
		static const float DEG_TO_RAD		= static_cast<float>(PI / 180.0f);
		static const float RAD_TO_DEG_HALF	= static_cast<float>(90.0f / PI);
		static const float DEG_TO_RAD_HALF	= static_cast<float>(PI / 360.0f);

		/* Compares floats within FLT_EPSILON value*/
		bool floatCmp(float a, float b, float threshold = FLT_EPSILON);

		/* Compares doubles within DBL_EPSILON value*/
		bool doubleCmp(double a, double b, float threshold = DBL_EPSILON);

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
	}// namespace Math
}// namespace GGEngine
#endif