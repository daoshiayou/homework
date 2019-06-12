/**P77 习题2
 * 如果用一个循环数组q[0..m-1]表示队列时，该队列只有一个队列头指针front，不设队列尾指针rear，而设置计数器count用以记录队列中结点的个数。
 * 试编写算法实现队列中的3个基本运算：判空、入队、出队。
 */
template <class T>
class arrQueue : public Queue
{
private:
    T qu[m];
    int count;
    int front;

public:
    bool isEmpty() { return count == 0; }
    bool enQueue(const T item)
    {
        if (count == m)
        {
            cout << "队满不能入" << endl;
            return false;
        }
        else
        {
            int r = (front + count++) % m;
            q[r] = item;
            return true;
        }
    }
    bool deQueue(T &item)
    {
        if (count == 0)
        {
            cout << "队空不能出" << endl;
            return false;
        }
        else
        {
            item = qu[front];
            front = (front + 1) % m;
            count--;
            return true;
        }
    }
}

/**P77 习题5
 * 假设以带头结点的循环链表表示队列，并且只设一个指针指向队尾元素结点（不设头结点）
 * 试编写队列初始化、入队列和出队列的算法
 */
template <class T>
class InkQueue : public Queue<T>
{
private:
    Link<T> *rear; //队尾指针
public:
    InkQueue()
    {
        rear = new Link<T>(NULL); //附加头结点
        rear->next = rear;
    }
    bool enQueue(const T item)
    {
        Link<T> *temp = new Link<T>(item, rear->next);
        rear->next = temp;
        rear = rear->next;
        return true;
    }
    bool deQueue(T &item)
    {
        if (rear->next == rear)
        {
            cout << "队空，不能出队" << endl;
            return false;
        }
        else
        {
            Link<T> *p = rear->next; //头结点
            item = p->data;
            rear->next = p->next; //分离头结点
            delete p;
            return true;
        }
    }
}

/**P77 习题6
 * 试在一个长度为n的数组中实现两个栈，使得二者在元素的总数目为n之前都不溢出，
 * 并且保证push和pop操作的时间代价为O(1)
 */
//用了自己的作业
template <class T>

class DoubleStack //把数组最左边的位置看作一个栈的栈底，把数组最右边的位置看作另一个栈的栈底
{
private:
    T *arr = NULL;
    int m_size, l_top, r_top;

public:
    DoubleStack(int n) : m_size(n), l_top(0), r_top(n - 1), arr(new T[n]) {} //构造函数
    ~DoubleStack()
    {
        if (arr != NULL)
            delete[] arr;
    }
    void clearl() { l_top = 0; }
    void clearr() { r_top = n - 1; }
    bool pushL(const T data)
    {
        if (l_top > r_top)
        {
            cout << "栈满，不能入栈" << endl;
            return false;
        }
        arr[l_top++] = data;
        return true;
    }
    bool pushR(const T data)
    {
        if (l_top > r_top)
        {
            cout << "栈满，不能入栈" << endl;
            return false;
        }
        arr[r_top--] = data;
        return true;
    }
    bool popL(T &item)
    {
        if (l_top == 0)
        {
            cout << "栈空，不能出栈" << endl;
            return false;
        }
        item = arr[--l_top];

        return true;
    }
    bool popR(T &item)
    {
        if (r_top == m_size - 1)
        {
            cout << "栈空，不能出栈" << endl;
            return false;
        }
        item = arr[++r_top];
        return true;
    };
}