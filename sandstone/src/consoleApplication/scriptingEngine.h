#pragma once

extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

#include "player.h"
#include "room.h"

namespace Sandstone {
    
    class scriptingEngine{
    public:
        scriptingEngine(objects* objectsPtr, player* playerPtr, room* roomPtr);

        void registerFunctions();

        // Functions that are register to lua
        static int logTrace(lua_State* L);
        static int logInfo(lua_State* L);
        static int logWarn(lua_State* L);
        static int logError(lua_State* L);
        static int logFatal(lua_State* L);
        
        lua_State* L;
        objects* m_objectsPtr;
        player* m_playerPtr;
        room* m_roomPtr;
    };
}
