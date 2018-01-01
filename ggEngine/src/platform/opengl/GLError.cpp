#include "platform/opengl/GLError.h"

#include "debug/Log.h"

namespace gg
{
	std::string getErrorName(GLenum error)
	{
		switch (error)
		{
		case GL_INVALID_ENUM:
			return "Invalid enum.";

		default: break;
		}
		return "";
	}

	void glClearError(void)
	{
		while (glGetError() != GL_NO_ERROR);
	}

	bool glLog(const char* function, const char* file, int line)
	{
		bool _hasNoError = true;
		while (GLenum _error = glGetError())
		{
			std::stringstream _ss;
			_ss << "-----------------------------------------------------------\nOpenGL Error: [" << _error
				<< "] " << getErrorName(_error) << "\n" << function << "\n:[" << file << ":" << line << "]\n";
			Log::log(_ss.str());
			_hasNoError = false;
		}
		return _hasNoError;
	}
}// namespace gg
