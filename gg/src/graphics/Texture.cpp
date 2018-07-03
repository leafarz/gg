#include "graphics/Texture.h"

#include "platform/opengl/GLCommon.h"

#include "debug/Log.h"
#include "security/cryptography/crc32.h"
#include "SOIL2.h"

namespace gg { namespace graphics {
	std::unordered_map<uint, GLuint> Texture::s_TextureHash;

	Texture::Texture(uint width, uint height, uint internalFormat, uint format, uint dataType)
	{
		GL(glGenTextures(1, &m_ID));

		GL(glBindTexture(GL_TEXTURE_2D, m_ID));
			GL(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, dataType, NULL));
		GL(glBindTexture(GL_TEXTURE_2D, 0));
	}

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

		// create the image
		unsigned char* _image = SOIL_load_image(filePath.c_str(), &m_Width, &m_Height, 0, SOIL_LOAD_RGB);

		GL(glBindTexture(GL_TEXTURE_2D, m_ID));
			GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, _image));
			GL(glGenerateMipmap(GL_TEXTURE_2D));
		GL(glBindTexture(GL_TEXTURE_2D, 0));

		// delete the image after
		SOIL_free_image_data(_image);
		
		s_TextureHash[m_TextureHash] = m_ID;
	}

	Texture::~Texture(void)
	{
		// TODO: add unreferencing
		GL(glDeleteTextures(1, &m_ID));
	}

	void Texture::setFilterType(MinFilterType minFilterType, MagFilterType magFilterType)
	{
		bind();
			GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (uint)minFilterType));
			GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (uint)magFilterType));
		unbind();
	}

	void Texture::setWrapType(WrapType wrapType)
	{
		bind();
			GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (uint)wrapType));
			GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (uint)wrapType));
		unbind();
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

	math::Vec2f Texture::getSize(void) const
	{
		return math::Vec2f((float)m_Width, (float)m_Height);
	}
}/*namespace graphics*/ } // namespace gg
