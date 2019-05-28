
# <center>数据结构第五次上机

<center>一位不愿意透露姓名的陈雎</center>

## 题目：

实现快排、堆排与归并排序并比较算法性能

1. 实现快排、堆排、归并排序3种排序；
2. 通过统计“测试数据的执行时间”来比较性能，得出结论

## 需求分析：

* __输入形式__：无

* __输入值的范围__：无

* __输出形式__：在控制台上显示即可。

* __程序功能__：计算快排、堆排、归并排序的执行时间。

* __测试数据__：  

    测试数据个数：600000

    正确输出：

    >quicksort spend 0.101 ms  
    >heapsort spend 0.265 ms  
    >mergesort spend 0.148 ms

## 概要设计：

__ADT定义__：  

自定义堆：

    template <class T>
    class MinHeap
    {
    private:
        T *array;
        int currentSize, maxSize;
        void swap(int pos_x, int pos_y);
        bool isLeaf(int pos); const
        int Parent(int pos); const
        int LeftChild(int pos); const
        void BuildHeap();
    public:
        MinHeap(int num);
        ~MinHeap();
        bool insert(const T &ele);
        void siftUp(int index);
        void SiftDown(int index);
        T RemoveMin();
        bool isEmpty();
    };

快速排序算法

    template <class T>
    void quicksort(T *array, int left, int right);

堆排序算法

    template <class T>
    void heapsort(T *array, int n);

归并排序算法

    template <class T>
    void mergesort(T *array, T *temp, int left, int right);

主程序流程：  
提示用户输入->获取用户输入的选项和数据->调用相应算法->输出算法生成结果  
调用关系：  
![调用关系](https://github.com/daoshiayou/homework/blob/master/Data%20Structures%20and%20Algorithms/source/5模块调用关系.png)

## 详细设计

__ADT定义__：  

自定义堆：

    template <class T>
    class MinHeap
    {
    private:
        T *array;
        int currentSize, maxSize;
        void swap(int pos_x, int pos_y)
        {
            T temp = array[pos_x];
            array[pos_x] = array[pos_y];
            array[pos_y] = temp;
        }
        bool isLeaf(int pos) const
        {
            return (pos >= currentSize / 2) && (pos < currentSize);
        }
        int Parent(int pos) const
        {
            return (pos - 1) / 2;
        }
        int LeftChild(int pos) const
        {
            return 2 * pos + 1;
        }
        void BuildHeap()
        {
            for (int i = currentSize / 2 - 1; i >= 0; i--)
            {
                SiftDown(i);
            }
        }

    public:
        MinHeap(int num)
        {
            if (num <= 0)
                return;
            currentSize = 0;
            maxSize = num;
            array = new T[maxSize];
            BuildHeap();
        }
        ~MinHeap()
        {
            if (array)
            {
                delete[] array;
            }
        }
        bool insert(const T &ele)
        {
            if (currentSize == maxSize)
            {
                cout << "the heap is full" << endl;
                return false;
            }
            array[currentSize] = ele;
            siftUp(currentSize);
            currentSize++;
            return true;
        }
        void siftUp(int index)
        {
            int temppos = index;
            T temp = array[temppos];
            while ((temppos > 0) && (array[Parent(temppos)] > temp))
            {
                array[temppos] = array[Parent(temppos)];
                temppos = Parent(temppos);
            }
            array[temppos] = temp;
        }
        void SiftDown(int index)
        {
            int i = index;
            int j = LeftChild(index);
            T temp = array[index];
            while (j < currentSize)
            {
                if ((j < currentSize - 1) && (array[j] > array[j + 1]))
                    j++;
                if (temp > array[j])
                {
                    array[i] = array[j];
                    i = j;
                    j = LeftChild(j);
                }
                else
                {
                    break;
                }
            }
            array[i] = temp;
        }
        T RemoveMin()
        {
            if (currentSize < 1)
            {
                cout << "The heap is empty" << endl;
                return T();
            }
            else
            {
                swap(0, --currentSize);
                if (currentSize > 1)
                {
                    SiftDown(0);
                }
                return array[currentSize];
            }
        }
        bool isEmpty() { return currentSize == 0; }
    };

快速排序算法

    template <class T>
    void quicksort(T *array, int left, int right)
    {
        if (left >= right)
            return;
        int l = left;
        int r = right;
        T pivot = array[l];
        while (l < r)
        {
            while (array[r] >= pivot && r > l)
            {
                r--;
            }
            if (l < r)
                array[l++] = array[r];
            while (array[l] <= pivot && r > l)
            {
                l++;
            }
            if (l < r)
                array[r--] = array[l];
        }
        array[r] = pivot;
        quicksort(array, left, r - 1);
        quicksort(array, r + 1, right);
    }

算法描述:

* 采用左侧第一个元素作为轴值，left与right记录比较位置。
1. 从右往左比较，right--，直到遇到第一个比轴值小的元素，交换其与轴值的位置
2. 从左往右比较，left++，直到遇到第一个比轴值大的元素，交换其与轴值的位置
3. 重复1、2直到left相遇（即扫描过一遍数组）以轴值位置将数组一分为二递归调用快排

堆排序算法

    template <class T>
    void heapsort(T *array, int n)
    {
        MinHeap<T> heap(n);
        for (int i = 0; i < n; i++)
        {
            heap.insert(array[i]);
        }
        for (int i = 0; i < n; i++)
        {
            array[i] = heap.RemoveMin();
        }
    }

算法描述：

* 用数组建堆，利用堆的定义直接取出数组最小值进行选择排序

归并排序算法

    template <class T>
    void mergesort(T *array, T *temp, int left, int right)
    {
        if (left < right)
        {
            int middle = (left + right) / 2;
            mergesort(array, temp, left, middle);
            mergesort(array, temp, middle + 1, right);
            int l = left;
            int m = middle + 1;
            for (int i = 0; i <= right - left; i++)
            {
                if (l > middle)
                {
                    temp[left + i] = array[m++];
                }
                else if (array[l] <= array[m] || m > right)
                {
                    temp[left + i] = array[l++];
                }
                else
                {
                    temp[left + i] = array[m++];
                }
            }
            for (int i = 0; i <= right - left; i++)
            {
                array[left + i] = temp[left + i];
            }
        }
    }


算法描述:

1. 分：将数组分为左右两个数组，分别递归调用归并排序。
2. 治：将两个数组合并，设置两个指针指向两个数组的开头，比较数组元素大小，择小插入。

函数调用关系：  
![函数调用关系](https://github.com/daoshiayou/homework/blob/master/Data%20Structures%20and%20Algorithms/source/5函数调用关系.PNG)

## 调试分析

__对设计与实现的分析讨论__：  
本次上机为了比较三种排序的时间算法性能，在原本的快排算法上进行了一些优化，使其优越性更加明显。

__调试中遇到的问题__： 
测试时发现快排时间是堆排和归并的上千倍，最后发现是用于测试堆排和归并的数组并未初始化 
__解决方式__：  
初始化所有数组

## 算法分析

__快速排序算法__：  
_时间复杂度_：O (nlogn)  
_空间复杂度_：O(1)  
__堆排序算法__：  
_时间复杂度_：O(nlogn)  
_空间复杂度_：O(1)  
__归并排序算法__：  
_时间复杂度_：O(nlogn)  
_空间复杂度_：O(n)  

## 用户使用说明

* 无。

## 测试结果

![待排数据个数为600000](https://github.com/daoshiayou/homework/blob/master/Data%20Structures%20and%20Algorithms/source/5测试1.PNG)
![待排数据个数为800000](https://github.com/daoshiayou/homework/blob/master/Data%20Structures%20and%20Algorithms/source/5测试2.PNG)  

## 源程序

    #include <iostream>
    #include <cstdlib>
    #include <ctime>

    using namespace std;

    const int NUM = 600000;

    //Heap
    template <class T>
    class MinHeap
    {
    private:
        T *array;
        int currentSize, maxSize;
        void swap(int pos_x, int pos_y)
        {
            T temp = array[pos_x];
            array[pos_x] = array[pos_y];
            array[pos_y] = temp;
        }
        bool isLeaf(int pos) const
        {
            return (pos >= currentSize / 2) && (pos < currentSize);
        }
        int Parent(int pos) const
        {
            return (pos - 1) / 2;
        }
        int LeftChild(int pos) const
        {
            return 2 * pos + 1;
        }
        void BuildHeap()
        {
            for (int i = currentSize / 2 - 1; i >= 0; i--)
            {
                SiftDown(i);
            }
        }

    public:
        MinHeap(int num)
        {
            if (num <= 0)
                return;
            currentSize = 0;
            maxSize = num;
            array = new T[maxSize];
            BuildHeap();
        }
        ~MinHeap()
        {
            if (array)
            {
                delete[] array;
            }
        }
        bool insert(const T &ele)
        {
            if (currentSize == maxSize)
            {
                cout << "the heap is full" << endl;
                return false;
            }
            array[currentSize] = ele;
            siftUp(currentSize);
            currentSize++;
            return true;
        }
        void siftUp(int index)
        {
            int temppos = index;
            T temp = array[temppos];
            while ((temppos > 0) && (array[Parent(temppos)] > temp))
            {
                array[temppos] = array[Parent(temppos)];
                temppos = Parent(temppos);
            }
            array[temppos] = temp;
        }
        void SiftDown(int index)
        {
            int i = index;
            int j = LeftChild(index);
            T temp = array[index];
            while (j < currentSize)
            {
                if ((j < currentSize - 1) && (array[j] > array[j + 1]))
                    j++;
                if (temp > array[j])
                {
                    array[i] = array[j];
                    i = j;
                    j = LeftChild(j);
                }
                else
                {
                    break;
                }
            }
            array[i] = temp;
        }
        T RemoveMin()
        {
            if (currentSize < 1)
            {
                cout << "The heap is empty" << endl;
                return T();
            }
            else
            {
                swap(0, --currentSize);
                if (currentSize > 1)
                {
                    SiftDown(0);
                }
                return array[currentSize];
            }
        }
        bool isEmpty() { return currentSize == 0; }
    };

    //quicksort
    template <class T>
    void quicksort(T *array, int left, int right)
    {
        if (left >= right)
            return;
        int l = left;
        int r = right;
        T pivot = array[l];
        while (l < r)
        {
            while (array[r] >= pivot && r > l)
            {
                r--;
            }
            if (l < r)
                array[l++] = array[r];
            while (array[l] <= pivot && r > l)
            {
                l++;
            }
            if (l < r)
                array[r--] = array[l];
        }
        array[r] = pivot;
        quicksort(array, left, r - 1);
        quicksort(array, r + 1, right);
    }

    template <class T>
    void heapsort(T *array, int n)
    {
        MinHeap<T> heap(n);
        for (int i = 0; i < n; i++)
        {
            heap.insert(array[i]);
        }
        for (int i = 0; i < n; i++)
        {
            array[i] = heap.RemoveMin();
        }
    }

    template <class T>
    void mergesort(T *array, T *temp, int left, int right)
    {
        if (left < right)
        {
            int middle = (left + right) / 2;
            mergesort(array, temp, left, middle);
            mergesort(array, temp, middle + 1, right);
            int l = left;
            int m = middle + 1;
            for (int i = 0; i <= right - left; i++)
            {
                if (l > middle)
                {
                    temp[left + i] = array[m++];
                }
                else if (array[l] <= array[m] || m > right)
                {
                    temp[left + i] = array[l++];
                }
                else
                {
                    temp[left + i] = array[m++];
                }
            }
            for (int i = 0; i <= right - left; i++)
            {
                array[left + i] = temp[left + i];
            }
        }
    }

    int main()
    {
        double *array1 = new double[NUM];
        double *array2 = new double[NUM];
        double *array3 = new double[NUM];
        srand((double)time(0));
        for (int i = 0; i < NUM; i++)
        {
            array1[i] = rand();
            array2[i] = array1[i];
            array3[i] = array1[i];
        }
        // cout << endl;
        clock_t begin, end;
        begin = clock();
        quicksort<double>(array1, 0, NUM - 1);
        end = clock();
        cout << "quicksort spend " << double(end - begin) / CLK_TCK << " ms" << endl;
        begin = clock();
        heapsort<double>(array2, NUM);
        end = clock();
        cout << "heapsort spend " << double(end - begin) / CLK_TCK << " ms" << endl;
        begin = clock();
        mergesort<double>(array3, new double[NUM], 0, NUM - 1);
        end = clock();
        cout << "mergesort spend " << double(end - begin) / CLK_TCK << " ms" << endl;
        system("pause");
    }