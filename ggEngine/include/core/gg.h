#ifndef		GG_GG_H
#define		GG_GG_H
#pragma once

#include <vector>
#include "debug/Log.h"

/* for loop from [a] to [b-1]
 * [var] is the index per iteration
 */
#define FOR(var,a,b)	for(int var = a-1; ++var < b; )

/* iterate std::vector
 * [it] is the iterator variable per iteration
 */
#define VFOR(it,vec)	for(auto it = vec.begin() ; it != vec.end(); ++it)

#endif
