#pragma once

#include "Core.h"

namespace Nitrogen {

	class Application
	{
	public:
		Application();

		void Run();

		virtual void OnUpdate() = 0;

	private:
		static Application* m_Instance;

		bool running = true;
	};

	Application* CreateApplication();

}