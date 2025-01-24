#include "ntgpch.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"

namespace Nitrogen{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:			NTG_CORE_ASSERT(false, "Nitro::VertexBuffer::Create(): 'RenderAPI::None' is currently not supported!");
		case RenderAPI::API::OpenGL:		return CreateRef<OpenGLVertexBuffer>(size);

		}

		NTG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:			NTG_CORE_ASSERT(false, "Nitro::VertexBuffer::Create(): 'RenderAPI::None' is currently not supported!");
		case RenderAPI::API::OpenGL:		return CreateRef<OpenGLVertexBuffer>(vertices, size);

		}

		NTG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:			NTG_CORE_ASSERT(false, "Nitro::IndexBuffer::Create(): 'RenderAPI::None' is currently not supported!");
		case RenderAPI::API::OpenGL:		return CreateRef<OpenGLIndexBuffer>(indices, count);

		}

		NTG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}