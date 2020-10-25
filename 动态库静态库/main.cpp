#include<iostream>
#include"add.h"
#include"max.h"
using namespace std;

int main()
{
    int a = 2;
    int b = 3;
    int res1 = add(a, b);
    cout << "add(a,b) = " << res1 << endl;
    int res2 = max(a,b);
    cout << "max(a,b) = " << res2 << endl;
    return 0;
}