#include "core/Time.h"

namespace gg
{
	double Time::s_StartTime = 0;
	double Time::s_Delta = 0;
	double Time::s_FixedDelta = 0;

	double Time::getCurrentTime(void)
	{
		return glfwGetTime();
	}

	double Time::getGameTime(void)
	{
		return glfwGetTime() - s_StartTime;
	}

	double Time::getDeltaTime(void)
	{
		return s_Delta;
	}
	double Time::getFixedDeltaTime(void)
	{
		return s_FixedDelta;
	}
} // namespace gg
