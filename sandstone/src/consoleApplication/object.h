#pragma once

#include "json.h"
#include "Log.h"

namespace Sandstone {

	struct object {
		std::string name;
		std::string use;
	};

	class objects {
	public:
		objects(std::string iFile);
		object* getObject(std::string name);
	private:
		json m_File;
		std::map<std::string, object*> m_Objects;
	};


}
