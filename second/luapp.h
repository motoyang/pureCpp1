#ifndef LUAPP_H
#define LUAPP_H

// ---

#ifndef GET_SET_VALUE_FORM_LUA
#define GET_SET_VALUE_FORM_LUA
//auto f_getNil       = [](lua_State * L, int idx) { return lua_toboolean(L, idx); };
auto f_getBoolean   = [](lua_State * L, int idx) { return lua_toboolean(L, idx); };
auto f_getInteger   = [](lua_State * L, int idx) { return lua_tointeger(L, idx); };
auto f_getLong      = [](lua_State * L, int idx) { return (long)lua_tointeger(L, idx); };
auto f_getNumber    = [](lua_State * L, int idx) { return lua_tonumber(L, idx); };
auto f_getString    = [](lua_State * L, int idx) { return lua_tostring(L, idx); };
//auto f_getObjlen    = [](lua_State * L, int idx) { return lua_toobjlen(L, idx); };
//auto f_getBuffer    = [](lua_State * L, int idx, size_t *len) { return lua_tolstring(L, idx, len); };
//auto f_getCFunction = [](lua_State * L, int idx) { return lua_tocfunction(L, idx); };
//auto f_getPointer   = [](lua_State * L, int idx) { return lua_topointer(L, idx); };
//auto f_getThread    = [](lua_State * L, int idx) { return lua_tothread(L, idx); };
//auto f_getUserData  = [](lua_State * L, int idx) { return lua_touserdata(L, idx); };

//auto f_setUserData  = [](lua_State * L, std::result_of<decltype(lua_touserdata)> v) { return lua_pushuserdata(L, v); };
auto f_setNull      = [](lua_State * L) { return lua_pushnil(L); };
auto f_setBoolean   = [](lua_State * L, bool v) { return lua_pushboolean(L, (int)v); };
auto f_setLong      = [](lua_State * L, long v) { return lua_pushinteger(L, v); };
auto f_setFloat     = [](lua_State * L, float v) { return lua_pushnumber(L, (lua_Number)v); };
auto f_setDouble    = [](lua_State * L, double v) { return lua_pushnumber(L, (lua_Number)v); };
auto f_setNumber    = [](lua_State * L, double v) { return lua_pushnumber(L, (lua_Number)v); };
auto f_setInteger   = [](lua_State * L, int v) { return lua_pushinteger(L, v); };
auto f_setString    = [](lua_State * L, const std::string& v) { return lua_pushstring(L, v.c_str()); };
auto f_setBuffer    = [](lua_State * L, const std::string& v, size_t len) { return lua_pushlstring(L, v.c_str(), len); };
#endif

// ---

template<typename T>
void f_push(lua_State * ls, T t);

template<>
void f_push(lua_State * ls, int i);

template<>
void f_push(lua_State *ls, std::string s);

template<>
void f_push(lua_State *ls, double d);

// ---

template<typename T >
void f_pop(lua_State * ls, T& t);

template<>
void f_pop(lua_State * ls, int& i);

template<>
void f_pop(lua_State * ls, double& d);

template<>
void f_pop(lua_State * ls, std::string& s);
// ---

// 逗号表达式展开参数包
// 不通过递归方式来展开参数包，这种方式需要借助逗号表达式和初始化列表。比如前面print的例子可以改成这样
template <typename F, typename... Args>
int expandArgs(lua_State * ls, const F& f, Args&&... args)
{
    std::initializer_list<int> il {(f(ls, std::forward< Args>(args)),0)...};
    return il.size();
}
// 调用方式如下，在printarg函数中，处理每个参数
// 此处不能直接调用printarg，因为模版展开时不能确定具体的类型
// expandArgs([](lua_State *ls, auto t){printarg(std::forward(t));}, 1, 2.2, 3.3, "abcdefg");

// 在popArgs时，不能传入闭包，因为闭包中的auto参数会导致pop不到stack中的值
template <typename... Args>
int popArgs(lua_State * ls, Args&&... args)
{
   int arr[] = {(f_pop(ls, std::forward<Args>(args)), 0)...};
   return sizeof(arr) / sizeof(arr[0]);
}

// ---

void l_output(lua_State * ls, int idx);

// ---

class LuaPP
{
    lua_State *m_ls;

public:
    LuaPP();
    virtual ~LuaPP();

    bool requireLibs(const luaL_Reg *libs);
    bool doFile(const std::string& fname);
    void dumpStack(std::function<void(lua_State*, int)> f = l_output);

    template <typename... Args> int push(Args&&... args)
    {
        int countOfArgs = expandArgs(m_ls,
                [](lua_State *ls, auto t){f_push(ls, t);},
                std::forward<Args>(args)...);

        return countOfArgs;
    }

    template <typename... Args> int pop(Args&&... args)
    {
        int countOfArgs = popArgs(m_ls,
                std::forward<Args>(args)...);

        return countOfArgs;
    }

    template<typename T> int getGlobal(const std::string& name, T& tValue) {
        lua_getglobal(m_ls, name.c_str());
        f_pop(m_ls, tValue);
        return 0;
    }

    template <typename... Args>
    int doFunction(const std::string& name, int countOfResult, Args... args)
    {
        // lua的函数名入栈
        lua_getglobal(m_ls, name.c_str());
        // lua函数的参数入栈
        int countOfArgs = push(std::forward<Args>(args)...);
        // 执行lua函数
        return lua_pcall(m_ls, countOfArgs, countOfResult, 0);
    }
};

#endif // LUAPP_H
