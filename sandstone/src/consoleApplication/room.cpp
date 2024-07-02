#include "room.h"
#include "object.h"

namespace Sandstone {

	rooms::rooms(std::string iFile, player* player, objects* objectsPtr)
		: m_player(player), m_FileName(iFile), m_ObjectsPtr(objectsPtr)
	{
		this->reload();
	}

    void rooms::reload()
    {
		// For some reason this gets called even whenever the point to the room class is called
		//std::vector<area*> m_Areas;

        m_File = JSON::Read(m_FileName);

		area* errorArea = new area;

		room* errorRoom = new room;
		errorRoom->name = "Error Room";
		errorRoom->description = "a very big error";
		errorArea->rooms.push_back(errorRoom);

		m_Areas.push_back(errorArea);

		for (json::iterator areaIt = m_File.begin(); areaIt != m_File.end(); ++areaIt)
		{
			if (areaIt.key() != "version") {
				area* localArea = new area;

				room* errorRoom = new room;
				errorRoom->name = "Error Room";
				errorRoom->description = "a very big error";
				localArea->rooms.push_back(errorRoom);

				for (json::iterator roomIt = m_File[areaIt.key()].begin(); roomIt != m_File[areaIt.key()].end(); ++roomIt)
				{
					room* localRoom = new room;

					localRoom->name = m_File[areaIt.key()][roomIt.key()]["name"];
					localRoom->description = m_File[areaIt.key()][roomIt.key()]["description"];
					for each (auto i in m_File[areaIt.key()][roomIt.key()]["items"])
					{
						localRoom->items.push_back(m_ObjectsPtr->getObject(i));
					}
					localRoom->npcs = "Not implimented";
					for (json::iterator dirIt = m_File[areaIt.key()][roomIt.key()]["directions"].begin(); dirIt != m_File[areaIt.key()][roomIt.key()]["directions"].end(); ++dirIt)
					{
						direction* localDirection = new direction;

						std::string rDirections;
						if (m_File[areaIt.key()][roomIt.key()]["directions"][dirIt.key()].contains("room")) {
							// Only gets called if the door is able to be locked or unlocked
							rDirections = m_File[areaIt.key()][roomIt.key()]["directions"][dirIt.key()]["room"];

							localDirection->locked = m_File[areaIt.key()][roomIt.key()]["directions"][dirIt.key()]["locked"];
							localDirection->itemBreaksOnOpen = m_File[areaIt.key()][roomIt.key()]["directions"][dirIt.key()]["breaks"];
							localDirection->unlockedBy = m_ObjectsPtr->getObject(m_File[areaIt.key()][roomIt.key()]["directions"][dirIt.key()]["unlockedBy"]);
							localDirection->lockedMsg = m_File[areaIt.key()][roomIt.key()]["directions"][dirIt.key()]["lockedMsg"];
							localDirection->unlockMsg = m_File[areaIt.key()][roomIt.key()]["directions"][dirIt.key()]["unlockMsg"];
						} else {
							rDirections = m_File[areaIt.key()][roomIt.key()]["directions"][dirIt.key()];
						}

						// Gets the gotoID
						size_t pos = 0;
						std::string word;
						while ((pos = rDirections.find(":")) != std::string::npos) {
							word = rDirections.substr(0, pos);
							localDirection->gotoID[pos-1] = std::stoi(word);
							rDirections.erase(0, pos+1);
						}
						localDirection->gotoID[1] = std::stoi(rDirections);

						localRoom->directions[dirIt.key()] = localDirection;
					}
					localArea->rooms.push_back(localRoom);
				}

				m_Areas.push_back(localArea);
			}
		}
    }

	void rooms::removeItemFromRoom(object* item)
	{
		std::vector<object*> items = m_Areas[m_player->m_CurrentArea]->rooms[m_player->m_CurrentRoom]->items;
		if (std::find(items.begin(), items.end(), item) != items.end()) {
			m_Areas[m_player->m_CurrentArea]->rooms[m_player->m_CurrentRoom]->items.erase(std::find(m_Areas[m_player->m_CurrentArea]->rooms[m_player->m_CurrentRoom]->items.begin(), m_Areas[m_player->m_CurrentArea]->rooms[m_player->m_CurrentRoom]->items.end(), item));
			saveRoom(m_player->m_CurrentArea, m_player->m_CurrentRoom);
		}
		return;

	}

	void rooms::addItemToRoom(std::string item)
	{
		m_Areas[m_player->m_CurrentArea]->rooms[m_player->m_CurrentRoom]->items.push_back(m_ObjectsPtr->getObject(item));
		saveRoom(m_player->m_CurrentArea, m_player->m_CurrentRoom);
		return;
	}

	void rooms::saveRoom(int area, int room)
	{
		std::vector<std::string> items;
		
		for (object* item : m_Areas[area]->rooms[room]->items)
			items.push_back(item->name);

		m_File[std::to_string(area)][std::to_string(room)]["items"] = items;

		JSON::Write(m_FileName, m_File);
	}

	std::vector<int> rooms::goDirection(std::string direction)
	{
		if (m_Areas[m_player->m_CurrentArea]->rooms[m_player->m_CurrentRoom]->directions[direction]->locked) {
			if (!debugger().ignoreLocks) {
				if (m_player->inInventory(m_Areas[m_player->m_CurrentArea]->rooms[m_player->m_CurrentRoom]->directions[direction]->unlockedBy)) {
					m_Areas[m_player->m_CurrentArea]->rooms[m_player->m_CurrentRoom]->directions[direction]->locked = false;
					std::cout << m_Areas[m_player->m_CurrentArea]->rooms[m_player->m_CurrentRoom]->directions[direction]->unlockMsg << std::endl;
					if (m_Areas[m_player->m_CurrentArea]->rooms[m_player->m_CurrentRoom]->directions[direction]->itemBreaksOnOpen == true)
						m_player->removeFromInventory(m_Areas[m_player->m_CurrentArea]->rooms[m_player->m_CurrentRoom]->directions[direction]->unlockedBy);
				}
				else {
					std::cout << m_Areas[m_player->m_CurrentArea]->rooms[m_player->m_CurrentRoom]->directions[direction]->lockedMsg << std::endl;
					std::vector<int> error;
					error.push_back(0);
					error.push_back(0);
					return error;
				}
			}
		}

		std::vector<int> vec;
		for each (int i in m_Areas[m_player->m_CurrentArea]->rooms[m_player->m_CurrentRoom]->directions[direction]->gotoID)
			vec.push_back(i);
		return vec;

	}

}
