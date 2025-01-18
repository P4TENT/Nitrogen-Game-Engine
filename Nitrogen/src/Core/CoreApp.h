#pragma once

#include "Core.h"
#include "Window.h"
#include "Layer.h"
#include "LayerStack.h"

namespace Nitrogen {

	class Application
	{
	public:
		Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *m_Instance; }

	private:
		static Application* m_Instance;

		bool m_Running = true;

		Scope<Window> m_Window;

		LayerStack m_LayerStack;
	
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	};

	Application* CreateApplication();
}