#pragma once

#include "Nitrogen/Renderer/Texture.h"

#include <stb_image.h>

#include <glad/glad.h>

namespace Nitrogen{
	class OpenGLTexture2D : public Texture2D
	{
	public:

		OpenGLTexture2D(const std::string& file_path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture2D() override;

		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool operator==(const Texture& other) const override { return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID; }

		virtual inline uint32_t GetWidth() const override { return m_Width; };
		virtual inline uint32_t GetHeight() const override { return m_Height; };

		virtual void SetData(void* data, uint32_t size) override;

	private:
		std::string m_FilePath;
		uint32_t m_Width, m_Height, m_Channels;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_Format;
	};
}