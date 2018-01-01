#include "util/Resource.h"

#include "core/gg.h"
namespace gg
{
	std::string Resource::read_file(const char *file)
	{
		FILE* _file = fopen(file, "rt");

		if (!_file)
		{
			WARN("File [" << file << "] not found. Returning empty string.");
			return "";
		}

		fseek(_file, 0, SEEK_END);
		uint _length = ftell(_file);
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
} // namespace gg
