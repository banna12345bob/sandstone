#include "interpreter.h"

namespace Sandstone {

	room::room(int area, int room, std::string iFile, std::string player)
		: m_Area(area), m_Room(room), m_Player(player)
	{
		std::string nFile = iFile.substr(0, iFile.find_last_of(".")) + m_Player + iFile.substr(iFile.find_last_of("."));
		if (JSON::Read(nFile) != false) {
			m_File = JSON::Read(nFile);
		} else {
			JSON::Write(nFile, JSON::Read(iFile));
			m_File = JSON::Read(nFile);
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