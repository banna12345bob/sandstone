#include "commands.h"

namespace Sandstone {

	look::look(rooms* roomPtr, objects* objectsPtr, player* playerPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_playerPtr = playerPtr;
		m_Description = "Gets a description of the current room";
	}

	std::string look::run(std::string lCommand[])
	{
		try {
			return "You are in " + m_roomPtr->m_Areas[m_playerPtr->m_CurrentArea]->rooms[m_playerPtr->m_CurrentRoom]->name + ":\nIt is " + m_roomPtr->m_Areas[m_playerPtr->m_CurrentArea]->rooms[m_playerPtr->m_CurrentRoom]->description;
		} catch (...) {
			SS_ASSERT(false, "Room doesn't exist");
			return "ERROR: Room doesn't exist";
		}
	}

	save::save(rooms* roomPtr, objects* objectsPtr, player* playerPtr, std::string baseRoomFile)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_playerPtr = playerPtr;
		m_BaseRoomFile = baseRoomFile;
		m_Description = "Saves the game";
	}

	std::string save::run(std::string lCommand[]) {
		auto save = JSON().Read(m_playerPtr->m_SaveFilePath);
		if(save == false || lCommand[1] == "reset") {
            m_playerPtr->resetSave();
			JSON().Write(m_roomPtr->m_FileName, JSON().Read(m_BaseRoomFile));

            m_roomPtr->reload();
			return "Save reset";
		} else {
			save["currentArea"] = m_playerPtr->m_CurrentArea;
			save["currentRoom"] = m_playerPtr->m_CurrentRoom;
			JSON().Write(m_playerPtr->m_SaveFilePath, save);
            m_playerPtr->saveInventory();
            return "File saved";
		}
	}

	inv::inv(rooms* roomPtr, objects* objectsPtr, player* playerPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_playerPtr = playerPtr;
		m_Description = "Displays your inventory";
	}

	std::string inv::run(std::string lCommand[]) {
		std::vector<object*> u_Inventory = m_playerPtr->getInventory();
		if (u_Inventory.size() <= 0)
			return "No items in inventory";
		for (int i = 0; i < u_Inventory.size() - 1; i++)
		{
			std::cout << u_Inventory[i]->name << std::endl;
		}
		if (u_Inventory.size() == 0) {
			return "No items in inventory";
		}
		return u_Inventory[u_Inventory.size() - 1]->name;
	}

	use::use(rooms* roomPtr, objects* objectsPtr, player* playerPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_playerPtr = playerPtr;
		m_Description = "Uses an item";
	}

	std::string use::run(std::string lCommand[]) {
		if (lCommand[1] != "") {
			object* lObject = m_objectsPtr->getObject(lCommand[1]);
			if (m_playerPtr->inInventory(lObject))
				return lObject->use;
			return lCommand[1] + " not found in inventory";
		}
		else {
			return "Expected second argument";
		}
	}

	dir::dir(rooms* roomPtr, objects* objectsPtr, player* playerPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_playerPtr = playerPtr;
		m_Description = "Displays the directions you can go";
	}

	std::string dir::run(std::string lCommand[]) {
		std::vector<std::string> directions = m_roomPtr->getDirection();
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

	pickup::pickup(rooms* roomPtr, objects* objectsPtr, player* playerPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_playerPtr = playerPtr;
		m_Description = "Picks item up";
	}

	std::string pickup::run(std::string lCommand[]) {
		std::vector<object*> items = m_roomPtr->m_Areas[m_playerPtr->m_CurrentArea]->rooms[m_playerPtr->m_CurrentRoom]->items;
		if(std::find(items.begin(), items.end(), m_objectsPtr->getObject(lCommand[1])) != items.end())
		{
			object* item = m_objectsPtr->getObject(lCommand[1]);
			m_playerPtr->addToInventory(item);
			m_roomPtr->removeItemFromRoom(item);
			return "Item added to inventory";
		}
		return "Item not found";
	}

	drop::drop(rooms* roomPtr, objects* objectsPtr, player* playerPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_playerPtr = playerPtr;
		m_Description = "Drops item from inventory";
	}

	std::string drop::run(std::string lCommand[]) {
		if (m_playerPtr->inInventory(m_objectsPtr->getObject(lCommand[1])))
		{
			object* item = m_objectsPtr->getObject(lCommand[1]);
			if (m_playerPtr->removeFromInventory(item)) {
				m_roomPtr->addItemToRoom(item->name);
				return "Removed item from inventory";
			}
		}
		return  lCommand[1] + " not found";
	}


	talk::talk(rooms* roomPtr, objects* objectsPtr, player* playerPtr, scriptingEngine* scripingEngine)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_playerPtr = playerPtr;
		command::m_playerPtr = playerPtr;
		command::m_scripingEngine = scripingEngine;
		m_Description = "Talk to an NPC";
	}

	std::string talk::run(std::string lCommand[]) {
		std::vector<std::string> npcs = m_roomPtr->m_Areas[m_playerPtr->m_CurrentArea]->rooms[m_playerPtr->m_CurrentRoom]->npcs;
		if (std::find(npcs.begin(), npcs.end(), lCommand[1]) != npcs.end())
		{
			std::string npcFunction = lCommand[1] + "Talk" + "1";
			lua_getglobal(m_scripingEngine->L, npcFunction.c_str());
			lua_pcall(m_scripingEngine->L, 0, 1, 0);
			const char* s = lua_tostring(m_scripingEngine->L, -1);
			SS_ASSERT(s, lCommand[1] + ": function doesn't return a string");
			return s;
		}
		return  lCommand[1] + " not found";
	}

	// ----------- Debug Commands ----------- //

	open::open(rooms* roomPtr, objects* objectsPtr, player* playerPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_playerPtr = playerPtr;
		m_DebugOnly = true;
		m_Description = "Prints out the contents of a JSON file      DEBUG ONLY";
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

	give::give(rooms* roomPtr, objects* objectsPtr, player* playerPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_playerPtr = playerPtr;
		m_DebugOnly = true;
		m_Description = "Give specified item                         DEBUG ONLY";
	}

	std::string give::run(std::string lCommand[]) {
		if (lCommand[1] != "") {
			object* lObject = m_objectsPtr->getObject(lCommand[1]);
			if (lObject->name == "null") {
				return "Item named " + lCommand[1] + " doesn't exist";
			}
			m_playerPtr->addToInventory(lObject);
			return "Added " + lObject->name + " to inventory";
		}
		else {
			return "Expected second argument";
		}
	}

	go_to::go_to(rooms* roomPtr, objects* objectsPtr, player* playerPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_playerPtr = playerPtr;
		m_DebugOnly = true;
		m_Description = "Goto room                                   DEBUG ONLY";
	}

	std::string go_to::run(std::string lCommand[]) {
		if (lCommand[1] != "" && lCommand[2] != "") {
			m_playerPtr->m_CurrentArea = std::stoi(lCommand[1]);
			m_playerPtr->m_CurrentRoom = std::stoi(lCommand[2]);
			return "You moved to room " + std::to_string(m_playerPtr->m_CurrentArea) + ":" + std::to_string(m_playerPtr->m_CurrentRoom);
		}
		else {
			return "Expected second argument";
		}
	}

	log::log(rooms* roomPtr, objects* objectsPtr, player* playerPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_playerPtr = playerPtr;
		m_DebugOnly = true;
		m_Description = "Print message to log                         DEBUG ONLY";
	}

	std::string log::run(std::string lCommand[]) {
		if (lCommand[1] != "" && lCommand[2] != "") {
			if (lCommand[1] == "trace") {
				SS_CORE_TRACE(lCommand[2]);
				return "";
			} else if (lCommand[1] == "info") {
				SS_CORE_INFO(lCommand[2]);
				return "";
			} else if (lCommand[1] == "warn") {
				SS_CORE_WARN(lCommand[2]);
				return "";
			} else if (lCommand[1] == "error") {
				SS_CORE_ERROR(lCommand[2]);
				return "";
			} else if (lCommand[1] == "fatal") {
				SS_CORE_FATAL(lCommand[2]);
				return "";
			} else {
				return "Unknown command";
			}
		}
		else {
			return "Expected more arguments";
		}
	}
}
