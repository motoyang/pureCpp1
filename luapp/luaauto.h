#ifndef LUA_AUTO_H
#define LUA_AUTO_H

DECLARE_LUA_OBJECT_BEGIN(luaAuto)
    EXPORT_METHOD_TO_LUA(l3_drive)
    EXPORT_METHOD_TO_LUA(l3_fuel)
    EXPORT_METHOD_TO_LUA(l3_maintain)
    EXPORT_METHOD_TO_LUA(l3_check)
DECLARE_LUA_OBJECT_END(luaAuto)

DECLARE_LUA_OBJECT_FROM_FATHER_BEGIN(luaCar, luaAuto)
    EXPORT_METHOD_TO_LUA(lc_music)
    EXPORT_METHOD_TO_LUA(lc_navi)
DECLARE_LUA_OBJECT_END(luaCar)

DECLARE_LUA_OBJECT_FROM_FATHER_BEGIN(luaTesla, luaCar)
    EXPORT_METHOD_TO_LUA(l_charge)
    EXPORT_METHOD_TO_LUA(l_bluetooth)
DECLARE_LUA_OBJECT_END(luaTesla)

DECLARE_LUA_OBJECT_BEGIN(luaAirVehicle)
    EXPORT_METHOD_TO_LUA(l_fly)
DECLARE_LUA_OBJECT_END(luaAirVehicle)

DECLARE_LUA_OBJECT_BEGIN(luaSeafaring)
    EXPORT_METHOD_TO_LUA(l_voyage)
    EXPORT_METHOD_TO_LUA(l_dive)
DECLARE_LUA_OBJECT_END(luaSeafaring)

DECLARE_LUA_OBJECT_FROM_FATHER_BEGIN(luaSuperCar, luaTesla)
    EXPORT_METHOD_TO_LUA(l_stealth)
    EXPORT_METHOD_TO_LUA(l_dive)
DECLARE_LUA_OBJECT_END(luaSuperCar)

void lua_Auto_test1();
void lua_Auto_test2();
void lua_Auto_test3();
void lua_Auto_test4();
void lua_Auto_test5();
void luapp_test1();

#endif // LUA_AUTO_H
