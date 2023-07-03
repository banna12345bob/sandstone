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
		std::string inp;
		while (inp != "quit" && inp != "exit") {
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
				std::cout << look(1, 1, m_RoomFile, m_ObjectFile, m_SaveFile, m_Player).run(arr) << std::endl;
			}
		}
	}

}