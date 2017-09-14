#ifndef LUAPP_H
#define LUAPP_H

#include <lua.hpp>

class LuaPP
{
    lua_State *m_ls;

public:
    LuaPP();
    virtual ~LuaPP();

    bool requireLibs(const luaL_Reg *libs);
    bool doFile(const std::string& fname); 
};
/*
template <typename U>
class LuaWrapper
{
//    T* m_p;

public:
    LuaWrapper()
//        : m_p(nullptr)
    {}

    static int open(lua_State *ls)
    {
        luaL_newmetatable(ls, U::sm_mateTableName);
        lua_pushvalue(ls, -1);
        lua_setfield(ls, -2, "__index");
        luaL_setfuncs(ls, U::sm_mateReg, 0);
        luaL_newlib(ls, U::sm_functionReg);

        return 0;
    }
};
*/
#endif // LUAPP_H
