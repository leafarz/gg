#ifndef		GG_TEXTURE_H
#define		GG_TEXTURE_H
#pragma once

#include <string>
#include <unordered_map>

#include "GL/glew.h"
#include "core/Types.h"

namespace gg { namespace graphics {
	class Texture
	{
	private:
		friend class Material;
		friend class Renderer;

	public:
		/* Minifying filter type.
		 * Default value is [Nearest_MipmapLinear] if not set.
		 */
		enum class MinFilterType
		{
			/* Returns the value of the texture element that is nearest
			 * (in Manhattan distance) to the specified texture coordinates.
			 */
			Nearest = GL_NEAREST,

			/* Returns the weighted average of the four texture elements that
			 * are closest to the specified texture coordinates. These can include
			 * items wrapped or repeated from other parts of a texture, depending
			 * on the values of GL_TEXTURE_WRAP_S and GL_TEXTURE_WRAP_T, and on the exact mapping.
			 */
			Linear = GL_LINEAR,

			/* Chooses the mipmap that most closely matches the size of the pixel
			 * being textured and uses the GL_NEAREST criterion (the texture element
			 * closest to the specified texture coordinates) to produce a texture value.
			 */
			Nearest_MipmapNearest = GL_NEAREST_MIPMAP_NEAREST,

			/* Chooses the mipmap that most closely matches the size of the pixel
			 * being textured and uses the GL_LINEAR criterion (a weighted average of
			 * the four texture elements that are closest to the specified texture
			 * coordinates) to produce a texture value.
			 */
			Linear_MipmapNearest = GL_LINEAR_MIPMAP_NEAREST,

			/* [Default if not set]
			 * Chooses the two mipmaps that most closely match the size of the pixel
			 * being textured and uses the GL_NEAREST criterion (the texture element
			 * closest to the specified texture coordinates) to produce a texture value
			 * from each mipmap. The final texture value is a weighted average of those two values.
			 */
			Nearest_MipmapLinear = GL_NEAREST_MIPMAP_LINEAR,

			/* Chooses the two mipmaps that most closely match the size of the pixel being textured and
			 * uses the GL_LINEAR criterion (a weighted average of the texture elements that are closest
			 * to the specified texture coordinates) to produce a texture value from each mipmap.
			 * The final texture value is a weighted average of those two values.
			 */
			Linear_MipmapLinear = GL_LINEAR_MIPMAP_LINEAR
		};

		/* Magnificication filter type.
		 * Default value is [Linear] if not set.
		 */
		enum class MagFilterType
		{
			/* Returns the value of the texture element that is nearest(in Manhattan distance)
			 * to the specified texture coordinates.
			 */
			Nearest = GL_NEAREST,
			/* [Default if not set]
			 * Returns the weighted average of the texture elements that are closest to the
			 * specified texture coordinates.These can include items wrapped or repeated from
			 * other parts of a texture, depending on the values of
			 * GL_TEXTURE_WRAP_S and GL_TEXTURE_WRAP_T, and on the exact mapping.
			 */
			Linear = GL_LINEAR
		};

		/* Wrap type.
		 * Default value is [Repeat] if not set.
		 */
		enum class WrapType
		{
			ClampToEdge = GL_CLAMP_TO_EDGE,
			ClampToBorder = GL_CLAMP_TO_BORDER,
			MirroredRepeat = GL_MIRRORED_REPEAT,
			/* [Default if not set] */
			Repeat = GL_REPEAT
		};

	public:
		Texture(const std::string& filePath);
		~Texture(void);

		void setFilterType(MinFilterType minFilterType, MagFilterType magFilterType);
		void setWrapType(WrapType wrapType);

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
}/*namespace graphics*/ } // namespace gg

#endif
