#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
#include <cfloat>
using namespace std;

// 克鲁斯卡尔算法中需要用到
template <typename VertexType, typename WeightType>
struct Edge
{
    int start, end;    // 顶点和终点的索引
    WeightType weight; // 边的权值

    Edge(int s, int e, WeightType w) : start(s), end(e), weight(w) {}

    // 在克鲁斯卡尔算法中需要对边的权值进行排序, 重载小于号方便排序
    bool operator<(const Edge &e) const
    {
        return weight < e.weight;
    }
};

// 并查集
class UnionFind
{
private:
    vector<int> parent; // 存放每个节点的父节点

public:
    // 初始化并查集
    UnionFind(int n)
    {
        parent.resize(n);
        for (int i = 0; i < n; i++)
            parent[i] = i; // 先初始化为一个个孤立的点, 每个点的祖先都是自己
    }

    // 查找x的祖先
    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // 一直往上找祖先 直到找到根节点
        return parent[x];                // 找到根节点就是祖先
    }

    // 合并两个节点
    void unite(int x, int y)
    {
        parent[find(x)] = find(y); // 将y的祖先赋给x的祖先, 也就是现在这两个元素的祖先都是y的祖先
    }

    // 判断两个节点是否在同一个集合
    bool isSame(int x, int y)
    {
        return find(x) == find(y);
    }
};

// 邻接表结构实现图
template <typename VertexType, typename WeightType>
class AMGraph
{
public:
    AMGraph(VertexType a[], int n, int e, bool isDirected = false); // 构造函数
    ~AMGraph() {}
    void DFS(int v);
    void BFS(int v);
    void visit(int v);                                              // 访问顶点
    void printGraph();                                              // 打印图的信息
    void resetVisited();                                            // 重置访问信息
    void addEdge(int i, int j, WeightType weight, bool isDirected); // 添加边

    // 最小生成树
    void Prim(int start);
    void Kruskal();

    // 最短路径
    void Dijkstra(int start);
    void Floyd();

private:
    vector<VertexType> vertex;          // 存放顶点
    vector<vector<bool>> arc;           // 存放邻接矩阵的二位vector
    vector<vector<WeightType>> weights; // 存放边权的二维vector
    vector<bool> visited;               // 存放是否已经访问过
    int vertexNum, arcNum;              // 顶点个数和边数
    bool directed;                      // 记录边是有向图 or 无向图

    // 辅助函数
    int getMinVertex(vector<WeightType> &dist, vector<bool> &used); // 获取dist中最小值对应的顶点
    void printPath(vector<int> &prev, int start, int end);
    void printFloydPath(vector<vector<int>> &nxt, int i, int j);

    // 获取无穷值
    WeightType getInfinity()
    {
        // 新用法
        if (std::is_same<WeightType, int>::value)
            return INT_MAX;
        if (std::is_same<WeightType, double>::value)
            return DBL_MAX;
        if (std::is_same<WeightType, float>::value)
            return FLT_MAX;
        return std::numeric_limits<WeightType>::max();
    }
};

// 初始化图, a[]为顶点数组, n为顶点个数, e为边数, isDirected为是否为有向图, 默认是无向图
template <typename VertexType, typename WeightType>
AMGraph<VertexType, WeightType>::AMGraph(VertexType a[], int n, int e, bool isDirected)
{
    vertexNum = n;         // n个顶点
    arcNum = e;            // e条边
    directed = isDirected; // 记录图的类型, true为有向, 反之无向

    // 初始化顶点数组
    vertex.resize(vertexNum);
    for (int i = 0; i < vertexNum; i++)
    {
        vertex[i] = a[i];
    }

    // 初始化邻接矩阵和边权矩阵
    arc.resize(vertexNum, vector<bool>(vertexNum, 0));           // 开一维vector作为行, 再在vector中的每个元素分别开vector, 里面初始化为0, 就等效于开了一个二维数组, 元素全为0
    weights.resize(vertexNum, vector<WeightType>(vertexNum, 0)); // 同上

    // 初始化访问数组
    visited.resize(vertexNum, false); // 初始标为false表示未被访问
}

template <typename VertexType, typename WeightType>
void AMGraph<VertexType, WeightType>::addEdge(int i, int j, WeightType weight, bool isDirected)
{
    // 确保加边的两个顶点合法
    if (i >= 0 && i < vertexNum && j >= 0 && j < vertexNum)
    {
        arc[i][j] = 1; // 记录i->j是有边的
        weights[i][j] = weight;

        if (!isDirected) // 如果是无向图, 则对称位置也要记录
        {
            arc[j][i] = 1;
            weights[j][i] = weight;
        }
    }
}

template <typename VertexType, typename WeightType>
void AMGraph<VertexType, WeightType>::resetVisited()
{
    fill(visited.begin(), visited.end(), false); // 重置访问数组
}

template <typename VertexType, typename WeightType>
void AMGraph<VertexType, WeightType>::printGraph()
{
    cout << "\n邻接矩阵: " << endl;
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            cout << arc[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\n权重矩阵: " << endl;
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            cout << weights[i][j] << " ";
        }
        cout << endl;
    }
}

template <typename VertexType, typename WeightType>
void AMGraph<VertexType, WeightType>::visit(int v)
{
    cout << vertex[v] << " ";
    visited[v] = true;
}

template <typename VertexType, typename WeightType>
void AMGraph<VertexType, WeightType>::DFS(int v)
{
    visit(v); // 访问顶点

    for (int j = 0; j < vertexNum; j++)
    {
        if (arc[v][j] == 1 && !visited[j]) // 如果v->j有边且j未被访问过
        {
            DFS(j); // 递归DFSj顶点
        }
    }
}

template <typename VertexType, typename WeightType>
void AMGraph<VertexType, WeightType>::BFS(int v)
{
    queue<int> q; // 用于存储待访问顶点的队列
    resetVisited();

    visit(v);
    q.push(v); // 将起始顶点入队

    while (!q.empty())
    {
        v = q.front();
        q.pop();

        for (int j = 0; j < vertexNum; j++)
        {
            if (arc[v][j] == 1 && !visited[j]) // 将与v相接且还没访问过的加入队列
            {
                visit(j);
                q.push(j);
            }
        }
    }
}

template <typename VertexType, typename WeightType>
int AMGraph<VertexType, WeightType>::getMinVertex(vector<WeightType> &dist, vector<bool> &used)
{
    WeightType minDist = getInfinity(); // 初始化到该点的最近的邻接点的距离为无穷大
    int minVertex = -1;                 // 初始化该点的邻接点为-1

    for (int v = 0; v < vertexNum; v++)
    {
        if (!used[v] && dist[v] < minDist)
        {
            minDist = dist[v];
            minVertex = v;
        }
    }

    return minVertex;
}

template <typename VertexType, typename WeightType>
void AMGraph<VertexType, WeightType>::printPath(vector<int> &prev, int start, int end)
{
    if (start == end)
    {
        cout << vertex[start] << " ";
        return;
    }

    if (prev[end] == -1)
    {
        cout << "没有路径从" << vertex[start] << "到" << vertex[end] << "的路径" << endl;
        return;
    }

    vector<int> path;
    for (int v = end; v != -1; v = prev[v])
        path.push_back(v); // 从终点开始向前遍历, 找到路径上的所有顶点

    // 逆序输出, 就是从源头到这个顶点的路径
    for (int i = path.size() - 1; i >= 0; i--)
    {
        cout << vertex[path[i]];
        if (i > 0)
            cout << "->";
    }
}

template <typename VertexType, typename WeightType>
void AMGraph<VertexType, WeightType>::printFloydPath(vector<vector<int>> &nxt, int i, int j)
{
    if (nxt[i][j] == -1)
    {
        cout << " -> " << vertex[j];
        return;
    }

    int k = nxt[i][j];
    cout << " -> " << vertex[k];
    if (k != j)
    {
        printFloydPath(nxt, k, j); // 递归输出从k到j的路径
    }
}

template <typename VertexType, typename WeightType>
void AMGraph<VertexType, WeightType>::Prim(int start)
{
    vector<bool> used(vertexNum, false);               // 记录顶点是否被访问过
    vector<WeightType> dist(vertexNum, getInfinity()); // 记录顶点到生成树的最小距离
    vector<int> parent(vertexNum, -1);                 // 记录顶点在生成树中的父节点

    WeightType totalWeight = WeightType(); // 最小生成树的总权重初始化为0
    dist[start] = WeightType();            // 起点到自身的距离为0

    // 不断地找距离当前已经加入最小生成树的最近的点, 找完之后要更新距离最小生成树这个点的集合最近的值
    for (int i = 0; i < vertexNum; i++)
    {
        int u = getMinVertex(dist, used); // 找到离生成树最近的顶点
        if (u == -1)
            break; // 如果找不到, 说明已经全部访问过, 退出循环

        used[u] = true;         // 标记该顶点为已访问
        totalWeight += dist[u]; // 将该顶点加入生成树, 更新总权重

        // 新顶点加入生成树之后, 更新每个顶点到生成树这块的最小距离
        for (int v = 0; v < vertexNum; v++)
        {
            if (!used[v] && arc[u][v] && weights[u][v] < dist[v])
            {
                dist[v] = weights[u][v]; // 更新顶点到生成树的最小距离
                parent[v] = u;           // 更新顶点的父节点
            }
        }
    }

    // 打印Prim生成的最小生成树
    cout << "\nPrim算法生成的最小生成树: " << endl;
    for (int i = 0; i < vertexNum; i++)
    {
        if (parent[i] != -1)
        {
            cout << vertex[parent[i]] << " -> " << vertex[i] << " : " << weights[parent[i]][i] << endl;
        }
    }
    cout << "最小生成树的总权重: " << totalWeight << endl;
}

template <typename VertexType, typename WeightType>
void AMGraph<VertexType, WeightType>::Kruskal()
{
    vector<Edge<VertexType, WeightType>> edges;
    WeightType totalWeight = WeightType();

    // 先把所有边收集起来发放到edges中去
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = i + 1; j < vertexNum; j++)
        {
            if (arc[i][j])
                edges.push_back(Edge<VertexType, WeightType>(i, j, weights[i][j]));
        }
    }

    // 按照边的权重从小到大排序
    sort(edges.begin(), edges.end());

    UnionFind uf(vertexNum);                  // 并查集
    vector<Edge<VertexType, WeightType>> mst; // 最小生成树

    // 从小到大遍历每一条边, 先检查这条边是否会与已经加入最小生成树的顶点形成环, 如果不会就可以加入最小生成树
    for (auto &e : edges)
    {
        if (!uf.isSame(e.start, e.end)) // 如果两个顶点不在同一个集合中(祖先不是同一个), 说明这条边不会形成环
        {
            // 不构成环就可以加进来
            uf.unite(e.start, e.end);
            mst.push_back(e);
            totalWeight += e.weight;
        }
    }

    // 打印Kruskal得出的最小生成树
    cout << "\nKruskal算法生成的最小生成树:" << endl;
    for (const auto &e : mst)
    {
        cout << vertex[e.start] << " -> " << vertex[e.end] << ": " << e.weight << endl;
    }
    cout << "最小生成树的总权重: " << totalWeight << endl;
}

template <typename VertexType, typename WeightType>
void AMGraph<VertexType, WeightType>::Dijkstra(int start)
{
    vector<bool> used(vertexNum, false);               // 记录顶点是否被访问过
    vector<WeightType> dist(vertexNum, getInfinity()); // 记录顶点到起点的最短距离
    vector<int> prev(vertexNum, -1);                   // 记录最短路的前驱顶点
    dist[start] = WeightType();                        // 起点到自身的距离为0

    for (int i = 0; i < vertexNum; i++)
    {
        int u = getMinVertex(dist, used); // 找到离生成树最近的顶点
        if (u == -1)
            break; // 如果找不到, 说明已经全部访问过, 退出循环

        used[u] = true; // 标记该顶点为已访问

        // 更新与u相邻的顶点到起点的最短距离
        for (int v = 0; v < vertexNum; v++)
        {
            if (!used[v] && arc[u][v] && dist[u] + weights[u][v] < dist[v]) // 如果v没有被访问过, 并且u到v的边存在, 并且u到v的路径比当前v到起点的最短路径更短, 就更新
            {
                WeightType newDist = dist[u] + weights[u][v];
                if (newDist < dist[v])
                {
                    dist[v] = newDist; // 更新v到起点的最短距离
                    prev[v] = u;       // 更新v的前驱顶点为u
                }
            }
        }
    }

    // 打印Dijkstra算法得出的最短路径
    cout << "\nDijkstra算法计算从" << vertex[start] << "到其他顶点的最短路径: " << endl;
    for (int i = 0; i < vertexNum; i++)
    {
        if (i != start && dist[i] != getInfinity())
        {
            cout << vertex[start] << "到" << vertex[i] << "的最短距离为: " << dist[i] << ", 路径为: ";
            printPath(prev, start, i);
            cout << endl;
        }
    }
}

template <typename VertexType, typename WeightType>
void AMGraph<VertexType, WeightType>::Floyd()
{
    vector<vector<WeightType>> dist = weights;
    vector<vector<int>> nxt(vertexNum, vector<int>(vertexNum, -1)); // nxt[i][j]表示从i到j的最短路径中, j的前驱结点

    // 初始化
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            if (arc[i][j])
                nxt[i][j] = j; // 如果i和j之间有边, 就把j作为i到j的最短路径中的前驱结点

            if (i == j)
                dist[i][j] = WeightType(); // 自己到自己的距离为0

            if (!arc[i][j] && i != j)
                dist[i][j] = getInfinity(); // 如果i和j之间没有边, 就把i到j的距离设为无穷大
        }
    }

    // Floyd算法核心部分, 三重for
    for (int k = 0; k < vertexNum; k++)
    {
        for (int i = 0; i < vertexNum; i++)
        {
            for (int j = 0; j < vertexNum; j++)
            {
                if (dist[i][k] != getInfinity() && dist[k][j] != getInfinity()) // 如果i到k有路径, 并且k到j有路径
                {
                    WeightType newDist = dist[i][k] + dist[k][j]; // 计算i到j通过k的长度
                    if (newDist < dist[i][j])                     // 如果i到j通过k的路径更短
                    {
                        dist[i][j] = newDist;  // 更新i到j的最短距离
                        nxt[i][j] = nxt[i][k]; // 更新i到j的最短路径中的前驱结点
                    }
                }
            }
        }
    }

    cout << "\nFloyd算法计算所有顶点对之间的最短路径: " << endl;
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            if (i != j && dist[i][j] != getInfinity())
            {
                cout << vertex[i] << "到" << vertex[j] << "的最短距离为: " << dist[i][j] << ", 路径为: ";
                cout << vertex[i];
                printFloydPath(nxt, i, j);
                cout << endl;
            }
        }
    }
}
