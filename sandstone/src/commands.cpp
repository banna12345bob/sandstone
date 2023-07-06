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
		m_Description = "Gets a description of the current room";
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
		m_Description = "Saves the game";
	}

	std::string save::run(std::string lCommand[]) {
		auto save = JSON().Read(m_saveFile);
		if(save == false || lCommand[1] == "reset") {
			resetSave(m_saveFile).init();
			return "Save reset";
		} else {
			save["currentRoom"] = m_Room;
			save["currentArea"] = m_Area;
			JSON().Write(m_saveFile, save);
			return "File saved";
		}
	}

	inv::inv(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player)
	{
		command::m_Area = area;
		command::m_Room = room;
		command::m_roomFile = roomFile;
		command::m_objectFile = objectFile;
		command::m_saveFile = saveFile;
		command::m_player = player;
		m_Description = "Displays your inventory";
	}

	std::string inv::run(std::string lCommand[]) {
		std::vector<std::string> u_Inventory = inventory(m_saveFile).getInvnetory();
		for (int i = 0; i < u_Inventory.size() - 1; i++)
		{
			std::cout << u_Inventory[i] << std::endl;
		}
		if (u_Inventory[u_Inventory.size() - 1] == "") {
			return "No items in inventory";
		}
		return u_Inventory[u_Inventory.size() - 1];
	}

	use::use(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player)
	{
		command::m_Area = area;
		command::m_Room = room;
		command::m_roomFile = roomFile;
		command::m_objectFile = objectFile;
		command::m_saveFile = saveFile;
		command::m_player = player;
		m_Description = "Uses an item";
	}

	std::string use::run(std::string lCommand[]) {
		if (lCommand[1] != "") {
			object* lObject = objects(m_objectFile).getObject(lCommand[1]);
			std::vector<std::string> u_Inventory = inventory(m_saveFile).getInvnetory();
			for (int i = 0; i < u_Inventory.size(); i++)
			{
				if (u_Inventory[i] == lObject->getName())
				{
					return lObject->getUse();
				}
			}
			return lCommand[1] + " not found in inventory";
		}
		else {
			return "Expected second argument";
		}
	}

	dir::dir(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player)
	{
		command::m_Area = area;
		command::m_Room = room;
		command::m_roomFile = roomFile;
		command::m_objectFile = objectFile;
		command::m_saveFile = saveFile;
		command::m_player = player;
		m_Description = "Displays the directions you can go";
	}

	std::string dir::run(std::string lCommand[]) {
		std::vector<std::string> directions = room(m_Area, m_Room, m_roomFile, m_player).getDirection();
		for (int i = 0; i < directions.size() - 1; i++)
		{
			std::cout << directions[i] << std::endl;
		}
		return directions[directions.size() - 1];
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
		m_Description = "Prints out the contents of a JSON file\nDEBUG ONLY";
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

	give::give(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player)
	{
		command::m_Area = area;
		command::m_Room = room;
		command::m_roomFile = roomFile;
		command::m_objectFile = objectFile;
		command::m_saveFile = saveFile;
		command::m_player = player;
		m_DebugOnly = true;
		m_Description = "Give specified item\nDEBUG ONLY";
	}

	std::string give::run(std::string lCommand[]) {
		if (lCommand[1] != "") {
			object* lObject = objects(m_objectFile).getObject(lCommand[1]);
			if (lObject->getName() == "null") {
				return "Item named " + lCommand[1] + " doesn't exist";
			}
			inventory(m_saveFile).addToInventory(lObject);
			return "Added " + lCommand[1] + " to inventory";
		}
		else {
			return "Expected second argument";
		}
	}
}
