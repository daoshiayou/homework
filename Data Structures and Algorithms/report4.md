
# <center>数据结构第四次上机

<center>一位不愿意透露姓名的陈雎</center>

## 题目：

实现最短路径和最小生成数算法

1. 单源最短、每对顶点最短路径算法
2. prim最小生成树算法：

## 需求分析：

* __输入形式__：从键盘输入测试的算法选项和源点下标。

* __输入值的范围__：算法选项1-3、源点下标不大于顶点数的数字。

* __输出形式__：在控制台上显示即可。

* __程序功能__：计算出图的源点到其他顶点的单源最短路径、每对顶点最短路径和最小生成树。

* __测试数据__：  
    _测试用图_：  
    ![测试用图](https://github.com/daoshiayou/homework/blob/master/Data%20Structures%20and%20Algorithms/source/P4测试用图.PNG)
    _单源最短路径_：  
    有效输入：

    >1  
    >1

    正确输出：  

    >The shortest path from source vertex 1 to others:  
    >0 length:6,pre:3  
    >1 length:0,pre:1  
    >2 length:5,pre:1  
    >3 length:2,pre:1  
    >4 length:7,pre:3  
    >5 length:9,pre:3  
    >6 length:11,pre:3  
    >7 length:10,pre:3  
    >Enter key to choose the algorithm:  
    >1: Dijkstra  
    >2: Floyd  
    >3: Prim  
    >Other: exit  

    无效输入：

    >1  
    >9

    正确输出：

    >The graph has only 8 vertices,Please enter a correct index  
    >Enter key to choose the algorithm:  
    >1: Dijkstra  
    >2: Floyd  
    >3: Prim  
    >Other: exit  

    _每对顶点最短路径_：
    有效输入：

    >2

    正确输出：

    >The Floyd algorithm's data:  
    >0 length:0,pre:0  
    >0 length:4,pre:0  
    >0 length:3,pre:0  
    >0 length:6,pre:1  
    >0 length:11,pre:3  
    >0 length:13,pre:3  
    >0 length:15,pre:3  
    >0 length:13,pre:2  
    >  
    >1 length:6,pre:3  
    >1 length:0,pre:1  
    >1 length:5,pre:1  
    >1 length:2,pre:1  
    >1 length:7,pre:3  
    >1 length:9,pre:3  
    >1 length:11,pre:3  
    >1 length:10,pre:3  
    >  
    >2 length:9,pre:3  
    >2 length:13,pre:0  
    >2 length:0,pre:2  
    >2 length:5,pre:2  
    >2 length:10,pre:3  
    >2 length:12,pre:3  
    >2 length:14,pre:3  
    >2 length:10,pre:2  
    >  
    >3 length:4,pre:3  
    >3 length:8,pre:0  
    >3 length:7,pre:0  
    >3 length:0,pre:3  
    >3 length:5,pre:3  
    >3 length:7,pre:3  
    >3 length:9,pre:3  
    >3 length:8,pre:3  
    >  
    >4 length:12,pre:3  
    >4 length:6,pre:4  
    >4 length:11,pre:1  
    >4 length:8,pre:1  
    >4 length:0,pre:4  
    >4 length:15,pre:3  
    >4 length:17,pre:3  
    >4 length:16,pre:3  
    >  
    >5 length:19,pre:3  
    >5 length:13,pre:4  
    >5 length:18,pre:1  
    >5 length:15,pre:1  
    >5 length:7,pre:6  
    >5 length:0,pre:5  
    >5 length:2,pre:5  
    >5 length:6,pre:5  
    >  
    >6 length:17,pre:3  
    >6 length:11,pre:4  
    >6 length:16,pre:1  
    >6 length:13,pre:1  
    >6 length:5,pre:6  
    >6 length:20,pre:3  
    >6 length:0,pre:6  
    >6 length:21,pre:3  
    >  
    >7 length:24,pre:3  
    >7 length:18,pre:4  
    >7 length:23,pre:1  
    >7 length:20,pre:1  
    >7 length:12,pre:6  
    >7 length:27,pre:3  
    >7 length:7,pre:7  
    >7 length:0,pre:7  
    >  
    >Enter key to choose the algorithm:  
    >1: Dijkstra  
    >2: Floyd  
    >3: Prim  
    >Other: exit

    _最小生成树_：  
    有效输入：

    >3  
    >1

    正确输出：  

    >The minimum spanning tree's edges obtained from the source vertex 1 are:  
    >from:1,to:3,weight:2  
    >from:1,to:2,weight:5  
    >from:3,to:0,weight:4  
    >from:3,to:4,weight:5  
    >from:3,to:5,weight:7  
    >from:3,to:7,weight:8  
    >from:3,to:6,weight:9  
    >Enter key to choose the algorithm:  
    >1: Dijkstra  
    >2: Floyd  
    >3: Prim  
    >Other: exit  

    无效输入：

    >3  
    >9

    正确输出：

    >The graph has only 8 vertices,Please enter a correct index  
    >Enter key to choose the algorithm:  
    >1: Dijkstra  
    >2: Floyd  
    >3: Prim  
    >Other: exit

## 概要设计：

__ADT定义__：  

边：

    class Edge
    {
    public:
        int from;
        int to;
        int weight;
        Edge(int from, int to, int weight);
        Edge();
    };
    ostream &operator<<(ostream &o, const Edge &e);

图(采用相邻矩阵表示法)：

    class Graph
    {
    private:
        int numVertex;
        int numEdge;
        bool *mark; //true: VISITED     false:UNVISITED
        int **matrix;

    public:
        Graph(const int &num);
        Graph();
        int getNumVertex(); const
        int getNumEdge(); const
        bool *getMark(); const
        int *&operator[](int i); const
        ~Graph();
        void setEdge(Edge e);
        void setEdge(int from, int to, int weight);
        void delEdge(int from, int to);
        Edge firstEdge(int index); const
        Edge nextEdge(Edge preEdge); const
        int getWeight(int from, int to); const
        int toVertex(Edge e); const
        bool isEdge(Edge e); const
    };

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

记录最短路径的类：

    class Dist
    {
    public:
        int index;
        int length;
        int pre;
        bool operator>(const Dist &d);
        bool operator<(const Dist &d);
    };
    ostream &operator<<(ostream &o, const Dist &d);

单源最短路径(Dijkstra算法)

    Dist *Dijkstra(const Graph *g, int s);

每对顶点最短路径(Floyd算法)

    Dist **Floyd(const Graph *g);

最小生成树(Prim算法)

    Edge *Prim(const Graph *g, int s);

主程序流程：  
提示用户输入->获取用户输入的选项和数据->调用相应算法->输出算法生成结果  
调用关系：  
![调用关系](https://github.com/daoshiayou/homework/blob/master/Data%20Structures%20and%20Algorithms/source/4模块调用关系.png)

## 详细设计

__ADT定义__：  
边：

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

图(采用相邻矩阵表示法)：

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

记录最短路径的类：

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

单源最短路径(Dijkstra算法)

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

算法描述:

1. 分配空间储存并初始化最短路径数据
2. 建最小堆存放原点到开销最小的最短路径数据，先把初始化后的源点路径插入堆（即已经找到最短路径的顶点）
3. 取出未访问过的顶点并标记以访问，以该点为起点更新最短路径数据，将更新过的路径插入堆
4. 重复3直到所有顶点都访问过（即所有顶点都找到最小路径）
5. 返回最短路径数据

每对顶点最短路径(Floyd算法)

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

算法描述:

1. 分配空间储存并初始化最短路径数据
2. 遍历图，将图中有边相连的顶点记录到最小数据路径中（单边）
3. 假设顶点i到顶点j经过中转点k，比较其路径长短，若较短，更新最短路径信息（此时可以输出一遍最小路径数据，可以对算法流程有比较直观的感受，大概）
4. 重复3遍历所有顶点，结束后得到每对顶点最短路径

最小生成树(Prim算法)

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

算法描述：

1. 分配空间储存并初始化最短路径数据，分配空间储存最小生成树的边
2. 建最小堆存放原点到开销最小的最短路径数据，先把初始化后的源点路径插入堆（即已经找到最短路径的顶点）
3. 取出顶点未访问过的并标记以访问，将pre到该顶点的边存到生成树数组中，以该点为起点更新最短路径数据，将更新过的路径插入堆
4. 重复3直到所有顶点都访问过
5. 返回生成树边数组

函数调用关系：  
![函数调用关系](https://github.com/daoshiayou/homework/blob/master/Data%20Structures%20and%20Algorithms/source/4函数调用关系.PNG)

## 调试分析

__对设计与实现的分析讨论__：  
因为书上有相关的算法,一开始想偷懒就照抄了一遍书上的算法.或许是时日已久,越抄越觉得迷惑,看不懂书上的代码在干嘛,强迫症上来决定自己写.最后觉得自己的水平也就这样了,大概就是把教材的代码改简洁了一点?教材果然还是有过人的地方啊.

__调试中遇到的问题__：  
相邻矩阵的构造函数都是堆分配的空间,将引用做参数传入函数,函数返回时自动释放了,导致只能每次运行程序只能测试一次算法.  
__解决方式__：  
改为将指针作为函数参数

## 算法分析

__Dijkstra算法__：  
_时间复杂度_：O((n+e)loge)  
_空间复杂度_：O(n)  
__Floyd算法__：  
_时间复杂度_：O(n*n*n)  
_空间复杂度_：O(n*n)  
__Prim算法__：  
_时间复杂度_：O(n*n)  
_空间复杂度_：O(n)  

## 用户使用说明

* 根据提示输入选项，回车确定。

## 测试结果

![输入1](https://github.com/daoshiayou/homework/blob/master/Data%20Structures%20and%20Algorithms/source/4测试1.PNG)
![输出1](https://github.com/daoshiayou/homework/blob/master/Data%20Structures%20and%20Algorithms/source/4测试2.PNG)  
![输入2](https://github.com/daoshiayou/homework/blob/master/Data%20Structures%20and%20Algorithms/source/4测试3.PNG)
![输出2](https://github.com/daoshiayou/homework/blob/master/Data%20Structures%20and%20Algorithms/source/4测试4.PNG)

## 源程序

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