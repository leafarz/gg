#include "debug/Log.h"

#include <iostream>

#include "util/BitMask.h"
namespace gg
{
	ubyte Log::s_LogLevel = static_cast<ubyte>(LogLevel::Info) |
		static_cast<ubyte>(LogLevel::Warn) |
		static_cast<ubyte>(LogLevel::Error) |
		static_cast<ubyte>(LogLevel::System);

	void Log::addLogLevel(LogLevel logLevel)
	{
		BitMask::addFlag(s_LogLevel, static_cast<ubyte>(logLevel));
	}
	void Log::removeLogLevel(LogLevel logLevel)
	{
		BitMask::removeFlag(s_LogLevel, static_cast<ubyte>(logLevel));
	}

	void Log::setLogLevel(LogLevel logLevel)
	{
		s_LogLevel = static_cast<ubyte>(logLevel);
	}

	LogLevel Log::getCurrentLogLevel(void) { return static_cast<LogLevel>(s_LogLevel); }

	void Log::log(const std::string& str, LogLevel logLevel)
	{
		if (BitMask::hasFlag(s_LogLevel, static_cast<ubyte>(logLevel)))
		{
			std::cout << str;
		}
	}
} // namespace gg
