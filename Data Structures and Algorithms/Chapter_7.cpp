/**
 * 题目：设计一个算法，在图（有向图或者无向图）的邻接表表示的基础上实现边的插入和删除
 * 
 * 书上的算法看了半天感觉不太对，原来是它只搞了边表，顶点结点没有分配数据空间:(
 * 
 * ===============>然后我发现其实只要把书上头结点的空位置加个T数据就行了<================
 * 
 * 总之我要
 *  一、定义一个邻接表
 *      1、定义一个存边的结点
 *      划掉2、定义一个顶点结点（把十年前的代码copy过来改一改）划掉
 *      3、定义一个带着顶点结点头其他都是边结点的链表
 *      4、定义一个带构造函数的邻接表
 * 
 *  二、实现边的插入
 *      1、返回值：布尔     参数：起点、终点、权值
 *     X2、找到起点遍历查找应该插入边的位置，判断边是否存在(遍历的时候注意避免空指针异常)
 *         存在：修改权值
 *         不存在：进行链表结点插入
 * 
 *  三、实现边的删除
 *      1、返回值：布尔     参数：起点、终点
 *      2、找到起点遍历查找删除的边，判断边是否存在
 *         存在：删除
 *         不存在：返回
 */

#include <iostream>

using namespace std;

//一条带权的单箭头
template <class W>
class edge
{
public:
    int vertex; //边的终点
    W weight;   //边的权值
    edge(const int &v, const W &w) : vertex(v), weight(w) {}
};
//边结点
template <class W>
class eLink
{
public:
    edge<W> *data;
    eLink<W> *next;
    eLink(eLink<W> *nextValue = NULL)
    {
        this->next = nextValue;
    }
    eLink(edge<W> *info, eLink<W> *nextValue = NULL)
    {
        this->data = info;
        this->next = nextValue;
    }
};

//一条链表
template <class T, class W>
class list
{
public:
    T data;
    eLink<W> *next;
    list(eLink<W> *nextValue = NULL)
    {
        this->next = nextValue;
    }
    list(T info, eLink<W> *nextValue = NULL)
    {
        this->data = info;
        this->next = nextValue;
    }
};
template <class T, class W>
class graph
{
private:
    list<T, W> *graList = NULL;

public:
    graph(T *v, const int &num)  //根据数组初始化顶点数组
    {
        this->graList = new list<T, W>[num];
        for (int i = 0; i < num; i++)
        {
            graList[i]->data = v[i];
        }
    }
    //有向图和无向图一起太难了吧！！！！！！！！！！！！！！！！！！！要比上机写得都多了？？？？？？？？？？？？？？
    bool insertEdge(int from, int to, W weight)
    {
        int f = from, t = to;
        eLink<W> *point = graList[f]->next;
        //如果该结点没有边，创建
        if (point == NULL)
        {
            graList[f]->next = new eLink<W>(new edge<W>(t, weight), NULL);
        }
        //有，定位边的位置
        while (point->next != NULL && point->next->data->vertex < t)
        {
            point = point->next;
        }
        //没找到边，在尾巴加上
        if (point->next == NULL)
        {
            point->next = new eLink<W>(new edge<W>(t, weight), NULL);
        }
        //边存在，修改权值
        else if (point->next->data->vertex == t)
        {
            cout << "The edge already exists" << endl;
            point->next->data->weight = weight;
        }
        //边的插入
        else
        {
            point->next = new eLink<W>(new edge<W>(t, weight), point->next);
        }
        return true;
    }
    //  *  三、实现边的删除
    //  *      1、返回值：布尔     参数：起点、终点
    //  *      2、找到起点遍历查找删除的边，判断边是否存在
    //  *         存在：删除,判断是否是无向图
    //  *              是：重复一遍
    //  *              不是：返回
    //  *         不存在：返回
    bool deleteEdge(int from, int to)
    {
        eLink<W> *point = graList[from]->next;
        //如果该结点无边，返回
        if (point == NULL)
        {
            cout << "The edge does not exist" << endl;
            return false;
        }
        //如果有，定位边的位置
        while (point->next != NULL && point->next->data->vertex < to)
        {
            point = point->next;
        }
        //如果无边，返回
        if (point->next == NULL)
        {
            cout << "The edge does not exist" << endl;
            return false;
        }
        //如果无边，返回
        else if (point->next->data->vertex > to)
        {
            cout << "The edge does not exist" << endl;
            return false;
        }
        //找到边，删除
        else
        {
            eLink<W> *temp = point->next;
            point->next = temp->next;
            delete temp;
            return true;
        }
    }
};