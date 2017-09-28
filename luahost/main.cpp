#include "luahost_global.h"

void lua_test1()
{
    auto ls = Luapp::create();
    ls->openLibs();

    ls->doFile("auto1.lua");
    ls->dispatchToLua2("f", 1, 2.2, "3.3");
}

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    lua_test1();
    return 0;
}
