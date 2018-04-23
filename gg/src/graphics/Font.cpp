#include "graphics/Font.h"

#include <string>

#include "Paths.h"

#include "platform/opengl/GLCommon.h"
#include "debug/Log.h"

namespace gg { namespace graphics {
	Font::Font(Fonts font)
	{
		FT_Error _error = FT_Init_FreeType(&library);
		_error = FT_Init_FreeType(&library);
		if (_error) { ASSERT(false); }

		std::string _path;

		switch (font)
		{
		case Fonts::Roboto:
			_path = ROOT_FONT + std::string("Roboto/Roboto-Regular.ttf");
			break;
		}

		_error = FT_New_Face(library, _path.c_str(), 0, &face );

		if (_error == FT_Err_Unknown_File_Format)
		{
			ERROR("Unknown File Format [" << _error << "] " << _path);
			ASSERT(false);
		}
		else if (_error)
		{
			ERROR("Unknown error [" << _error << "] " << _path);
			ASSERT(false);
		}
	}

	Font::~Font(void)
	{
	}
}/*namespace graphics*/ } // namespace gg
