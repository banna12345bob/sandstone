#include "commands.h"

namespace Sandstone {

	look::look(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player)
	{
		command::m_Area = area;
		command::m_Room = room;
		command::m_roomFile = roomFile;
		command::m_objectFile = objectFile;
		command::m_saveFile = saveFile;
		command::m_player = player;
	}

	std::string look::run(std::string lCommand[])
	{
		if (lCommand[1] != "") {
			if (lCommand[1] == "room") {
				return "You are in " + room(m_Area, m_Room, m_roomFile, m_player).getRoomName() + ":\nIt is " + room(m_Area, m_Room, m_roomFile, m_player).getDesciption();
			}
			else if (room(m_Area, m_Room, m_roomFile, m_player).getFurnature().contains(lCommand[1]))
			{
				return room(m_Area, m_Room, m_roomFile, m_player).getFurnatureDescription(lCommand[1]);
			}
		}
		else if (lCommand[1] == "") {
			return "You are in " + room(m_Area, m_Room, m_roomFile, m_player).getRoomName() + ":\nIt is " + room(m_Area, m_Room, m_roomFile, m_player).getDesciption();
		}
		return "No description found";
	}

	save::save(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player)
	{
		command::m_Area = area;
		command::m_Room = room;
		command::m_roomFile = roomFile;
		command::m_objectFile = objectFile;
		command::m_saveFile = saveFile;
		command::m_player = player;
	}

	std::string save::run(std::string lCommand[]) {
		auto save = JSON().Read(m_saveFile);
		if(save == false || lCommand[1] == "reset") {
			json save;
			save["currentRoom"] = 1;
			save["currentArea"] = 1;
			for (int i = 0; i < 10; i++) {
				save["inventory"][i] = "";
			}
			JSON().Write(m_saveFile, save);
		} else {
			save["currentRoom"] = m_Room;
			save["currentArea"] = m_Area;
			JSON().Write(m_saveFile, save);
		}
		return "File saved";
	}

	open::open(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player)
	{
		command::m_Area = area;
		command::m_Room = room;
		command::m_roomFile = roomFile;
		command::m_objectFile = objectFile;
		command::m_saveFile = saveFile;
		command::m_player = player;
		m_DebugOnly = true;
	}

	std::string open::run(std::string lCommand[]) {
		if (lCommand[1] != "") {
			auto read = JSON().Read(lCommand[1]);
			if (read == false) {
				return "File not found";
			}
			else {
				return read.dump();
			}
		}
		else {
			return "Expected second argument";
		}
	}
}
