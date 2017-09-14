#ifndef FIRSTA_H
#define FIRSTA_H

#include "purecpp1.h"

template<int Value>
struct Print
{
    operator char()
    {
        return Value + 0xFF;            // INVOKE OVERFLOW WARNNING LOG !
    }
};

#define __DO_JOIN(symbol1, symbol2)     symbol1##symbol2
#define _JOIN(symbol1, symbol2)         __DO_JOIN(symbol1, symbol2)
#define UNIQUE_NAME(prefix)             _JOIN(prefix, __LINE__)

#define __print(...)                    char UNIQUE_NAME(print_value_) = Print<__VA_ARGS__>()

// 检查函数的参数个数
// 不足之处：
// 1、不能直接用到重载函数上面。
// 2、不能用到参数个数不定的函数上面，比如：printf。
// 补充：
// 1、如果不能使用新标准，可以手动对不同参数个数的函数进行特化。
// 2、如果需要使用到类成员函数，则需要对成员函数指针类型进行特化。
// 3、如果不想用这个方法，可以考虑分析typeid返回的字符串。但是因为这个字符串和具体的编译器有关，不能保证一定可用。

template<typename Sig>
struct get_;

template<typename R, typename... Args>
struct get_<R(*)(Args...)> {
    static size_t const value = sizeof...(Args);
};

template<typename Sig>
inline size_t get(Sig) {
    return get_<Sig>::value;
}
// -- end

// 在check_type.cpp中实现
int check_type_test(void);
int check_type_test2();

// 在has_member_test.cpp中实现
int has_member_test1();
void fibonacci_test();
int router_test();

// 在bind_test.cpp中实现
int bind_test();

#endif // FIRSTA_H
