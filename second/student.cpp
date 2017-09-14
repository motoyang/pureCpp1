#include <iostream>
#include "purecpp1.h"
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

void Student::setName(const string& name)
{
    this->name = name;
}

void Student::setNA(const string &name, int age)
{
    setName(name);
    setAge(age);
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

void Student::set3Value(int i, long l, const char* n)
{
    i_1 = i;
    l_2 = l;
    s_3 = n;
}

void Student::set4Value(int i, const char *n, float f, long l)
{
    i_1 = i;
    s_3 = n;
    f_4 = f;
    l_2 = l;
}

void Student::print4()
{
    SHOW_NAME_AND_RESULT(i_1);
    SHOW_NAME_AND_RESULT(l_2);
    SHOW_NAME_AND_RESULT(s_3);
    SHOW_NAME_AND_RESULT(f_4);
}
