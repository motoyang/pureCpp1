#ifndef LUAOBJECT_H
#define LUAOBJECT_H

//#include <functional>
//#include "purecpp1.h"

#ifndef LUA_OBJECT_REGISTER
#define LUA_OBJECT_REGISTER(tn, mt, ft)     \
    luaL_newmetatable(L, tn);               \
    lua_pushvalue(L, -1);                   \
    lua_setfield(L, -2, "__index");         \
    luaL_setfuncs(L, mt, 0);                \
    luaL_newlib(L, ft);
#endif

#ifndef GET_SET_VALUE_FORM_LUA
#define GET_SET_VALUE_FORM_LUA
auto f_getBoolean   = [](lua_State * L, int idx) { return lua_toboolean(L, idx); };
auto f_getCFunction = [](lua_State * L, int idx) { return lua_tocfunction(L, idx); };
auto f_getInteger   = [](lua_State * L, int idx) { return lua_tointeger(L, idx); };
//auto f_getLong      = [](lua_State * L, int idx) { return (long)lua_tointeger(L, idx); };
auto f_getNumber    = [](lua_State * L, int idx) { return lua_tonumber(L, idx); };
auto f_getPointer   = [](lua_State * L, int idx) { return lua_topointer(L, idx); };
auto f_getString    = [](lua_State * L, int idx) { return lua_tostring(L, idx); };
auto f_getThread    = [](lua_State * L, int idx) { return lua_tothread(L, idx); };
auto f_getUserData  = [](lua_State * L, int idx) { return lua_touserdata(L, idx); };

//auto f_setUserData  = [](lua_State * L, std::result_of<decltype(lua_touserdata)> v) { return lua_pushuserdata(L, v); };
auto f_setLong      = [](lua_State * L, long v) { return lua_pushnumber(L, v); };
auto f_setFloat     = [](lua_State * L, float v) { return lua_pushnumber(L, v); };
auto f_setInteger   = [](lua_State * L, int v) { return lua_pushnumber(L, v); };
auto f_setString    = [](lua_State * L, const std::string& v) { return lua_pushstring(L, v.c_str()); };

#endif

template<typename U>
struct LuaObject
{
    template<typename T>
    static int newObject(lua_State * L)
    {
        T **s = (T**)lua_newuserdata(L, sizeof(T*));  // lua will manage Student** pointer
        *s = new T;
        luaL_getmetatable(L, U::sm_mateTable);
        lua_setmetatable(L, -2);

        return 1;
    }

    template<typename T>
    static int auto_gc(lua_State *L)
    {
        T **s = (T**)luaL_checkudata(L, 1, U::sm_mateTable);
        if( *s )
        {
            delete *s;
        }

        return 0;
    }

    // T: 访问的对象类型
    // CM：方法的地址
    // C1: 从lua栈中提取第一个参数的闭包
    template<typename T, typename CM, typename C1>
    static int set1(lua_State * ls, CM f, C1 c1)
    {
        T **s = (T**)luaL_checkudata(ls, 1, U::sm_mateTable);
        luaL_argcheck(ls, s != NULL, 1, "invalid user data");

//        auto fn = std::bind(f, *s, std::placeholders::_1);
        std::bind(f, *s, c1(ls, 2))();
//        fn(c1(ls, 2));

        return 0;
    }

    template<typename T, typename CM, typename C1, typename C2>
    static int set2(lua_State * L, CM f, C1 c1, C2 c2)
    {
        T **s = (T**)luaL_checkudata(L, 1, U::sm_mateTable);
        luaL_argcheck(L, s != NULL, 1, "invalid user data");
        auto p1 = c1(L, 2);
        auto p2 = c2(L, 3);

        auto fn = std::bind(f, *s, std::placeholders::_1, std::placeholders::_2);
        fn(p1, p2);

        return 0;
    }

    template<typename T, typename CM, typename C1, typename C2, typename C3>
    static int set3(lua_State * L, CM f, C1 c1, C2 c2, C3 c3)
    {
        T **s = (T**)luaL_checkudata(L, 1, U::sm_mateTable);
        luaL_argcheck(L, s != NULL, 1, "invalid user data");
        auto p1 = c1(L, 2);
        auto p2 = c2(L, 3);

        auto fn = std::bind(f, *s, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        fn(p1, p2, c3(L, 4));

        return 0;
    }

    template<typename T, typename CM, typename... Cn>
    static int setN(lua_State * L, CM f, Cn... args)
    {
        T **s = (T**)luaL_checkudata(L, 1, U::sm_mateTable);
        luaL_argcheck(L, s != NULL, 1, "invalid user data");

        auto fn = std::bind(f, *s, std::forward<Cn>(args)...);
        fn();

        return 0;
    }

    template<typename T, typename CM, typename C1, typename C2, typename C3, typename C4>
    static int set4(lua_State * L, CM f, C1 c1, C2 c2, C3 c3, C4 c4)
    {
        T **s = (T**)luaL_checkudata(L, 1, U::sm_mateTable);
        luaL_argcheck(L, s != NULL, 1, "invalid user data");
        auto p1 = c1(L, 2);
        auto p2 = c2(L, 3);

        auto fn = std::bind(f, *s, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
        fn(p1, p2, c3(L, 4), c4(L, 5));

        return 0;
    }

    template<typename T, typename CM, typename C1>
    static int get1(lua_State * ls, CM f, C1 c1)
    {
        T **s = (T**)luaL_checkudata(ls, 1, U::sm_mateTable);
        luaL_argcheck(ls, s != NULL, 1, "invalid user data");
        lua_settop(ls, 0);

        auto fn = std::bind(f, *s);
        c1(ls, fn());

        return 1;
    }

    template<typename T, typename CM, typename C1, typename C2, typename C3, typename C4>
    static int get4(lua_State * ls, CM f, C1 c1, C2 c2, C3 c3, C4 c4)
    {
        T **s = (T**)luaL_checkudata(ls, 1, U::sm_mateTable);
        luaL_argcheck(ls, s != NULL, 1, "invalid user data");
        lua_settop(ls, 0);

        auto fn = std::bind(f, *s);
        auto r = fn();

        c1(ls, std::get<0>(r));
        c2(ls, std::get<1>(r));
        c3(ls, std::get<2>(r));
        c4(ls, std::get<3>(r));

        return 4;
    }

    template<typename T, typename CM>
    static auto getN(lua_State * ls, CM f)
    {
        T **s = (T**)luaL_checkudata(ls, 1, U::sm_mateTable);
        luaL_argcheck(ls, s != NULL, 1, "invalid user data");
        lua_settop(ls, 0);

        auto fn = std::bind(f, *s);
        return fn();
    }

    template<typename T, typename CM>
    static int doSomething(lua_State * ls, CM f)
    {
//        T **s = (T**)luaL_checkudata(ls, 1, U::sm_mateTable);
//        luaL_argcheck(ls, s != NULL, 1, "invalid user data");

//        auto fn = std::bind(f, *s);
//        fn();

//        return 0;

        getN<T>(ls, f);
        return 0;
//        return setN<T>(ls, f);
    }

};

struct LuaStudent : public LuaObject<LuaStudent>
{
    static const char* sm_mateTable;
    static int openlib(lua_State *L);

    static int l_setName(lua_State * L);
    static int l_setAge(lua_State* L);
    static int l_setNA(lua_State* L);
    static int l_getName(lua_State* L);
    static int l_getAge(lua_State* L);
    static int l_print(lua_State* L);
    static int student2string(lua_State* L);

    static int l_set3Value(lua_State* ls);
    static int l_set4Value(lua_State* ls);
    static int l_get4Value(lua_State* ls);
    static int l_print4(lua_State* ls);
};

void lua_test7();
void lua_test8();

#endif // LUAOBJECT_H
