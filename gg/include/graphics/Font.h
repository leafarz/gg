#ifndef		GG_FONT_H
#define		GG_FONT_H
#pragma once

#include "core/Types.h"
#include "GL/glew.h"

#include <unordered_map>

#include "ft2build.h"
#include FT_FREETYPE_H

// TODO: add font cache
namespace gg { namespace graphics {
	enum class Fonts
	{
		Roboto
	};

	class Font
	{
	private:
		struct Character {
			GLuint textureID;
			uint sizeX, sizeY;
			int bearingX, bearingY;
			uint advance;
		};

	public:
		Font(Fonts font);
		~Font(void);

	private:
		// TODO: make static?
		FT_Library  library;
		FT_Face     face;
	}; // class Font
}/*namespace graphics*/ } // namespace gg

#endif
