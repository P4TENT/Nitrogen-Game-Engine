#include "ntgpch.h"

#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Nitrogen{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:			NTG_CORE_ASSERT(false, "Nitro::VertexArray::Create(): 'RenderAPI::None' is currently not supported!");
		case RenderAPI::API::OpenGL:		return CreateRef<OpenGLVertexArray>();

		}

		NTG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}