#include <Nitrogen.h>
#include <Nitrogen/Core/EntryPoint.h>

#include "game/GameLayer.h"

class ProjectApplication : public Nitrogen::Application
{
public:
	ProjectApplication()
		: Nitrogen::Application("Emberfall")
	{
		PushLayer(new Emberfall::GameLayer());
	}

	~ProjectApplication()
	{

	}
};

Nitrogen::Application* Nitrogen::CreateApplication()
{
	return new ProjectApplication();
}