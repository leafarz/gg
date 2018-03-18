#include "platform/opengl/GLError.h"

#include "debug/Log.h"

namespace gg
{
	std::string getErrorName(GLenum error)
	{
		switch (error)
		{
		case GL_INVALID_ENUM:		return "Invalid enum.";
		case GL_INVALID_OPERATION:	return "Invalid operation.";
		case GL_INVALID_VALUE:		return "Invalid value.";

		default:
			return "Unidentified error! [" + std::to_string(error) + std::string("]");
		}
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
			debug::Log::log(_ss.str());
			_hasNoError = false;
		}
		return _hasNoError;
	}
} // namespace gg
