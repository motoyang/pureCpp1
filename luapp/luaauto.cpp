#include "luapp_global.h"
#include "luapp.h"
#include "auto.h"
#include "luaauto.h"

// ---

DEFINE_MODULE_NAME(luaSuperCar, "SuperCar")
DEFINE_META_TABLE_NAME(luaSuperCar, "F9872759-8308-4DDA-A5C2-740F6E285911")

IMPLEMENT_OPENLIB_METHOD_BEGIN(luaSuperCar)
    LIST_META_TABLE_BEGIN(luaSuperCar, SuperCar)
        ITEM_IN_TABLE("stealth",            luaSuperCar::l_stealth)
        ITEM_IN_TABLE("dive",               luaSuperCar::l_dive)
    LIST_META_TABLE_END

    LIST_FUNC_TABLE_BEGIN(luaSuperCar, SuperCar)
    LIST_FUNC_TABLE_END

    REGISTER_LUA_OBJECT_METHODS(luaSuperCar)
    INHERIT_METHOD_FROM_FATHER(luaTesla)

IMPLEMENT_OPENLIB_METHOD_END

int luaSuperCar::l_stealth(lua_State * ls)
{
    Luapp l(ls);
    l.dispatchToC<SuperCar>(&SuperCar::stealth);

    return 0;
}

int luaSuperCar::l_dive(lua_State * ls)
{
    Luapp l(ls);
    std::string r = l.dispatchToC<SuperCar>(&SuperCar::dive, l.toNumber(2), l.toInteger(3));
    l.pop(2);
    l.pushString(r.c_str());

    return 1;
}

// ---

DEFINE_MODULE_NAME(luaSeafaring, "Seafaring")
DEFINE_META_TABLE_NAME(luaSeafaring, "A81F2DB0-2B23-4456-BC20-0D37C3D06035")

IMPLEMENT_OPENLIB_METHOD_BEGIN(luaSeafaring)
    LIST_META_TABLE_BEGIN(luaSeafaring, Seafaring)
        ITEM_IN_TABLE("voyage",            luaSeafaring::l_voyage)
        ITEM_IN_TABLE("dive",              luaSeafaring::l_dive)
    LIST_META_TABLE_END

    LIST_FUNC_TABLE_BEGIN(luaSeafaring, Seafaring)
    LIST_FUNC_TABLE_END

    REGISTER_LUA_OBJECT_METHODS(luaSeafaring)

IMPLEMENT_OPENLIB_METHOD_END

int luaSeafaring::l_voyage(lua_State * ls)
{
    Luapp l(ls);
    int r = l.dispatchToC<Seafaring>(&Seafaring::voyage, l.toNumber(2));
    l.pop(1);
    l.pushInteger(r);

    return 1;
}

int luaSeafaring::l_dive(lua_State * ls)
{
    Luapp l(ls);
    std::string r = l.dispatchToC<Seafaring>(&Seafaring::dive, l.toNumber(2), l.toInteger(3));
    l.pop(2);
    l.pushString(r.c_str());

    return 1;
}

// ---

DEFINE_MODULE_NAME(luaAirVehicle, "AirVehicle")
DEFINE_META_TABLE_NAME(luaAirVehicle, "BBCAA017-886E-4F11-AE4E-89A0C88A9418")

IMPLEMENT_OPENLIB_METHOD_BEGIN(luaAirVehicle)
    LIST_META_TABLE_BEGIN(luaAirVehicle, AirVehicle)
        ITEM_IN_TABLE("fly",            luaAirVehicle::l_fly)
    LIST_META_TABLE_END

    LIST_FUNC_TABLE_BEGIN(luaAirVehicle, AirVehicle)
    LIST_FUNC_TABLE_END

    REGISTER_LUA_OBJECT_METHODS(luaAirVehicle)

IMPLEMENT_OPENLIB_METHOD_END

int luaAirVehicle::l_fly(lua_State * ls)
{
    Luapp l(ls);
    int r = l.dispatchToC<AirVehicle>(&AirVehicle::fly, l.toNumber(2));
    l.pop(1);
    l.pushInteger(r);

    return 1;
}

// ---

DEFINE_MODULE_NAME(luaTesla, "Tesla")
DEFINE_META_TABLE_NAME(luaTesla, "F66A760E-3F7F-4F8B-8824-E16C07E02E7C")

IMPLEMENT_OPENLIB_METHOD_BEGIN(luaTesla)
    LIST_META_TABLE_BEGIN(luaTesla, Tesla)
        ITEM_IN_TABLE("charge",         luaTesla::l_charge)
        ITEM_IN_TABLE("bluetooth",      luaTesla::l_bluetooth)
    LIST_META_TABLE_END

    LIST_FUNC_TABLE_BEGIN(luaTesla, Tesla)
    LIST_FUNC_TABLE_END

    REGISTER_LUA_OBJECT_METHODS(luaTesla)
    INHERIT_METHOD_FROM_FATHER(luaCar)

IMPLEMENT_OPENLIB_METHOD_END

int luaTesla::l_charge(lua_State * ls)
{
    Luapp l(ls);
    int r = l.dispatchToC<Tesla>(&Tesla::charge, l.toNumber(2));
    l.pop(1);
    l.pushInteger(r);

    return 1;
}

int luaTesla::l_bluetooth(lua_State * ls)
{
    Luapp l(ls);
    l.dispatchToC<Tesla>(&Tesla::bluetooth, l.toString(2));
    l.pop(1);

    return 0;
}

// ---

DEFINE_MODULE_NAME(luaCar, "Car")
DEFINE_META_TABLE_NAME(luaCar, "77E5E7E8-367F-4A6A-ADE7-3C17A26A0C8D")

IMPLEMENT_OPENLIB_METHOD_BEGIN(luaCar)
    LIST_META_TABLE_BEGIN(luaCar, Car)
        ITEM_IN_TABLE("music",         luaCar::lc_music)
        ITEM_IN_TABLE("navi",          luaCar::lc_navi)
    LIST_META_TABLE_END

    LIST_FUNC_TABLE_BEGIN(luaCar, Car)
    LIST_FUNC_TABLE_END

    REGISTER_LUA_OBJECT_METHODS(luaCar)
    INHERIT_METHOD_FROM_FATHER(luaAuto)

IMPLEMENT_OPENLIB_METHOD_END

int luaCar::lc_music(lua_State * ls)
{
    Luapp l(ls);
    double r = l.dispatchToC<Car>(&Car::music, l.toString(2));
    l.pop(1);
    l.pushNumber(r);

    return 1;
}

int luaCar::lc_navi(lua_State * ls)
{
    Luapp l(ls);
    bool r = l.dispatchToC<Car>(&Car::navi, l.toString(2));
    l.pop(1);
    l.pushBoolean(r);

    return 1;
}

// ---

DEFINE_MODULE_NAME(luaAuto, "Auto")
DEFINE_META_TABLE_NAME(luaAuto, "E141BB75-DE03-4004-A700-936B68242766")

IMPLEMENT_OPENLIB_METHOD_BEGIN(luaAuto)
    LIST_META_TABLE_BEGIN(luaAuto, Auto)
        ITEM_IN_TABLE("drive",         luaAuto::l3_drive)
        ITEM_IN_TABLE("fuel",          luaAuto::l3_fuel)
        ITEM_IN_TABLE("maintain",      luaAuto::l3_maintain)
        ITEM_IN_TABLE("check",         luaAuto::l3_check)
    LIST_META_TABLE_END

    LIST_FUNC_TABLE_BEGIN(luaAuto, Auto)
    LIST_FUNC_TABLE_END

    REGISTER_LUA_OBJECT_METHODS(luaAuto)

IMPLEMENT_OPENLIB_METHOD_END

int luaAuto::l3_drive(lua_State * ls)
{
    Luapp l(ls);
    l.dispatchToC<Auto>(&Auto::drive, l.toString(2), l.toInteger(3), l.toNumber(4));
    l.pop(4);

    return 0;
}

int luaAuto::l3_fuel(lua_State * ls)
{
    Luapp l(ls);
    l.dispatchToC<Auto>(&Auto::fuel, l.toInteger(2));
    l.pop(1);

    return 0;
}

int luaAuto::l3_maintain(lua_State * ls)
{
    Luapp l(ls);
    auto p = l.dispatchToC<Auto>(&Auto::maintain, l.toString(2));

    // 将传入到参数出栈
    l.pop(1);

    // 返回到值如栈
    l.pushInteger(p);

    return 1;
}

int luaAuto::l3_check(lua_State * ls)
{
    Luapp l(ls);
    auto p = l.dispatchToC<Auto>(&Auto::check);

    l.pushString(std::get<0>(p).c_str());
    l.pushInteger(std::get<1>(p));
    l.pushNumber(std::get<2>(p));
    l.pushInteger(std::get<3>(p));

    return 4;
}

// ---

// ---

LUAPPSHARED_C_EXPORT int luaopen_libluaauto(lua_State* L)
{
    static const luaL_Reg lualibs[] =
    {
        {"Auto",                luaAuto::open_luaAuto},
        {"Car",                 luaCar::open_luaCar},
        {"Tesla",               luaTesla::open_luaTesla},
        {"AirVehicle",          luaAirVehicle::open_luaAirVehicle},
        {"Seafaring",           luaSeafaring::open_luaSeafaring},
        {"SuperCar",            luaSuperCar::open_luaSuperCar},
        {NULL, NULL}
    };

    Luapp lp(L);
    return lp.requireLibs(lualibs);
}
