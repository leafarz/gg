#ifndef		GG_TIME_H
#define		GG_TIME_H
#pragma once

#include "GLFW/glfw3.h"

namespace gg
{
	class Application;
	class Time
	{
		friend class Application;
	public:
		Time(void) = delete;
		~Time(void) = delete;

		static GLdouble getCurrentTime(void);
		static GLdouble getGameTime(void);
		static GLdouble getDeltaTime(void);
		static GLdouble getFixedDeltaTime(void);

	private:
		static GLdouble s_StartTime;
		static GLdouble s_Delta;
		static GLdouble s_FixedDelta;
	}; // class Time
} // namespace gg

#endif
