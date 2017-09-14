//代码出自链接：http://www.jellythink.com/archives/771
#include <functional>
#include <iostream>
#include "firstA.h"

using namespace std;

std::function< int(int)> Functional;
std::function< double(int, float, double)> F2;

// 普通函数
int TestFunc(int a)
{
    return a;
}

// Lambda表达式
auto lambda = [](int a)->int{ return a; };

// 仿函数(functor)
class Functor
{
public:
    int operator()(int a)
    {
        return a;
    }
};

// 1.类成员函数
// 2.类静态函数
class TestClass
{
public:
    int ClassMember(int a) { return a; }
    double ClassMember2(int a, float b, double c) { return a + b + c; }
    static int StaticMember(int a) { return a; }
};

int bind_test()
{
    START_FUNC();

    // 普通函数
    Functional = TestFunc;
    int result = Functional(10);
    cout << "普通函数："<< result << endl;

    // Lambda表达式
    Functional = lambda;
    result = Functional(20);
    cout << "Lambda表达式："<< result << endl;

    // 仿函数
    Functor testFunctor;
    Functional = testFunctor;
    result = Functional(30);
    cout << "仿函数："<< result << endl;

    // 类成员函数
    TestClass testObj;
    Functional = std::bind(&TestClass::ClassMember, testObj, std::placeholders::_1);
    result = Functional(40);
    cout << "类成员函数："<< result << endl;

    F2 = std::bind(&TestClass::ClassMember2, testObj, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    result = F2(2, 3.0, 4.0);
    cout << "类成员函数："<< result << endl;

    // 类静态函数
    Functional = TestClass::StaticMember;
    result = Functional(50);
    cout << "类静态函数："<< result << endl;

    return 0;
}
