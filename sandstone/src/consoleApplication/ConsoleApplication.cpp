#include "ConsoleApplication.h"
#ifdef SS_PLATFORM_WINDOWS
#include <Windows.h>
#endif
#include <filesystem>
#include "version.h"

namespace Sandstone {
    ConsoleApplication::ConsoleApplication(std::string roomFile, std::string objectFile, std::string saveFile, std::string playerName)
		:m_RoomFile(roomFile), m_ObjectFile(objectFile), m_PlayerName(playerName)
	{
        SS_CORE_INFO("Version: {0}.{1}.{2}", Sandstone::getMajorVersion(), Sandstone::getMinorVersion(), Sandstone::getPatchVersion());
#ifdef SS_PLATFORM_WINDOWS
        size_t len;
		char* pValue;
		_dupenv_s(&pValue, &len, "APPDATA");
#elif defined(SS_PLATFORM_MACOS_ARM64) || defined(SS_PLATFORM_MACOS_x86)
		std::string pValue;
        std::string const& key = "HOME";
        char const* val = getenv(key.c_str());
        std::string home = (val == NULL ? std::string() : std::string(val));
        pValue = home + std::string("/Library/Application Support");
#elif defined(SS_PLATFORM_LINUX)
		std::string pValue;
		pValue = getenv("HOME");
#endif
		std::string appData(pValue);
		std::string m_SaveDir = appData + "/sandstone/";
		if (!std::filesystem::is_directory(m_SaveDir) || !std::filesystem::exists(m_SaveDir)) {
			std::filesystem::create_directory(m_SaveDir);
		}
		m_SaveDir = m_SaveDir + m_PlayerName + "/";
		if (!std::filesystem::is_directory(m_SaveDir) || !std::filesystem::exists(m_SaveDir)) {
			std::filesystem::create_directory(m_SaveDir);
		}
        SS_INFO("Save Directory: {0}", m_SaveDir);
		m_SaveFile = m_SaveDir + saveFile;
		m_RoomFile = m_SaveDir + roomFile.substr(0, roomFile.find_last_of(".")) + "Save" + roomFile.substr(roomFile.find_last_of("."));
		if (!std::filesystem::exists(m_RoomFile))
			JSON().Write(m_RoomFile, JSON().Read(roomFile));

		m_baseRoomFile = roomFile;

		checkVersionForFile(m_RoomFile);
		checkVersionForFile(m_ObjectFile);

		int m_Area = 1;
		int m_Room = 1;
		auto file = JSON().Read(m_SaveFile);
		if (file != false) {
			m_Area = file["currentArea"];
			m_Room = file["currentRoom"];
			SS_CORE_INFO("Autoloaded save");
		}
		else {
			SS_CORE_WARN("Failed to find save file");
		}

		m_objectsPtr = new objects(m_ObjectFile);
        m_playerPtr = new player(m_SaveFile, m_objectsPtr);
        m_roomPtr = new rooms(m_Area, m_Room, m_RoomFile, m_playerPtr, m_objectsPtr);
        m_scripingEngine = new scriptingEngine(m_objectsPtr, m_playerPtr, m_roomPtr);
    
        
		m_Commands["look"] = new look(m_roomPtr, m_objectsPtr, m_playerPtr);
		m_Commands["save"] = new save(m_roomPtr, m_objectsPtr, m_playerPtr, m_baseRoomFile);
		m_Commands["inv"] = new inv(m_roomPtr, m_objectsPtr, m_playerPtr);
		m_Commands["use"] = new use(m_roomPtr, m_objectsPtr, m_playerPtr);
		m_Commands["dir"] = new dir(m_roomPtr, m_objectsPtr, m_playerPtr);
		m_Commands["pickup"] = new pickup(m_roomPtr, m_objectsPtr, m_playerPtr);
		m_Commands["drop"] = new drop(m_roomPtr, m_objectsPtr, m_playerPtr);
		//m_Commands["talk"] = new talk(m_roomPtr, m_objectsPtr, m_playerPtr);

		// ----------- Debug Commands ----------- //
		m_Commands["open"] = new open(m_roomPtr, m_objectsPtr, m_playerPtr);
		m_Commands["give"] = new give(m_roomPtr, m_objectsPtr, m_playerPtr);
		m_Commands["goto"] = new go_to(m_roomPtr, m_objectsPtr, m_playerPtr);
		m_Commands["log"] = new log(m_roomPtr, m_objectsPtr, m_playerPtr);

		m_scripingEngine->registerFunctions();
	}

    ConsoleApplication::~ConsoleApplication()
	{
#ifdef SS_DEBUG
        std::cout << "Press enter to quit...";
        std::cin.ignore();
#endif
    }

	void ConsoleApplication::Run()
	{
		std::string inp;

		while (true) {
			std::string arr[100];
			int arr_length = 0;
			std::cout << "Command: ";
			std::getline(std::cin, inp);
			size_t pos = 0;
			std::string word;
			while ((pos = inp.find(" ")) != std::string::npos) {
				word = inp.substr(0, pos);
				arr[arr_length] = word;
				inp.erase(0, pos + 1);
				arr_length++;
			}
			arr[arr_length] = inp;

			
			if (m_Commands.count(arr[0]))
			{
				if (!m_Commands[arr[0]]->m_DebugOnly) {
					std::string run = m_Commands[arr[0]]->run(arr);
					if (run != "quit")
						std::cout << run << std::endl;
					else
						break;
				}
				else if (debugger().m_Enable) {
					std::cout << m_Commands[arr[0]]->run(arr) << std::endl;
				}
				else {
					SS_CORE_WARN("Debugger disabled");
					std::cout << "Unknown command" << std::endl;
				}
			}
			else if (arr[0] == "help") {
				std::map<std::string, command*>::iterator it = m_Commands.begin();

				if (arr[1] == "") {
					while (it != m_Commands.end())
					{
						if (it->second->m_DebugOnly && debugger().m_Enable) {
							std::cout << it->first << ": " << it->second->m_Description << std::endl;
							it++;
						} else if (it->second->m_DebugOnly && !debugger().m_Enable) {
							it++;
						} else {
							std::cout << it->first << ": " << it->second->m_Description << std::endl;
							it++;
						}
					}
				} else {
					if (m_Commands.count(arr[1])) {
						std::string description = m_Commands[arr[1]]->m_Description;
						if (description == "") {
							description = "Description not found";
						}
						std::cout << arr[1] << ": " << description << std::endl;
					} else {
						SS_ERROR("{0}: command nonexistent", arr[1]);
						std::cout << arr[1] << ": Command not found" << std::endl;
					}
				}

			}
			else if (arr[0] == "quit" || arr[0] == "exit") {
				break;
			}
			else if (m_roomPtr->m_Areas[m_roomPtr->m_CurrentArea]->rooms[m_roomPtr->m_CurrentRoom]->directions.find(arr[0]) != m_roomPtr->m_Areas[m_roomPtr->m_CurrentArea]->rooms[m_roomPtr->m_CurrentRoom]->directions.end()) {
				auto a = m_roomPtr->goDirection(arr[0]);
				if (a[0] != 0 || a[0] != 0) {
					m_roomPtr->m_CurrentArea = a[0];
					m_roomPtr->m_CurrentRoom = a[1];
				}
				std::cout << "You are in the " << m_roomPtr->m_Areas[m_roomPtr->m_CurrentArea]->rooms[m_roomPtr->m_CurrentRoom]->name << "\nIt is a " << m_roomPtr->m_Areas[m_roomPtr->m_CurrentArea]->rooms[m_roomPtr->m_CurrentRoom]->description << std::endl;
			}
			else {
				SS_CORE_WARN("{0}: unknown command", inp);
				std::cout << "Unknown command" << std::endl;
			}
		}
        m_playerPtr->~player();
	}

}
