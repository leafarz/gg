#include "graphics/Texture.h"

#include "GL/glew.h"
#include "platform/opengl/GLCommon.h"

#include "core/gg.h"
#include "security/cryptography/crc32.h"
#include "SOIL2.h"

namespace gg
{
	Texture::Texture(const std::string& filePath)
		: m_FilePath(filePath)
	{
		m_TextureHash = Crc32::getHash(m_FilePath.c_str(), m_FilePath.size());
		bool _isCached = s_TextureHash.find(m_TextureHash) != s_TextureHash.end();

		if (_isCached)
		{
			_SYS("Fetching cached texture: \"" << m_FilePath << "\"");
			m_ID = s_TextureHash[m_TextureHash];
			return;
		}

		GL(glGenTextures(1, &m_ID));
			GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
			GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));

			unsigned char* image = SOIL_load_image(filePath.c_str(), &m_Width, &m_Height, 0, SOIL_LOAD_RGB);
			GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image));
			GL(glGenerateMipmap(GL_TEXTURE_2D));
			SOIL_free_image_data(image);
		GL(glBindTexture(GL_TEXTURE_2D, 0));
		
		s_TextureHash[m_TextureHash] = m_ID;
	}

	Texture::~Texture(void)
	{
	}

	void Texture::bind(int samplerSlot) const
	{
		ASSERT(samplerSlot >= 0 && samplerSlot <= 31);
		GL(glActiveTexture(GL_TEXTURE0 + samplerSlot));
		GL(glBindTexture(GL_TEXTURE_2D, m_ID));
	}

	void Texture::unbind(void) const
	{
		GL(glBindTexture(GL_TEXTURE_2D, 0));
	}
} // namespace gg
