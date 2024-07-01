#include <sandstone.h>

// Little demo of application commands
class sand : public Sandstone::command {
public:
	sand(Sandstone::rooms* roomPtr, Sandstone::objects* objectsPtr, Sandstone::player* playerPtr, Sandstone::scriptingEngine* scripingEngine) {
        command::m_roomPtr = roomPtr;
        command::m_objectsPtr = objectsPtr;
        command::m_playerPtr = playerPtr;
        command::m_scripingEngine = scripingEngine;
		command::m_DebugOnly = true;
	}
	virtual std::string run(std::string lCommand[]) override {
        SS_WARN("Current room {0}:{1}", m_roomPtr->m_CurrentArea, m_roomPtr->m_CurrentRoom);
		luaL_openlibs(m_scripingEngine->L);
		luaL_dofile(m_scripingEngine->L, "scripts/main.lua"); // This only loads the file it doesn't reload it
		lua_getglobal(m_scripingEngine->L, "MyLuaFunction");
		lua_pcall(m_scripingEngine->L, 0, 0, 0);
		return "I hate sand it's rough it's coarse and it gets everywhere";
	}
};

class ConsoleSandbox : public Sandstone::ConsoleApplication
{
public:
	ConsoleSandbox()
		: Sandstone::ConsoleApplication("consoleSandboxRooms.json", "consoleSandboxObjects.json")
	{
		this->m_Commands["sand"] = new sand(m_roomPtr, m_objectsPtr, m_playerPtr, m_scripingEngine);
	}
	~ConsoleSandbox()
	{

	}
};

Sandstone::Application* Sandstone::CreateApplication()
{
	return new ConsoleSandbox();
}
