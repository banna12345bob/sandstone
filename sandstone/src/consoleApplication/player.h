#pragma once

#include "json.h"
#include "object.h"

namespace Sandstone {

	class player {
	public:
		player(std::string saveFilePath, objects* objects);
        ~player();
        void loadInventory(objects* objects);
        void saveInventory();
		void resetSave();
        std::vector<object*> getInventory() {return m_Inventory;}
        bool inInventory(object* object);
        bool inInventory(std::string objectName);
		void addToInventory(object* lObject);
		bool removeFromInventory(object* lObject);
        bool removeFromInventory(std::string lObject);

		std::string m_SaveFilePath;
	private:
        objects* m_Objects;
        std::vector<object*> m_Inventory;
		json m_SaveFile;
	};

}
