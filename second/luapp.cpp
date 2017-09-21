#include "precompiled.h"
#include "luaobject.h"
#include "luapp.h"

// ---
/*
template<typename T>
void f_push(lua_State * ls, const T& t)
{
    UNUSED(ls);
    UNUSED(t);
    static_assert( is_decay_same<T, int>::value ||
                is_decay_same<T, double>::value ||
                is_decay_same<T, std::string>::value,
                "error type!");}
*/
template<>
void f_push(lua_State * ls, const int& i)
{f_setInteger(ls, i);}

template<>
void f_push(lua_State *ls, const std::string& s)
{f_setString(ls, s);}

template<>
void f_push(lua_State *ls, const double& d)
{f_setNumber(ls, d);}

//---
/*
template<typename T >
void f_pop(lua_State * ls, T& t)
{
    UNUSED(ls);
    UNUSED(t);
    static_assert( is_decay_same<T, int>::value ||
                is_decay_same<T, double>::value ||
                is_decay_same<T, std::string>::value,
                "error type!");}
*/
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

// ---

LuaStack::LuaStack(lua_State *ls)
    : m_ls(ls)
{

}

LuaStack::~LuaStack()
{

}

void LuaStack::xmove(LuaStack *to, int n)
{
    lua_xmove(m_ls, to->m_ls, n);
}

// ---

LuaThread::LuaThread(lua_State *ls)
    : LuaStack(ls)
{

}

LuaThread::~LuaThread()
{

}

int LuaThread::yieldk(int nresults, lua_KContext ctx, lua_KFunction k)
{
    return lua_yieldk(m_ls, nresults, ctx, k);
}

int LuaThread::status() const
{
    return lua_status(m_ls);
}

int LuaThread::isYieldable() const
{
    return lua_isyieldable(m_ls);
}

// ---

LuaState::LuaState(lua_State *ls, LUA_STATE_RESOUECE_TYPE resourceType)
    : LuaThread(ls), m_lsResource(resourceType)
{

}

LuaState::~LuaState()
{
    if (m_lsResource == LuaState::LUA_STATE_RESOUECE_TYPE::UNIQUE_LUA_STATE) {
        lua_close(m_ls);
        m_ls = nullptr;
        m_lsResource = LuaState::LUA_STATE_RESOUECE_TYPE::NONE_STATE;
    }
}

LuaThread *LuaState::newThread()
{
    lua_State* ls = lua_newthread(m_ls);
    if (!ls) {
        return nullptr;
    }

    return new LuaThread(ls);
}

LuaState *LuaState::create(lua_Alloc f, void *ud)
{
    lua_State * ls = lua_newstate(f, ud);
    if (!ls) {
        return nullptr;
    }

    return new LuaState(ls, LuaState::LUA_STATE_RESOUECE_TYPE::UNIQUE_LUA_STATE);
}

template<typename... Args>
int LuaThread::resume(LuaThread *from, const std::string &func, Args... args)
{
    // lua的函数名入栈
    lua_getglobal(from->m_ls, func.c_str());
    // lua函数的参数入栈
    int countOfArgs = from->push(std::forward<Args>(args)...);
    // 执行lua函数
    return lua_resume(m_ls, from->m_ls, countOfArgs);
}
