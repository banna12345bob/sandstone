#include "object.h"

namespace Sandstone {

	objects::objects(std::string iFile)
		:m_File(JSON::Read(iFile))
	{
		object* nullObject = new object;

		nullObject->name = "null";
		nullObject->use = "Error object. How did you get this item?";

        m_Objects.insert({ "null",  nullObject});
		for (auto& [key, value] : m_File.items()) {
			if (key != "version") {
				object* tempObject = new object;
				tempObject->name = key;
				tempObject->use = m_File[key]["use"];
				m_Objects.insert({ key, tempObject });
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
