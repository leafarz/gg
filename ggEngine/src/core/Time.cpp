#include "core/Time.h"

namespace GGEngine
{
	GLdouble Time::s_StartTime = 0;
	GLdouble Time::s_Delta = 0;
	GLdouble Time::s_FixedDelta = 0;

	GLdouble Time::getCurrentTime(void)
	{
		return glfwGetTime();
	}

	GLdouble Time::getGameTime(void)
	{
		return glfwGetTime() - s_StartTime;
	}

	GLdouble Time::getDeltaTime(void)
	{
		return s_Delta;
	}
	GLdouble Time::getFixedDeltaTime(void)
	{
		return s_FixedDelta;
	}
} // namespace GGEngine
