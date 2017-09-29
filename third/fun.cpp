#include "precompiled.h"
#include "fun.h"

// ---

IMPLEMENT_OPENLIB_FUNCTION_BEGIN(spdlogger)
    LIST_FUNCTIONS_BEGIN
        ITEM_IN_FUNCTIONS(get)
        ITEM_IN_FUNCTIONS(drop)
        ITEM_IN_FUNCTIONS(drop_all)
        ITEM_IN_FUNCTIONS(set_pattern)
        ITEM_IN_FUNCTIONS(set_level)

        ITEM_IN_FUNCTIONS(basic_logger)
        ITEM_IN_FUNCTIONS(rotating_logger)
        ITEM_IN_FUNCTIONS(daily_logger)

        ITEM_IN_FUNCTIONS(stdout_logger)
        ITEM_IN_FUNCTIONS(stderr_logger)
        ITEM_IN_FUNCTIONS(stdout_color)
        ITEM_IN_FUNCTIONS(stderr_color)

    LIST_FUNCTIONS_END
IMPLEMENT_OPENLIB_FUNCTION_END
