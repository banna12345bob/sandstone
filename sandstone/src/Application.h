#pragma once

#include "core.h"
#include <string>
#include <sstream>
#include <map>
#include "consoleApplication/commands.h"

namespace Sandstone {

	class Application
	{
	public:
        Application();
		virtual ~Application();

		virtual void Run() = 0;
	};

	//	To be defined in client
    Application* CreateApplication();
}
