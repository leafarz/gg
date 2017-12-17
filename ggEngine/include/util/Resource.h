#ifndef		GGENGINE_RESOURCE_H
#define		GGENGINE_RESOURCE_H
#pragma once

#include <iostream>

namespace GGEngine
{
	class Resource
	{
	public:
		Resource(void) = delete;
		~Resource(void) = delete;

		static std::string read_file(const char *file);
	}; // class Resource
} // namespace GGEngine

#endif
