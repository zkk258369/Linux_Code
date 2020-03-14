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
//start-------------------------------------------------------
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

//start-------------------------------------------------------
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
//end---------------------------------------------------------
//SeletcSort()

//start-------------------------------------------------------
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
//end---------------------------------------------------------

//4.归并排序
//MergeSort()
//start-------------------------------------------------------

//recursive
void mergeArray1(int* arr, int start, int mid, int end, int* temp)
{
    int i = start;
    int j = mid+1;
    int m = mid;
    int n = end;
    int k = 0;

    while(i<=m && j<=n)
    {
        if(arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while(i <= m)
        temp[k++] = arr[i++];
    while(j <= n)
        temp[k++] = arr[j++];
    for(i=0; i<k; i++)
        arr[start+i] = temp[i];        
}

void _MergeSort1(int* arr, int start, int end, int* temp)
{
    if(start < end)
    {
        int mid = (start+end)/2;
        _MergeSort1(arr, start, mid, temp);
        _MergeSort1(arr, mid+1, end, temp);
        mergeArray1(arr, start, mid, end, temp);
    }
}
template<typename T>
void MergeSort(T* arr, int len)//直接创建一个大数组
{
    if(arr == nullptr || len <= 1)
        return;
    T* p = new T[len];
    if(p == nullptr)
    {
        cout << "new error" << endl;
        return;
    }
    _MergeSort1(arr, 0, len-1, p);
}
//recursive

//non recursive
void non_recursive_mergeSort(int* arr, int len)
{
    int* pa = arr;
    int* pb = new int[len];
    for(int seg=1; seg<len; seg+=seg)
    {
        for(int start=0; start<len; start+=seg+seg)
        {
            int low = start;
            int mid = min(start+seg, len);
            int high = min(start+seg+seg, len);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while(start1 < end1 && start2 < end2)
                pb[k++] = pa[start1] < pa[start2] ? pa[start1++] : pa[start2++];
            while(start1 < end1)
                pb[k++] = pa[start1++];
            while(start2 < end2)
                pb[k++] = pa[start2++];
        }
        int* temp = pa;
        pa = pb;
        pb = temp;
    }
    if(pa != arr)
    {
        for(int i=0; i<len; i++)
            pb[i] = pa[i];
        pb=pa;
    }
    delete[] pb;
}

/*
 * 我的理解
 * 对一个数组先进行两个两个的排序，比如先排序下标为0,1的两个数进行排序，
 * 然后对下标为2,3进行排序，排序到数组结束后，将数组pb变成源数组，
 * 然后将seg扩大成2，每次要排序的数组就变成了0,1,2,3; 4,5,6,7;这样的四个一组
 * 随着seg的增大，直到数组序列书为1.
*/
//non recursive

//MergeSort()
//end---------------------------------------------------------




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

    #define size 10000
    int arr[size];
    int send = 0;
    srand((int)time(nullptr) + send++);
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand()%size;
    }

    int len = sizeof(arr)/sizeof(arr[0]);
    vector<int> vec(arr,arr+len);
    int arr1[] = {1,8,6,7,9,5,1,7,5,93,1,54,6,8,15,45,2,76,82,35};
    int len1 = sizeof(arr1)/sizeof(arr1[0]);
    //Show(arr, len);
    start = clock();
    //BubbleSort(arr, len);
    //InsertSort2(arr, len);
    //ShellSort(arr, len);
    //QuickSort(arr, len);
    //SelectSort(arr, len);
    //HeapSort(arr, len);
    //MergeSort(arr, len);
    non_recursive_mergeSort(arr1, len1);



    end = clock();
    Show(arr1, len1);
    cout << "The run time is:" <<(double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
    cout << "The all run time is:" << (double)clock() / CLOCKS_PER_SEC<< "s" << endl;
    system("pause");
    return 0;
}
