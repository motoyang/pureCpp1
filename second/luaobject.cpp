#include "precompiled.h"
#include "luapp.h"
#include "luaobject.h"




/*

#include <lauxlib.h>
#include <lua.h>

void traverse_table(lua_State *L, int index)
{
    lua_pushnil(L);
    // 现在的栈：-1 => nil; index => table
    while (lua_next(L, index))
    {
        // 现在的栈：-1 => value; -2 => key; index => table
        // 拷贝一份 key 到栈顶，然后对它做 lua_tostring 就不会改变原始的 key 值了
        lua_pushvalue(L, -2);
        // 现在的栈：-1 => key; -2 => value; -3 => key; index => table
        const char* key = lua_tostring(L, -1);
        const char* value = lua_tostring(L, -2);

        printf("%s => %s\n", key, value);

        // 弹出 value 和拷贝的 key，留下原始的 key 作为下一次 lua_next 的参数
        lua_pop(L, 2);
        // 现在的栈：-1 => key; index => table
    }
    // 现在的栈：index => table （最后 lua_next 返回 0 的时候它已经把上一次留下的 key 给弹出了）
    // 所以栈已经恢复到进入这个函数时的状态
}

int main()
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // 假设现在栈上已经有了一个 talbe，内容为 {one=1,[2]='two',three=3}，位置在 top

    traverse_table(L, -1);

    return 0;
}
*/
