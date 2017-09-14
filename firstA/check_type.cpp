#include <iostream>
#include "firstA.h"
#include "check_type.hpp"

class Foo {
public:
    void f1();
    void f2(int i);
    float f3(double, char*, const char*, float&){return 1.0f;}
    float f4(double, char*);
};

void f5(int, char*, float);

template <typename T>
auto func(T&&) -> T;

int check_type_test(void)
{
    START_FUNC();

    SHOW_NAME_AND_RESULT(check_type<const volatile void *>());

//    std::cout << check_type<const volatile void *>()
//              << std::endl;
    SHOW_NAME_AND_RESULT(check_type<const volatile void *(&)[10]>());

//    std::cout << check_type<const volatile void *(&)[10]>()
//              << std::endl;

    SHOW_NAME_AND_RESULT(check_type<int [1][2][3]>());
//    std::cout << check_type<int [1][2][3]>()
//              << std::endl;
    SHOW_NAME_AND_RESULT(check_type<const int [3][10]>());
//    std::cout << check_type<const int [3][10]>()
//              << std::endl << std::endl;

    SHOW_NAME_AND_RESULT(check_type<int(unsigned)>());
//    std::cout << check_type<int(unsigned)>()
//              << std::endl;
    SHOW_NAME_AND_RESULT(check_type<int(*)(const int *(*)[3][10], Foo&&, int, unsigned)>());
//    std::cout << check_type<int(*)(const int *(*)[3][10], Foo&&, int, unsigned)>()
//              << std::endl;
    SHOW_NAME_AND_RESULT(check_type<char(*(*const)(const int(&)[10]))[10]>());
//    std::cout << check_type<char(*(*const)(const int(&)[10]))[10]>()
//              << std::endl << std::endl;

    SHOW_NAME_AND_RESULT(check_type<int Foo::* const(&)[]>());
//    std::cout << check_type<int Foo::* const(&)[]>()
//              << std::endl << std::endl;

    SHOW_NAME_AND_RESULT(check_type<void(Foo::*)(void)>());
//    std::cout << check_type<void(Foo::*)(void)>()
//              << std::endl;
    SHOW_NAME_AND_RESULT(check_type<void(Foo::*)(void) volatile const>());
//    std::cout << check_type<void(Foo::*)(void) volatile const>()
//              << std::endl;
    SHOW_NAME_AND_RESULT(check_type<void(Foo::*(*)[])(int) const>());
//    std::cout << check_type<void(Foo::*(*)[])(int) const>()
//              << std::endl;
    SHOW_NAME_AND_RESULT(check_type<int (Foo::* const)(int, Foo&&, int) volatile>());
//    std::cout << check_type<int (Foo::* const)(int, Foo&&, int) volatile>()
//              << std::endl << std::endl;

    SHOW_NAME_AND_RESULT(check_type<decltype(func<Foo>)>());
    SHOW_NAME_AND_RESULT(check_type<decltype(func<Foo&>)>());
    SHOW_NAME_AND_RESULT(check_type<decltype(func<Foo&&>)>());
//    std::cout << check_type<decltype(func<Foo>)>() << std::endl;
//    std::cout << check_type<decltype(func<Foo&>)>() << std::endl;
//    std::cout << check_type<decltype(func<Foo&&>)>() << std::endl;

    SHOW_NAME_AND_RESULT(check_type<decltype(f5)>());
    SHOW_NAME_AND_RESULT(check_type<decltype(&f5)>());
    SHOW_NAME_AND_RESULT(check_type<decltype(&Foo::f3)>());

    return 0;
}


template<typename F>
void check_type_test3(F f)
{
    std::cout << check_type<decltype(std::forward<F>(f))>() << std::endl;
}

void fun(int, int) {}

int check_type_test2()
{
    check_type_test3(&Foo::f3);

    SHOW_NAME_AND_RESULT(get(fun));

    return 0;
}

