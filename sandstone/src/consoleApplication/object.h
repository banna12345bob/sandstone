#include "json.h"
#include "Log.h"

namespace Sandstone {

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
