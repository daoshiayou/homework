#include <iostream>
using namespace std;

//链表结点
template <class T>
class Link
{
  public:
    T data;
    Link<T> *next;
    Link(Link<T> *nextValue = NULL)
    {
        this->next = nextValue;
    }
    Link(T info, Link<T> *nextValue = NULL)
    {
        this->data = info;
        this->next = nextValue;
    }
};
//用来表示圆桌的单循环链表
class LnkList
{
  public:
    Link<int> *head; //头结点
    LnkList()        //无参构造函数
    {
        head = new Link<int>();
    }
    LnkList(int personNumber) //有参构造函数
    {

        head = new Link<int>(1);
        Link<int> *p1 = head;
        for (int i = 1; i < personNumber; i++)
        {
            Link<int> *temp = new Link<int>(i + 1);
            p1->next = temp;
            p1 = p1->next;
        }
        p1->next = head;
    }
    ~LnkList() //析构函数
    {
        Link<int> *p1, *p2;
        p1 = head;
        while (p1 != NULL)
        {
            p2 = p1;
            p1 = p1->next;
            delete p2;
        }
        delete head;
    }
};

class ArrList
{
  public:
    int *arr;
    ArrList(int n)
    {
        arr = new int[n];
        for (int i = 0; i < n; i++)
        {
            arr[i] = i + 1;
        }
    }
    ~ArrList()
    {
        if (arr != NULL)
        {
            delete[] arr;
        }
    }
};

void JosephusList(int n, int s, int m) //有n个人，从第s个人开始报数，数到第m的人出列
{
    if (!(n > 0 && s > 0 && m > 0))
    {
        cout << "Please enter the correct value" << endl;
        return;
    }
    LnkList *persons = new LnkList(n);
    for (int i = 1; i < s; i++) //从第s个人开始报数
    {
        persons->head = persons->head->next;
    }
    int i = 0;
    Link<int> *p = persons->head;
    while (persons->head->next != persons->head)
    {
        i++;
        if (i % m == 0)
        {
            p->next = persons->head->next;
            cout << "No." << persons->head->data << " is out" << endl;
            delete persons->head;
            persons->head = p;
        }
        p = persons->head;
        persons->head = persons->head->next;
    }
    cout << "Game over,No." << persons->head->data << " is left" << endl;
}

void JosephusArr(int n, int s, int m)
{
    if (!(n > 0 && s > 0 && m > 0))
    {
        cout << "Please enter the correct value" << endl;
        return;
    }
    ArrList *persons = new ArrList(n);
    int index = s - 1, count = 0, p = n;
    while (p > 1)
    {
        if (persons->arr[index] == -1)
        {
            index = (index + 1) % n;
            continue;
        }
        count++;
        if (count == m)
        {
            cout << "No." << persons->arr[index] << " is out" << endl;
            persons->arr[index] = -1;
            p--;
            count = 0;
        }
        index = (index + 1) % n;
    }
    index = 0;
    while (persons->arr[index++] == -1)
        ;
    cout << "Game over,No." << persons->arr[--index] << " is left" << endl;
}

int main()
{

    int n, s, m;
    cout << "Enter Persons number n, start number s,count number m:" << endl;
    cin >> n >> s >> m;
    cout << "Chain method:" << endl;
    JosephusList(n, s, m);
    cout << "Array methods:" << endl;
    JosephusArr(n, s, m);
    system("pause");
}