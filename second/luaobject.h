#ifndef LUAOBJECT_H
#define LUAOBJECT_H

#ifndef LUA_OBJECT_REGISTER
#define LUA_OBJECT_REGISTER(ls, tn, mt, ft)         \
    luaL_newmetatable((ls), (tn));                  \
    lua_pushvalue((ls), -1);                        \
    lua_setfield((ls), -2, "__index");              \
    luaL_setfuncs((ls), (mt), 0);                   \
    luaL_newlib((ls), (ft));
#endif

#ifndef GET_SET_VALUE_FORM_LUA
#define GET_SET_VALUE_FORM_LUA
auto f_getBoolean   = [](lua_State * L, int idx) { return lua_toboolean(L, idx); };
auto f_getCFunction = [](lua_State * L, int idx) { return lua_tocfunction(L, idx); };
auto f_getInteger   = [](lua_State * L, int idx) { return lua_tointeger(L, idx); };
auto f_getLong      = [](lua_State * L, int idx) { return (long)lua_tointeger(L, idx); };
auto f_getNumber    = [](lua_State * L, int idx) { return lua_tonumber(L, idx); };
auto f_getPointer   = [](lua_State * L, int idx) { return lua_topointer(L, idx); };
auto f_getString    = [](lua_State * L, int idx) { return lua_tostring(L, idx); };
auto f_getThread    = [](lua_State * L, int idx) { return lua_tothread(L, idx); };
auto f_getUserData  = [](lua_State * L, int idx) { return lua_touserdata(L, idx); };

//auto f_setUserData  = [](lua_State * L, std::result_of<decltype(lua_touserdata)> v) { return lua_pushuserdata(L, v); };
auto f_setLong      = [](lua_State * L, long v) { return lua_pushnumber(L, v); };
auto f_setFloat     = [](lua_State * L, float v) { return lua_pushnumber(L, v); };
auto f_setDouble    = [](lua_State * L, float v) { return lua_pushnumber(L, v); };
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

        // 返回给Lua的只有T*一个变量
        return 1;
    }

    template<typename T>
    static int deleteObject(lua_State *L)
    {
        T **s = (T**)luaL_checkudata(L, 1, U::sm_mateTable);
        if( *s )
        {
            delete *s;
        }

        // 不需要返回lua任何变量
        return 0;
    }

    // T: 访问的对象类型
    // CM：类方法的地址
    // Cn: 从lua栈中提取参数的闭包
    template<typename T, typename CM, typename... Cn>
    static auto put(lua_State * L, CM f, Cn... args)
    {
        T **s = (T**)luaL_checkudata(L, 1, U::sm_mateTable);
        luaL_argcheck(L, s != NULL, 1, "invalid user data");

        auto fn = std::bind(f, *s, std::forward<Cn>(args)...);
        return fn();
    }

    template<typename T, typename CM>
    static auto get(lua_State * ls, CM f)
    {
        T **s = (T**)luaL_checkudata(ls, 1, U::sm_mateTable);
        luaL_argcheck(ls, s != NULL, 1, "invalid user data");
        lua_settop(ls, 0);

        auto fn = std::bind(f, *s);
        return fn();
    }

};

// used in .h file.
#define DECLARE_LUA_OBJECT_BEGIN(o)                         \
    struct o : public LuaObject<o> {                        \
    static const char* sm_mateTable;                        \
    static int openlib(lua_State *L);

#define EXPORT_METHOD_TO_LUA(n)                             \
    static int n(lua_State *ls);

#define DECLARE_LUA_OBJECT_END                              \
    };

// used in .cpp file.
#define DEFINE_MATE_TABLE_NAME(o, n)                \
    const char* o::sm_mateTable = (n);

#define IMPLEMENT_OPENLIB_METHOD_BEGIN(o)           \
    int o::openlib(lua_State *ls)                   \
    {

#define LIST_MATE_TABLE_BEGIN(lo, co)               \
        static const struct luaL_Reg lib_m [] = {   \
        {"__gc",        lo::deleteObject<co>},

#define ITEM_IN_TABLE(luaMethod, cppMethod)         \
    {(luaMethod), (cppMethod) },

#define LIST_MATE_TABLE_END                         \
    {NULL,          NULL}                           \
    };

#define LIST_FUNC_TABLE_BEGIN(lo, co)               \
        static const struct luaL_Reg lib_f [] = {   \
        {"create",      lo::newObject<co>},

#define LIST_FUNC_TABLE_END                         \
    {NULL,          NULL}                           \
    };

#define IMPLEMENT_OPENLIB_METHOD_END                \
    LUA_OBJECT_REGISTER(ls, sm_mateTable, lib_m, lib_f);        \
    return 1;                                                   \
}

void lua_test7();
void lua_test8();

#endif // LUAOBJECT_H
