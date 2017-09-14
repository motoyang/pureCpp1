#include <iostream>
#include "lua.hpp"
#include "student.h"
#include "luaclass.h"

// ---

// ---

const char* LuaStudent::sm_mateTable = "cc.Student";

int LuaStudent::openlib(lua_State *L)
{
    static const struct luaL_Reg studentlib_m [] = {
        {"setName",     LuaStudent::l_setName},
        {"setAge",      LuaStudent::l_setAge},
        {"print",       LuaStudent::l_print},
        {"getName",     LuaStudent::l_getName},
        {"getAge",      LuaStudent::l_getAge},
        {"__tostring",  LuaStudent::student2string},
        {"__gc",        LuaStudent::auto_gc<Student>},
        {NULL,          NULL}
    };

    static const struct luaL_Reg stuentlib_f [] = {
        {"create",      LuaStudent::newObject<Student>},
        {"setName",     LuaStudent::l_setName},
        {"setAge",      LuaStudent::l_setAge},
        {"print",       LuaStudent::l_print},
        {"getName",     LuaStudent::l_getName},
        {"getAge",      LuaStudent::l_getAge},
        {"__gc",        LuaStudent::auto_gc<Student>},
        {NULL,          NULL}
    };

    LUACLASS_REGISTER(sm_mateTable, studentlib_m, stuentlib_f);

    return 1;
}
/*
int LuaStudent::newStudent(lua_State * L)
{
    Student **s = (Student**)lua_newuserdata(L, sizeof(Student*));  // lua will manage Student** pointer
    *s = new Student;
    luaL_getmetatable(L, sm_mateTable);
    lua_setmetatable(L, -2);

    return 1;
}

int LuaStudent::auto_gc(lua_State *L)
{
    Student **s = (Student**)luaL_checkudata(L,1,"cc.Student");
    if( *s )
    {
        delete *s;
    }

    return 0;
}
*/
int LuaStudent::l_setName(lua_State * L)
{
//    Student **s = (Student**)luaL_checkudata(L,1,"cc.Student");
//    luaL_argcheck(L, s != NULL, 1, "invalid user data");
//    luaL_checktype(L, -1, LUA_TSTRING);
//    std::string name = lua_tostring(L, -1);
//    (*s)->setName(name);

    //    std::function<FB> fn = std::bind(f, *s, std::placeholders::_1);
//    fn(name);

    set1<Student, void(std::string)>(&Student::setName, [] (lua_State * L, int idx) {
        return lua_tostring(L, idx);
    },  L);

    return 0;
}

int LuaStudent::l_setAge(lua_State* L)
{
    Student **s = (Student**)luaL_checkudata(L,1,"cc.Student");
    luaL_argcheck(L, s != NULL, 1, "invalid user data");
    luaL_checktype(L, -1, LUA_TNUMBER);
    int age = lua_tonumber(L, -1);
    (*s)->setAge(age);
    return 0;
}

int LuaStudent::l_getName(lua_State* L)
{
    Student **s = (Student**)luaL_checkudata(L,1,"cc.Student");
    luaL_argcheck(L, s != NULL, 1, "invalid user data");
    lua_settop(L, 0);
    lua_pushstring(L, (*s)->getName().c_str());
    return 1;
}

int LuaStudent::l_getAge(lua_State* L)
{
    Student **s = (Student**)luaL_checkudata(L,1,"cc.Student");
    luaL_argcheck(L, s != NULL, 1, "invalid user data");
    lua_settop(L, 0);
    lua_pushnumber(L, (*s)->getAge());
    return 1;
}

int LuaStudent::l_print(lua_State* L)
{
    Student **s = (Student**)luaL_checkudata(L,1,"cc.Student");
    luaL_argcheck(L, s != NULL, 1, "invalid user data");
    (*s)->print();
    return 0;
}

int LuaStudent::student2string(lua_State* L)
{
    return l_print(L);
}
