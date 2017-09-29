#include "luaspdlogger_global.h"
#include "luaspdlogger.h"
#include "luafun.h"

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

// ---

spdlog::logger* getLogger(lua_State* ls)
{
    Luapp l(ls);
    spdlog::logger **s = (spdlog::logger**)l.checkUData(1, lua_spdlogger_object::mt_lua_spdlogger_object);
    l.argCheck(s != nullptr, 1, "invalid user data");

    return *s;
}

int lua_get(lua_State * ls)
{
    Luapp lp(ls);
    std::string name(lp.toString(1));
    auto logger = spdlog::get(name);

    spdlog::logger **s = (spdlog::logger**)lp.newUserdata(sizeof(spdlog::logger*));
    *s = logger.get();

    lp.getMetatable(lua_spdlogger_object::mt_lua_spdlogger_object);
    lp.setMetatable(-2);

    // 返回给Lua的只有logger*一个变量
    return 1;
}

int lua_drop(lua_State * ls)
{
    Luapp lp(ls);
    std::string name(lp.toString(1));
    spdlog::drop(name);

    return 0;
}

int lua_drop_all(lua_State * ls)
{
    UNUSED(ls);

    spdlog::drop_all();
    return 0;
}

int lua_set_pattern(lua_State * ls)
{
    Luapp lp(ls);
    std::string pattern(lp.toString(1));
    spdlog::set_pattern(pattern);
    return 0;
}

int lua_set_level(lua_State * ls)
{
    Luapp lp(ls);
    int level = (lp.toInteger(1));
    spdlog::set_level(spdlog::level::level_enum(level));
    return 0;
}

int lua_basic_logger(lua_State * l)
{
    Luapp lp(l);
    std::string name(lp.toString(1));
    std::string filename(lp.toString(2));
    auto logger = spdlog::basic_logger_st(name, filename);

    spdlog::logger **s = (spdlog::logger**)lp.newUserdata(sizeof(spdlog::logger*));
    *s = logger.get();

    lp.getMetatable(lua_spdlogger_object::mt_lua_spdlogger_object);
    lp.setMetatable(-2);

    // 返回给Lua的只有logger*一个变量
    return 1;
}

int lua_rotating_logger(lua_State * l)
{
    Luapp lp(l);
    std::string name(lp.toString(1));
    std::string filename(lp.toString(2));
    int max_file_size = lp.toInteger(3);
    int max_file = lp.toInteger(4);
    auto logger = spdlog::rotating_logger_st(name, filename, max_file_size, max_file);

    spdlog::logger **s = (spdlog::logger**)lp.newUserdata(sizeof(spdlog::logger*));
    *s = logger.get();

    lp.getMetatable(lua_spdlogger_object::mt_lua_spdlogger_object);
    lp.setMetatable(-2);

    // 返回给Lua的只有logger*一个变量
    return 1;
}

int lua_daily_logger(lua_State * l)
{
    Luapp lp(l);
    std::string name(lp.toString(1));
    std::string filename(lp.toString(2));
    int hour = lp.toInteger(3);
    int minute = lp.toInteger(4);
    auto logger = spdlog::daily_logger_st(name, filename, hour, minute);

    spdlog::logger **s = (spdlog::logger**)lp.newUserdata(sizeof(spdlog::logger*));
    *s = logger.get();

    lp.getMetatable(lua_spdlogger_object::mt_lua_spdlogger_object);
    lp.setMetatable(-2);

    // 返回给Lua的只有logger*一个变量
    return 1;
}

int create_std_logger(lua_State * l,
                      std::function<std::shared_ptr<spdlog::logger>(const std::string&)>&& f
                      )
{
    Luapp lp(l);
    std::string name(lp.toString(1));
    auto logger = f(name);

    spdlog::logger **s = (spdlog::logger**)lp.newUserdata(sizeof(spdlog::logger*));
    *s = logger.get();

    lp.getMetatable(lua_spdlogger_object::mt_lua_spdlogger_object);
    lp.setMetatable(-2);

    // 返回给Lua的只有logger*一个变量
    return 1;
}

int lua_stdout_logger(lua_State * l)
{
    return create_std_logger(l, spdlog::stdout_logger_st);
}

int lua_stderr_logger(lua_State * l)
{
    return create_std_logger(l, spdlog::stderr_logger_st);
}

int lua_stdout_color(lua_State * l)
{
    return create_std_logger(l, spdlog::stdout_color_st);
}

int lua_stderr_color(lua_State * l)
{
    return create_std_logger(l, spdlog::stderr_color_st);
}

// ---
