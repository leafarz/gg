#ifndef		GGENGINE_GG_H
#define		GGENGINE_GG_H
#pragma once

#include <iostream>
#include <vector>

#if _DEBUG
	/* Logs str with function name and line number.
	 * Uses std::cout function for printing.
	 */
	#define LOG(str)\
	{\
		std::cout << str << std::endl << "(" << __FUNCTION__ << ":" << __LINE__ << ")" << std::endl << std::endl;\
	}
#else
	/* Does nothing.
	 * This does not affect performance even if declared.
	 */
	#define LOG(str)
#endif

/* for loop from [a] to [b-1]*/
#define FOR(a,b)		for(int i=a-1; ++i < b; )

/* iterate std::vector */
#define VFOR(vec)	for(auto it = vec.begin() ; it != vec.end(); ++it)

#endif
