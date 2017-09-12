#include <iostream>
#include "firstA.h"
#include "check_type.hpp"

class Foo {};

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

    return 0;
}
