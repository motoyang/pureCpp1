#include "luapp_global.h"
#include "luapp.h"
#include "fun.h"
#include "luafun.h"

// ---

IMPLEMENT_OPENLIB_FUNCTION_BEGIN(some_funs)
    LIST_FUNCTIONS_BEGIN
        ITEM_IN_FUNCTIONS(add)
    LIST_FUNCTIONS_END
IMPLEMENT_OPENLIB_FUNCTION_END

// ---

int lua_add(lua_State * ls)
{
    Luapp l(ls);
    auto r = l.dispatchToFunction(add, l.toNumber(1), l.toNumber(2));
    l.pop(2);
    l.pushNumber(r);

    return 1;
}
