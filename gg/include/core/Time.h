#ifndef		GG_TIME_H
#define		GG_TIME_H
#pragma once

#include "GLFW/glfw3.h"

namespace gg
{
	class Application;
	class Time
	{
	private:
		friend class Application;

	public:
		Time(void) = delete;
		~Time(void) = delete;

		static double getCurrentTime(void);
		static double getGameTime(void);
		static double getDeltaTime(void);
		static double getFixedDeltaTime(void);

	private:
		static double s_StartTime;
		static double s_Delta;
		static double s_FixedDelta;
	}; // class Time
} // namespace gg

#endif
