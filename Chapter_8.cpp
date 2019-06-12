/**P237 习题13
 * 一个非零数列中有些为正数，有些为负数。
 * 试编写一个算法，重新排列这些非零实数，使得负数排在前面，正数排在后面。
 */
void zeroSort(T *arr, int n)
{
    int l = 0, r = n - 1;
    T temp = arr[r];
    while (l < r)
    {
        while (arr[l] < 0 && l < r)
        {
            l++;
        }
        arr[r--] = arr[l];
        while (arr[r] > 0 && l < r)
        {
            r--;
        }
        arr[l++] = arr[r];
    }
    arr[r] = temp;
}

/**P237 习题14
 * 设有一个仅由红、白、蓝3种颜色的条块（每个色除了颜色一样外，其他性质相同）组成的序列，各种色块的个数是随机的，但三种颜色色块的总数为n。
 * 试编写一个时间复杂度为O(n)的算法，使用辅助空间最少的算法，使得这些条块按照红、白、蓝的顺序排好。
 */
//桶式排序
enum color
{
    red,
    white,
    blue
};
void colorSort(color *c, int n)
{
    color *temp = new color[n];
    int count[3] = {0, 0, 0};
    for (int i = 0; i < n; ++i)
    {
        temp[i] = c[i];
        count[c[i]]++;
    }
    for (int i = i; i < 3; ++i)
    {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; --i)
    {
        c[--count[temp[i]]] = temp[i];
    }
    delete[] temp;
}