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

}
