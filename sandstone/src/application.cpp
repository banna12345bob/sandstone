#include "Application.h"
#include "commands.h"
#include <Windows.h>
#include <filesystem>

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
			m_SaveDir = appData + "\\sandstone\\" + player + "\\";
			std::filesystem::create_directory(m_SaveDir);
		}
		m_SaveFile = m_SaveDir + saveFile;
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		int m_Area = 1;
		int m_Room = 1;
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

			std::map<std::string, command*> commands;
			commands["look"] = new look(m_Area, m_Room, m_RoomFile, m_ObjectFile, m_SaveFile, m_Player);
			commands["save"] = new save(m_Area, m_Room, m_RoomFile, m_ObjectFile, m_SaveFile, m_Player);
			//myMap["sub"] = sub;
			if (commands.count(arr[0]))
			{
				std::cout << commands[arr[0]]->run(arr) << std::endl;
			}
			else if (room(m_Area, m_Room, m_RoomFile, m_Player).getDirections().contains(arr[0])) {
				auto a = room(m_Area, m_Room, m_RoomFile, m_Player).getDirection(arr[0]);
				if (a[0] != 0 || a[0] != 0) {
					m_Area = a[0];
					m_Room = a[1];
				}
				std::cout << room(m_Area, m_Room, m_RoomFile, m_Player).getRoomName() << std::endl;
			}
			else if (inp == "quit" || inp == "exit") {
				break;
			}
			else {
				std::cout << "Unknown command" << std::endl;
			}
		}
	}

}