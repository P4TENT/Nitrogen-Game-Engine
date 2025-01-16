#pragma once

#include "Core.h"

namespace Nitrogen {

	class Application
	{
	public:
		Application();

		void Run();

	private:
		static Application* m_Instance;
	};

	Application* CreateApplication();

}