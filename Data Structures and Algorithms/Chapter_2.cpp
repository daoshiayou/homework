#include <iostream>
#include <cstdarg>

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

//带头结点的链表
template <class T>
class LnkList
{
  private:
    Link<T> *head; //头结点
  public:
    LnkList() //无参构造函数
    {
        head = new Link<T>();
    }
    LnkList(const initializer_list<T> &links) //有参构造函数，用了C++11特性
    {
        head = new Link<T>();
        Link<T> *p = head;
        for (auto link : links)
        {
            Link<T> *temp = new Link<T>(link);
            p->next = temp;
            p = p->next;
        }
    }
    ~LnkList() //析构函数
    {
        Link<T> *p1, *p2;
        p1 = head;
        while (p1 != NULL)
        {
            p2 = p1;
            p1 = p1->next;
            delete p2;
        }
        delete head;
    }
    Link<T> *getHead()
    {
        return head;
    }
    bool append(const T data) //在链表尾部添加元素
    {
        Link<T> *p = head;
        while (p->next != NULL)
        {
            p = p->next;
        }
        Link<T> *temp = new Link<T>(data);
        p->next = temp;
        return true;
    }
};

//P45 第3题
template <class T>
void delectValue(LnkList<T> *list)
{

    Link<T> *p1;
    p1 = list->getHead()->next;
    int count = 0; //计算结点个数,防止误删
    while (p1 != NULL)
    {
        count++;
        p1 = p1->next;
    }
    if (count <= 2) //当结点数小于等于2时直接返回
    {
        return;
    }
    Link<T> *p2;
    p1 = list->getHead()->next->next;
    while (p1->next != NULL)
    {
        p2 = p1;
        p1 = p1->next;
        delete p2;
    }
    list->getHead()->next->next = p1;
}

//P45 第8题
template <class T>
T *intersection(T *a, T *b, int lenA, int lenB)
{
    T *c = new T[lenA > lenB ? lenB : lenA];
    int k = 0;
    for (int i = 0; i < lenA; i++)
    {
        for (int j = 0; j < lenB; j++)
        {
            if (b[j] > a[i])
                break;
            else if (b[j] == a[i])
            {
                c[k++] = b[j];
                break;
            }
        }
    }
    return c;
}

//P45 第9题
template <class T>
LnkList<T> *intersection(LnkList<T> *listA, LnkList<T> *listB)
{
    LnkList<T> *listC = new LnkList<T>();
    Link<T> *pa = listA->getHead()->next;
    while (pa != NULL)
    {
        Link<T> *pb = listB->getHead()->next;
        while (pb != NULL)
        {
            if (pb->data == pa->data)
            {
                listC->append(pb->data);
                break;
            }
            pb = pb->next;
        }
        pa = pa->next;
    }
    return listC;
}

template <class T>
void showLnkList(LnkList<T> *list)
{
    Link<T> *p = list->getHead()->next;
    while (p != NULL)
    {
        cout << p->data << endl;
        p = p->next;
    }
}

int main()
{
    // LnkList<int> *test1 = new LnkList<int>({1,2,3});
    // showLnkList(test1);
    // delectValue(test1);
    // showLnkList(test1);
    LnkList<int> *listA = new LnkList<int>({1, 2, 3, 4, 5, 6});
    LnkList<int> *listB = new LnkList<int>({2, 3, 4, 5, 6, 7});
    LnkList<int> *listC = intersection(listA, listB);
    cout<<"A"<<endl;
    showLnkList(listA);
    cout<<"B"<<endl;
    showLnkList(listB);
    cout<<"C"<<endl;
    showLnkList(listC);
    return 0;
}
