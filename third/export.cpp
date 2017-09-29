#include "precompiled.h"
#include "fun.h"
#include "luaspdloger.h"
#include "export.h"

// ---

__attribute__ ((visibility("default"))) extern "C" int luaopen_liblualogger(lua_State* L)
{
    std::cout << "open lualogger2" << std::endl;

    static const luaL_Reg lua_modules[] = {
        { lua_spdlogger_object::mt_lua_spdlogger_object,     lua_spdlogger_object::open_lua_spdlogger_object},
        { "spdlogger",          open_spdlogger },
        {NULL, NULL}
    };

    Luapp lp(L);
    int i = lp.requireLibs(lua_modules);

    std::cout << "models = " << i << std::endl;

    return i;
}


/*
IMPLEMENT_EXPORT_LIB_BEGIN(liblualogger)
    EXPORT_MODULE_TO_LUA(lua_spdlogger_object)

    EXPORT_FUNCTIONS_TO_LUA(spdlogger)


IMPLEMENT_EXPORT_LIB_END
*/
