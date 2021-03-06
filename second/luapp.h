#ifndef LUAPP_H
#define LUAPP_H

// ---

#ifndef DECLARE_AND_IMPLEMENT_LUA_OBJECT
#define DECLARE_AND_IMPLEMENT_LUA_OBJECT

#define DECLARE_LUA_OBJECT_BEGIN(o)                                 \
    struct o {

#define DECLARE_LUA_OBJECT_FROM_FATHER_BEGIN(o, f)                 \
    struct o: public f {

#define EXPORT_METHOD_TO_LUA(n)                                 \
    static int n(lua_State *ls);

#define DECLARE_LUA_OBJECT_END(o)                               \
    template<typename T> static int new_##o(lua_State * L) {    \
        return Luapp(L).newObject<T>(mt_##o); }                 \
    template<typename T> static int delete_##o(lua_State *L) {  \
        return Luapp(L).deleteObject<T>(mt_##o); }              \
    static const char * mt_##o;                                 \
    static int open_##o(lua_State * L);                         \
    };

// used in .cpp file.
#define DEFINE_META_TABLE_NAME(o, n)                \
    const char* o::mt_##o = (n);

#define IMPLEMENT_OPENLIB_METHOD_BEGIN(o)           \
    int o::open_##o(lua_State *ls)                  \
    {

#define LIST_META_TABLE_BEGIN(lo, co)               \
        static const struct luaL_Reg lib_m [] = {   \
        {"__gc",        lo::delete_##lo<co>},

#define ITEM_IN_TABLE(luaMethod, cppMethod)         \
    {(luaMethod), (cppMethod) },

#define LIST_META_TABLE_END                         \
    {NULL,          NULL}                           \
    };

#define LIST_FUNC_TABLE_BEGIN(lo, co)               \
        static const struct luaL_Reg lib_f [] = {   \
        {"create",      lo::new_##lo<co>},

#define LIST_FUNC_TABLE_END                         \
    {NULL,          NULL}                           \
    };

#define REGISTER_LUA_OBJECT_METHODS(o)                 \
    Luapp l(ls);                                       \
    l.newMetatable(mt_##o);                            \
    l.pushValue(-1);                                   \
    l.setField(-2, "__index");                         \
    l.setFuncs(lib_m, 0);

#define INHERIT_METHOD_FROM_FATHER(f)                       \
    l.getMetatable(f::mt_##f);                              \
    l.tableAppend(l.absIndex(-2), l.absIndex(-1), false);   \
    l.pop(1);

#define IMPLEMENT_OPENLIB_METHOD_END                 \
    luaL_newlib(ls, lib_f);                          \
    return 1;                                        \
}

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
// stackindex的默认输入函数
void stackindex_stdcout(lua_State * ls, int idx);

// table的默认输出函数，栈顶就是key和value
void keyvalue_stdcout(lua_State * ls);
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

    std::string typeNameFromIndex(int idx);
    std::string valueToString(int idx);

    void dumpStack(std::function<void(lua_State*, int)> f = stackindex_stdcout);
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

};

//---

class Luapp: public LuaLState
{
public:
    Luapp(lua_State * ls, LUA_STATE_RESOUECE_TYPE resourceType = LUA_STATE_RESOUECE_TYPE::SHARED_LUA_STATE);
    virtual ~Luapp();

    static std::shared_ptr<Luapp> create(lua_Alloc f, void *ud);
    static std::shared_ptr<Luapp> create();

    int tableAppend(int idxTo, int idxFrom, bool replaceable);
    int tableForeach(int index, std::function<void(lua_State*)> f);
    void tableStdcout(int index);

    bool requireLibs(const luaL_Reg *libs);
    bool doFile(const std::string& fname);

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

    // 把从lua来的调用，转发到相应到c++方法，并返回执行结果
    // 注意：输入参数和返回值到处理，是调用者到责任，调用者对此也很清楚
    template<typename T, typename CM, typename... Cn>
    auto dispatchToC(CM f, Cn... args)
    {
        // 为了能够被子类调用，此处不能使用checkUData
        // such as: T **s = (T**)checkUData(1, tname);
        T **s = (T**)toUserdata(1);
        argCheck(s != nullptr, 1, "invalid user data");

        auto fn = std::bind(f, *s, std::forward<Cn>(args)...);
        return fn();
    }

    template <typename... Args>
    int dispatchToLua(const std::string& name, int countOfResult, Args... args)
    {
        // lua的函数名入栈
        getGlobal(name.c_str());
        // lua函数的参数入栈
        int countOfArgs = pushN(std::forward<Args>(args)...);
        // 执行lua函数
        return pcall(countOfArgs, countOfResult, 0);
    }

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
    void dumpStack(std::function<void(lua_State*, int)> f = stackindex_stdcout);

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
