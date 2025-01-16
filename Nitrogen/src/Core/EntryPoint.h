#pragma once

#ifdef NTG_PLATFORM_WINDOWS

#include "CoreApp.h"

extern Nitrogen::Application* Nitrogen::CreateApplication();

int main(int argc, char** argv)
{
	auto EngineApp = Nitrogen::CreateApplication();
	EngineApp->Run();
	delete EngineApp;
}

#endif