#include "scriptingEngine.h"
#include "Log.h"

namespace Sandstone {
    scriptingEngine::scriptingEngine()
    {
        SS_CORE_INFO("Created scripting engine");
        L = luaL_newstate();
#ifdef SS_DEBUG
        luaL_openlibs(L);
        luaL_dofile(L, "../sandstone/scripts/main.lua");
        lua_getglobal(L, "CreateEngine");
        lua_pcall(L, 0, 0, 0);
#endif
    }
}
