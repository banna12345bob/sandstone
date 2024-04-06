#pragma once
#include "json.h"
#include "object.h"

namespace Sandstone {

	class inventory {
	public:
		inventory(std::string saveFilePath, objects* objects);
        ~inventory();
		void resetSave();
		std::vector<std::string> getInvnetory();
		void addToInventory(object* lObject);
		bool removeFromInventory(object* lObject);
        bool removeFromInventory(std::string lObject);

		std::string m_SaveFilePath;
        std::vector<std::string> m_Inventory;
	private:
		json m_SaveFile;
        objects* m_Objects;
	};

}
