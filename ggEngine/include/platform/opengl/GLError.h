#ifndef		GG_GLERROR_H
#define		GG_GLERROR_H
#pragma once

#include <GL/glew.h>
#include <string>

#define ASSERT(x) if(!(x)) __debugbreak();

namespace gg
{
	std::string getErrorName(GLenum error);
	void glClearError(void);
	bool glLog(const char* function, const char* file, int line);
}

#endif
