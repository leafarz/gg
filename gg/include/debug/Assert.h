#ifndef		GG_ASSERT_H
#define		GG_ASSERT_H
#pragma once

#define ASSERT(x) if(!(x)) __debugbreak();

#endif