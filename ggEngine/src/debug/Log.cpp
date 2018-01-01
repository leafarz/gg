#include "debug/Log.h"

#include <iostream>

#include "util/BitMask.h"
namespace gg
{
	unsigned char Log::s_LogLevel = static_cast<unsigned char>(LogLevel::Error) | static_cast<unsigned char>(LogLevel::Warn) | static_cast<unsigned char>(LogLevel::Info);

	void Log::addLog(LogLevel logLevel)
	{
		BitMask::addFlag(s_LogLevel, static_cast<unsigned char>(logLevel));
	}
	void Log::removeLog(LogLevel logLevel)
	{
		BitMask::removeFlag(s_LogLevel, static_cast<unsigned char>(logLevel));
	}

	void Log::log(std::string str, LogLevel logLevel)
	{
		if (BitMask::hasFlag(s_LogLevel, static_cast<unsigned char>(logLevel)))
		{
			std::cout << str;
		}
	}
} // namespace gg
