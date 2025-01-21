#pragma once

#include "Nitrogen/Core/Core.h"

#ifdef NTG_PLATFORM_WINDOWS

extern Nitrogen::Application* Nitrogen::CreateApplication();

int main(int argc, char** argv) 
{
	Nitrogen::Log::Init();

	NTG_PROFILE_BEGIN_SESSION("Startup", "../backend/debug/NtgProfile-Startup.json");
	auto app = Nitrogen::CreateApplication();
	NTG_PROFILE_END_SESSION();

	NTG_PROFILE_BEGIN_SESSION("Runtime", "../backend/debug/NtgProfile-Runtime.json");
	app->Run();
	NTG_PROFILE_END_SESSION();

	NTG_PROFILE_BEGIN_SESSION("Shutdown", "../backend/debug/NtgProfile-Shutdown.json");
	delete app;
	NTG_PROFILE_END_SESSION();
}

#endif