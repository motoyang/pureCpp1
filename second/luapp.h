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

#endif // LUAPP_H
