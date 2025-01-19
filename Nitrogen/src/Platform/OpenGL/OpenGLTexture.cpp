#include "ntgpch.h"

#include "OpenGLTexture.h"

#include <glad/glad.h>

namespace Nitrogen{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& file_path)
		: m_FilePath(file_path)
	{
		stbi_set_flip_vertically_on_load(1);
		int width, height, channels;
		stbi_uc* data =  stbi_load(file_path.c_str(), &width, &height, &channels, 0);
		NTG_CORE_ASSERT(data, "Nitro::OpenGLTexture2D::OpenGLTexture2D(): Failed to load image!");

		m_Width = width;
		m_Height = height;
		m_Channels = channels;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		NTG_CORE_ASSERT(internalFormat & dataFormat, "Nitro::OpenGLTexture2D::OpenGLTexture2D(): Unknown Format!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
}