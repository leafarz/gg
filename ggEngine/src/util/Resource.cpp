#include "util/Resource.h"

#include "core/gg.h"
namespace GGEngine
{
	std::string Resource::read_file(const char *file)
	{
		FILE* _file = fopen(file, "rt");

		if (!_file)
		{
			LOG("File [" << file << "] not found.");
			return "";
		}

		fseek(_file, 0, SEEK_END);
		unsigned long _length = ftell(_file);
		char* _data = new char[_length + 1];
		memset(_data, 0, _length + 1);
		fseek(_file, 0, SEEK_SET);

		// faster than ifstream
		fread(_data, 1, _length, _file);
		fclose(_file);

		std::string _text(_data);
		delete[] _data;
		return _text;
	}
} // namespace GGEngine
