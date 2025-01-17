#pragma once

#include "Core.h"
#include "Window.h"

namespace Nitrogen {

	class Application
	{
	public:
		Application();

		void Run();
		void OnEvent(Event& e);


	private:
		static Application* m_Instance;

		bool m_Running = true;

		Scope<Window> m_Window;
	
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	};

	Application* CreateApplication();

}