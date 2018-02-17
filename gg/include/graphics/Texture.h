#ifndef		GG_TEXTURE_H
#define		GG_TEXTURE_H
#pragma once

#include <string>
#include <unordered_map>

#include "GL/glew.h"
#include "core/Types.h"

namespace gg
{
	class Texture
	{
	private:
		friend class Material;

	public:
		Texture(const std::string& filePath);
		~Texture(void);

	private:
		void bind(int samplerSlot = 0) const;
		void unbind(void) const;

	private:
		/* Key value pairs of hash to ids created throughout the app. */
		static std::unordered_map<uint, GLuint> s_TextureHash;

		GLuint m_ID = 0;

		/* Hash of the filepath. */
		uint m_TextureHash;

		std::string m_FilePath;
		int m_Width = 0;
		int m_Height = 0;
	}; // class Texture
} // namespace gg

#endif
