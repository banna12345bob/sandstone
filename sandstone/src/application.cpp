#include "Application.h"
#include "commands.h"

namespace Sandstone {

	Application::Application(std::string roomFile, std::string objectFile, std::string saveFile, std::string player)
		:m_RoomFile(roomFile), m_ObjectFile(objectFile), m_SaveFile(saveFile), m_Player(player)
	{
		
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
			if (arr[0] == "look") {
				std::cout << look(m_Area, m_Room, m_RoomFile, m_ObjectFile, m_SaveFile, m_Player).run(arr) << std::endl;
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