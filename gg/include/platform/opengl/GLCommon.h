#ifndef		GG_GLCOMMON_H
#define		GG_GLCOMMON_H
#pragma once

#include "GL/glew.h"
#include "platform/opengl/GLError.h"

#ifdef _DEBUG
	/* Put OpenGL command as parameter to log if there's
	 * an error with the call.
	 */
	#define GL(x) glClearError();\
		x;\
		ASSERT(glLog(#x, __FILE__, __LINE__))
#else
	/* Does nothing.
	 * This does not affect performance even if GL is used.
	 */
	#define GL(x) x
#endif

#endif
