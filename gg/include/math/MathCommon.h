#ifndef		GG_MATHCOMMON_H
#define		GG_MATHCOMMON_H
#pragma once

namespace gg { namespace Math {
	/* Keeps val within min and max and returns the value. */
	float clamp(float val, float min, float max);
} } // namespace gg

#endif
