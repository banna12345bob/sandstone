#include <sandstone.h>

extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

// Little demo of application commands
class sand : public Sandstone::command {
public:
	sand(Sandstone::room* roomPtr, Sandstone::objects* objectsPtr, Sandstone::inventory* invPtr) {
        command::m_roomPtr = roomPtr;
        command::m_objectsPtr = objectsPtr;
        command::m_invPtr = invPtr;
		command::m_DebugOnly = true;
	}
	virtual std::string run(std::string lCommand[]) override {
        SS_WARN("Current room {0}:{1}", m_roomPtr->m_Area, m_roomPtr->m_Room);
		luaL_openlibs(m_roomPtr->L);
		luaL_dofile(m_roomPtr->L, "../sandstone/main.lua");
		lua_getglobal(m_roomPtr->L, "MyLuaFunction");
		lua_pushstring(m_roomPtr->L, "parse string");
		lua_pcall(m_roomPtr->L, 1, 0, 0);
		return "I hate sand it's rough it's coarse and it gets everywhere";
	}
};

class ConsoleSandbox : public Sandstone::ConsoleApplication
{
public:
	ConsoleSandbox()
		: Sandstone::ConsoleApplication("consoleSandboxRooms.json", "consoleSandboxObjects.json")
	{
		this->m_Commands["sand"] = new sand(m_roomPtr, m_objectsPtr, m_invPtr);
	}
	~ConsoleSandbox()
	{

	}
};

Sandstone::Application* Sandstone::CreateApplication()
{
	return new ConsoleSandbox();
}
