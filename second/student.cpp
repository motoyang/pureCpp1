#include <iostream>
#include <lua.hpp>
#include "luapp.h"
#include "luaclass.h"
#include "student.h"

using namespace std;

Student::Student()
:name("default")
{
    cout<<"Student Contructor called"<<endl;
}

Student::~Student()
{
    cout<<"Student Destructor called"<<endl;
}

string Student::getName()
{
    return name;
}

void Student::setName(string name)
{
    this->name = name;
}

int Student::getAge()
{
    return age;
}

void Student::setAge(int age)
{
    this->age = age;
}

void Student::print()
{
    cout<<"My name is: "<<name<<", and my age is "<<age<<endl;
}

// ---

void lua_test7()
{
    START_FUNC();

    static const luaL_Reg lualibs[] =
    {
        {"base", luaopen_base},
        {"io", luaopen_io},
//        {"cc",luaopen_student},
        {"cc", LuaStudent::openlib},
        {NULL, NULL}
    };

    LuaPP luapp;
    luapp.requireLibs(lualibs);
    luapp.doFile("hello8.lua");
}
