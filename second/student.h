#ifndef STUDENT_H
#define STUDENT_H

class Student
{
public:
    Student();
    ~Student();

    std::string getName();
    void setName(const std::string& name);
    void setNA(const std::string& name, int age);
    int getAge();
    void setAge(int age);
    void print();

    void set3Value(int i, long l, const char* n);
    void set4Value(int i, const char* n, float f, long l);
    int getI() const
    {
        return i_1;
    }
    float getF() const
    {
        return f_4;
    }
    std::string getS() const
    {
        return s_3;
    }
    long getL() const
    {
        return l_2;
    }
    std::tuple<int, long, std::string, float> get4Value() const
    {
        return std::make_tuple(i_1, l_2, s_3, f_4);
    }
    void print4();

private:
    std::string name;
    int age;

    int i_1;
    long l_2;
    std::string s_3;
    float f_4;
};

#endif // STUDENT_H
