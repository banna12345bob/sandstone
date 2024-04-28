#pragma once

#include "core.h"
#include <string>
#include <sstream>
#include <map>
#include "commands.h"
#include "Application.h"

namespace Sandstone {

	class ConsoleApplication : public Application
	{
	public:
        ConsoleApplication(std::string roomFile, std::string objectFile, std::string saveFile = "save.json", std::string player = "Player1");
		virtual ~ConsoleApplication();

		virtual void Run() override;
		std::map<std::string, command*> m_Commands;
        room* m_roomPtr;
        objects* m_objectsPtr;
        player* m_playerPtr;
        scriptingEngine* m_scripingEngine;
	private:
		std::string m_RoomFile;
		std::string m_baseRoomFile;
		std::string m_ObjectFile;
		std::string m_SaveFile;
		std::string m_PlayerName;
	};

	//	To be defined in client
    Application* CreateApplication();
}
