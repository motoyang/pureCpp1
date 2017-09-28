#ifndef LUASPDLOGER_H
#define LUASPDLOGER_H

// ---

DECLARE_OPENLIB_FUNCTION(spdlogger)

// ---

EXPORT_FUNCTION_TO_LUA(lua_get)
EXPORT_FUNCTION_TO_LUA(lua_drop)
EXPORT_FUNCTION_TO_LUA(lua_drop_all)
EXPORT_FUNCTION_TO_LUA(lua_set_pattern)
EXPORT_FUNCTION_TO_LUA(lua_set_level)


EXPORT_FUNCTION_TO_LUA(lua_basic_logger)
EXPORT_FUNCTION_TO_LUA(lua_rotating_logger)
EXPORT_FUNCTION_TO_LUA(lua_daily_logger)

EXPORT_FUNCTION_TO_LUA(lua_stdout_logger)
EXPORT_FUNCTION_TO_LUA(lua_stderr_logger)
EXPORT_FUNCTION_TO_LUA(lua_stdout_color)
EXPORT_FUNCTION_TO_LUA(lua_stderr_color)

// ---

DECLARE_LUA_OBJECT_BEGIN(lua_spdlogger_object)
    EXPORT_METHOD_TO_LUA(l_trace)
    EXPORT_METHOD_TO_LUA(l_debug)

DECLARE_LUA_OBJECT_END(lua_spdlogger_object)

// ---

DECLARE_EXPORT_LIB_FUNCTION(liblualogger)

// ---

#endif // LUASPDLOGER_H
