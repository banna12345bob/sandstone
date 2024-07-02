#pragma once

#include "json.h"
#include "Log.h"

#include "player.h"

namespace Sandstone {

	struct direction {
		int gotoID[2];
		bool locked = false;
		object* unlockedBy;
		bool itemBreaksOnOpen = false;
		std::string lockedMsg;
		std::string unlockMsg;
	};

	struct room {
		int roomID;
		std::string name;
		std::string description;
		std::vector<object*> items;
		std::string npcs;
		std::map<std::string, direction*> directions;
	};

	struct area {
		int areaID;
		std::vector<room*> rooms;
	};

	class rooms {
	public:
		rooms(int larea, int room, std::string iFile, player* player, objects* objectsPtr);
        void reload();

		// ------------- Item functions ------------- //
		bool removeItemFromRoom(object* item);
		bool addItemToRoom(std::string item);


		// -------------- NPC functions -------------- //
		/*json getNpcs() { return m_File[std::to_string(m_Area)][std::to_string(m_Room)]["npcs"]; }
		std::vector<std::string> getNpcList();*/
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
		std::vector<std::string> getDirection() { std::vector<std::string> a; return a; };
		std::vector<int> goDirection(std::string direction);

		int m_CurrentArea;
		int m_CurrentRoom;
		player* m_player;
		objects* m_ObjectsPtr;
		std::string m_FileName;
		std::vector<area*> m_Areas;
	private:
		json m_File;
	};

}
