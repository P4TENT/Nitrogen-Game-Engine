#pragma once

#include "Nitrogen/Core/Core.h"
#include "Nitrogen/Core/Timestep.h"

#include "Window.h"
#include "Nitrogen/Core/LayerStack.h"
#include "Nitrogen/Core/Events/Event.h"
#include "Nitrogen/Core/Events/AppEvent.h"

#include "Nitrogen/ImGui/ImGuiLayer.h"

#include "Nitrogen/Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#include "Nitrogen/Renderer/OrthographicCamera.h"

namespace Nitrogen{

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.f;
		//Timestep m_Timestep;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}