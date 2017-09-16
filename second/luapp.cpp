#include "precompiled.h"
#include "luaobject.h"
#include "luapp.h"

// ---

template<typename T>
void f_push(lua_State * ls, T t)
{
    UNUSED(ls);
    UNUSED(t);
    static_assert( is_decay_same<T, int>::value ||
                is_decay_same<T, double>::value ||
                is_decay_same<T, std::string>::value,
                "error type!");}

template<>
void f_push(lua_State * ls, int i)
{f_setInteger(ls, i);}

template<>
void f_push(lua_State *ls, std::string s)
{f_setString(ls, s);}

template<>
void f_push(lua_State *ls, double d)
{f_setNumber(ls, d);}

//---

template<typename T >
void f_pop(lua_State * ls, T& t)
{
    UNUSED(ls);
    UNUSED(t);
    static_assert( is_decay_same<T, int>::value ||
                is_decay_same<T, double>::value ||
                is_decay_same<T, std::string>::value,
                "error type!");}

template<>
void f_pop(lua_State * ls, int& i)
{i = f_getInteger(ls, -1); lua_pop(ls, 1);}

template<>
void f_pop(lua_State * ls, double& d)
{d = f_getNumber(ls, -1); lua_pop(ls, 1);}

template<>
void f_pop(lua_State * ls, std::string& s)
{s = f_getString(ls, -1); lua_pop(ls, 1);}

// ---

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


void LuaPP::dumpStack(std::function<void(lua_State*, int)> f)
{
    std::cout << "----- stack dump -----" << std::endl;
    int top = lua_gettop(m_ls);
    for (int i = top; i >= 1; --i) {
        f(m_ls, i);
    }
    std::cout << "--------- end --------" << std::endl;
}

//---

void l_output(lua_State * ls, int idx)
{
    std::cout << "[" << idx << "] = ";

    switch (lua_type(ls, idx)) {
    case LUA_TNIL:
        std::cout << "nil" << std::endl;
        break;

    case LUA_TBOOLEAN:
        std::cout << f_getBoolean(ls, idx) << std::endl;
        break;

    case LUA_TNUMBER:
        std::cout << f_getNumber(ls, idx) << std::endl;
        break;

    case LUA_TSTRING:
        std::cout << f_getString(ls, idx) << std::endl;
        break;

    default:
        ;
    }
};
