#include "math/MathUtil.h"
#include <limits>

namespace gg { namespace Math {
	bool floatCmp(float a, float b, float threshold)
	{
		return abs(a - b) < threshold;
	}

	bool doubleCmp(double a, double b, float threshold)
	{
		return abs(a - b) < threshold;
	}

	float clamp(float val, float min, float max)
	{
		return (val < min) ? min : (val > max) ? max : val;
	}

	float lerp(float from, float to, float p)
	{
		return from + (to - from) * p;
	}

	float lerp(double from, double to, double p)
	{
		return (float)(from + (to - from) * p);
	}

	Vec3f bezier(Vec3f p0, Vec3f p1, Vec3f p2, float t)
	{
		float _poly1 = (1 - t) * (1 - t);
		float _poly2 = (2 * t) - (2 * t * t);
		float _poly3 = (t * t);

		return Vec3f(
			(_poly1 * p0.x) + (_poly2 * p1.x) + (_poly3 * p2.x),
			(_poly1 * p0.y) + (_poly2 * p1.y) + (_poly3 * p2.y),
			(_poly1 * p0.z) + (_poly2 * p1.z) + (_poly3 * p2.z)
		);
	}
}/*namespace Math*/ }// namespace gg
