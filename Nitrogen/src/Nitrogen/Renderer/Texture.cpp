#include "ntgpch.h"

#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Nitrogen {
	Ref<Texture2D> Texture2D::Create(const std::string& file_path)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:			NTG_CORE_ASSERT(false, "Texture2D::Texture2D::Create(): 'RenderAPI::None' is currently not supported!");
		case RenderAPI::API::OpenGL:		return std::make_shared<OpenGLTexture2D>(file_path);

		}

		NTG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}