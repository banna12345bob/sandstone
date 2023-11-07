#include "commands.h"
#ifdef SS_PY_SCRIPTING
	#include <pybind11/embed.h>
	namespace py = pybind11;
#endif

namespace Sandstone {

	look::look(room* roomPtr, objects* objectsPtr, inventory* invPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_invPtr = invPtr;
		m_Description = "Gets a description of the current room";
	}

	std::string look::run(std::string lCommand[])
	{
		try {
			return "You are in " + m_roomPtr->getRoomName() + ":\nIt is " + m_roomPtr->getDesciption();
		} catch (...) {
			SS_ASSERT(false, "Room doesn't exist");
			return "ERROR: Room doesn't exist";
		}
	}

	save::save(room* roomPtr, objects* objectsPtr, inventory* invPtr, std::string baseRoomFile)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_invPtr = invPtr;
		m_BaseRoomFile = baseRoomFile;
		m_Description = "Saves the game";
	}

	std::string save::run(std::string lCommand[]) {
		auto save = JSON().Read(m_invPtr->m_SaveFilePath);
		if(save == false || lCommand[1] == "reset") {
			m_invPtr->resetSave();
			JSON().Write(m_roomPtr->m_FileName, JSON().Read(m_BaseRoomFile));
			return "Save reset";
		} else {
			save["currentRoom"] = m_roomPtr->m_Room;
			save["currentArea"] = m_roomPtr->m_Area;
            save["inventory"]   = m_invPtr->m_Inventory;
			JSON().Write(m_invPtr->m_SaveFilePath, save);
			return "File saved";
		}
	}

	inv::inv(room* roomPtr, objects* objectsPtr, inventory* invPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_invPtr = invPtr;
		m_Description = "Displays your inventory";
	}

	std::string inv::run(std::string lCommand[]) {
		std::vector<std::string> u_Inventory = m_invPtr->getInvnetory();
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

	use::use(room* roomPtr, objects* objectsPtr, inventory* invPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_invPtr = invPtr;
		m_Description = "Uses an item";
	}

	std::string use::run(std::string lCommand[]) {
		if (lCommand[1] != "") {
			object* lObject = m_objectsPtr->getObject(lCommand[1]);
			std::vector<std::string> u_Inventory = m_invPtr->getInvnetory();
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

	dir::dir(room* roomPtr, objects* objectsPtr, inventory* invPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_invPtr = invPtr;
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

	pickup::pickup(room* roomPtr, objects* objectsPtr, inventory* invPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_invPtr = invPtr;
		m_Description = "Picks item up";
	}

	std::string pickup::run(std::string lCommand[]) {
		std::vector<std::string> items = m_roomPtr->getItemsInRoom();
		if(std::find(items.begin(), items.end(), lCommand[1]) != items.end())
		{
			object* item = m_objectsPtr->getObject(lCommand[1]);
			m_invPtr->addToInventory(item);
			m_roomPtr->removeItemFromRoom(item->getName());
			return "Item added to inventory";
		}
		return "Item not found";
	}

	drop::drop(room* roomPtr, objects* objectsPtr, inventory* invPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_invPtr = invPtr;
		m_Description = "Drops item from inventory";
	}

	std::string drop::run(std::string lCommand[]) {
		std::vector<std::string> inven = m_invPtr->getInvnetory();
		if (std::find(inven.begin(), inven.end(), lCommand[1]) != inven.end())
		{
			object* item = m_objectsPtr->getObject(lCommand[1]);
			if (m_invPtr->removeFromInventory(item)) {
				m_roomPtr->addItemToRoom(item->getName());
				return "Removed item from inventory";
			}
		}
		return  lCommand[1] + " not found";
	}


	talk::talk(room* roomPtr, objects* objectsPtr, inventory* invPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_invPtr = invPtr;
		m_Description = "Talk to an NPC";
	}

	std::string talk::run(std::string lCommand[]) {
		std::vector<std::string> npcs = m_roomPtr->getNpcList();
		if (std::find(npcs.begin(), npcs.end(), lCommand[1]) != npcs.end())
		{
#ifdef SS_PY_SCRIPTING
			py::scoped_interpreter guard{};
			try {
				auto npcModule = py::module::import("scripts.npcs");
				std::string dump = m_roomPtr->getNpcs()[lCommand[1]]["script"].dump();
				if (dump != "null") {
					// I have to do this because quotes are left on when dumping from json
					dump.erase(0, 1);
					dump.erase(dump.size() - 1);
					const char* key = dump.c_str();
					auto func = npcModule.attr(key);
					return func().cast<std::string>();
				}
				SS_ERROR("[{0}][script] == null", lCommand[1]);
				return "ERROR: Script not set";
			} catch (py::error_already_set &e) {
				SS_ERROR("{0}", e.what());
				return "Python error";
			}
#else
			SS_CORE_ERROR("Python scripting not supported");
			return "Python not supported";
#endif
		}
		return  lCommand[1] + " not found";
	}

	// ----------- Debug Commands ----------- //

	open::open(room* roomPtr, objects* objectsPtr, inventory* invPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_invPtr = invPtr;
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

	give::give(room* roomPtr, objects* objectsPtr, inventory* invPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_invPtr = invPtr;
		m_DebugOnly = true;
		m_Description = "Give specified item                         DEBUG ONLY";
	}

	std::string give::run(std::string lCommand[]) {
		if (lCommand[1] != "") {
			object* lObject = m_objectsPtr->getObject(lCommand[1]);
			if (lObject->getName() == "null") {
				return "Item named " + lCommand[1] + " doesn't exist";
			}
			m_invPtr->addToInventory(lObject);
			return "Added " + lCommand[1] + " to inventory";
		}
		else {
			return "Expected second argument";
		}
	}

	go_to::go_to(room* roomPtr, objects* objectsPtr, inventory* invPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_invPtr = invPtr;
		m_DebugOnly = true;
		m_Description = "Goto room                                   DEBUG ONLY";
	}

	std::string go_to::run(std::string lCommand[]) {
		if (lCommand[1] != "" && lCommand[2] != "") {
			m_roomPtr->m_Area = std::stoi(lCommand[1]);
			m_roomPtr->m_Room = std::stoi(lCommand[2]);
			return "You moved to room " + std::to_string(m_roomPtr->getArea()) + ":" + std::to_string(m_roomPtr->getRoom());
		}
		else {
			return "Expected second argument";
		}
	}

	log::log(room* roomPtr, objects* objectsPtr, inventory* invPtr)
	{
		command::m_roomPtr = roomPtr;
		command::m_objectsPtr = objectsPtr;
		command::m_invPtr = invPtr;
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
