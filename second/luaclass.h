#ifndef LUACLASS_H
#define LUACLASS_H

#include <functional>

#define LUACLASS_REGISTER(tn, mt, ft)       \
    luaL_newmetatable(L, tn);               \
    lua_pushvalue(L, -1);                   \
    lua_setfield(L, -2, "__index");         \
    luaL_setfuncs(L, mt, 0);                \
    luaL_newlib(L, ft);

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

    template<typename T, typename FB, typename F>
        static int set(F f, lua_State * L)
        {
            T **s = (T**)luaL_checkudata(L, 1, U::sm_mateTable);
            luaL_argcheck(L, s != NULL, 1, "invalid user data");
            luaL_checktype(L, -1, LUA_TSTRING);
            std::string name = lua_tostring(L, -1);

            std::function<FB> fn = std::bind(f, *s, std::placeholders::_1);
            fn(name);

            return 0;
        }

        // T: 访问的对象类型
        // FB: 方法的类型
        // CM：方法的地址
        // C1: 从lua栈中提取第一个参数的闭包
        template<typename T, typename FB, typename CM, typename C1>
            static int set1(CM f, C1 c1, lua_State * L)
            {
                int n = lua_gettop(L);
                std::cout << n << std::endl;

                T **s = (T**)luaL_checkudata(L, 1, U::sm_mateTable);
                luaL_argcheck(L, s != NULL, 1, "invalid user data");
                auto p1 = c1(L, 2);

                std::function<FB> fn = std::bind(f, *s, std::placeholders::_1);
                fn(p1);

                return 0;
            }
        /*
        template<typename T, typename FB, typename F>
            static int setN(F f, lua_State * L)
            {
                T **s = (T**)luaL_checkudata(L, 1, U::sm_mateTable);
                luaL_argcheck(L, s != NULL, 1, "invalid user data");

                // number of arguments
                int n = lua_gettop(L);
                for (int i = 1; i <= n; i++) {
//                     if (lua_isnumber(L, i)) {
//                       lua_pushliteral(L, "incorrect argument");
//                       lua_error(L);
//                     }
//                 sum += lua_tonumber(L, i);
               }

                std::function<FB> fn;
                switch (n) {

                case 1:
                    std::function<FB> fn = std::bind(f, *s, std::placeholders::_1);
                    break;
                case 2:
                    std::function<FB> fn = std::bind(f, *s, std::placeholders::_1, std::placeholders::_2);
                    break;

                }

                luaL_checktype(L, -1, LUA_TSTRING);
                std::string name = lua_tostring(L, -1);

                std::function<FB> fn = std::bind(f, *s, std::placeholders::_1);
                fn(name);

                return 0;
            }
*/
};

struct LuaStudent : public LuaObject<LuaStudent>
{
    static const char* sm_mateTable;
    static int openlib(lua_State *L);

//    static int newStudent(lua_State * L);
//    static int auto_gc(lua_State *L);
    static int l_setName(lua_State * L);
    static int l_setAge(lua_State* L);
    static int l_getName(lua_State* L);
    static int l_getAge(lua_State* L);
    static int l_print(lua_State* L);
    static int student2string(lua_State* L);
};

#endif // LUACLASS_H
