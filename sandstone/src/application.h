#pragma once

#include"Core.h"
#include <string>
#include <sstream>
#include <map>
#include "commands.h"

namespace Sandstone {

	class Application
	{
	public:
		Application(std::string roomFile, std::string objectFile, std::string saveFile = "save.json", std::string player = "Player1");
		virtual ~Application();

		void Run();
		std::map<std::string, command*> m_Commands;
	private:
		std::string m_RoomFile;
		std::string m_ObjectFile;
		std::string m_SaveFile;
		std::string m_Player;
	};

	//	To be defined in client
	Application* CreateApplication();
}