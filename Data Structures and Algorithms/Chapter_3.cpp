#include <iostream>
using namespace std;

//结点
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

//P77 第2题
template <class T>
class Queue
{
  private:
    T *p;      //储存数组的地址
    int size;  //队列可以存储的数据个数
    int front; //头结点
    int count; //结点个数

  public:
    Queue(T *q, int m, int f = 0, int c = 0) : p(q), size(m), front(f), count(c) {}
    //判空
    bool isEmpty()
    {
        if (count == 0)
            return true;
        return false;
    }
    //入队
    bool enQuene(const T data)
    {
        p[(front + count) % size] = data;
        count++;
        return true;
    }
    //出队
    bool deQuene(T &data)
    {
        if (this->isEmpty())
            return false;
        data = p[front];
        front = (front + 1) % size;
        count--;
        return true;
    }
};

//P77 第5题
template <class T>
class InkQueue
{
  private:
    Link<T> *rear; //队列尾结点

  public:
    InkQueue() //初始化
    {
        rear = new Link<T>();
        rear->next = rear;
    }
    Link<T> *getRear()
    {
        return rear;
    }
    bool enInkQueue(const T item) //入队
    {
        Link<T> *temp = new Link<T>(item, rear->next);
        rear->next = temp;
        rear = temp;
        return true;
    }
    bool deInkQueue(T &item) //出队
    {
        if (rear->next == rear) //判断队空
        {
            cout << "The Queue is empty" << endl;
            return false;
        }
        Link<T> *temp = rear->next->next;
        item = temp->data;
        rear->next->next = temp->next;
        if (temp == rear)
        {
            rear = rear->next;
        }
        delete temp;
        return true;
    }
};

//P77 第6题
template <class T>
class DoubleStack //把数组最左边的位置看作一个栈的栈底，把数组最右边的位置看作另一个栈的栈底
{
  private:
    int m_size;
    int l_top;
    int r_top;
    T *arr = NULL;

  public:
    DoubleStack(int n) : m_size(n), l_top(0), r_top(n - 1), arr(new T[n]) {} //构造函数
    ~DoubleStack()
    {
        if (arr != NULL)
            delete[] arr;
    }
    void clearl() { l_top = 0; }
    void clearr() { r_top = 0; }
    bool pushL(const T data)
    {
        if (l_top > r_top)
        {
            cout << "Stack is full" << endl;
            return false;
        }
        arr[l_top++] = data;
        return true;
    }
    bool pushR(const T data)
    {
        if (l_top > r_top)
        {
            cout << "Stack is full" << endl;
            return false;
        }
        arr[r_top--] = data;
        return true;
    }
    bool popL(T &item)
    {
        if (l_top == 0)
        {
            cout << "The left stack is empty" << endl;
            return false;
        }
        item = arr[--l_top];
        return true;
    }
    bool popR(T &item)
    {
        if (r_top == m_size - 1)
        {
            cout << "The right stack is empty" << endl;
            return false;
        }
        item = arr[++r_top];
        return true;
    }
};

template <class T>
void show(InkQueue<T> *queue)
{
    Link<T> *p = queue->getRear()->next->next;
    while (p != queue->getRear())
    {
        cout << p->data << endl;
        p = p->next;
    }
    cout << p->data << endl;
}

int main()
{
    DoubleStack<int> *test = new DoubleStack<int>(10);
    for (int i = 0; i < 3; i++)
    {
        test->pushL(i);
    }
    for (int i = 0; i < 10; i++)
    {
        test->pushR(i);
    }
    int j;
    for (int i = 0; i < 10; i++)
    {
        test->popL(j);
        cout << j << endl;
    }
    for (int i = 0; i < 10; i++)
    {
        test->popR(j);
        cout << j << endl;
    }
    return 0;
}
