#include <Nitrogen.h>

#include <iostream>

class Sandbox : public Nitrogen::Application
{
public:
	void OnUpdate() override
	{
		Nitrogen::WindowResizeEvent e(1280, 720);

		if (e.IsInCategory(Nitrogen::EventCategoryApplication))
		{
			NTG_TRACE(e.ToString());
		}
	}
};

Nitrogen::Application* Nitrogen::CreateApplication()
{
	return new Sandbox();
}