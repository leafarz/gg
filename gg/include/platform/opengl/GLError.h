#ifndef		GG_GLERROR_H
#define		GG_GLERROR_H
#pragma once

#include <GL/glew.h>
#include <string>

#define ASSERT(x) if(!(x)) __debugbreak();

namespace gg
{
	/* Converts enum error to string name. */
	std::string getErrorName(GLenum error);

	/* Clears all errors from glGetError() command. */
	void glClearError(void);

	/* Logs all errors in the current glGetError() stack.
	 * Returns true if no error, otherwise false.
	 */
	bool glLog(const char* function, const char* file, int line);

} // namespace gg

#endif
