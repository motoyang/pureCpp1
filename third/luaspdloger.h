#ifndef LUASPDLOGER_H
#define LUASPDLOGER_H

// ---

DECLARE_LUA_OBJECT_BEGIN(lua_spdlogger_object)
    EXPORT_METHOD_TO_LUA(l_trace)
    EXPORT_METHOD_TO_LUA(l_debug)

    static spdlog::logger* getLogger(lua_State* l);
DECLARE_LUA_OBJECT_END(lua_spdlogger_object)

// ---

#endif // LUASPDLOGER_H
