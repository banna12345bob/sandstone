extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

namespace Sandstone {
    
    class scriptingEngine{
    public:
        scriptingEngine();

        void registerFunctions();

        // Functions that are register to lua
        static int logTrace(lua_State* L);
        static int logInfo(lua_State* L);
        static int logWarn(lua_State* L);
        static int logError(lua_State* L);
        static int logFatal(lua_State* L);
        
        lua_State* L;
    };
}
