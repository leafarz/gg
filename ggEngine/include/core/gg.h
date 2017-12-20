#ifndef		GGENGINE_GG_H
#define		GGENGINE_GG_H
#pragma once

#include <iostream>
#include <vector>
#include <string>

#if _DEBUG
	/* Logs str with function name and line number.
	 * Uses std::cout function for printing.
	 */
	#define LOG(str)\
	{\
		std::cout << str << std::endl << "(" << __FUNCTION__ << "():" << __LINE__ << ")" << std::endl << std::endl;\
	}
#else
	/* Does nothing.
	 * This does not affect performance even if LOG is used.
	 */
	#define LOG(str)
#endif

/* for loop from [a] to [b-1]
 * [i] is the index per iteration
 */
#define FOR(a,b)	for(int i=a-1; ++i < b; )

/* iterate std::vector
 * [it] is the iterator variable per iteration
 */
#define VFOR(vec)	for(auto it = vec.begin() ; it != vec.end(); ++it)

#endif
