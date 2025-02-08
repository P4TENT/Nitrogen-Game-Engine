#include <Nitrogen.h>
#include <Nitrogen/Core/EntryPoint.h>

#include "GameLayer.h"

class Emberfall : public Nitrogen::Application
{
public:
	Emberfall()
		: Application("Emberfall")
	{
		PushLayer(new GameLayer());
	}
};

Nitrogen::Application* Nitrogen::CreateApplication()
{
	return new Emberfall();
}