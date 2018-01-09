#ifndef		GG_RESOURCE_H
#define		GG_RESOURCE_H
#pragma once

#include <iostream>
#include <string>

namespace gg
{
	class Resource
	{
	public:
		static std::string read_file(const char *file);

	private:
		Resource(void) = delete;
		~Resource(void) = delete;
	}; // class Resource
} // namespace gg

#endif
