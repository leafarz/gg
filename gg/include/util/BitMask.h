#ifndef		GG_BITMASK_H
#define		GG_BITMASK_H
#pragma once

namespace gg
{
	class BitMask
	{
	public:
		template<typename T>
		static bool hasFlag(T mask, T bit)
		{
			return (mask & bit) == bit;
		}

		template<typename T>
		static void addFlag(T& mask, T bit)
		{
			if (!hasFlag(mask, bit)) { mask ^= bit; }
		}

		template<typename T>
		static void removeFlag(T& mask, T bit)
		{
			if (hasFlag(mask, bit)) { mask ^= bit; }
		}

	private:
		BitMask(void) = delete;
		~BitMask(void) = delete;
	};
	// class BitMask
} // namespace gg

#endif
