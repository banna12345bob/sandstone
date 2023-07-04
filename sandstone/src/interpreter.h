#include "json.h"
#include "Log.h"

namespace Sandstone {

	class room {
	public:
		room(int area, int room, std::string iFile, std::string player);
		std::string getAreaName() { return m_File[std::to_string(m_Area)]["name"]; }
		std::string getRoomName() { return m_File[std::to_string(m_Area)][std::to_string(m_Room)]["name"]; }
		std::string getDesciption() { return m_File[std::to_string(m_Area)][std::to_string(m_Room)]["description"]; }
		// ----------- Furnature functions ----------- //
		json getFurnature() { return m_File[std::to_string(m_Area)][std::to_string(m_Room)]["furnature"]; }
		std::string getFurnatureDescription(std::string furnature) { return getFurnature()[furnature]["description"]; }
		json getFunratureObjects(std::string furnature) { return getFurnature()[furnature]["objects"]; }
		std::string getFunratureObjectLocation(std::string furnature, std::string object) { return getFunratureObjects(furnature)[object]["location"]; }
		bool getFunratureObjectPickedUp(std::string furnature, std::string object) { return getFunratureObjects(furnature)[object]["pickedup"]; }
		// -------------- NPC functions -------------- //
		json getNpcs() { return m_File[std::to_string(m_Area)][std::to_string(m_Room)]["npcs"]; }
		// NPC dialogue will be done late when commands are implimented
		/*json getNpcDialouge(std::string npc) { return getNpcs()[npc]["says"]; }
		std::string getNpcDialougeExtension(std::string npc)*/

		// These functions should return an item but I need to impliment items
		/*getNpcGives()
		getNpcDrops()*/
		bool checkItemGiven(std::string npc) { return getNpcs()["given"]; }
		bool checkNpcKilled(std::string npc) { return getNpcs()["killed"]; }
		//killNpc()

		// ----------- Direction functions ----------- //
		json getDirections() { return m_File[std::to_string(m_Area)][std::to_string(m_Room)]["directions"]; }
		std::vector<int> getDirection(std::string direction);

	private:
		int m_Area;
		int m_Room;
		std::string m_Player;
		std::string m_FileName;

		json m_File;
	};

	class object {
	public:
		object(std::string name, std::string use);
		std::string getUse() { return m_Use; }
		std::string getName() { return m_Name; }
	private:
		std::string m_Name;
		std::string m_Use;
	};

	class objects {
	public:
		objects(std::string iFile);
		object* getObject(std::string name);
	private:
		json m_File;
		std::map<std::string, object *> m_Objects;
	};


}