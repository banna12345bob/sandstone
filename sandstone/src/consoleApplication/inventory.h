#pragma once
#include "json.h"
#include "object.h"

namespace Sandstone {

	class inventory {
	public:
		inventory(std::string saveFilePath, objects* objects);
        ~inventory();
		void resetSave();
		std::vector<object*> getInventory();
        std::vector<std::string> getInventoryString();
		void addToInventory(object* lObject);
		bool removeFromInventory(object* lObject);
        bool removeFromInventory(std::string lObject);

		std::string m_SaveFilePath;
        objects* m_Objects;
	private:
        std::vector<object*> m_Inventory;
		json m_SaveFile;
	};

}
