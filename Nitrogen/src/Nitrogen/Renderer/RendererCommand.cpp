#include "ntgpch.h"

#include "RendererCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Nitrogen{
	RenderAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI;
}