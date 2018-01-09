#ifndef		GG_CRC32_H
#define		GG_CRC32_H
#pragma once

namespace gg {

	class Crc32
	{
	public:
		
		static unsigned int getHash(const char *pData, size_t iLen);

	private:
		Crc32(void) = delete;
		~Crc32(void) = delete;
		static unsigned int uiCRC32_Table[256];
	};

} // namespace gg

#endif
