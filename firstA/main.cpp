#include <iostream>
#include "firstA.h"
#include "print_tuple.hpp"
#include "factorial.hpp"
#include "check_type.hpp"

#include <tuple>

using namespace std;

// helper function to print a tuple of any size
template<class Tuple, std::size_t N>
struct TuplePrinter {
    static void print(const Tuple& t)
    {
        TuplePrinter<Tuple, N-1>::print(t);
        std::cout << ", " << std::get<N-1>(t);
    }
};

template<class Tuple>
struct TuplePrinter<Tuple, 1> {
    static void print(const Tuple& t)
    {
        std::cout << std::get<0>(t);
    }
};

template<class... Args>
void print(const std::tuple<Args...>& t)
{
    std::cout << "(";
    TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
    std::cout << ")\n";
}

void tuple_test()
{
    START_FUNC();

    std::tuple<> t;
    for (int i = 0; i < 10; i++) {
        auto t2 = std::tuple_cat(t, std::make_tuple(i));
        print(t2);
    }
}

struct A1 {
    A1() {
        std::cout << "A1::A1()" << std::endl;
    }
    ~A1() {
        std::cout << "A1::~A1()" << std::endl;
    }
};

struct B1 {
    B1() {
        std::cout << "B1::B1()" << std::endl;
    }
    ~B1() {
        std::cout << "B1::~B1()" << std::endl;
    }

    void print() {
        std::cout << "B1::print" << std::endl;
    }

    A1 a;
};

void test_obj1()
{
    START_FUNC();

    B1 b;
    b.print();
}

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    START_FUNC();

//    __print(Factorial<8>::Value);
    SHOW_NAME_AND_RESULT(Factorial<8>::Value);

    check_type_test();
    check_type_test2();
    has_member_test1();
    fibonacci_test();
    router_test();

    bind_test();

    tuple_test();


    expand(1,2.3,3.5,"4aafa");

    check_type_test4();

    test_obj1();

    return 0;
}
