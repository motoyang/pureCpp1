#ifndef LUA_AUTO_H
#define LUA_AUTO_H

DECLARE_LUA_OBJECT_BEGIN(luaAuto)
    EXPORT_METHOD_TO_LUA(l_drive)
    EXPORT_METHOD_TO_LUA(l_fuel)
    EXPORT_METHOD_TO_LUA(l_maintain)
    EXPORT_METHOD_TO_LUA(l_check)
DECLARE_LUA_OBJECT_END

DECLARE2_LUA_OBJECT_BEGIN(lua3Auto)
    EXPORT2_METHOD_TO_LUA(l3_drive)
    EXPORT2_METHOD_TO_LUA(l3_fuel)
    EXPORT2_METHOD_TO_LUA(l3_maintain)
    EXPORT2_METHOD_TO_LUA(l3_check)
DECLARE2_LUA_OBJECT_END

DECLARE2_LUA_OBJECT_BEGIN2(luaCar, lua3Auto)
    EXPORT2_METHOD_TO_LUA(lc_music)
    EXPORT2_METHOD_TO_LUA(lc_navi)
DECLARE2_LUA_OBJECT_END


void lua_Auto_test1();
void lua_Auto_test2();
void lua_Auto_test3();
void lua_Auto_test4();
void luapp_test1();

#endif // LUA_AUTO_H
