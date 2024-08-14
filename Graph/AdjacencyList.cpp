#include <iostream>

using namespace std;

// queue
const int queueSize = 100;
template <class T>
class queue
{
public:
    T data[queueSize];
    int front, rear;
};

// ALgraph
// 定义边表结点
struct ArcNode
{
    int adjvex; // 存储某顶点的邻接点在顶点表中的下标
    ArcNode *next;
};

// 定义顶点表结点
struct VertexNode
{
    int vertex;         // 存放顶点存储的数值
    ArcNode *firstedge; // 存放指向边表的第一个结点
};

// 基于邻接表存储结构的图的类实现
const int maxsize = 10;
int visited[maxsize] = {0}; // 顶点是否被访问过的标记(用于dfs/bfs)
template <class T>
class ALGraph
{
public:
    ALGraph(T a[], int n, int e); // 构造函数建立具有n个顶点e条边的图
    void DFS(int v);              // 深度优先遍历图
    void BFS(int v);              // 广度优先遍历图

private:
    VertexNode adjlist[maxsize]; // 存放顶点的数组
    int vertexNum, arcNum;       // 图中顶点数和边数
};

template <class T>
ALGraph<T>::ALGraph(T a[], int n, int e)
{
    vertexNum = n;
    arcNum = e;
    // 先初始化边表
    for (int i = 0; i < vertexNum; i++)
    {
        adjlist[i].vertex = a[i];
        adjlist[i].firstedge = nullptr;
    }
    // 然后初始化顶点, 并确定边之间的关系
    for (int k = 0; k < arcNum; k++)
    {
        // i,j代表顶点i到顶点j有边
        int i, j;
        cin >> i >> j;
        ArcNode *s = new ArcNode;
        s->adjvex = j; // s的邻接点在顶点表中下标的编号是j
        s->next = adjlist[i].firstedge;
        adjlist[i]->firstedge = s;
    }
}

template <class T>
void ALGraph<T>::DFS(int v)
{
    cout << adjlist[v].vertex;         // 访问下标为v的结点
    visited[v] = 1;                    // 标记下标为v的结点已经访问过
    ArcNode *p = adjlist[v].firstedge; // 准备访问下一个结点的指针
    while (p != nullptr)
    {
        int j = p->adjvex;   // 这个指针指向的是j结点
        if (visited[j] == 0) // 如果下标编号为j的结点没有被访问过
        {
            DFS(j); // 从j结点开始递归地访问
        }
        p = p->next; // 让指针p移动到当前节点的下一个邻接节点。
    }
}

template <class T>
void ALGraph<T>::BFS(int v)
{
    int visited[maxsize] = {0};
    queue<T> Q;
    Q.front = Q.rear = -1;     // 队列初始化
    cout << adjlist[v].vertex; // 访问顶点表中下标为v的顶点
    visited[v] = 1;            // 将被访问的结点标记
    Q.data[++Q.rear] = v;      // 将被访问的顶点入队
    while (Q.front != Q.rear)  // 一直循环到队空为止
    {
        v = Q.data[++Q.front]; // 对头元素出队
        ArcNode *p = adjlist[v].firstedge;
        while (p != nullptr)
        {
            int j = p->adjvex;
            if (visited[j] == 0)
            {
                int j = p->adjvex;
                cout << adjlist[j].vertex;
                visited[j] = 1;
                Q.data[++Q.rear] = j; // 将顶点j入队，等待后续处理。
            }
            p = p->next;
        }
    }
}