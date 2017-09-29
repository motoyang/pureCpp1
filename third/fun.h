#ifndef FUN_H
#define FUN_H

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

DECLARE_OPENLIB_FUNCTION(spdlogger)

// ---

#endif // FUN_H
