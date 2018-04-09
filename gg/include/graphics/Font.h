#ifndef		GG_FONT_H
#define		GG_FONT_H
#pragma once

#include "debug/Log.h"
#include "Paths.h"

#include "Texture.h"

#include "ft2build.h"
#include FT_FREETYPE_H

namespace gg { namespace graphics {
	class Font
	{
	public:
		struct Character {
			GLuint textureID;   // ID handle of the glyph texture
			uint sizeX, sizeY;
			uint bearingX, bearingY;
			GLuint advance;    // Horizontal offset to advance to next glyph
		};

		FT_Library  library;   /* handle to library     */
		FT_Face     face;      /* handle to face object */

		Font(void)
		{
			FT_Error error = FT_Init_FreeType(&library);
			error = FT_Init_FreeType(&library);
			if (error) { ASSERT(false); }

			std::string _path = ROOT_FONT + std::string("Roboto/Roboto-Regular.ttf");
			error = FT_New_Face(library,
				_path.c_str(),
				0,
				&face
			);
			if (error == FT_Err_Unknown_File_Format)
			{
				ASSERT(false);
			}
			else if (error)
			{
				ASSERT(false);
			}
		}

		~Font(void);

	}; // class Font
}/*namespace graphics*/ } // namespace gg

#endif
