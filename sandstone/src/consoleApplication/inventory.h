#pragma once
#include "json.h"
#include "interpreter.h"

namespace Sandstone {

	class inventory {
	public:
		inventory(std::string saveFilePath);
        ~inventory();
		void resetSave();
		std::vector<std::string> getInvnetory();
		void addToInventory(object* lObject);
		bool removeFromInventory(object* lObject);

		std::string m_SaveFilePath;
        std::vector<std::string> m_Inventory;
	private:
		json m_SaveFile;
	};

}
