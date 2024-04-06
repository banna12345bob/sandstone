#include "json.h"
#include "Log.h"

#include "inventory.h"

namespace Sandstone {

	class room {
	public:
		room(int area, int room, std::string iFile, inventory* inv);
        void reload();
		int getArea() { return m_Area; }
		int getRoom() { return m_Room; }
		std::string getAreaName() { return m_File[std::to_string(m_Area)]["name"]; }
		std::string getRoomName() { return m_File[std::to_string(m_Area)][std::to_string(m_Room)]["name"]; }
		std::string getDesciption() { return m_File[std::to_string(m_Area)][std::to_string(m_Room)]["description"]; }

		// ----------- Furnature functions ----------- //
		// Depricated functions removed in v2.0
		//json getFurnature() { return m_File[std::to_string(m_Area)][std::to_string(m_Room)]["furnature"]; }
		//std::string getFurnatureDescription(std::string furnature) { return getFurnature()[furnature]["description"]; }
		//json getFunratureObjects(std::string furnature) { return getFurnature()[furnature]["objects"]; }
		//std::string getFunratureObjectLocation(std::string furnature, std::string object) { return getFunratureObjects(furnature)[object]["location"]; }

		// ------------- Item functions ------------- //
		std::vector<std::string> getItemsInRoom();
		bool removeItemFromRoom(std::string item);
		bool addItemToRoom(std::string item);


		// -------------- NPC functions -------------- //
		json getNpcs() { return m_File[std::to_string(m_Area)][std::to_string(m_Room)]["npcs"]; }
		std::vector<std::string> getNpcList();
		// NPC dialogue will be done late when commands are implimented
		/*json getNpcDialouge(std::string npc) { return getNpcs()[npc]["says"]; }
		std::string getNpcDialougeExtension(std::string npc)*/

		// These functions should return an item but I need to impliment items
		/*getNpcGives()
		getNpcDrops()*/
		// bool checkItemGiven(std::string npc) { return getNpcs()["given"]; }
		// bool checkNpcKilled(std::string npc) { return getNpcs()["killed"]; }
		//killNpc()

		// ----------- Direction functions ----------- //
		json getDirections() { return m_File[std::to_string(m_Area)][std::to_string(m_Room)]["directions"]; }
		std::vector<std::string> getDirection();
		std::vector<int> goDirection(std::string direction);

		int m_Area;
		int m_Room;
		inventory* m_inv;
		std::string m_FileName;

	private:
		json m_File;
	};

}
