#pragma once
#include "commands.h"
#include <string>
#include <sstream>

namespace Sandstone {
	class run {
	public:
		run(std::string RoomFile, std::string ObjectFile, std::string player = "1") {
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
					std::cout << look(1, 1, RoomFile, ObjectFile, "save.json", player).run(arr) << std::endl;
				}
			}
		}
	};
}