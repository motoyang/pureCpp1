#ifndef PRINT_TUPLE_HPP
#define PRINT_TUPLE_HPP


#include <tuple>
#include <iostream>
#include "check_type.hpp"

template <int IDX, int MAX, typename... Args>
struct PRINT_TUPLE {
    static void print(std::ostream& strm, const std::tuple<Args...>& t) {
        strm << std::get<IDX>(t) << (IDX+1 == MAX ? "" : ", ");
        PRINT_TUPLE<IDX+1, MAX, Args...>::print(strm, t);
    }
};

template <int MAX, typename... Args>
struct PRINT_TUPLE<MAX, MAX, Args...> {
    static void print(std::ostream& strm, const std::tuple<Args...>& t) {}
};

template <typename... Args>
std::ostream& operator<< (std::ostream& strm, const std::tuple<Args...>& t) {
    strm << "[";
    PRINT_TUPLE<0, sizeof...(Args), Args...>::print(strm, t);
    return strm << "]";
}

void print(std::ostream& strm)
{
    strm << std::endl;
}

template<typename T, typename... Types>
void print(std::ostream& strm, const T& firstArg, const Types&... args)
{
    strm << firstArg << (sizeof...(args) > 0 ? ", " : "");
    print(strm, args...);
}

// ---

// 逗号表达式展开参数包
// 不通过递归方式来展开参数包，这种方式需要借助逗号表达式和初始化列表。比如前面print的例子可以改成这样
template <class T>
void printarg(T t)
{
   std::cout << t << " <- " << check_type<decltype(t)>()  << std::endl;
}

template <class ...Args>
void expand(Args... args)
{
   int arr[] = {(printarg(args), 0)...};
}

#endif // PRINT_TUPLE_HPP
