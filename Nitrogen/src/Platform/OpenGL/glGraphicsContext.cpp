#include "ntgpch.h"

#include "glGraphicsContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <Core/Core.h>

namespace Nitrogen {
	
	glGraphicsContext::glGraphicsContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		NTG_CORE_ASSERT(windowHandle, 2, "Window handle is NULL!");
	}

	void glGraphicsContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NTG_CORE_ASSERT(status, 1, "Failed to initialize Glad!");
	}

	void glGraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}