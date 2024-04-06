#include "inventory.h"

namespace Sandstone {

	inventory::inventory(std::string saveFilePath, objects* objects)
		: m_SaveFilePath(saveFilePath), m_Objects(objects)
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

    inventory::~inventory()
    {
        m_SaveFile = JSON::Read(m_SaveFilePath);
//        m_SaveFile["inventory"] = m_Inventory;
        std::vector<std::string> inv;
        for (int i = 0; i < m_Inventory.size(); i++)
        {
            inv.push_back(m_Inventory[i]->getName());
        }
        m_SaveFile["inventory"] = inv;
        JSON().Write(m_SaveFilePath, m_SaveFile);
    }

	std::vector<object*> inventory::getInventory()
	{
		return m_Inventory;
	}

    std::vector<std::string> inventory::getInventoryString()
    {
        std::vector<std::string> inven;
        for (int i = 0; i < m_Inventory.size(); i++)
        {
            inven.push_back(m_Inventory[i]->getName());
        }
        return inven;
    }

	void inventory::addToInventory(object* lObject)
	{
		m_Inventory.push_back(lObject);
	}

	bool inventory::removeFromInventory(object* lObject)
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

    bool inventory::removeFromInventory(std::string lObject)
    {
        if (std::find(m_Inventory.begin(), m_Inventory.end(), m_Objects->getObject(lObject)) != m_Inventory.end())
        {
            m_Inventory.erase(std::find(m_Inventory.begin(), m_Inventory.end(), m_Objects->getObject(lObject)));
            return true;
        }
        return false;
    }

	void inventory::resetSave()
	{
		json save;
		save["currentRoom"] = 1;
		save["currentArea"] = 1;
        save["inventory"] = std::vector<std::string>();
		JSON().Write(m_SaveFilePath, save);
        m_Inventory = std::vector<object*>();
	}

}
