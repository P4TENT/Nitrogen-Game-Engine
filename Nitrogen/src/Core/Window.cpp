#include "ntgpch.h"
#include "Window.h"

#ifdef NTG_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Nitrogen {
	Scope<Window> Window::Create(const WindowStructure& windowProps)
	{
#ifdef NTG_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(windowProps);
#endif
	}
}