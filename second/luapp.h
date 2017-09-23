#ifndef LUAPP_H
#define LUAPP_H

// ---

#ifndef DECLARE_AND_IMPLEMENT_LUA_OBJECT
#define DECLARE_AND_IMPLEMENT_LUA_OBJECT

#define DECLARE2_LUA_OBJECT_BEGIN(o)                                \
    struct o{                                                      \
        template<typename T> static int new_##o(lua_State * L) {    \
            return Luapp(L).newObject<T>(mt_##o); }                 \
        template<typename T> static int delete_##o(lua_State *L) {  \
            return Luapp(L).deleteObject<T>(mt_##o); }              \
        static const char * mt_##o;                                 \
        static int open_##o(lua_State * L);

#define DECLARE2_LUA_OBJECT_BEGIN2(o, f)                                \
    struct o: public f{                                                      \
        template<typename T> static int new_##o(lua_State * L) {    \
            return Luapp(L).newObject<T>(mt_##o); }                 \
        template<typename T> static int delete_##o(lua_State *L) {  \
            return Luapp(L).deleteObject<T>(mt_##o); }              \
        static const char * mt_##o;                                 \
        static int open_##o(lua_State * L);

#define EXPORT2_METHOD_TO_LUA(n)                             \
    static int n(lua_State *ls);

#define DECLARE2_LUA_OBJECT_END                              \
    };


// used in .cpp file.
#define DEFINE2_META_TABLE_NAME(o, n)                \
    const char* o::mt_##o = (n);

#define IMPLEMENT2_OPENLIB_METHOD_BEGIN(o)           \
    int o::open_##o(lua_State *ls)                   \
    {

#define LIST2_META_TABLE_BEGIN(lo, co)               \
        static const struct luaL_Reg lib_m [] = {    \
        {"__gc",        lo::delete_##lo<co>},

#define ITEM2_IN_TABLE(luaMethod, cppMethod)         \
    {(luaMethod), (cppMethod) },

#define LIST2_META_TABLE_END                         \
    {NULL,          NULL}                            \
    };

#define LIST2_FUNC_TABLE_BEGIN(lo, co)               \
        static const struct luaL_Reg lib_f [] = {    \
        {"create",      lo::new_##lo<co>},

#define LIST2_FUNC_TABLE_END                         \
    {NULL,          NULL}                            \
    };

#define LUA2_OBJECT_REGISTER(ls, tn, mt, ft)         \
    luaL_newmetatable((ls), (tn));                   \
    lua_pushvalue((ls), -1);                         \
    lua_setfield((ls), -2, "__index");               \
    luaL_setfuncs((ls), (mt), 0);                    \
    luaL_newlib((ls), (ft));

#define IMPLEMENT2_OPENLIB_METHOD_END(o)             \
    Luapp l(ls);                                     \
    l.newMetatable(mt_##o);                            \
    l.pushValue(-1);                                   \
    l.setField(-2, "__index");                         \
    l.setFuncs(lib_m, 0);                              \
    luaL_newlib(ls, lib_f);                          \
    return 1;                                        \
}

//l.objectRegister(mt_##o, nullptr, lib_m, lib_f);
//    return 1;

#define IMPLEMENT2_OPENLIB_METHOD_END2(o, f)         \
    Luapp l(ls);                                     \
    l.newMetatable(mt_##o);                            \
    l.pushValue(-1);                                   \
    l.setField(-2, "__index");                         \
    l.setFuncs(lib_m, 0);                              \
    l.getField(LUA_REGISTRYINDEX, f::mt_##f);          \
    l.tableAdd(l.absIndex(-2), l.absIndex(-1), false);                     \
    luaL_newlib(ls, lib_f);                          \
    return 1;                                        \
}

//}                                                \
//if (f::mt_##f) {                                 \
//    l.pushString(f::mt_##f);                          \
//    l.getTable(LUA_REGISTRYINDEX);                 \
//    l.objectRegister(mt_##o, f::mt_##f, lib_m, lib_f);
//    LUA2_OBJECT_REGISTER(ls, mt_##o, lib_m, lib_f);

#endif

// ---

#ifndef GET_SET_VALUE_FORM_LUA
#define GET_SET_VALUE_FORM_LUA
//auto f_getNil       = [](lua_State * L, int idx) { return lua_toboolean(L, idx); };
auto f_getBoolean   = [](lua_State * L, int idx) { return lua_toboolean(L, idx); };
auto f_getInteger   = [](lua_State * L, int idx) { return lua_tointeger(L, idx); };
auto f_getLong      = [](lua_State * L, int idx) { return (long)lua_tointeger(L, idx); };
auto f_getNumber    = [](lua_State * L, int idx) { return lua_tonumber(L, idx); };
auto f_getString    = [](lua_State * L, int idx) { return std::string(lua_tostring(L, idx)); };
auto f_getCFunction = [](lua_State * L, int idx) { return lua_tocfunction(L, idx); };
auto f_getUserdata  = [](lua_State * L, int idx) { return lua_touserdata(L, idx); };
auto f_getTable     = [](lua_State * L, int idx) { return lua_topointer(L, idx); };
//auto f_getObjlen    = [](lua_State * L, int idx) { return lua_toobjlen(L, idx); };
//auto f_getBuffer    = [](lua_State * L, int idx, size_t *len) { return lua_tolstring(L, idx, len); };
//auto f_getPointer   = [](lua_State * L, int idx) { return lua_topointer(L, idx); };
//auto f_getThread    = [](lua_State * L, int idx) { return lua_tothread(L, idx); };

//auto f_setUserData  = [](lua_State * L, std::result_of<decltype(lua_touserdata)> v) { return lua_pushuserdata(L, v); };
auto f_setNull      = [](lua_State * L) { return lua_pushnil(L); };
auto f_setBoolean   = [](lua_State * L, bool v) { return lua_pushboolean(L, (int)v); };
auto f_setLong      = [](lua_State * L, long v) { return lua_pushinteger(L, v); };
auto f_setFloat     = [](lua_State * L, float v) { return lua_pushnumber(L, (lua_Number)v); };
auto f_setDouble    = [](lua_State * L, double v) { return lua_pushnumber(L, (lua_Number)v); };
auto f_setNumber    = [](lua_State * L, double v) { return lua_pushnumber(L, (lua_Number)v); };
auto f_setInteger   = [](lua_State * L, int v) { return lua_pushinteger(L, v); };
auto f_setString    = [](lua_State * L, const std::string& v) { return lua_pushstring(L, v.c_str()); };
auto f_setBuffer    = [](lua_State * L, const std::string& v, size_t len) { return lua_pushlstring(L, v.c_str(), len); };
#endif

// ---

template<typename T>
void f_push(lua_State * ls, const T& t);

template<>
void f_push(lua_State * ls, const int& i);

template<>
void f_push(lua_State *ls, const std::string& s);

template<>
void f_push(lua_State *ls, const double& d);

// ---

template<typename T >
void f_pop(lua_State * ls, T& t);

template<>
void f_pop(lua_State * ls, int& i);

template<>
void f_pop(lua_State * ls, double& d);

template<>
void f_pop(lua_State * ls, std::string& s);

// ---

// 逗号表达式展开参数包
// 不通过递归方式来展开参数包，这种方式需要借助逗号表达式和初始化列表。比如前面print的例子可以改成这样
template <typename F, typename... Args>
int expandArgs(lua_State * ls, const F& f, Args&&... args)
{
    std::initializer_list<int> il {(f(ls, std::forward< Args>(args)),0)...};
    return il.size();
}
// 调用方式如下，在printarg函数中，处理每个参数
// 此处不能直接调用printarg，因为模版展开时不能确定具体的类型
// expandArgs([](lua_State *ls, auto t){printarg(std::forward(t));}, 1, 2.2, 3.3, "abcdefg");

// 在popArgs时，不能传入闭包，因为闭包中的auto参数会导致pop不到stack中的值
template <typename... Args>
int popArgs(lua_State * ls, Args&&... args)
{
   int arr[] = {(f_pop(ls, std::forward<Args>(args)), 0)...};
   return sizeof(arr) / sizeof(arr[0]);
}

// 在popArgs时，不能传入闭包，因为闭包中的auto参数会导致pop不到stack中的值
template <typename... Args>
int countOfArgs(Args&&... args)
{
   int arr[] = {((std::forward<Args>(args)), 0)...};
   return sizeof(arr) / sizeof(arr[0]);
}

// ---

void stdcpp_output(lua_State * ls, int idx);

// ---

class LuaStack
{
protected:
    lua_State * m_ls;

public:
    LuaStack(lua_State * ls);
    virtual ~LuaStack();

    // 不能拷贝构造，也不能赋值
    LuaStack(const LuaStack& ls) = delete;
    LuaStack(LuaStack&& ls) = delete;
    LuaStack operator=(const LuaStack& ls) = delete;
    LuaStack operator=(LuaStack&& ls) = delete;

    // basic stack manipulation
    int absIndex(int idx) const;
    int getTop() const;
    void setTop(int idx);
    void pushValue(int idx);
    void rotate(int idx, int n);
    void copy(int fromidx, int toidx);
    int checkStack(int n);
    void xmove(lua_State *to, int n);
    void pop(int n);

    // access functions (stack -> C)
    bool isNumber(int idx) const;
    bool isString(int idx) const;
    bool isCFunction(int idx) const;
    bool isInteger(int idx) const;
    bool isUserdata(int idx) const;
    int type(int idx) const;
    std::string typeName(int tp) const;

    lua_Number toNumberx(int idx, int *isnum) const;
    lua_Number toNumber(int idx) const;
    lua_Integer toIntegerx(int idx, int *isnum) const;
    lua_Integer toInteger(int idx) const;
    bool toBoolean(int idx) const;
    std::string toString(int idx) const;
    size_t rawLen(int idx) const;
    lua_CFunction toCFunction(int idx) const;
    void * toUserdata(int idx) const;
    lua_State * toThread(int idx) const;
    const void * toPointer(int idx) const;

    // Comparison and arithmetic functions
    int rawEqual(int idx1, int idx2) const;
    int compare(int idx1, int idx2, int op) const;
    void arith (int op);

    // push functions (C -> stack)
    void pushNil();
    void pushNumber(lua_Number n);
    void pushInteger(lua_Integer n);
    std::string pushLString(const char *s, size_t len);
    std::string pushString(const char *s);
    std::string pushVFString(const char *fmt, va_list argp);
    std::string pushFString(const char *fmt, ...);
    void pushCClosure(lua_CFunction fn, int n);
    void pushBoolean(bool b);
    void pushLightUserdata(void *p);

    // 多个参数入栈
    template <typename... Args> int pushN(Args&&... args)
    {
        int countOfArgs = expandArgs(m_ls,
                [](lua_State *ls, auto t){f_push(ls, t);},
                std::forward<Args>(args)...);

        return countOfArgs;
    }

    // 多个参数出栈
    template <typename... Args> int popN(Args&&... args)
    {
        int countOfArgs = popArgs(m_ls,
                std::forward<Args>(args)...);

        return countOfArgs;
    }

    void dumpStack(std::function<void(lua_State*, int)> f = stdcpp_output);
};

// ---

class LuaThread : public LuaStack
{
public:
    LuaThread(lua_State * ls);
    virtual ~LuaThread();

    // coroutine functions
    int yieldk(int nresults, lua_KContext ctx, lua_KFunction k);
    int resume(lua_State *from, int nargs);
    int status() const;
    int isYieldable() const;
    int yield(int nresults);

    int pushThread();
    template<typename... Args> int resume(LuaThread* from, const std::string& func, Args... args);
};

// ---

class LuaState : public LuaThread
{
public:
    enum class LUA_STATE_RESOUECE_TYPE {
        NONE_STATE,
        UNIQUE_LUA_STATE,
        SHARED_LUA_STATE
    };

    LUA_STATE_RESOUECE_TYPE m_lsResource;

public:
    LuaState(lua_State * ls, LUA_STATE_RESOUECE_TYPE resourceType = LUA_STATE_RESOUECE_TYPE::SHARED_LUA_STATE);
    virtual ~LuaState();

    // state manipulation
    const lua_Number *version() const;
    lua_CFunction atPanic(lua_CFunction panicf);
    lua_State * newThread();
    static lua_State * newState(lua_Alloc f, void *ud);
    void close();

    // garbage-collection function and options
    int gc(int what, int data);

    // get functions (Lua -> stack)
    int getGlobal(const char *name);
    int getTable(int idx);
    int getField(int idx, const char *k);
    int getI(int idx, lua_Integer n);
    int rawGet(int idx);
    int rawGetI(int idx, lua_Integer n);
    int rawGetP(int idx, const void *p);

    void createTable(int narr, int nrec);
    void *newUserdata(size_t sz);
    int getMetatable(int index);
    int getUserValue(int idx);

    // set functions (stack -> Lua)
    void setGlobal(const char *name);
    void setTable(int idx);
    void setField(int idx, const char *k);
    void setI(int idx, lua_Integer n);
    void rawSet(int idx);
    void rawSetI(int idx, lua_Integer n);
    void rawSetP(int idx, const char *p);
    void setMetatable(int objindex);
    void setUserValue(int idx);

    // 'load' and 'call' functions (load and run Lua code)
    void callK(int nargs, int nresults, lua_KContext ctx, lua_KFunction k);
    void call(int nargs, int nresults);
    int pcallK(int nargs ,int nresults, int errfunc, lua_KContext ctx, lua_KFunction k);
    int pcall(int nargs, int nresults, int errfunc);
    int load(lua_Reader reader, void *dt, const char *chunkname, const char *mode);
    int dump(lua_Writer writer, void *data, int strip);

    // miscellaneous functions
    int error();
    int next(int idx);
    void concat(int n);
    void len(int idx);
    size_t stringToNumber(const char *s);
    lua_Alloc getAllocF(void **ud);
    void setAllocF(lua_Alloc f, void *ud);
    void *getExtraSpace();
};

// ---

class LuaLState: public LuaState
{
public:
    LuaLState(lua_State * ls, LUA_STATE_RESOUECE_TYPE resourceType = LUA_STATE_RESOUECE_TYPE::SHARED_LUA_STATE);
    virtual ~LuaLState();

    // luaL_*
    static lua_State *newLState();
    int getMetatable(const char* tname);
    void * checkUData(int arg, const char *tname);
    int argError(int arg, const char *extramsg);
    void argCheck(int cond, int arg, const char *extramsg);
    void openLibs();
    void requireF(const char *modname, lua_CFunction openf, int glb);
    int loadFile(const char *filename);
    int newMetatable(const char *tname);
    void setFuncs(const luaL_Reg *l, int nup);


//#define newLib(l)       luaL_newlib(m_ls, )
//    void newLibtable(const luaL_Reg l[]);
};

//---

class Luapp: public LuaLState
{
public:
    Luapp(lua_State * ls, LUA_STATE_RESOUECE_TYPE resourceType = LUA_STATE_RESOUECE_TYPE::SHARED_LUA_STATE);
    virtual ~Luapp();

    static std::shared_ptr<Luapp> create(lua_Alloc f, void *ud);
    static std::shared_ptr<Luapp> create();

//    void objectRegister(const char* tname, const char* ftname, const luaL_Reg lib_m[], const luaL_Reg lib_f[]);
    int tableAdd(int idxTo, int idxFrom, bool replaceable);
    int tablePrint(int index);

    template<typename T> int newObject(const char * mtname)
    {
        T **s = (T**)newUserdata(sizeof(T*));  // lua will manage Student** pointer
        *s = new T;
        getMetatable(mtname);
        setMetatable(-2);

        // 返回给Lua的只有T*一个变量
        return 1;
    }

    template<typename T> int deleteObject(const char * mtname)
    {
        T **s = (T**)checkUData(1, mtname);
        if( *s ) { delete *s; }

        // 不需要返回lua任何变量
        return 0;
    }

    template<typename T, typename CM, typename... Cn>
    auto put(const char *tname, CM f, Cn... args)
    {
//        T **s = (T**)checkUData(1, tname);
          T **s = (T**)toUserdata(1);
        argCheck(s != nullptr, 1, "invalid user data");

        auto fn = std::bind(f, *s, std::forward<Cn>(args)...);
        return fn();
    }

    template<typename T, typename CM>
    auto get(const char * tname, CM f)
    {
//        T **s = (T**)checkUData(1, tname);
        T **s = (T**)toUserdata(1);
        argCheck(s != nullptr, 1, "invalid user data");

        auto fn = std::bind(f, *s);
        return fn();
    }

    bool requireLibs(const luaL_Reg *libs);
    bool doFile(const std::string& fname);
};

// ---

class LuaTable: public LuaLState
{
    friend class Luapp;

//    lua_State * m_ls;

protected:
    LuaTable(lua_State * ls);

public:
    virtual ~LuaTable();

    void forEach(int index);
};

// ---
class LuaPP
{
    lua_State *m_ls;

public:
    LuaPP();
    virtual ~LuaPP();

    bool requireLibs(const luaL_Reg *libs);
    bool doFile(const std::string& fname);
    void dumpStack(std::function<void(lua_State*, int)> f = stdcpp_output);

    template <typename... Args> int push(Args&&... args)
    {
        int countOfArgs = expandArgs(m_ls,
                [](lua_State *ls, auto t){f_push(ls, t);},
                std::forward<Args>(args)...);

        return countOfArgs;
    }

    template <typename... Args> int pop(Args&&... args)
    {
        int countOfArgs = popArgs(m_ls,
                std::forward<Args>(args)...);

        return countOfArgs;
    }

    template<typename T> int getGlobal(const std::string& name, T& tValue) {
        lua_getglobal(m_ls, name.c_str());
        f_pop(m_ls, tValue);
        return 0;
    }

    template <typename... Args>
    int doFunction(const std::string& name, int countOfResult, Args... args)
    {
        // lua的函数名入栈
        lua_getglobal(m_ls, name.c_str());
        // lua函数的参数入栈
        int countOfArgs = push(std::forward<Args>(args)...);
        // 执行lua函数
        return lua_pcall(m_ls, countOfArgs, countOfResult, 0);
    }
};

#endif // LUAPP_H
