/**P45 习题3
 * 设线性表中的数据元素以值递增排列，并以单链表作为存储结构。
 * 设计一个高效的算法，删除表中所有值大于min且小于max的元素，同时释放被删除结点的空间。
 * 并分析算法的时间复杂度
 */
template <class T>
bool lnKList<T>::ListDelete(T min, T max)
{
    //带头结点的非降序链表删除min<且<max的结点
    Link<T> *p, *q, *temp;
    q = head;
    p = head->next;
    //让p定位到第一个被删结点
    while (p->data <= min)
    {
        p = q;
        p = p->next;
    }
    while (p->data > min && p->data < max)
    {
        temp = p;
        q->next = p->next;
        p = p->next;
        delete temp;
    }
    return true;
}
//时间复杂度：O(n)
//当时想得太浅，链表中可能存在相同数值的数，所以需要进行比较

/**P45 8
 * 已知两个元素按值增值有序排列的线性表A和B，且同一表中的元素值各不相同。
 * 试构造一个线性表C，其元素为A和B中元素的交集，且表C中的元素也按值递增有序排列。
 * 设计对A、B、C都是顺序表时的算法。
 */
//老师的答案太绕了，我直接用我的改了
template <class T>
T *intersection(T *a, T *b, int lenA, int lenB)
{
    T *c = new T[lenA > lenB ? lenB : lenA];
    int i = j = k = 0;
    while (i < lenA && j < lenB)
    {
        if (a[i] > b[j])
        {
            j++;
        }
        else if (a[i] < b[j])
        {
            i++;
        }
        else
        {
            c[k++] = a[i++];
            j++;
        }
    }
    return c;
}

/**P45 9
 * 同上题，设计当A、B、C都是单链表的算法
 */
//和第8题的思路是一样的
InkList<T> InkList<T>::Intersection(InkList<T> A, InkList<T> B)
{
    InkList<T> *C, *p, *q, *r;
    p = A.head->next;
    q = B.head->next;
    C.head = C.tail = new Link();
    while (p != NULL && q != NULL)
    {
        if (p->data < q->data)
        {
            p = p->next;
        }
        else if (p->data > q->data)
        {
            q = q->next;
        }
        else
        {
            r = new Link(p->data, NULL);
            C.tail->next = r;
            C.tail = r;
            p = p->next;
            q = q->next;
        }
        return C;
    }
}
