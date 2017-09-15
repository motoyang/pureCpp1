#ifndef LUAPP_H
#define LUAPP_H

//#include <lua.hpp>

// 检查两种类型是否基本一致
template <typename T, typename U>
struct is_decay_equiv :
    std::is_same<typename std::decay<T>::type, U>::type
{};

template<typename T,
         typename = typename std::enable_if<
             is_decay_equiv<T, int>::value ||
             is_decay_equiv<T, double>::value ||
             is_decay_equiv<T, std::string>::value
             >::type
        >
void f_push(lua_State * ls, T&& t)
{
    // Checks whether T is an integral type. Provides the member constant value which is equal to true,
    // if T is the type bool, char, char16_t, char32_t, wchar_t, short, int, long, long long,
    // or any implementation-defined extended integer types, including any signed, unsigned,
    // and cv-qualified variants. Otherwise, value is equal to false.
    if (std::is_integral<T>::value) {f_setInteger(ls, std::forward<T>(t));}

    // Checks whether T is a floating-point type. Provides the member constant value which is equal to true,
    // if T is the type float, double, long double, including any cv-qualified variants. Otherwise,
    // value is equal to false.
    else if (std::is_floating_point<T>::value) {f_setNumber(ls, std::forward<T>(t));}

    else if (is_decay_equiv<T, std::string>::value || is_decay_equiv<T, const char *>::value) {f_setString(ls, std::forward<T>(t));}
    else {;}
}


//template<typename T>
//void printarg(T&& t)
//{
//   std::cout << t << " <- " << std::endl;
//}


// 逗号表达式展开参数包
// 不通过递归方式来展开参数包，这种方式需要借助逗号表达式和初始化列表。比如前面print的例子可以改成这样
//template <typename F, typename... Args>
//void expandArgs(const F& f, Args&&... args)
template <typename... Args>
int expandArgs(lua_State * ls, Args&&... args)
{
    // 如下的两种方式都可以
   int arr[] = {(f_push(ls, args), 0)...};
   return sizeof(arr) / sizeof(arr[0]);
//    std::initializer_list<int>{(f(std::forward< Args>(args)),0)...};
}
// 调用方式如下，在printarg函数中，处理每个参数
// 此处不能直接调用printarg，因为模版展开时不能确定具体的类型
// expandArgs([](auto t){printarg(std::forward(t));}, 1, 2.2, 3.3, "abcdefg");


class LuaPP
{
    lua_State *m_ls;

public:
    LuaPP();
    virtual ~LuaPP();

    bool requireLibs(const luaL_Reg *libs);
    bool doFile(const std::string& fname);
    template <typename F> void dumpStack(const F& f);

/*
    template<typename T> int getGlobal(const std::string& name, T *tValue) {
        return 0;
    }
*/
    template<typename F, typename... Args>
    int doFunction(const std::string& name, int countOfResult, const F& f, Args... args) {

        // lua的函数名入栈
        lua_getglobal(m_ls, name.c_str());
        int countOfArgs = expandArgs(m_ls, std::forward<Args>(args)...);
        lua_pcall(m_ls, countOfArgs, countOfResult, 0);
        f(m_ls, countOfResult);
    }

};

#endif // LUAPP_H
