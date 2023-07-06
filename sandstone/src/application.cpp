#include "Application.h"
#include <Windows.h>
#include <filesystem>
#include "version.h"

namespace Sandstone {

	Application::Application(std::string roomFile, std::string objectFile, std::string saveFile, std::string player)
		:m_RoomFile(roomFile), m_ObjectFile(objectFile), m_Player(player)
	{
		char* pValue;
		size_t len;
		_dupenv_s(&pValue, &len, "APPDATA");
		std::string appData(pValue);
		std::string m_SaveDir = appData + "\\sandstone\\";
		if (!std::filesystem::is_directory(m_SaveDir) || !std::filesystem::exists(m_SaveDir)) {
			std::filesystem::create_directory(m_SaveDir);
		}
		m_SaveDir = m_SaveDir + player + "\\";
		if (!std::filesystem::is_directory(m_SaveDir) || !std::filesystem::exists(m_SaveDir)) {
			std::filesystem::create_directory(m_SaveDir);
		}
		m_SaveFile = m_SaveDir + saveFile;
		version().checkVersion(m_RoomFile);
		version().checkVersion(m_ObjectFile);
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		int m_Area = 1;
		int m_Room = 1;
		std::string inp;
		auto file = JSON().Read(m_SaveFile);
		if (file != false) {
			m_Area = file["currentArea"];
			m_Room = file["currentRoom"];
			SS_CORE_INFO("Autoloaded save");
		} else {
			SS_CORE_WARN("Failed to find save file");
		}
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

			m_Commands["look"] = new look(m_Area, m_Room, m_RoomFile, m_ObjectFile, m_SaveFile, m_Player);
			m_Commands["save"] = new save(m_Area, m_Room, m_RoomFile, m_ObjectFile, m_SaveFile, m_Player);
			m_Commands["inv"] = new inv(m_Area, m_Room, m_RoomFile, m_ObjectFile, m_SaveFile, m_Player);
			m_Commands["use"] = new use(m_Area, m_Room, m_RoomFile, m_ObjectFile, m_SaveFile, m_Player);
			m_Commands["dir"] = new dir(m_Area, m_Room, m_RoomFile, m_ObjectFile, m_SaveFile, m_Player);

			// ----------- Debug Commands ----------- //
			m_Commands["open"] = new open(m_Area, m_Room, m_RoomFile, m_ObjectFile, m_SaveFile, m_Player);
			m_Commands["give"] = new give(m_Area, m_Room, m_RoomFile, m_ObjectFile, m_SaveFile, m_Player);
			
			if (m_Commands.count(arr[0]))
			{
				if (!m_Commands[arr[0]]->m_DebugOnly) {
					std::cout << m_Commands[arr[0]]->run(arr) << std::endl;
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
						std::cout << it->first << std::endl;
						it++;
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
			else if (room(m_Area, m_Room, m_RoomFile, m_Player).getDirections().contains(arr[0])) {
				auto a = room(m_Area, m_Room, m_RoomFile, m_Player).goDirection(arr[0]);
				if (a[0] != 0 || a[0] != 0) {
					m_Area = a[0];
					m_Room = a[1];
				}
				std::cout << room(m_Area, m_Room, m_RoomFile, m_Player).getRoomName() << std::endl;
			}
			else {
				std::cout << "Unknown command" << std::endl;
			}
		}
	}

}