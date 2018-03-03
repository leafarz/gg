#include "math/MathCommon.h"

namespace gg { namespace Math {
	float clamp(float val, float min, float max)
	{
		return val < min ? min : val > max ? max : val;
	}
} } // namespace gg
