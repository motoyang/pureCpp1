#ifndef LUASPDLOGGER_H
#define LUASPDLOGGER_H

// ---

spdlog::logger* getLogger(lua_State* l);

// ---

DECLARE_LUA_OBJECT_BEGIN(lua_spdlogger_object)
    EXPORT_METHOD_TO_LUA(l_trace)
    EXPORT_METHOD_TO_LUA(l_debug)
    EXPORT_METHOD_TO_LUA(l_info)
    EXPORT_METHOD_TO_LUA(l_warn)
    EXPORT_METHOD_TO_LUA(l_error)
    EXPORT_METHOD_TO_LUA(l_critical)

    EXPORT_METHOD_TO_LUA(l_set_level)
DECLARE_LUA_OBJECT_END(lua_spdlogger_object)

// ---

DECLARE_EXPORT_LIB_FUNCTION(libluaspdlogger)

// ---

#endif // LUASPDLOGGER_H
