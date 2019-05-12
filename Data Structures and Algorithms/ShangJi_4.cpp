/**实现最短路径和最小生成数算法
 * 1. 单源最短、每对顶点最短路径算法
 * 2. prim最小生成树算法
 * 
 * 流程：
 *  1. 定义计算的图
 *  2. 用户输入调用算法
 *     （1）单源最短：Dijkstra算法
 *          需要用户输入源点
 *          a. 分配空间储存并初始化最短路径数据
 *          b. 建最小堆存放原点到开销最小的最短路径数据，先把初始化后的源点路径插入堆（即已经找到最短路径的顶点）
 *          c. 取出未访问过的顶点并标记以访问，以该点为起点更新最短路径数据，将更新过的路径插入堆
 *          d. 重复c直到所有顶点都访问过（即所有顶点都找到最小路径）
 *          e. 返回最短路径数据
 *     （2）每对顶点最短：Floyd算法
 *          a. 分配空间储存并初始化最短路径数据
 *          b. 遍历图，将图中有边相连的顶点记录到最小数据路径中（单边）
 *          c. 假设顶点i到顶点j经过中转点k，比较其路径长短，若较短，更新最短路径信息（此时可以输出一遍最小路径数据，可以对算法流程有比较直观的感受，大概）
 *          d. 重复c遍历所有顶点，结束后得到每对顶点最短路径
 *            （思维误区：计算中转点时取出的最短路径是最终的最短吗？如果不是如何保证是最短路径？
 *                       即，执行d[i][j]=min(d[i][j],d[i][k]+d[k][j])时，d[i][k]与d[k][j]是否都保证为最小值？
 *              找到的答案：对于所有的k,执行那个语句前d[i][k]和d[k][j]不一定都是最小值.但是存在一个k=x,在执行那个语句前d[i][x]和d[x][j]都是最小值.并且x是i和j最短路径的点集里最大的编号）https://blog->csdn.net/ljhandlwt/article/details/52096932
 *             妙啊:open_mouth:
 *     （3）最小生成树：prim算法（在Dijkstra里加一步就是了，还可以调用Dijkstra后用得到的最短路径直接生成吧）
 *          需要用户输入源点
 *          a. 分配空间储存并初始化最短路径数据，分配空间储存最小生成树的边
 *          b. 建最小堆存放原点到开销最小的最短路径数据，先把初始化后的源点路径插入堆（即已经找到最短路径的顶点）
 *          c. 取出顶点未访问过的并标记以访问，将pre到该顶点的边存到生成树数组中，以该点为起点更新最短路径数据，将更新过的路径插入堆
 *          d. 重复c直到所有顶点都访问过
 *          e. 返回生成树边数组
 *          为了直观显示的附加工作：根据数组生成树（to do）
 * 准备工作：
 *  1. 定义相关类（边类、图类、、堆类、用于存放路径的数据类）
 *  2. 敲算法
 *  3. 敲测试函数
*/

#include <iostream>
#include <limits>
#include <vector>
using namespace std;
int const INFINITY = numeric_limits<int>::max();

//Edge, weights are set to integer type for convenience
class Edge
{
public:
    int from;
    int to;
    int weight;
    Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
    Edge() : from(-1), to(-1) {}
};
ostream &operator<<(ostream &o, const Edge &e)
{
    cout << "from:" << e.from << ",to:" << e.to << ",weight:" << e.weight;
    return o;
}

//Graph, use a matrix of adjacency for convenience
class Graph
{
private:
    int numVertex;
    int numEdge;
    bool *mark; //true: VISITED     false:UNVISITED
    int **matrix;

public:
    Graph(const int &num)
    {
        if (num <= 0)
        {
            cout << "The number of vertices cannot be less than 0" << endl;
            return;
        }
        numVertex = num;
        numEdge = 0;
        mark = new bool[num];
        matrix = new int *[num];
        for (int i = 0; i < num; i++)
        {
            matrix[i] = new int[num];
            mark[i] = false;
        }
        for (int i = 0; i < num; i++)
        {
            for (int j = 0; j < num; j++)
            {
                if (i == j)
                {
                    matrix[i][j] = 0;
                }
                else
                {
                    matrix[i][j] = INFINITY; //different from book
                }
            }
        }
    }
    Graph() : numVertex(0), mark(NULL), matrix(NULL) {}
    int getNumVertex() const
    {
        return numVertex;
    }
    int getNumEdge() const
    {
        return numEdge;
    }
    bool *getMark() const
    {
        return mark;
    }
    int *&operator[](int i) const
    {
        return matrix[i];
    }
    ~Graph()
    {
        if (mark)
        {
            delete[] mark;
        }
        if (matrix)
        {
            for (int i = 0; i < numVertex; i++)
            {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
    }
    void setEdge(Edge e)
    {
        matrix[e.from][e.to] = e.weight;
        numEdge++;
    }
    void setEdge(int from, int to, int weight)
    {
        matrix[from][to] = weight;
        numEdge++;
    }
    void delEdge(int from, int to)
    {
        matrix[from][to] = INFINITY;
        numEdge--;
    }
    Edge firstEdge(int index) const
    {
        for (int i = 0; i < numVertex; i++)
        {
            if (matrix[index][i] != 0 && matrix[index][i] != INFINITY)
            {
                return Edge(index, i, matrix[index][i]);
            }
        }
        return Edge();
    }
    Edge nextEdge(Edge preEdge) const
    {
        for (int i = preEdge.to + 1; i < numVertex; i++)
        {
            if (matrix[preEdge.from][i] != 0 && matrix[preEdge.from][i] != INFINITY)
                return Edge(preEdge.from, i, matrix[preEdge.from][i]);
        }
        return Edge();
    }
    int getWeight(int from, int to) const
    {
        return matrix[from][to];
    }
    int toVertex(Edge e) const
    {
        return e.to;
    }
    bool isEdge(Edge e) const
    {
        if (e.to == -1 || e.from == -1)
            return false;
        return matrix[e.from][e.to] != 0 && matrix[e.from][e.to] != INFINITY;
    }
};

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

//Dist, to record shortest path information
class Dist
{
public:
    int index;
    int length;
    int pre;
    bool operator>(const Dist &d)
    {
        return this->length > d.length;
    }
    bool operator<(const Dist &d)
    {
        return this->length < d.length;
    }
};
ostream &operator<<(ostream &o, const Dist &d)
{
    cout << d.index << " length:" << d.length << ",pre:" << d.pre;
    return o;
}

Dist *Dijkstra(const Graph *g, int s)
{
    Dist *path = new Dist[g->getNumVertex()];
    bool *mark = g->getMark();
    //initializes path information and visited tag
    for (int i = 0; i < g->getNumVertex(); i++)
    {
        path[i].index = i;
        path[i].length = INFINITY;
        path[i].pre = s;
        mark[i] = false;
    }
    path[s].length = 0;
    MinHeap<Dist> heap(g->getNumEdge());
    heap.insert(path[s]);
    Dist temp;
    //main algorithm
    while (!heap.isEmpty())
    {
        temp = heap.RemoveMin();
        if (mark[temp.index] == false)
        {
            mark[temp.index] = true;
            for (Edge e = g->firstEdge(temp.index); g->isEdge(e); e = g->nextEdge(e))
            {
                if (path[e.to].length > path[e.from].length + e.weight)
                {
                    path[e.to].length = path[e.from].length + e.weight;
                    path[e.to].pre = e.from;
                    heap.insert(path[e.to]);
                }
            }
        }
    }
    return path;
}

Dist **Floyd(const Graph *g)
{
    Dist **path = new Dist *[g->getNumVertex()];
    //initializes path information and visited tag
    for (int i = 0; i < g->getNumVertex(); i++)
    {
        path[i] = new Dist[g->getNumVertex()];
    }
    for (int i = 0; i < g->getNumVertex(); i++)
    {
        for (int j = 0; j < g->getNumVertex(); j++)
        {
            if (i == j)
            {
                path[i][j].length = 0;
                path[i][j].pre = i;
            }
            else
            {
                path[i][j].length = (*g)[i][j];
                path[i][j].pre = (*g)[i][j] == INFINITY ? -1 : i;
            }
            path[i][j].index = i;
        }
    }
    //main algorithm
    for (int k = 0; k < g->getNumVertex(); k++)
    {
        for (int i = 0; i < g->getNumVertex(); i++)
        {
            for (int j = 0; j < g->getNumVertex(); j++)
            {
                if (path[i][k].length == INFINITY || path[k][j].length == INFINITY)
                    continue;
                if (path[i][j].length > path[i][k].length + path[k][j].length)
                {
                    path[i][j].length = path[i][k].length + path[k][j].length;
                    path[i][j].pre = path[k][j].pre;
                }
            }
        }
    }
    return path;
}

Edge *Prim(const Graph *g, int s)
{
    Dist *path = new Dist[g->getNumVertex()];
    bool *mark = g->getMark();
    Edge *tree = new Edge[g->getNumVertex() - 1];
    int index = 0;
    //initializes path information and visited tag
    for (int i = 0; i < g->getNumVertex(); i++)
    {
        path[i].index = i;
        path[i].length = INFINITY;
        path[i].pre = s;
        mark[i] = false;
    }
    path[s].length = 0;
    MinHeap<Dist> heap(g->getNumVertex());
    for (Edge e = g->firstEdge(s); g->isEdge(e); e = g->nextEdge(e))
    {
        if (path[e.to].length > path[e.from].length + e.weight)
        {
            path[e.to].length = path[e.from].length + e.weight;
            path[e.to].pre = e.from;
            heap.insert(path[e.to]);
        }
    }
    Dist temp;
    //main algorithm
    while (!heap.isEmpty())
    {
        temp = heap.RemoveMin();
        if (mark[temp.index] == false)
        {
            mark[temp.index] = true;
            tree[index++] = Edge(temp.pre, temp.index, /*path[temp.index].length - path[temp.pre].index*/ (*g)[temp.pre][temp.index]);
            for (Edge e = g->firstEdge(temp.index); g->isEdge(e); e = g->nextEdge(e))
            {
                if (path[e.to].length > path[e.from].length + e.weight)
                {
                    path[e.to].length = path[e.from].length + e.weight;
                    path[e.to].pre = e.from;
                    heap.insert(path[e.to]);
                }
            }
        }
    }
    delete[] path;
    return tree;
}

int main()
{
    Graph *g = new Graph(8);
    g->setEdge(0, 1, 4);
    g->setEdge(0, 2, 3);
    g->setEdge(3, 0, 4);
    g->setEdge(1, 2, 5);
    g->setEdge(1, 3, 2);
    g->setEdge(4, 1, 6);
    g->setEdge(2, 3, 5);
    g->setEdge(2, 7, 10);
    g->setEdge(3, 4, 5);
    g->setEdge(3, 5, 7);
    g->setEdge(3, 6, 9);
    g->setEdge(3, 7, 8);
    g->setEdge(3, 7, 8);
    g->setEdge(6, 4, 5);
    g->setEdge(5, 6, 2);
    g->setEdge(5, 7, 6);
    g->setEdge(7, 6, 7);
    while (1)
    {
        cout << "Enter key to choose the algorithm:" << endl;
        cout << "1: Dijkstra" << endl;
        cout << "2: Floyd" << endl;
        cout << "3: Prim" << endl;
        cout << "Other: exit" << endl;
        char choice;
        cin >> choice;
        cin.clear();
        cin.ignore(1024, '\n');
        switch (choice)
        {
        case '1':
        {
            cout << "Please enter the source vertex:" << endl;
            int source;
            cin >> source;
            cin.clear();
            cin.ignore(1024, '\n');
            if (source >= g->getNumVertex())
            {
                cout << "The graph has only " << g->getNumVertex() << " vertices,Please enter a correct index" << endl;
                break;
            }
            cout << "The shortest path from source vertex " << source << " to others:" << endl;
            ;
            Dist *d = Dijkstra(g, source);
            for (int i = 0; i < g->getNumVertex(); i++)
            {
                cout << d[i] << endl;
            }
            delete[] d;
            break;
        }
        case '2':
        {
            Dist **d = Floyd(g);
            cout << "The Floyd algorithm's data:" << endl;
            ;
            for (int i = 0; i < g->getNumVertex(); i++)
            {
                for (int j = 0; j < g->getNumVertex(); j++)
                {
                    cout << d[i][j] << " " << endl;
                }
                cout << endl;
                delete[] d[i];
            }
            delete[] d;
            break;
        }
        case '3':
        {
            cout << "Please enter the source vertex:" << endl;
            int source;
            cin >> source;
            cin.clear();
            cin.ignore(1024, '\n');
            if (source >= g->getNumVertex())
            {
                cout << "The graph has only " << g->getNumVertex() << " vertices,Please enter a correct index" << endl;
                break;
            }
            cout << "The minimum spanning tree's edges obtained from the source vertex " << source << " are:" << endl;
            ;
            Edge *edges = Prim(g, source);
            for (int i = 0; i < g->getNumVertex() - 1; i++)
            {
                cout << edges[i] << endl;
            }
            delete[] edges;
            break;
        }
        default:
            break;
        }
    }
    return 0;
}