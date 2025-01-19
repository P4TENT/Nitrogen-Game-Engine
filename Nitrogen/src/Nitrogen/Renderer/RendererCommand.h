#pragma once

#include "VertexArray.h"
#include "RenderAPI.h"

namespace Nitrogen{
	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class RendererCommand	
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}
			
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static RenderAPI* s_RendererAPI;
	};

}