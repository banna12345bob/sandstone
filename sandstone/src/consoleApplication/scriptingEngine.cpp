#include "scriptingEngine.h"
#include "Log.h"

namespace Sandstone {

    scriptingEngine::scriptingEngine(objects* objectsPtr, player* playerPtr, rooms* roomPtr)
        : m_objectsPtr(objectsPtr), m_playerPtr(playerPtr), m_roomPtr(roomPtr)
    {
        L = luaL_newstate();
    }

    void scriptingEngine::registerFunctions()
    {
        SS_CORE_INFO("Registering functions for lua");
        lua_register(L, "Trace", logTrace);
        lua_register(L, "Info",  logInfo);
        lua_register(L, "Warn",  logWarn);
        lua_register(L, "Error", logError);
        lua_register(L, "Fatal", logFatal);
    }

    int scriptingEngine::logTrace(lua_State* L)
    {
        const char* str = lua_tostring(L, 1);
        SS_TRACE(str);
        return 0;
    }

    int scriptingEngine::logInfo(lua_State* L)
    {
        const char* str = lua_tostring(L, 1);
        SS_INFO(str);
        return 0;
    }

    int scriptingEngine::logWarn(lua_State* L)
    {
        const char* str = lua_tostring(L, 1);
        SS_WARN(str);
        return 0;
    }

    int scriptingEngine::logError(lua_State* L)
    {
        const char* str = lua_tostring(L, 1);
        SS_ERROR(str);
        return 0;
    }

    int scriptingEngine::logFatal(lua_State* L)
    {
        const char* str = lua_tostring(L, 1);
        SS_FATAL(str);
        return 0;
    }

}
