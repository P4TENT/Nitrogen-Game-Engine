#include "ntgpch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Nitrogen{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		NTG_CORE_ASSERT(windowHandle, "Nitro::OpenGLContext::OpenGLContext(): Window handle is null!!")
	}
	
	void OpenGLContext::Init()
	{
		NTG_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NTG_CORE_ASSERT(status, "Nitro::OpenGLContext::Init(): Failed to initialize Glad!");
	}
	
	void OpenGLContext::SwapBuffers()
	{
		NTG_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}