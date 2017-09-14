#include <iostream>
#include <sstream>
#include "lua.hpp"
#include "luaobject.h"
#include "purecpp1.h"

using namespace std;

void lua_test()
{
    //1. 初始化Lua虚拟机
    lua_State *lua_state;
    lua_state = luaL_newstate();

    //2.设置待注册的Lua标准库，这个库是给你的Lua脚本用的
    //因为接下来我们只想在Lua脚本里面输出hello world，所以只引入基本库就可以了
    static const luaL_Reg lualibs[] =
    {
        { "base", luaopen_base },
        { NULL, NULL}
    };

    //3.注册Lua标准库并清空栈
    const luaL_Reg *lib = lualibs;
    for(; lib->func != NULL; lib++)
    {
        luaL_requiref(lua_state, lib->name, lib->func, 1);
        lua_pop(lua_state, 1);
    }

    //4、运行hello.lua脚本
    luaL_dofile(lua_state, "hello.lua");

    //5. 关闭Lua虚拟机
    lua_close(lua_state);
}


int luaAdd(lua_State *lua_state , int x, int y)
{
    int sum;
    //获取lua里面的add函数并把它放到lua的栈顶
    lua_getglobal(lua_state, "add");
    //往lua栈里面压入两个参数
    lua_pushnumber(lua_state, x);
    lua_pushnumber(lua_state, y);
    //调用lua函数,这里的2是参数的个数，1是返回值的个数
    lua_call(lua_state, 2, 1);
    //从栈顶读取返回值,注意这里的参数是-1
    sum = lua_tointeger(lua_state, -1);
    //最后我们把返回值从栈顶拿掉
    lua_pop(lua_state, 1);
    return sum;
}

void lua_test2()
{
    static const luaL_Reg lualibs[] =
    {
        {"base", luaopen_base},
        {"io", luaopen_io},
        {NULL, NULL}
    };

    lua_State *lua_state;
    lua_state = luaL_newstate();

    const luaL_Reg *lib = lualibs;
    for(; lib->func != NULL; lib++)
    {
        luaL_requiref(lua_state, lib->name, lib->func, 1);
        lua_pop(lua_state,1);
    }


    lua_pushstring(lua_state, "World333");
    lua_setglobal(lua_state, "myname2");

    lua_getglobal(lua_state, "myname2");
    std::string myname = lua_tostring(lua_state, -1);
    lua_pop(lua_state, 1);
    std::cout<<"Hello: "<<myname<<std::endl;

    std::string scriptPath = ("hello2.lua");
    int status = luaL_loadfile(lua_state, scriptPath.c_str());
    std::cout << " return: " << status << std::endl;
    int result = 0;
    if(status == LUA_OK)
    {
        result = lua_pcall(lua_state, 0, LUA_MULTRET, 0);
    }
    else
    {
        std::cout << " Could not load the script." << std::endl;
    }

    std::cout<< "2 + 1= " << luaAdd(lua_state,4,1)<<std::endl;

    lua_getglobal(lua_state, "myname");
    myname = lua_tostring(lua_state, -1);
    lua_pop(lua_state, 1);
    std::cout<<"Hello: "<<myname<<std::endl;

}


void luaAbc(lua_State *lua_state)
{
    //获取lua里面的add函数并把它放到lua的栈顶
    lua_getglobal(lua_state, "abc");
    //调用lua函数,这里的2是参数的个数，1是返回值的个数
    lua_call(lua_state, 0, 3);

    std::stringstream str_buf;
        while(lua_gettop(lua_state))
        {
            str_buf.str(std::string());
            str_buf << " ";
            switch(lua_type(lua_state, lua_gettop(lua_state)))
            {
                case LUA_TNUMBER:
                    str_buf << "script returned the number: "
                    << lua_tonumber(lua_state, lua_gettop(lua_state));
                    break;
                case LUA_TTABLE:
                    str_buf << "script returned a table";
                    break;
                case LUA_TSTRING:
                    str_buf << "script returned the string: "
                    << lua_tostring(lua_state, lua_gettop(lua_state));
                    break;
                case LUA_TBOOLEAN:
                    str_buf << "script returned the boolean: "
                    << lua_toboolean(lua_state, lua_gettop(lua_state));
                    break;
                default:
                    str_buf << "script returned an unknown-type value";
            }
            lua_pop(lua_state, 1);
            std::cout << str_buf.str() << std::endl;
        }

}
void lua_test3()
{
    static const luaL_Reg lualibs[] =
    {
        {"base", luaopen_base},
        {"io", luaopen_io},
        {NULL, NULL}
    };

    lua_State *lua_state;
    lua_state = luaL_newstate();

    const luaL_Reg *lib = lualibs;
    for(; lib->func != NULL; lib++)
    {
        luaL_requiref(lua_state, lib->name, lib->func, 1);
        lua_pop(lua_state,1);
    }

    lua_createtable(lua_state, 2, 0);
        lua_pushnumber(lua_state, 1);
        lua_pushnumber(lua_state, 49);
    //    lua_settable(lua_state, -3);
        lua_rawset(lua_state, -3);
        lua_pushnumber(lua_state, 2);
        lua_pushstring(lua_state, "Life is a beach");
    //    lua_settable(lua_state, -3);
        lua_rawset(lua_state, -3);
        lua_setglobal(lua_state, "arg");

        std::string scriptPath = ("hello4.lua");
        int status = luaL_loadfile(lua_state, scriptPath.c_str());
        std::cout << " return: " << status << std::endl;
        int result = 0;
        if(status == LUA_OK)
        {
            result = lua_pcall(lua_state, 0, LUA_MULTRET, 0);
        }
        else
        {
            std::cout << " Could not load the script." << std::endl;
        }

        luaAbc(lua_state);

}

int average(lua_State *L)
{
    // get number of arguments
    int n = lua_gettop(L);
    double sum = 0;
    int i;
    // loop through each argument
    for (i = 1; i <= n; i++)
    {
        // total the arguments
        sum += lua_tonumber(L, i);
    }
    // push the average
    lua_pushnumber(L, sum / n);
    // push the sum
    lua_pushnumber(L, sum);
    // return the number of results
    return 2;
}

void lua_test4()
{
    static const luaL_Reg lualibs[] =
    {
        {"base", luaopen_base},
        {"io", luaopen_io},
        {NULL, NULL}
    };

    lua_State *lua_state;
    lua_state = luaL_newstate();

    const luaL_Reg *lib = lualibs;
    for(; lib->func != NULL; lib++)
    {
        luaL_requiref(lua_state, lib->name, lib->func, 1);
        lua_pop(lua_state,1);
    }

    lua_register(lua_state, "average", average);

    std::string scriptPath = ("hello5.lua");
    int status = luaL_loadfile(lua_state, scriptPath.c_str());
    std::cout << " return: " << status << std::endl;
    int result = 0;
    if(status == LUA_OK)
    {
        result = lua_pcall(lua_state, 0, LUA_MULTRET, 0);
    }
    else
    {
        std::cout << " Could not load the script." << std::endl;
    }
}

int displayLuaFunction(lua_State *l)
{
    // number of input arguments
    int argc = lua_gettop(l);
    // print input arguments
    std::cout << "[C++] Function called from Lua with " << argc
              << " input arguments" << std::endl;
    for(int i=0; i<argc; i++)
    {
        std::cout << " input argument #" << argc-i << ": "
                  << lua_tostring(l, lua_gettop(l)) << std::endl;
        lua_pop(l, 1);
    }
    // push to the stack the multiple return values
    std::cout << "[C++] Returning some values" << std::endl;
    lua_pushnumber(l, 12);
    lua_pushstring(l, "See you space cowboy");
    // number of return values
    return 2;
}

void lua_test5()
{
    static const luaL_Reg lualibs[] =
    {
        {"base", luaopen_base},
        {"io", luaopen_io},
        {NULL, NULL}
    };

    lua_State *lua_state;
    lua_state = luaL_newstate();

    const luaL_Reg *lib = lualibs;
    for(; lib->func != NULL; lib++)
    {
        luaL_requiref(lua_state, lib->name, lib->func, 1);
        lua_pop(lua_state,1);
    }

    // push the C++ function to be called from Lua
   std::cout << "[C++] Pushing the C++ function" << std::endl;
   lua_pushcfunction(lua_state, displayLuaFunction);
   lua_setglobal(lua_state, "displayLuaFunction");

    std::string scriptPath = ("hello6.lua");
    int status = luaL_loadfile(lua_state, scriptPath.c_str());
    std::cout << " return: " << status << std::endl;
    int result = 0;
    if(status == LUA_OK)
    {
        result = lua_pcall(lua_state, 0, LUA_MULTRET, 0);
    }
    else
    {
        std::cout << " Could not load the script." << std::endl;
    }
}

int lua_openmylib(lua_State *L)
{
    static const luaL_Reg mylibs[]=
    {
        {"average", average},
        {"displayLuaFunction", displayLuaFunction},
        {NULL, NULL}
    };

    luaL_newlib(L, mylibs);
    return 1;
}

void lua_test6()
{
    static const luaL_Reg lualibs[] =
    {
        {"base", luaopen_base},
        {"io", luaopen_io},
        {"mylib", lua_openmylib},
        {NULL, NULL}
    };

    lua_State *lua_state;
    lua_state = luaL_newstate();

    const luaL_Reg *lib = lualibs;
    for(; lib->func != NULL; lib++)
    {
        luaL_requiref(lua_state, lib->name, lib->func, 1);
        lua_pop(lua_state,1);
    }

    std::string scriptPath = ("hello7.lua");
    int status = luaL_loadfile(lua_state, scriptPath.c_str());
    std::cout << " return: " << status << std::endl;
    int result = 0;
    if(status == LUA_OK)
    {
        result = lua_pcall(lua_state, 0, LUA_MULTRET, 0);
    }
    else
    {
        std::cout << " Could not load the script." << std::endl;
    }
}

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

//    lua_test();
//    lua_test2();
//    lua_test3();
//    lua_test4();
//    lua_test5();
//    lua_test6();
    lua_test7();
    lua_test8();


    cout << "222Hello World!" << endl;
    return 0;
}
