#include "scriptingEngine.h"
#include "Log.h"

namespace Sandstone {
    scriptingEngine::scriptingEngine()
    {
        SS_CORE_INFO("Created scripting engine");
        L = luaL_newstate();
    }
}
