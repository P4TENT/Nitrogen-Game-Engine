#pragma once

#ifdef NTG_PLATFORM_WINDOWS

extern Nitrogen::Application* Nitrogen::CreateApplication();

int main(int argc, char** argv) 
{
	Nitrogen::Log::Init();

	auto app = Nitrogen::CreateApplication();
	app->Run();
	delete app;
}

#endif