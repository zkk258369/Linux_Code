#include<iostream>
using namespace std;

int sum(int a, int b)
{
    return a+b;
}

int main()
{
    int a = 10;
    int b = 20;

    int ret = sum(a,b);
    cout << "sum = " << sum << endl;

    return 0;

}
