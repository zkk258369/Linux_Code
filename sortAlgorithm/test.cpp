#include<iostream>
#include<cstdlib>
#include<vector>
#include<ctime>


using namespace std;
using std::vector;

//1.插入排序  直接插入排序  希尔排序

//InsertSort()   O(n^2),O(1),稳定;最好情况为O(n)
//start-------------------------------------------------------
void InsertSort1(vector<int>& vec)
{
    int len = vec.size();
    for(int i=1; i<len; ++i)
    {
        int j = i-1;
        for(; j>=0; --j)
        {
            if(vec[j] < vec[i])
                break;
        }

        if(j != i-1)
        {
            int tmp = vec[i];
            for(int k=i-1; k>j; --k)
            {
                vec[k+1] = vec[k];
            }
            vec[j+1] = tmp;
        }
    }
}

void InsertSort2(vector<int>& vec)//最快
{
    int len = vec.size();
    for(int i=1; i<len; ++i)
    {
        if(vec[i] < vec[i-1])
        {
            int j = i-1;
            int tmp = vec[i];
            for(; vec[j] > tmp && j >= 0; --j)
            {
                vec[j+1] = vec[j];
            }
            vec[j+1] = tmp;
        }
    }
}

void InsertSort(vector<int>& vec)
{
    int len = vec.size();
    for(int i=1; i<len; ++i)
    {
        for(int j=i-1; j >= 0 && vec[j] > vec[j+1]; --j)
        {
            swap(vec[j], vec[j+1]);
        }
    }
}

//end---------------------------------------------------------
//InsertSort() 

//ShellSort()  缩小增量排序   O(n^1.3~n^1.5),O(1),不稳定
//start-------------------------------------------------------
void ShellSort(vector<int>& vec)
{
    int len = vec.size();
    for(int gap=len>>1; gap > 0; gap>>=1)
    {
        for(int i=gap; i < len; i++)
        {
            for(int j=i-gap; j >= 0 && vec[j] > vec[j+gap]; j-=gap)
                swap(vec[j], vec[j+gap]);
        }
    }
}

//end---------------------------------------------------------
//ShellSort()


//2.交换排序 冒泡 快排

//BubbleSort()   O(n^2),O(1),稳定
//start--------------------------------------------------------
void BubbleSort(vector<int>& vec)
{
    int len = vec.size();
    for(int i=0; i<len-1; ++i)
    {
        for(int j=0; j+1<len-i; ++j)
        {
            if(vec[j] > vec[j+1])
                swap(vec[j], vec[j+1]);
        }
    }
}

//end---------------------------------------------------------
//BubbleSort()

//QuickSort()
//start-------------------------------------------------------
//递归
template<typename T>
void QuickSort_recursive(T arr[], int l, int r)
{
    if(l >= r)
        return;
    T X = arr[l];//基准
    int left = l;
    int right = r;
    while(left < right)
    {
        while(arr[right] >= X && left < right)
            right--;
        arr[left] = arr[right];
        while(arr[left] < X && left < right)
            left++;
        arr[right] = arr[left];
    }
    arr[left] = X;
    QuickSort_recursive(arr, l, left-1);
    QuickSort_recursive(arr, left+1, r);
}

template<typename T>
void QuickSort(T arr[], int len)
{
    QuickSort_recursive(arr, 0, len-1);
}
//递归

//非递归
//非递归
//end---------------------------------------------------------
//QuickSort() 

template<typename T>
void Show(T arr[], int len)
{
    for(int i=0; i<len; ++i)
    {
        cout << arr[i] << " ";
    }
    cout<<endl;
}

int main()
{
    clock_t start;
    clock_t end;

    vector<int> vec;
	srand(time(nullptr));
	for (int i = 0; i < 30000; i++)
    {
        vec.push_back(rand() % 30000);
    }

    int arr[] = {6,9,1,2,5,8,4,12,34,56,7,32,45,6,0,122};
    int len = sizeof(arr)/sizeof(arr[0]);
    vector<int> vec1(arr,arr+len);


    Show(arr, len);
    start = clock();
    //BubbleSort(vec);
    //InsertSort2(vec);
    //ShellSort(vec);
    QuickSort(arr, len);


    end = clock();
    Show(arr, len);
    cout << "The run time is:" <<(double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
    cout << "The all run time is:" << (double)clock() / CLOCKS_PER_SEC<< "s" << endl;

    return 0;
}