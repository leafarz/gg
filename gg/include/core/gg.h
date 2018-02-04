#ifndef		GG_GG_H
#define		GG_GG_H
#pragma once

#include <vector>

#include "debug/Log.h"
#include "core/Types.h"

/* for loop from [a] to [b-1]
 * [var] is the int index per iteration
 */
#define FOR(var,a,b)	for(int var = a-1; ++var < b; )

/* for loop from [a] to [b-1]
 * [var] is the uint index per iteration
 */
#define FORU(var,a,b)	for(uint var = a; var < b; var++)

/* iterate std::vector
 * [it] is the iterator variable per iteration
 */
#define VFOR(it,vec)	for(auto it = vec.begin() ; it != vec.end(); ++it)

 /* iterate std::unordered_map
 * [kv] is the key value pair per iteration
 */
#define UFOR(kv,umap)	for(auto kv : umap)

#endif
