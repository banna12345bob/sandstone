#include "object.h"

//#include "inventory.h"

namespace Sandstone {

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
		if (m_Objects.count(name) == false) {
			return m_Objects["null"];
		}
		return m_Objects[name];
	}

}
