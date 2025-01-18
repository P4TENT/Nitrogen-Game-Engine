#pragma once

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Nitrogen {
	class glGraphicsContext : public GraphicsContext
	{
	public:
		glGraphicsContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}