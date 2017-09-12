#include <iostream>
#include "firstA.h"
#include "timer.hpp"
#include "cache.hpp"
#include "router.hpp"
#include "has_member.h"

HAS_MEMBER(foo);
HAS_MEMBER(func);

struct MyStruct
{
    std::string foo() { return ""; }
    int func(int i) { return i; }
};

template<typename T>
typename std::enable_if<has_member_foo<T, int>::value>::type testfoo(T t) {
    UNUSED(t);
    std::cout << "has foo(int)" << std::endl;
}

template<typename T>
typename std::enable_if<!has_member_foo<T, int>::value>::type testfoo(T t) {
    UNUSED(t);
    std::cout << "has no foo(int)" << std::endl;
}

template<typename T>
typename std::enable_if<has_member_func<T, int>::value>::type testfunc(T t) {
    UNUSED(t);
    std::cout << "has func(int)" << std::endl;
}

template<typename T>
typename std::enable_if<!has_member_func<T, int>::value>::type testfunc(T t) {
    UNUSED(t);
    std::cout << "has no foo(int)" << std::endl;
}

int has_member_test1()
{
    START_FUNC();

    static_assert(has_member_foo<MyStruct>::value, "true");
    static_assert(has_member_func<MyStruct, int>::value, "true");

    MyStruct ms;
    testfoo(ms);
    testfunc(ms);

    return 0;
}

// --------

size_t fibonacci(size_t n)
{
    return (n < 2) ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

size_t fibonacci2(size_t n)
{
    return (n < 2) ? n : sugar(fibonacci2)(n - 1) + sugar(fibonacci2)(n - 2);
}

void fibonacci_test()
{
    START_FUNC();

    do {
        Timer t;
        SHOW_NAME_AND_RESULT(fibonacci(45));
        cout << "Elapsed " << t.elapsed() << " ms." << endl;
    } while(false);

    do {
        Timer t2;
        SHOW_NAME_AND_RESULT(fibonacci2(45));
        cout << "Elapsed " << t2.elapsed() << " ms." << endl;
    } while(false);

}


// ----


void add(int a, int b)
{
    std::cout << a + b << std::endl;
}

void hello()
{
    std::cout << "hello" << std::endl;
}

void foo(std::string b, int a)
{
    UNUSED(a);
    std::cout << b << std::endl;
}

int router_test()
{
    START_FUNC();

    using namespace std;
    router r;
    //设置路由
    r.register_handler("add", &add);
    r.register_handler("about", &hello);
    r.register_handler("fun", &foo);
    try
    {
        //解析uri实现调用
        string s1 = "add/1/2";
        string s2 = "about";
        string s3 = "fun/test/1";
        r.route(s1);
        r.route(s2);
        r.route(s3);
    }
    catch (std::runtime_error &error)
    {
        std::cerr << error.what() << std::endl;
    }
    return 0;
}
