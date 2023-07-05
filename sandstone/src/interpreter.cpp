#include "interpreter.h"

namespace Sandstone {

	room::room(int area, int room, std::string iFile, std::string player)
		: m_Area(area), m_Room(room), m_Player(player)
	{
		char* pValue;
		size_t len;
		_dupenv_s(&pValue, &len, "APPDATA");
		std::string appData(pValue);
		std::string m_SaveDir = appData + "\\sandstone\\";
		if (!std::filesystem::is_directory(m_SaveDir) || !std::filesystem::exists(m_SaveDir)) {
			std::filesystem::create_directory(m_SaveDir);
		}
		m_SaveDir = m_SaveDir + player + "\\";
		if (!std::filesystem::is_directory(m_SaveDir) || !std::filesystem::exists(m_SaveDir)) {
			std::filesystem::create_directory(m_SaveDir);
		}
		std::string nFile = m_SaveDir + iFile.substr(0, iFile.find_last_of(".")) + "Save" + iFile.substr(iFile.find_last_of("."));
		if (JSON::Read(nFile) != false) {
			m_File = JSON::Read(nFile);
		} else {
			JSON::Write(nFile, JSON::Read(iFile));
			m_File = JSON::Read(nFile);
		}
		m_FileName = nFile;
	}

	std::vector<int> room::getDirection(std::string direction)
	{
		std::string rDirections;
		if (getDirections().contains(direction)) 
		{
			if (getDirections()[direction].contains("locked")) {
				if (getDirections()[direction]["locked"] == true && debugger().ignoreLocks == false) {
					if (getDirections()[direction].contains("unlockedBy")/* in inv.getInventory(True)*/) {

						m_File[std::to_string(m_Area)][std::to_string(m_Room)]["directions"][direction]["locked"] = false;
						JSON().Write(m_FileName, m_File);
						std::string unlockMsg = getDirections()[direction]["unlockMsg"];
						std::cout << unlockMsg << std::endl;
						rDirections = getDirections()[direction]["room"];
						//if self.file[str(self.area)][str(self.room)]["directions"][direction]["breaks"][0] == True:
							//inv.removeFromInventory(self.file[str(self.area)][str(self.room)]["directions"][direction]["unlockedBy"])
					}
					else {
						std::string a = getDirections()[direction]["lockedMsg"];
						std::cout << a << std::endl;
						std::vector<int> error;
						error.push_back(0);
						error.push_back(0);
						return error;
					}
				}
			}
			if (getDirections()[direction].contains("room")) {
				rDirections = getDirections()[direction]["room"];
			}
			else {
				rDirections = getDirections()[direction];
			}
			std::vector<int> vec;
			size_t pos = 0;
			std::string word;
			while ((pos = rDirections.find(":")) != std::string::npos) {
				word = rDirections.substr(0, pos);
				vec.push_back(std::stoi(word));
				rDirections.erase(0, pos + 1);
			}
			vec.push_back(std::stoi(rDirections));
			SS_CORE_ASSERT(m_File[std::to_string(vec[0])].contains(std::to_string(vec[1])), "Room doesn't exist");
			return vec;
		}
	}

	object::object(std::string name, std::string use)
		: m_Name(name), m_Use(use)
	{
	}

	objects::objects(std::string iFile)
		:m_File(JSON::Read(iFile))
	{
		//SS_CORE_ERROR(m_File.dump());
		for (auto& [key, value] : m_File.items()) {
			if (key != "version") {
				m_Objects.insert({ key, new object(key, m_File[key]["use"]) });
			}
		}
	}

	object* objects::getObject(std::string name)
	{
		SS_CORE_ASSERT(m_Objects.count(name), "Object doesn't exist");
		return m_Objects[name];
	}

}