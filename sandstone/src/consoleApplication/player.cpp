#include "player.h"

namespace Sandstone {

	player::player(std::string saveFilePath, objects* objects)
		: m_SaveFilePath(saveFilePath), m_Objects(objects)
	{
        loadInventory(objects);
	}

    player::~player()
    {
        saveInventory();
    }

    void player::loadInventory(objects* objects)
    {
        m_SaveFile = JSON().Read(m_SaveFilePath);
        if (m_SaveFile == false) {
            this->resetSave();
            m_SaveFile = JSON().Read(m_SaveFilePath);
        }
        for (int i = 0; i < m_SaveFile["inventory"].size(); i++)
        {
            m_Inventory.push_back(objects->getObject(m_SaveFile["inventory"][i]));
        }
    }

    void player::saveInventory()
    {
        m_SaveFile = JSON::Read(m_SaveFilePath);
        std::vector<std::string> inv;
        for (int i = 0; i < m_Inventory.size(); i++)
        {
            inv.push_back(m_Inventory[i]->getName());
        }
        m_SaveFile["inventory"] = inv;
        JSON().Write(m_SaveFilePath, m_SaveFile);
    }


    bool player::inInventory(object *object)
    {
        return (std::find(m_Inventory.begin(), m_Inventory.end(), object) != m_Inventory.end());
    }

    bool player::inInventory(std::string objectName)
    {
        return inInventory(m_Objects->getObject(objectName));
    }

	void player::addToInventory(object* lObject)
	{
		m_Inventory.push_back(lObject);
	}

	bool player::removeFromInventory(object* lObject)
	{
		if (std::find(m_Inventory.begin(), m_Inventory.end(), lObject) != m_Inventory.end())
		{
			m_Inventory.erase(std::find(m_Inventory.begin(), m_Inventory.end(), lObject));
//			m_SaveFile["inventory"] = m_Inventory;
//			JSON().Write(m_SaveFilePath, m_SaveFile);
			return true;
		}
		return false;
	}

    bool player::removeFromInventory(std::string lObject)
    {
        return removeFromInventory(m_Objects->getObject(lObject));
    }

	void player::resetSave()
	{
		json save;
		save["currentRoom"] = 1;
		save["currentArea"] = 1;
        save["inventory"] = std::vector<std::string>();
		JSON().Write(m_SaveFilePath, save);
        m_Inventory = std::vector<object*>();
	}

}
