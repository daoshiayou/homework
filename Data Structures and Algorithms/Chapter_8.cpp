#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int NUM = 10;

void sort1(int *a, int num)
{
    for (int i = 0; i < num; i++)
    {
        int min = a[i];
        int index = 0;
        for (int j = i; j < num; j++)
        {
            if (a[j] < min)
            {
                min = a[j];
                index = j;
            }
        }
        int temp = a[i];
        a[i] = min;
        a[index] = temp;
    }
}

void sort2(int *a, int num)
{
    for (int i = 0; i < num; i++)
    {
        int min = a[i];
        int index = i;
        for (int j = i; j < num; j++)
        {
            if (a[j] < min)
            {
                min = a[j];
                index = j;
            }
        }
        if (i == index)
            continue;
        int temp = a[i];
        a[i] = min;
        a[index] = temp;
    }
}

template <class T>
void sort3(T *a, int num)
{
    int l = 0, r = num - 1;
    while (l < r)
    {
        while (a[l++] < 0)
            ;
        while (a[r--] > 0)
            ;
        T temp = a[l - 1];
        a[l - 1] = a[r + 1];
        a[r + 1] = temp;
    }
}

enum color
{
    red,
    white,
    blue
};
void sort4(color *a, int num)
{
    color *temp = new color[num];
    int count[3] = {0, 0, 0};
    for (int i = 0; i < num; i++)
    {
        temp[i] = a[i];
        count[temp[i]]++;
    }
    for (int i = 1; i < 3; i++)
    {
        count[i] = count[i - 1] + count[i];
    }
    for (int i = num - 1; i >= 0; i--)
    {
        a[--count[temp[i]]] = temp[i];
    }
}

int main()
{
    color a[NUM];
    for (int i = 0; i < NUM; i++)
    {
        a[i] = color(rand() % 3);
        cout << a[i] << endl;
    }
    sort4(a, NUM);
    cout << " " << endl;
    for (int i = 0; i < NUM; i++)
    {
        cout << a[i] << endl;
    }
}