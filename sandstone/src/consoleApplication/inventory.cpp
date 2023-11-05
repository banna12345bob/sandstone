#include "inventory.h"
#ifdef SS_PY_SCRIPTING
#include <pybind11/embed.h>
namespace py = pybind11;
#endif

namespace Sandstone {

	/*resetSave::resetSave(std::string saveFile)
		: m_saveFile(saveFile)
	{
		json save;
		save["currentRoom"] = 1;
		save["currentArea"] = 1;
		for (int i = 0; i < 1; i++) {
			save["inventory"][i] = "";
		}
		JSON().Write(m_saveFile, save);
	}*/

	inventory::inventory(std::string saveFilePath)
		: m_SaveFilePath(saveFilePath)
	{
		m_SaveFile = JSON().Read(m_SaveFilePath);
		if (m_SaveFile == false) {
			this->resetSave();
			m_SaveFile = JSON().Read(m_SaveFilePath);
		}
		for (int i = 0; i < m_SaveFile["inventory"].size(); i++)
		{
			m_Inventory.push_back(m_SaveFile["inventory"][i]);
		}
	}

	std::vector<std::string> inventory::getInvnetory()
	{
		return m_Inventory;
	}

	void inventory::addToInventory(std::string lObject)
	{
		//object* object = objects().getObject(lObject);
		//addToInventory(object);
		return;
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

	bool inventory::removeFromInventory(object* lObject)
	{
		if (std::find(m_Inventory.begin(), m_Inventory.end(), lObject->getName()) != m_Inventory.end())
		{
			m_Inventory.erase(std::find(m_Inventory.begin(), m_Inventory.end(), lObject->getName()));
			m_SaveFile["inventory"] = m_Inventory;
			JSON().Write(m_SaveFilePath, m_SaveFile);
			return true;
		}
		return false;
	}

	void inventory::resetSave()
	{
		json save;
		save["currentRoom"] = 1;
		save["currentArea"] = 1;
		for (int i = 0; i < 1; i++) {
			save["inventory"][i] = "";
		}
		JSON().Write(m_SaveFilePath, save);
	}

}