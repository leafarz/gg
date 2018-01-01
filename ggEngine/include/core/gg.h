#ifndef		GG_GG_H
#define		GG_GG_H
#pragma once

#include <vector>
#include "debug/Log.h"

/* for loop from [a] to [b-1]
 * [i] is the index per iteration
 */
#define FOR(a,b)	for(int i=a-1; ++i < b; )

/* iterate std::vector
 * [it] is the iterator variable per iteration
 */
#define VFOR(vec)	for(auto it = vec.begin() ; it != vec.end(); ++it)

#endif
