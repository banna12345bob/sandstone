#pragma once
#include "json.h"
#include "interpreter.h"

namespace Sandstone {

	/*class resetSave {
	public:
		resetSave(std::string saveFile);
		void init() {}
	private:
		std::string m_saveFile;
	};*/

	class inventory {
	public:
		inventory(std::string saveFilePath);
		void resetSave();
		std::vector<std::string> getInvnetory();
		void addToInventory(std::string lObject);
		void addToInventory(object* lObject);
		bool removeFromInventory(object* lObject);

		std::string m_SaveFilePath;
	private:
		json m_SaveFile;
		std::vector<std::string> m_Inventory;
	};

}