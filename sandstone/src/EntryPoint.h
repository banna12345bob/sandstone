#pragma once

#ifdef SS_PLATFORM_WINDOWS

	extern Sandstone::Application* Sandstone::CreateApplication();

	int main(int argc, char** argv)
	{
		Sandstone::Log::Init();

		SS_CORE_INFO("Sandstone Initialised");
		SS_TRACE("Build successful");

		auto app = Sandstone::CreateApplication();
		app->Run();
		delete app;
	}

#endif