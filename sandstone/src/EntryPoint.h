#pragma once
#include "version.h"

#if defined(SS_PLATFORM_WINDOWS) || defined(SS_PLATFORM_MACOS)

	extern Sandstone::Application* Sandstone::CreateApplication();

	int main(int argc, char** argv)
	{
		Sandstone::Log::Init();

		SS_CORE_INFO("Sandstone Initialised");
		SS_CORE_INFO("Version: {0}.{1}.{2}", Sandstone::version().major, Sandstone::version().minor, Sandstone::version().patch);

		auto app = Sandstone::CreateApplication();
		app->Run();
		delete app;
	}
#else
    #error "Entry point not built for current OS!"
#endif
