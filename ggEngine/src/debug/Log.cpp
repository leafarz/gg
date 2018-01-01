#include "debug/Log.h"

#include <iostream>

#include "util/BitMask.h"
namespace gg
{
	unsigned char Log::s_LogLevel = static_cast<byte>(LogLevel::Info) |
		static_cast<byte>(LogLevel::Warn) |
		static_cast<byte>(LogLevel::Error) |
		static_cast<byte>(LogLevel::System);

	void Log::addLog(LogLevel logLevel)
	{
		BitMask::addFlag(s_LogLevel, static_cast<byte>(logLevel));
	}
	void Log::removeLog(LogLevel logLevel)
	{
		BitMask::removeFlag(s_LogLevel, static_cast<byte>(logLevel));
	}

	void Log::log(std::string str, LogLevel logLevel)
	{
		if (BitMask::hasFlag(s_LogLevel, static_cast<byte>(logLevel)))
		{
			std::cout << str;
		}
	}
} // namespace gg
