#include <iostream>
#include <lua.hpp>
#include "purecpp1.h"
#include "student.h"
#include "luapp.h"
#include "luaobject.h"

// ---

const char* LuaStudent::sm_mateTable = "cc.Student";

int LuaStudent::openlib(lua_State *ls)
{
    static const struct luaL_Reg studentlib_m [] = {
        {"setName",     LuaStudent::l_setName},
        {"setAge",      LuaStudent::l_setAge},
        {"setNA",       LuaStudent::l_setNA},
        {"print",       LuaStudent::l_print},
        {"getName",     LuaStudent::l_getName},
        {"getAge",      LuaStudent::l_getAge},
        {"set3Value",   LuaStudent::l_set3Value},
        {"set4Value",   LuaStudent::l_set4Value},
        {"get4Value",   LuaStudent::l_get4Value},
        {"print4",      LuaStudent::l_print4},
        {"__tostring",  LuaStudent::student2string},
        {"__gc",        LuaStudent::deleteObject<Student>},
        {NULL,          NULL}
    };

    static const struct luaL_Reg stuentlib_f [] = {
        {"create",      LuaStudent::newObject<Student>},
        {"setName",     LuaStudent::l_setName},
        {"setAge",      LuaStudent::l_setAge},
        {"setNA",       LuaStudent::l_setNA},
        {"print",       LuaStudent::l_print},
        {"getName",     LuaStudent::l_getName},
        {"getAge",      LuaStudent::l_getAge},
        {"set3Value",   LuaStudent::l_set3Value},
        {"set4Value",   LuaStudent::l_set4Value},
        {"get4Value",   LuaStudent::l_get4Value},
        {"print4",      LuaStudent::l_print4},
        {NULL,          NULL}
    };

    LUA_OBJECT_REGISTER(ls, sm_mateTable, studentlib_m, stuentlib_f);

    return 1;
}

int LuaStudent::l_setName(lua_State * ls)
{
    put<Student>(ls, &Student::setName, f_getString(ls, 2));
    return 0;
}

int LuaStudent::l_setNA(lua_State *ls)
{
    put<Student>(ls, &Student::setNA, f_getString(ls, 2), f_getInteger(ls, 3));
    return 0;
}

int LuaStudent::l_setAge(lua_State* ls)
{
    put<Student>(ls, &Student::setAge, f_getInteger(ls, 2));
    return 0;
}

int LuaStudent::l_getName(lua_State* ls)
{
    auto p = get<Student>(ls, &Student::getName);
    f_setString(ls, p);
    return 1;
}

int LuaStudent::l_getAge(lua_State* ls)
{
    auto p = get<Student>(ls, &Student::getAge);
    f_setInteger(ls, p);
    return 1;
}

int LuaStudent::l_print(lua_State* ls)
{
    put<Student>(ls, &Student::print);
    return 0;
}

int LuaStudent::student2string(lua_State* L)
{
    return l_print(L);
}

int LuaStudent::l_set3Value(lua_State* ls)
{
    put<Student>(ls, &Student::set3Value,
                        f_getInteger(ls, 2),
                        f_getInteger(ls, 3),
                        f_getString(ls, 4));
    return 0;
}

int LuaStudent::l_set4Value(lua_State *ls)
{
    put<Student>(ls, &Student::set4Value,
                        f_getInteger(ls, 2),
                        f_getString(ls, 3),
                        f_getNumber(ls, 4),
                        f_getInteger(ls, 5));
    return 0;
}

int LuaStudent::l_get4Value(lua_State *ls)
{
    auto r = get<Student>(ls, &Student::get4Value);
    f_setInteger(ls, std::get<0>(r));
    f_setLong(ls, std::get<1>(r));
    f_setString(ls, std::get<2>(r));
    f_setFloat(ls, std::get<3>(r));

    return 4;
}

int LuaStudent::l_print4(lua_State *ls)
{
    put<Student>(ls, &Student::print4);
    return 0;
}

// ---

void lua_test7()
{
    START_FUNC();

    static const luaL_Reg lualibs[] =
    {
        {"base", luaopen_base},
        {"io", luaopen_io},
//        {"cc",luaopen_student},
        {"cc", LuaStudent::openlib},
        {NULL, NULL}
    };

    LuaPP luapp;
    luapp.requireLibs(lualibs);
    luapp.doFile("hello8.lua");
}

void lua_test8()
{
    START_FUNC();

    static const luaL_Reg lualibs[] =
    {
        {"base", luaopen_base},
        {"io", luaopen_io},
//        {"cc",luaopen_student},
        {"cc", LuaStudent::openlib},
        {NULL, NULL}
    };

    LuaPP luapp;
    luapp.requireLibs(lualibs);
    luapp.doFile("hello9.lua");
}
