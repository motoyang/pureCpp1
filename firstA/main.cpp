#include <iostream>
#include "firstA.h"
#include "factorial.hpp"
#include "check_type.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    START_FUNC();

//    __print(Factorial<8>::Value);
    SHOW_NAME_AND_RESULT(Factorial<8>::Value);

    check_type_test();

    has_member_test1();
    fibonacci_test();
    router_test();

    return 0;
}
