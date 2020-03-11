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
template<typename T>
void ShellSort(T* arr, int len)
{
    for(int gap=len>>1; gap > 0; gap>>=1)
    {
        for(int i=gap; i < len; i++)
        {
            for(int j=i-gap; j >= 0 && arr[j] > arr[j+gap]; j-=gap)
                swap(arr[j], arr[j+gap]);
        }
    }
}

//end---------------------------------------------------------
//ShellSort()


//2.交换排序 冒泡 快排

//BubbleSort()   O(n^2),O(1),稳定
//start--------------------------------------------------------
template<typename T>
void BubbleSort(T* arr, int len)
{
    for(int i=0; i<len-1; ++i)
    {
        for(int j=0; j+1<len-i; ++j)
        {
            if(arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
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
typedef struct Range
{
    int start;
    int end;
    Range(const int& s = 0, const int& e = 0)
    {
        start = s;
        end = e;
    }
}Range;

template<typename T>
void QuickSort2(T* arr, int len)
{
    if(len <= 1)
        return;
    Range r[len];
    int p = 0;
    r[p++] = Range(0, len-1);//r[p++] 相当于入栈  r[--p] 相当于出栈
    while(p)
    {
        Range range = r[--p];
        if(range.start >= range.end)
            continue;
        int left = range.start;
        int right = range.end;
        int X = arr[left];//基准
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
        r[p++] = Range(range.start, left-1);
        r[p++] = Range(left+1, range.end);
    }
}
//非递归
//end---------------------------------------------------------
//QuickSort()

//3.选择排序  选择排序  堆排序

//start
//SelectSort()
template<typename T>
void SelectSort(T* arr, int len)
{
    int minIndex=0;
    for(int i=0; i<len-1; ++i)
    {
        for(int j=i+1; j<len; ++j)
        {
            minIndex = i;
            if(arr[j]<arr[i])
            {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}
//end
//SeletcSort()

//start
//HeapSort()
template<typename T>
void Max_heapify(T* arr, int start, int end)
{
    int dad = start;
    int son = dad*2 + 1;
    while(son <= end)
    {
        if(son+1 <= end && arr[son] < arr[son+1])
            son++;
        if(arr[dad] > arr[son])
            break;
        else
        {
            swap(arr[son], arr[dad]);
            dad = son;
            son = dad*2 + 1;
        }
    }
}

template<typename T>
void HeapSort(T* arr, int len)
{
    if(len<=1 || arr==nullptr)
        return;
    for(int i=len/2 - 1; i>=0; --i)
    {
        Max_heapify(arr, i, len-1);
    }
    for(int i=len-1; i>0; --i)
    {
        swap(arr[0], arr[i]);
        Max_heapify(arr, 0, i-1);
    }
}

//HeapSort()
//end

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

    #define size 20000
    int arr[size];
    int send = 0;
    srand((int)time(nullptr) + send++);
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand()%size;
    }

    int len = sizeof(arr)/sizeof(arr[0]);
    vector<int> vec1(arr,arr+len);


    //Show(arr, len);
    start = clock();
    //BubbleSort(arr, len);
    //InsertSort2(arr, len);
    //ShellSort(arr, len);
    //QuickSort2(arr, len);
    //SelectSort(arr, len);
    HeapSort(arr, len);


    end = clock();
    Show(arr, len);
    cout << "The run time is:" <<(double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
    cout << "The all run time is:" << (double)clock() / CLOCKS_PER_SEC<< "s" << endl;

    return 0;
}
