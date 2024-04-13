extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

namespace Sandstone {
    
    class scriptingEngine{
    public:
        scriptingEngine();
        
        lua_State* L;
    };
}
