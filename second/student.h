#ifndef STUDENT_H
#define STUDENT_H

#include "purecpp1.h"

class Student
{
public:
    Student();
    ~Student();
    std::string getName();
    void setName(std::string name);
    int getAge();
    void setAge(int age);
    void print();

private:
    std::string name;
    int age;
};
/*
class LuaStudent
{
    template<typename F>
    static int route(F&& f, lua_State *ls)
    {
//        SHOW_NAME_AND_RESULT(check_type<std::forward<F>(f)>)
        return 0;
    }

    static int l_setName(lua_State *ls)
    {
        route(&Student::setName, ls);
        return 0;
    }

    static int l_setAge(lua_State *ls)
    {
        return 0;
    }
    static int l_print(lua_State *ls)
    {
        return 0;
    }

public:
//    static const std::string sm_mateTableName = "cc.Student";

    const static luaL_Reg sm_mateReg [];
//    = {
//        {"setName", LuaStudent::l_setName},
//        {"setAge", LuaStudent::l_setAge},
//        {"print", LuaStudent::l_print},
//        {NULL, NULL}
//    };

    static const luaL_Reg sm_functionReg [];
//    = {
//        {NULL, NULL}
//    };
};
*/
void lua_test7();

#endif // STUDENT_H
