#include "ntgpch.h"

#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#include "Nitrogen/Core/Core.h"

namespace Nitrogen {
	Ref<Texture2D> Texture2D::Create(const std::string& file_path)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:			NTG_CORE_ASSERT(false, "Texture2D::Texture2D::Create(): 'RenderAPI::None' is currently not supported!");
		case RenderAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(file_path);

		}

		NTG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:			NTG_CORE_ASSERT(false, "Texture2D::Texture2D::Create(): 'RenderAPI::None' is currently not supported!");
		case RenderAPI::API::OpenGL:		return CreateRef<OpenGLTexture2D>(width, height);

		}

		NTG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}