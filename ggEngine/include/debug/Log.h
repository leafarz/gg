#ifndef		GG_LOG_H
#define		GG_LOG_H
#pragma once

#include <string>
#include <sstream>
#include "core/Types.h"

#if _DEBUG
	/* Logs str with function name, file name and line number. */
	#define LOG(msg)\
	{\
		std::stringstream _ss;\
		_ss << "-----------------------------------------------------------\n" << msg << "\n:[" << __FUNCTION__ << "()]" << "\n:[" << __FILE__ << ":" << __LINE__ << "]\n";\
		Log::log(_ss.str(), LogLevel::Info);\
	}
	/* Logs str with function name, file name and line number. */
	#define WARN(msg)\
	{\
		std::stringstream _ss;\
		_ss << "-----------------------------------------------------------\n" << msg << "\n:[" << __FUNCTION__ << "()]" << "\n:[" << __FILE__ << ":" << __LINE__ << "]\n";\
		Log::log(_ss.str(), LogLevel::Warn);\
	}
	#define _SYS(msg)\
	{\
		std::stringstream _ss;\
		_ss << "-----------------------------------------------------------\n" << msg << "\n:[" << __FUNCTION__ << "()]" << "\n:[" << __FILE__ << ":" << __LINE__ << "]\n";\
		Log::log(_ss.str(), LogLevel::System);\
	}
#else
	/* Does nothing.
	* This does not affect performance even if LOG is used.
	*/
	#define LOG(msg)
	/* Does nothing.
	* This does not affect performance even if WARN is used.
	*/
	#define WARN(msg)
	/* Does nothing.
	* This does not affect performance even if _SYS is used.
	*/
	#define _SYS(msg)
#endif

/* Logs str with function name, file name and line number. */
#define ERROR(msg)\
{\
	std::stringstream _ss;\
	_ss << "-----------------------------------------------------------\n" << msg << "\n:[" << __FUNCTION__ << "()]" << "\n:[" << __FILE__ << ":" << __LINE__ << "]\n";\
	Log::log(_ss.str(), LogLevel::Error);\
}

namespace gg
{
	enum class LogLevel : byte
	{
		Info	= 1,
		Warn	= 2,
		Error	= 4,
		System	= 8
		
	};

	class Log
	{
	public:
		/* Enables the specific log level to be logged in console.
		 * LogLevel is the type of log which can be filtered for logging.
		 */
		static void addLog(LogLevel logLevel);
		/* Disables the specific log level to be logged in console.
		 * LogLevel is the type of log which can be filtered for logging.
		*/
		static void removeLog(LogLevel logLevel);
		/* Logs the [str] to console with the LogLevel type.
		 * LogLevel is the type of log which can be filtered for logging.
		*/
		static void log(std::string str, LogLevel logLevel = LogLevel::Info);

	private:
		Log(void) = delete;
		~Log(void) = delete;

	private:
		static byte s_LogLevel;
	}; // class Log
} // namespace gg
#endif
