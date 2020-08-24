#if 1
/*
 *   贪吃的小明
 *   小明的父母要出差N天,走之前给小明留下了M块奶糖,
 * 小明决定每天吃的奶糖数量不少于前一天吃的一半,
 * 但是他又不想在父母回来之前的某一天没有奶糖吃，
 * 请问他第一天最多能吃多少块奶糖。
*/
#include<iostream>
using namespace std;

int N = 4;
int M = 7;

int MaxSugerInFirstDay(int day, int num)
{
    int left = 1;
    int right = num;
    int mid = left + (right - left) / 2;
    while(left <= right)
    {
        int mid = left + (right - left) / 2;
        int sum = 0;
        int _mid = mid;
        for(int i=1; i<day; i++)
        {
            sum += _mid;
            _mid = (_mid + 1) / 2;
        }
        if(sum > num) right = mid - 1;
        else if(sum < num) left = mid + 1;
        else return mid;
    }
    return right;
}

int main()
{
    int res = MaxSugerInFirstDay(N, M);
    cout << "res = " << res << endl;

    return 0;
}
#endif
