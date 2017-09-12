#ifndef FIRSTA_H
#define FIRSTA_H

#define UNUSED(x)                   (void)(x)
#define START_FUNC()                std::cout<<"--- Start "<<__PRETTY_FUNCTION__<<std::endl
#define SHOW_NAME_AND_RESULT(n)     std::cout<<#n" return "<< (n)<<std::endl

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

// 在check_type.cpp中实现
int check_type_test(void);

// 在has_member_test.cpp中实现
int has_member_test1();
void fibonacci_test();
int router_test();

#endif // FIRSTA_H
