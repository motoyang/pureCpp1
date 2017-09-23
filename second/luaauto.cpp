#include "precompiled.h"
#include "luapp.h"
#include "luaobject.h"
#include "auto.h"
#include "luaauto.h"

// ---

DEFINE2_META_TABLE_NAME(luaCar, "xt.Car")

IMPLEMENT2_OPENLIB_METHOD_BEGIN(luaCar)
    LIST2_META_TABLE_BEGIN(luaCar, Car)
        ITEM2_IN_TABLE("music",         luaCar::lc_music)
        ITEM2_IN_TABLE("navi",          luaCar::lc_navi)
    LIST2_META_TABLE_END

    LIST2_FUNC_TABLE_BEGIN(luaCar, Car)
    LIST2_FUNC_TABLE_END
//IMPLEMENT2_OPENLIB_METHOD_END(luaCar)
IMPLEMENT2_OPENLIB_METHOD_END2(luaCar, lua3Auto)



int luaCar::lc_music(lua_State * ls)
{
    Luapp l(ls);
    double r = l.put<Car>(mt_luaCar, &Car::music, l.toString(2));
    l.pop(1);
    l.pushNumber(r);

    return 1;
}

int luaCar::lc_navi(lua_State * ls)
{
    Luapp l(ls);
    bool r = l.put<Car>(mt_luaCar, &Car::navi, l.toString(2));
    l.pop(1);
    l.pushBoolean(r);

    return 1;
}

// ---

DEFINE2_META_TABLE_NAME(lua3Auto, "xt3.Auto")

IMPLEMENT2_OPENLIB_METHOD_BEGIN(lua3Auto)
    LIST2_META_TABLE_BEGIN(lua3Auto, Auto)
        ITEM2_IN_TABLE("drive",         lua3Auto::l3_drive)
        ITEM2_IN_TABLE("fuel",          lua3Auto::l3_fuel)
        ITEM2_IN_TABLE("maintain",      lua3Auto::l3_maintain)
        ITEM2_IN_TABLE("check",         lua3Auto::l3_check)
    LIST2_META_TABLE_END

    LIST2_FUNC_TABLE_BEGIN(lua3Auto, Auto)
    LIST2_FUNC_TABLE_END
IMPLEMENT2_OPENLIB_METHOD_END(lua3Auto)

int lua3Auto::l3_drive(lua_State * ls)
{
    Luapp l(ls);
    l.put<Auto>(mt_lua3Auto, &Auto::drive, l.toString(2), l.toInteger(3), l.toNumber(4));
    l.pop(4);

    return 0;
}

int lua3Auto::l3_fuel(lua_State * ls)
{
    Luapp l(ls);
    l.put<Auto>(mt_lua3Auto, &Auto::fuel, l.toInteger(2));
    l.pop(1);

    return 0;
}


int lua3Auto::l3_maintain(lua_State * ls)
{
    Luapp l(ls);
    auto p = l.put<Auto>(mt_lua3Auto, &Auto::maintain, l.toString(2));

    // 将传入到参数出栈
    l.pop(1);

    // 返回到值如栈
    l.pushInteger(p);

    l.dumpStack();

    return 1;
}

int lua3Auto::l3_check(lua_State * ls)
{
    Luapp l(ls);
    l.dumpStack();

    auto p = l.get<Auto>(mt_lua3Auto, &Auto::check);

    l.pushString(std::get<0>(p).c_str());
    l.pushInteger(std::get<1>(p));
    l.pushNumber(std::get<2>(p));
    l.pushInteger(std::get<3>(p));

    l.dumpStack();

    return 4;
}
// ---

const char * lua2Auto::sm_mtlua2Auto = "xt2.Auto";

int lua2Auto::openlua2Auto(lua_State * L)
{
    static const struct luaL_Reg lib_m [] = {
        {"drive",               lua2Auto::l2_drive},
        {"fuel",                lua2Auto::l2_fuel},
        {"maintain",            lua2Auto::l2_maintain},
        {"check",               lua2Auto::l2_check},
        {"__gc",                lua2Auto::deletelua2Auto<Auto>},
        {NULL,                  NULL}
    };

    static const struct luaL_Reg lib_f [] = {
        {"create",      lua2Auto::newlua2Auto<Auto>},
        {NULL,          NULL}
    };

    LUA_OBJECT_REGISTER(L, sm_mtlua2Auto, lib_m, lib_f);

    return 1;
}

int lua2Auto::l2_drive(lua_State * ls)
{
    Luapp l(ls);
    l.put<Auto>(sm_mtlua2Auto, &Auto::drive, l.toString(2), l.toInteger(3), l.toNumber(4));
    l.pop(4);

    return 0;
}

int lua2Auto::l2_fuel(lua_State * ls)
{
    Luapp l(ls);
    l.put<Auto>(sm_mtlua2Auto, &Auto::fuel, l.toInteger(2));
    l.pop(1);

    return 0;
}


int lua2Auto::l2_maintain(lua_State * ls)
{
    Luapp l(ls);
    auto p = l.put<Auto>(sm_mtlua2Auto, &Auto::maintain, l.toString(2));

    // 将传入到参数出栈
    l.pop(1);

    // 返回到值如栈
    l.pushInteger(p);

    l.dumpStack();

    return 1;
}

int lua2Auto::l2_check(lua_State * ls)
{
    Luapp l(ls);
    l.dumpStack();

    auto p = l.get<Auto>(sm_mtlua2Auto, &Auto::check);

    l.pushString(std::get<0>(p).c_str());
    l.pushInteger(std::get<1>(p));
    l.pushNumber(std::get<2>(p));
    l.pushInteger(std::get<3>(p));

    l.dumpStack();

    return 4;
}

// ---

DEFINE_META_TABLE_NAME(luaAuto, "xt.Auto");

IMPLEMENT_OPENLIB_METHOD_BEGIN(luaAuto)
    LIST_META_TABLE_BEGIN(luaAuto, Auto)
        ITEM_IN_TABLE("drive",         luaAuto::l_drive)
        ITEM_IN_TABLE("fuel",          luaAuto::l_fuel)
        ITEM_IN_TABLE("maintain",      luaAuto::l_maintain)
        ITEM_IN_TABLE("check",         luaAuto::l_check)
    LIST_META_TABLE_END

    LIST_FUNC_TABLE_BEGIN(luaAuto, Auto)
        ITEM_IN_TABLE("drive",         luaAuto::l_drive)
        ITEM_IN_TABLE("fuel",          luaAuto::l_fuel)
        ITEM_IN_TABLE("maintain",      luaAuto::l_maintain)
        ITEM_IN_TABLE("check",         luaAuto::l_check)
    LIST_FUNC_TABLE_END
IMPLEMENT_OPENLIB_METHOD_END


int luaAuto::l_drive(lua_State * ls)
{
//    put<Auto>(ls, &Auto::drive,
//                     f_getString(ls, 2),
//                     f_getInteger(ls, 3),
//                     f_getNumber(ls, 4));

    Luapp l(ls);
    l.put<Auto>(sm_metaTable, &Auto::drive, l.toString(2), l.toInteger(3), l.toNumber(4));
    l.pop(4);

    return 0;
}

int luaAuto::l_fuel(lua_State * ls)
{
//    put<Auto>(ls, &Auto::fuel, f_getInteger(ls, 2));

    Luapp l(ls);
    l.put<Auto>(sm_metaTable, &Auto::fuel, l.toInteger(2));
    l.pop(1);

    return 0;
}


int luaAuto::l_maintain(lua_State * ls)
{
    Luapp l(ls);
    auto p = l.put<Auto>(sm_metaTable, &Auto::maintain, l.toString(2));

    // 将传入到参数出栈
    l.pop(1);

    // 返回到值如栈
    l.pushInteger(p);

//    auto p = put<Auto>(ls, &Auto::maintain, f_getString(ls, 2));
//    f_setInteger(ls, p);
//    LuaStack l(ls);
    l.dumpStack();

    return 1;
}

int luaAuto::l_check(lua_State * ls)
{
    Luapp l(ls);
    l.dumpStack();

    auto p = l.get<Auto>(sm_metaTable, &Auto::check);
//    auto p = get<Auto>(ls, &Auto::check);

    l.pushString(std::get<0>(p).c_str());
    l.pushInteger(std::get<1>(p));
    l.pushNumber(std::get<2>(p));
    l.pushInteger(std::get<3>(p));

//    f_setString(ls, std::get<0>(p));
//    f_setInteger(ls, std::get<1>(p));
//    f_setDouble(ls, std::get<2>(p));
//    f_setInteger(ls, std::get<3>(p));

    l.dumpStack();

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


void lua_Auto_test2()
{
    START_FUNC();

    static const luaL_Reg lualibs[] =
    {
        {"base", luaopen_base},
        {"io", luaopen_io},
        {"auto2", lua2Auto::openlua2Auto},
        {NULL, NULL}
    };

    LuaPP luapp;
    luapp.requireLibs(lualibs);
    luapp.doFile("auto3.lua");
}

void lua_Auto_test3()
{
    START_FUNC();


    static const luaL_Reg lualibs[] =
    {
//        {"base", luaopen_base},
//        {"io", luaopen_io},
        {"auto3", lua3Auto::open_lua3Auto},
        {"Car", luaCar::open_luaCar},

        {NULL, NULL}
    };

//    Luapp l(luaL_newstate(), LuaState::LUA_STATE_RESOUECE_TYPE::UNIQUE_LUA_STATE);
//    l.openLibs();
//    l.requireLibs(lualibs);

//    l.pushString("xt3.Auto");
//    l.getTable(LUA_REGISTRYINDEX);
//    l.setGloabl("xt3Auto");

//    l.doFile("auto4.lua");


    auto lp = Luapp::create();
    lp->openLibs();
    lp->requireLibs(lualibs);

//    lp->pushString("xt3.Auto");
//    lp->getTable(LUA_REGISTRYINDEX);
//    lp->getField(LUA_REGISTRYINDEX, "xt3.Auto");
//    lp->setGlobal("xt3Auto");

    lp->doFile("auto4.lua");




//    LuaPP luapp;
//    luapp.requireLibs(lualibs);
//    luapp.openLibs();
//    luapp.doFile("auto4.lua");
}

void lua_Auto_test4()
{
    START_FUNC();

    static const luaL_Reg lualibs[] =
    {
        {"auto3", lua3Auto::open_lua3Auto},
        {"Car", luaCar::open_luaCar},
        {NULL, NULL}
    };

    auto lp = Luapp::create();
    lp->openLibs();
    lp->requireLibs(lualibs);

//    lp->pushString("xt3.Auto");
//    lp->getTable(LUA_REGISTRYINDEX);
//    lp->setGloabl("xt3Auto");

    lp->doFile("auto5.lua");
}

void luapp_test1()
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
    luapp.doFile("auto2.lua");

    luapp.push(2, 3.3);
    luapp.push(std::string("aaa"));

    std::string b("bbb");
    luapp.push(b);

    luapp.dumpStack();

    std::string s1, s2;
    int i1 = 1111;
    double d = 2222;
    luapp.pop(s1, s2, d, i1);
    std::cout << s1 <<", " << s2 << ", " << d << ", " << i1 << std::endl;

    luapp.doFunction("f", 1, 2, 3.0);
    luapp.dumpStack();
    luapp.pop(d);
    std::cout << "restule =" << d << std::endl;
    luapp.dumpStack();

    luapp.getGlobal("width", d);
    std::cout << "width = " << d << std::endl;
    luapp.dumpStack();
}
