#include<iostream>
using namespace std;

class Student
{
public:
    Student();
    Student(int _a, double _b);
    int fun8(int x, double y) const;
private:
    int fun1(int x, double y);
    int fun7(int x, double y) const;
protected:
    int fun2(float x, bool y);
    int fun6(int x, double y) const;
private:
    int a;
    double b;
};

Student::Student()
{

}
Student::Student(int _a, double _b)
{
    a = _a;
    b = _b;
}
int Student::fun8(int x, double y) const
{
    return x;
}

int Student::fun1(int x, double y)
{
    return x;
}

int Student::fun7(int x, double y) const
{
    return x;
}
int Student::fun2(float x, bool y)
{
    return 1;
}
int Student::fun6(int x, double y) const
{
    return x;
}
double fun3(int x, double y)
{
    return y;
}
void fun4(int x, double y)
{

}
int fun5()
{
    return 1;
}

int main()
{
    return 0;
}
