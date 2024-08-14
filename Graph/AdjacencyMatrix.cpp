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

// AMGraph
const int maxszie = 10;
int visited[maxszie] = {0}; // 顶点是否被访问过的标记 (用于dfs/bfs)
// 基于邻接矩阵存储结构的图的类实现
template <class T>
class AMGraph
{
public:
    AMGraph(T a[], int n, int e); // 构造函数建立具有n个顶点e条边的图
    ~AMGraph() {};
    void DFS(int v); // 深度有限遍历图
    void BFS(int v); // 广度优先遍历图

private:
    T vertex[maxsize];     // 存放图中顶点的数组
    int arc[maxsize];      // 存放图中边的数组
    int vertexNum, arcNum; // 图中顶点数和边数
};

template <class T>
AMGraph<T>::AMGraph(T a[], int n, int e)
{
    vertexNum = n;
    arcNum = e;
    for (int i = 0; i < vertexNum; i++) // 顶点初始化
    {
        vertex[i] = a[i];
    }
    for (int i = 0; i < vertexNum; i++) // 邻接矩阵初始化
    {
        for (int j = 0; i < vertexNum; j++)
        {
            a[i][j] = 0;
        }
    }
    for (int k = 0; k < arcNum; k++)
    {
        int i, j;
        cin >> i >> j; // 依次输入依附的顶点的编号
        arc[i][j] = 1; // 标记为两点之间有边
        arc[j][i] = 1;
    }
}

template <class T>
void AMGraph<T>::DFS(int v)
{
    cout << vertex[v] << " "; // 访问这个点
    visited[v] = 1;           // 标记这个点已经被访问
    // 按照编号从小到大的规则一直遍历走下去
    for (int j = 0; j < vertexNum; j++)
    {
        if (arc[v][j] == 1 && visited[j] == 0) // 如果v到j有边 && j没有被访问到过
        {
            DFS(j); // 对j进行递归地搜索(也就是从小到大一直走下去)
        }
    }
}

template <class T>
void AMGraph<T>::BFS(int v)
{
    int visited[maxsize] = {0};
    queue<T> Q;
    Q.front = Q.rear = -1;    // 初始化队列
    cout << vertex[v] << " "; // 访问顶点
    visited[v] = 1;           // 标记该顶点被访问过
    Q.data[++Q.rear] = v;     // 被访问顶点入队
    while (Q.front != Q.rear) // 一直循环到队空
    {
        v = Q.data[++Q.front]; // 头元素出队
        for (int j = 0; j < vertexNum; j++)
        {
            if (arc[v][j] == 1 && visited[j] == 0)
            {
                cout << vertex[j] << " ";
                visited[j] = 1;
                Q.data[++Q.rear] = j; // 邻接点入队,这样在后续的BFS遍历中，可以进一步访问顶点j及其邻接点。
            }
        }
    }
}