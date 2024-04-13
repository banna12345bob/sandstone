#include "room.h"

namespace Sandstone {

	room::room(int area, int room, std::string iFile, inventory* inv)
		: m_Area(area), m_Room(room), m_inv(inv), m_FileName(iFile)
	{
		m_File = JSON::Read(iFile);
	}

    void room::reload()
    {
        m_File = JSON::Read(m_FileName);
    }

	std::vector<std::string> room::getItemsInRoom()
	{
		std::vector<std::string> items;
		json item = m_File[std::to_string(m_Area)][std::to_string(m_Room)]["items"];
		for (int i = 0; i < item.size(); i++)
		{
			items.push_back(item[i]);
		}
		return items;
	}

	bool room::removeItemFromRoom(std::string item)
	{
		std::vector<std::string> items = getItemsInRoom();
		if (std::find(items.begin(), items.end(), item) != items.end()) {
			items.erase(std::find(items.begin(), items.end(), item));
			m_File[std::to_string(m_Area)][std::to_string(m_Room)]["items"] = items;
			JSON::Write(m_FileName, m_File);
			return true;
		}
		return false;

	}

	bool room::addItemToRoom(std::string item)
	{
		std::vector<std::string> items = getItemsInRoom();
		items.push_back(item);
		m_File[std::to_string(m_Area)][std::to_string(m_Room)]["items"] = items;
		JSON::Write(m_FileName, m_File);
		return true;
	}

	std::vector<std::string> room::getNpcList()
	{
		std::vector<std::string> npcs;
		json npc = m_File[std::to_string(m_Area)][std::to_string(m_Room)]["npcs"];
		for (json::iterator it = npc.begin(); it != npc.end(); ++it)
		{
			npcs.push_back(it.key());
		}
		return npcs;
	}

	std::vector<std::string> room::getDirection()
	{
		std::vector<std::string> directions;
		json file = getDirections();
		for (json::iterator it = file.begin(); it != file.end(); ++it)
		{
			directions.push_back(it.key());
		}
		return directions;
	}

	std::vector<int> room::goDirection(std::string direction)
	{
		std::string rDirections;
		if (getDirections().contains(direction)) 
		{
			if (getDirections()[direction].contains("locked")) {
				if (getDirections()[direction]["locked"] == true && debugger().ignoreLocks == false) {
					std::vector<object*> inv = m_inv->getInventory();
					if (std::find(inv.begin(), inv.end(), m_inv->m_Objects->getObject(getDirections()[direction]["unlockedBy"])) != inv.end()) {
						m_File[std::to_string(m_Area)][std::to_string(m_Room)]["directions"][direction]["locked"] = false;
						JSON::Write(m_FileName, m_File);
						std::string unlockMsg = getDirections()[direction]["unlockMsg"];
						std::cout << unlockMsg << std::endl;
						rDirections = getDirections()[direction]["room"];
						if (getDirections()[direction]["breaks"][0] == true)
                            m_inv->removeFromInventory(getDirections()[direction]["unlockedBy"]);
					}
					else {
						std::string a = getDirections()[direction]["lockedMsg"];
						std::cout << a << std::endl;
						std::vector<int> error;
						error.push_back(0);
						error.push_back(0);
						return error;
					}
				}
			}
			if (getDirections()[direction].contains("room")) {
				rDirections = getDirections()[direction]["room"];
			}
			else {
				rDirections = getDirections()[direction];
			}
			std::vector<int> vec;
			size_t pos = 0;
			std::string word;
			while ((pos = rDirections.find(":")) != std::string::npos) {
				word = rDirections.substr(0, pos);
				vec.push_back(std::stoi(word));
				rDirections.erase(0, pos + 1);
			}
			vec.push_back(std::stoi(rDirections));
			SS_CORE_ASSERT(m_File[std::to_string(vec[0])].contains(std::to_string(vec[1])), "Room doesn't exist");
			return vec;
		}
		std::vector<int> error;
		error.push_back(0);
		error.push_back(0);
		return error;
	}

}
