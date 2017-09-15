#include <iostream>
#include <lua.hpp>
#include "purecpp1.h"
#include "luapp.h"
#include "luaobject.h"
#include "auto.h"
#include "luaauto.h"

// ---

DEFINE_MATE_TABLE_NAME(luaAuto, "xt.Auto");

IMPLEMENT_OPENLIB_METHOD_BEGIN(luaAuto)
    LIST_MATE_TABLE_BEGIN(luaAuto, Auto)
        ITEM_IN_TABLE("drive",         luaAuto::l_drive)
        ITEM_IN_TABLE("fuel",          luaAuto::l_fuel)
        ITEM_IN_TABLE("maintain",      luaAuto::l_maintain)
        ITEM_IN_TABLE("check",         luaAuto::l_check)
    LIST_MATE_TABLE_END

    LIST_FUNC_TABLE_BEGIN(luaAuto, Auto)
        ITEM_IN_TABLE("drive",         luaAuto::l_drive)
        ITEM_IN_TABLE("fuel",          luaAuto::l_fuel)
        ITEM_IN_TABLE("maintain",      luaAuto::l_maintain)
        ITEM_IN_TABLE("check",         luaAuto::l_check)
    LIST_FUNC_TABLE_END
IMPLEMENT_OPENLIB_METHOD_END


int luaAuto::l_drive(lua_State * ls)
{
    put<Auto>(ls, &Auto::drive,
                     f_getString(ls, 2),
                     f_getInteger(ls, 3),
                     f_getNumber(ls, 4));

    return 0;
}

int luaAuto::l_fuel(lua_State * ls)
{
    put<Auto>(ls, &Auto::fuel, f_getInteger(ls, 2));
    return 0;
}


int luaAuto::l_maintain(lua_State * ls)
{
    auto p = put<Auto>(ls, &Auto::maintain, f_getString(ls, 2));
    f_setInteger(ls, p);

    return 1;
}

int luaAuto::l_check(lua_State * ls)
{
    auto p = get<Auto>(ls, &Auto::check);

    f_setString(ls, std::get<0>(p));
    f_setInteger(ls, std::get<1>(p));
    f_setDouble(ls, std::get<2>(p));
    f_setInteger(ls, std::get<3>(p));

    return 4;
}

// ---

void lua_Auto_test1()
{
    START_FUNC();

    static const luaL_Reg lualibs[] =
    {
        {"base", luaopen_base},
        {"io", luaopen_io},
        {"auto", luaAuto::openlib},
        {NULL, NULL}
    };

    LuaPP luapp;
    luapp.requireLibs(lualibs);
    luapp.doFile("auto1.lua");
}
