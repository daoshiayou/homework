//？我觉得我被骗了？用书上的函数算自己的算法吗？

//邻接表插删边（setEdge、insertEdge参见P172代码7.4同名函数
//邻接表插入边
void insertEdge(int from,int to,int weight,int isDirected){
    //isDirected==1 有向图， ==0无向图
    if(isDirected)
    {
        setEdge(from,to,weight);
        //有向图在邻接表中插两个弧结点
    }else{
        //无向图在邻接表中插两个弧结点
        setEdge(from,to,weight);
        setEdge(to,from,weight);
    }
}
//邻接表删除边
void delEdge(int from,int to,int weight,int isDirected){
    //isDirected==1 有向图， ==0无向图
    if(isDirected)
    {
        delEdge(from,to,weight);
        //有向图在邻接表中插两个弧结点
    }else{
        //无向图在邻接表中插两个弧结点
        delEdge(from,to,weight);
        delEdge(to,from,weight);
    }
}