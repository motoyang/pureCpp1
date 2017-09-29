#include "luaspdlogger_global.h"
#include "luafun.h"
#include "luaspdlogger.h"

// ---

DEFINE_MODULE_NAME(lua_spdlogger_object, "logger_object")
DEFINE_META_TABLE_NAME(lua_spdlogger_object, "496DA522-71FE-48B6-A270-A4186353AEEF")

IMPLEMENT_OPENLIB_METHOD_BEGIN(lua_spdlogger_object)
    static const struct luaL_Reg lib_m [] = {
//        ITEM_IN_TABLE("trace",              lua_spdlogger_object::l_trace)
//        ITEM_IN_TABLE("debug",              lua_spdlogger_object::l_debug)
        ITEM_IN_TABLE("info",               lua_spdlogger_object::l_info)
        ITEM_IN_TABLE("warn",               lua_spdlogger_object::l_warn)
        ITEM_IN_TABLE("error",              lua_spdlogger_object::l_error)
        ITEM_IN_TABLE("critical",           lua_spdlogger_object::l_critical)
        ITEM_IN_TABLE("set_level",          lua_spdlogger_object::l_set_level)
        {NULL,          NULL}
    };
    static const struct luaL_Reg lib_f [] = {
        {NULL,          NULL}
    };

    REGISTER_LUA_OBJECT_METHODS(lua_spdlogger_object)

IMPLEMENT_OPENLIB_METHOD_END

// ---

int lua_spdlogger_object::l_set_level(lua_State *ls)
{
    Luapp l(ls);
    int level = l.toInteger(2);
    getLogger(ls)->set_level(spdlog::level::level_enum(level));
    return 0;
}

int lua_spdlogger_object::l_trace(lua_State * ls)
{
    Luapp l(ls);
    getLogger(ls)->trace(l.toString(2));

    return 0;
}

int lua_spdlogger_object::l_debug(lua_State * ls)
{
    Luapp l(ls);
    getLogger(ls)->debug(l.toString(2));

    return 0;
}

int lua_spdlogger_object::l_info(lua_State * ls)
{
    Luapp l(ls);
    getLogger(ls)->info(l.toString(2));

    return 0;
}

int lua_spdlogger_object::l_warn(lua_State * ls)
{
    Luapp l(ls);
    getLogger(ls)->warn(l.toString(2));

    return 0;
}

int lua_spdlogger_object::l_error(lua_State * ls)
{
    Luapp l(ls);
    getLogger(ls)->error(l.toString(2));

    return 0;
}

int lua_spdlogger_object::l_critical(lua_State * ls)
{
    Luapp l(ls);
    getLogger(ls)->critical(l.toString(2));

    return 0;
}

// ---

IMPLEMENT_EXPORT_LIB_BEGIN(libluaspdlogger)
    EXPORT_MODULE_TO_LUA(lua_spdlogger_object)
    EXPORT_FUNCTIONS_TO_LUA(spdlogger)
IMPLEMENT_EXPORT_LIB_END
