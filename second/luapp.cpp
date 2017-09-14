#include <iostream>
#include <lua.hpp>
#include "purecpp1.h"
#include "luapp.h"

LuaPP::LuaPP()
    : m_ls(nullptr)
{

}

LuaPP::~LuaPP()
{
    if (m_ls) {
        lua_close(m_ls);
        m_ls = nullptr;
    }
}

bool LuaPP::requireLibs(const luaL_Reg *libs)
{
    m_ls = luaL_newstate();
    if (!m_ls) {
        // TODO:

        return false;
    }

    for(const luaL_Reg *lib = libs; lib->func != NULL; lib++)
    {
        luaL_requiref(m_ls, lib->name, lib->func, 1);
        lua_pop(m_ls, 1);
    }

    return true;
}

bool LuaPP::doFile(const std::string& fname)
{
    bool r = false;

    std::string scriptPath = fname;
    int status = luaL_loadfile(m_ls, fname.c_str());

    if(status == LUA_OK)
    {
        lua_pcall(m_ls, 0, LUA_MULTRET, 0);
    }
    else
    {
        // TODO:
        std::cerr << " Could not load the script. error no.: " << status << std::endl;
        r = false;
    }

    return r;
}

