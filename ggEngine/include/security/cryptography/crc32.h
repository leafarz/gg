#ifndef		GGENGINE_CRC32_H
#define		GGENGINE_CRC32_H
#pragma once

namespace GGEngine {

	class Crc32
	{
	public:
		
		static unsigned int getHash(const char *pData, size_t iLen);

	private:
		Crc32(void) = delete;
		~Crc32(void) = delete;
		static unsigned int uiCRC32_Table[256];
	};

} // namespace GGEngine

#endif
