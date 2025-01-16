#pragma once

#ifdef NTG_PLATFORM_WINDOWS

#include "CoreApp.h"
#include "Log.h"

extern Nitrogen::Application* Nitrogen::CreateApplication();

int main(int argc, char** argv)
{
	Nitrogen::Log::Init();
	auto EngineApp = Nitrogen::CreateApplication();
	NTG_CORE_INFO("Nitrogen Engine Started!");
	EngineApp->Run();
	delete EngineApp;
}

#endif