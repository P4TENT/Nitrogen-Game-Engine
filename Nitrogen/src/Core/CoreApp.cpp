#include "ntgpch.h"

#include "CoreApp.h"

namespace Nitrogen {

	Application* Application::m_Instance = nullptr;

	Application::Application()
	{
		m_Instance = this;
	}

	void Application::Run()
	{
		while (running)
		{
			m_Instance->OnUpdate();
		}
	}
}