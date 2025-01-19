#pragma once

#include "Nitrogen/Renderer/Texture.h"

#include <stb_image.h>

namespace Nitrogen{
	class OpenGLTexture2D : public Texture2D
	{
	public:

		OpenGLTexture2D(const std::string& file_path);
		virtual ~OpenGLTexture2D() override;

		virtual void Bind(uint32_t slot = 0) const override;

		virtual inline uint32_t GetWidth() const override { return m_Width; };
		virtual inline uint32_t GetHeight() const override { return m_Height; };

	private:
		std::string m_FilePath;
		uint32_t m_Width, m_Height, m_Channels;
		uint32_t m_RendererID;
	};
}