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
		return "You are in " + room(m_Area, m_Room, m_roomFile, m_player).getRoomName() + ":\nIt is " + room(m_Area, m_Room, m_roomFile, m_player).getDesciption();
	}

	save::save(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player, std::string baseRoomFile)
	{
		command::m_Area = area;
		command::m_Room = room;
		command::m_roomFile = roomFile;
		command::m_objectFile = objectFile;
		command::m_saveFile = saveFile;
		command::m_player = player;
		m_BaseRoomFile = baseRoomFile;
		m_Description = "Saves the game";
	}

	std::string save::run(std::string lCommand[]) {
		auto save = JSON().Read(m_saveFile);
		if(save == false || lCommand[1] == "reset") {
			resetSave(m_saveFile).init();
			JSON().Write(m_roomFile, JSON().Read(m_BaseRoomFile));
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
		if (u_Inventory.size() <= 0)
			return "No items in inventory";
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
		if (directions.size() == 0)
		{
			SS_CORE_FATAL("No directions detected");
			return "You are stuck";
		}
		for (int i = 0; i < directions.size() - 1; i++)
		{
			std::cout << directions[i] << std::endl;
		}
		return directions[directions.size() - 1];
	}

	pickup::pickup(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player)
	{
		command::m_Area = area;
		command::m_Room = room;
		command::m_roomFile = roomFile;
		command::m_objectFile = objectFile;
		command::m_saveFile = saveFile;
		command::m_player = player;
		m_Description = "Picks item up";
	}

	std::string pickup::run(std::string lCommand[]) {
		std::vector<std::string> items = room(m_Area, m_Room, m_roomFile, m_player).getItemsInRoom();
		if(std::find(items.begin(), items.end(), lCommand[1]) != items.end())
		{
			object* item = objects(m_objectFile).getObject(lCommand[1]);
			inventory(m_saveFile).addToInventory(item);
			room(m_Area, m_Room, m_roomFile, m_player).removeItemFromRoom(item->getName());
			return "Item added to inventory";
		}
		return "Item not found";
	}

	drop::drop(int area, int room, std::string roomFile, std::string objectFile, std::string saveFile, std::string player)
	{
		command::m_Area = area;
		command::m_Room = room;
		command::m_roomFile = roomFile;
		command::m_objectFile = objectFile;
		command::m_saveFile = saveFile;
		command::m_player = player;
		m_Description = "Drops item from inventory";
	}

	std::string drop::run(std::string lCommand[]) {
		std::vector<std::string> inven = inventory(m_saveFile).getInvnetory();
		if (std::find(inven.begin(), inven.end(), lCommand[1]) != inven.end())
		{
			object* item = objects(m_objectFile).getObject(lCommand[1]);
			if (inventory(m_saveFile).removeFromInventory(item)) {
				room(m_Area, m_Room, m_roomFile, m_player).addItemToRoom(item->getName());
				return "Removed item from inventory";
			}
		}
		return  lCommand[1] + " not found";
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
