#ifndef LUAOBJECT_H
#define LUAOBJECT_H

template<typename U>
struct LuaObject
{
    template<typename T>
    static int newObject(lua_State * L)
    {
//        T **s = (T**)lua_newuserdata(L, sizeof(T*));  // lua will manage Student** pointer
//        *s = new T;
//        luaL_getmetatable(L, U::sm_mateTable);
//        lua_setmetatable(L, -2);

        Luapp ls(L);
        T **s = (T**)ls.newUserdata(sizeof(T*));  // lua will manage Student** pointer
        *s = new T;
        ls.getMetatable(U::sm_metaTable);
        ls.setMetatable(-2);

        // 返回给Lua的只有T*一个变量
        return 1;
    }

    template<typename T>
    static int deleteObject(lua_State *L)
    {
        Luapp ls(L);
        T **s = (T**)ls.checkUData(1, U::sm_metaTable);
//        T **s = (T**)luaL_checkudata(L, 1, U::sm_metaTable);
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
//        T **s = (T**)luaL_checkudata(L, 1, U::sm_metaTable);
//        luaL_argcheck(L, s != NULL, 1, "invalid user data");
        Luapp ls(L);
        T **s = (T**)ls.checkUData(1, U::sm_metaTable);
        ls.argCheck(s != nullptr, 1, "invalid user data");

        auto fn = std::bind(f, *s, std::forward<Cn>(args)...);
        return fn();
    }

    template<typename T, typename CM>
    static auto get(lua_State * L, CM f)
    {
//        T **s = (T**)luaL_checkudata(ls, 1, U::sm_metaTable);
//        luaL_argcheck(ls, s != NULL, 1, "invalid user data");
//        lua_settop(ls, 0);
//        ls.setTop(0);
        Luapp ls(L);
        T **s = (T**)ls.checkUData(1, U::sm_metaTable);
        ls.argCheck(s != nullptr, 1, "invalid user data");

        auto fn = std::bind(f, *s);
        return fn();
    }

};

// used in .h file

#define EXPORT_METHOD_TO_LUA(n)                             \
    static int n(lua_State *ls);

struct lua2Auto {
    static const char * sm_mtlua2Auto;
    static int openlua2Auto(lua_State * L);

    template<typename T>
    static int newlua2Auto(lua_State * L)
    {
        Luapp ls(L);
        T **s = (T**)ls.newUserdata(sizeof(T*));  // lua will manage Student** pointer
        *s = new T;
        ls.getMetatable(sm_mtlua2Auto);
        ls.setMetatable(-2);

        // 返回给Lua的只有T*一个变量
        return 1;
    }

    template<typename T>
    static int deletelua2Auto(lua_State *L)
    {
        Luapp ls(L);
        T **s = (T**)ls.checkUData(1, sm_mtlua2Auto);
        if( *s )
        {
            delete *s;
        }

        // 不需要返回lua任何变量
        return 0;
    }

    EXPORT_METHOD_TO_LUA(l2_drive)
    EXPORT_METHOD_TO_LUA(l2_fuel)
    EXPORT_METHOD_TO_LUA(l2_maintain)
    EXPORT_METHOD_TO_LUA(l2_check)
};



// used in .h file.
#define DECLARE_LUA_OBJECT_BEGIN(o)                         \
    struct o : public LuaObject<o> {                        \
    static const char* sm_metaTable;                        \
    static int openlib(lua_State *L);

#define EXPORT_METHOD_TO_LUA(n)                             \
    static int n(lua_State *ls);

#define DECLARE_LUA_OBJECT_END                              \
    };

// used in .cpp file.
#define DEFINE_META_TABLE_NAME(o, n)                \
    const char* o::sm_metaTable = (n);

#define IMPLEMENT_OPENLIB_METHOD_BEGIN(o)           \
    int o::openlib(lua_State *ls)                   \
    {

#define LIST_META_TABLE_BEGIN(lo, co)               \
        static const struct luaL_Reg lib_m [] = {   \
        {"__gc",        lo::deleteObject<co>},

#define ITEM_IN_TABLE(luaMethod, cppMethod)         \
    {(luaMethod), (cppMethod) },

#define LIST_META_TABLE_END                         \
    {NULL,          NULL}                           \
    };

#define LIST_FUNC_TABLE_BEGIN(lo, co)               \
        static const struct luaL_Reg lib_f [] = {   \
        {"create",      lo::newObject<co>},

#define LIST_FUNC_TABLE_END                         \
    {NULL,          NULL}                           \
    };

#define LUA_OBJECT_REGISTER(ls, tn, mt, ft)         \
    luaL_newmetatable((ls), (tn));                  \
    lua_pushvalue((ls), -1);                        \
    lua_setfield((ls), -2, "__index");              \
    luaL_setfuncs((ls), (mt), 0);                   \
    luaL_newlib((ls), (ft));

#define IMPLEMENT_OPENLIB_METHOD_END                \
    LUA_OBJECT_REGISTER(ls, sm_metaTable, lib_m, lib_f);        \
    return 1;                                                   \
}

void lua_test7();
void lua_test8();

#endif // LUAOBJECT_H
