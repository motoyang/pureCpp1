#ifndef LUA_AUTO_H
#define LUA_AUTO_H

DECLARE_LUA_OBJECT_BEGIN(luaAuto)
    EXPORT_METHOD_TO_LUA(l_drive)
    EXPORT_METHOD_TO_LUA(l_fuel)
    EXPORT_METHOD_TO_LUA(l_maintain)
    EXPORT_METHOD_TO_LUA(l_check)
DECLARE_LUA_OBJECT_END

void lua_Auto_test1();
void luapp_test1();

#endif // LUA_AUTO_H
