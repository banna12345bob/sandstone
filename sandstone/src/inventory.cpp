#include "inventory.h"

namespace Sandstone {

	resetSave::resetSave(std::string saveFile)
		: m_saveFile(saveFile)
	{
		json save;
		save["currentRoom"] = 1;
		save["currentArea"] = 1;
		for (int i = 0; i < 1; i++) {
			save["inventory"][i] = "";
		}
		JSON().Write(m_saveFile, save);
	}

	inventory::inventory(std::string saveFilePath)
		: m_SaveFilePath(saveFilePath)
	{
		m_SaveFile = JSON().Read(m_SaveFilePath);
		if (m_SaveFile == false) {
			resetSave(saveFilePath).init();
			m_SaveFile = JSON().Read(m_SaveFilePath);
		}
		for (int i = 0; i < m_SaveFile["inventory"].size(); i++)
		{
			m_Inventory.push_back(m_SaveFile["inventory"][i]);
		}
	}

	std::string inventory::getInvnetory()
	{
		for (int i = 0; i < m_Inventory.size() - 1; i++)
		{
			std::cout << m_Inventory[i] << std::endl;
		}
		if (m_Inventory[m_Inventory.size() - 1] == "") {
			return "No items in inventory";
		}
		return m_Inventory[m_Inventory.size() - 1];
	}

	void inventory::addToInventory(object* lObject)
	{
		for (int i = 0; i < m_Inventory.size(); i++)
		{
			if (m_Inventory[i] == "") {
				m_Inventory[i] = lObject->getName();
				m_SaveFile["inventory"] = m_Inventory;
				JSON().Write(m_SaveFilePath, m_SaveFile);
				return;
			}
		}
		m_Inventory.push_back(lObject->getName());
		m_SaveFile["inventory"] = m_Inventory;
		JSON().Write(m_SaveFilePath, m_SaveFile);
	}

}