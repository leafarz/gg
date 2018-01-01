#ifndef		GG_GLCOMMON_H
#define		GG_GLCOMMON_H
#pragma once

#include "platform/opengl/GLError.h"

#ifdef _DEBUG
	#define GL(x) glClearError();\
		x;\
		ASSERT(glLog(#x, __FILE__, __LINE__))
#else
	#define GL(x) x
#endif

#endif
