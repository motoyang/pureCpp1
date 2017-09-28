#include "precompiled.h"
#include "luaspdloger.h"

// ---

IMPLEMENT_OPENLIB_FUNCTION_BEGIN(spdlogger)
    LIST_FUNCTIONS_BEGIN
        ITEM_IN_FUNCTIONS(get)
        ITEM_IN_FUNCTIONS(drop)
        ITEM_IN_FUNCTIONS(drop_all)
        ITEM_IN_FUNCTIONS(set_pattern)
        ITEM_IN_FUNCTIONS(set_level)

        ITEM_IN_FUNCTIONS(basic_logger)
        ITEM_IN_FUNCTIONS(rotating_logger)
        ITEM_IN_FUNCTIONS(daily_logger)

        ITEM_IN_FUNCTIONS(stdout_logger)
        ITEM_IN_FUNCTIONS(stderr_logger)
        ITEM_IN_FUNCTIONS(stdout_color)
        ITEM_IN_FUNCTIONS(stderr_color)

    LIST_FUNCTIONS_END
IMPLEMENT_OPENLIB_FUNCTION_END

// ---

DEFINE_MODULE_NAME(lua_spdlogger_object, "logger_object")
DEFINE_META_TABLE_NAME(lua_spdlogger_object, "496DA522-71FE-48B6-A270-A4186353AEEF")

IMPLEMENT_OPENLIB_METHOD_BEGIN(lua_spdlogger_object)
    static const struct luaL_Reg lib_m [] = {
        ITEM_IN_TABLE("trace",              lua_spdlogger_object::l_trace)
        ITEM_IN_TABLE("debug",              lua_spdlogger_object::l_debug)
        {NULL,          NULL}
    };
    static const struct luaL_Reg lib_f [] = {
        {NULL,          NULL}
    };

    REGISTER_LUA_OBJECT_METHODS(lua_spdlogger_object)

IMPLEMENT_OPENLIB_METHOD_END

// ---

int lua_spdlogger_object::l_trace(lua_State * ls)
{

    return 1;
}

int lua_spdlogger_object::l_debug(lua_State * ls)
{

    return 1;
}

// ---

int lua_get(lua_State * ls)
{
    Luapp lp(ls);
    std::string name(lp.toString(1));
    auto logger = spdlog::get(name);

    spdlog::logger **s = (spdlog::logger**)lp.newUserdata(sizeof(spdlog::logger*));
    *s = logger.get();

    lp.getMetatable("basic_logger");
    lp.setMetatable(-2);

    // 返回给Lua的只有logger*一个变量
    return 1;
}

int lua_drop(lua_State * ls)
{
    return 1;
}

int lua_drop_all(lua_State * ls)
{
    return 1;
}

int lua_set_pattern(lua_State * ls)
{
    return 1;
}

int lua_set_level(lua_State * ls)
{
    return 1;
}

int lua_basic_logger(lua_State * l)
{
    Luapp lp(l);
    std::string name(lp.toString(1));
    std::string filename(lp.toString(2));
    auto bl = spdlog::basic_logger_st(name, filename);

    spdlog::logger **s = (spdlog::logger**)lp.newUserdata(sizeof(spdlog::logger*));
    *s = bl.get();

    lp.getMetatable("basic_logger");
    lp.setMetatable(-2);

    // 返回给Lua的只有logger*一个变量
    return 1;
}

int lua_rotating_logger(lua_State * l)
{
    return 1;
}

int lua_daily_logger(lua_State * l)
{
    return 1;
}

int lua_stdout_logger(lua_State * l)
{
    return 1;
}

int lua_stderr_logger(lua_State * l)
{
    return 1;
}

int lua_stdout_color(lua_State * l)
{
    return 1;
}

int lua_stderr_color(lua_State * l)
{
    return 1;
}

// ---

IMPLEMENT_EXPORT_LIB_BEGIN(liblualogger)
    EXPORT_MODULE_TO_LUA(lua_spdlogger_object)

    EXPORT_FUNCTIONS_TO_LUA(spdlogger)
IMPLEMENT_EXPORT_LIB_END
