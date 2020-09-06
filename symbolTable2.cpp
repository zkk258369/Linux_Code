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

//Student::Student();
//Student::Student(int _a, double _b);
//int Student::fun8(int x, double y) const;
//
//int Student::fun1(int x, double y);
//
//int Student::fun7(int x, double y) const;
//int Student::fun2(float x, bool y);
//int Student::fun6(int x, double y) const;

double fun3(int x, double y);
void fun4(int x, double y);
int fun5();

int main()
{
	fun3(1, 2);
	fun4(1, 2);
	fun5();

	Student stu;
	stu.fun8(1, 2);

	return 0;
}
