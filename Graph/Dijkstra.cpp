#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 510; // 本题中点的个数范围 <= 500
int g[N][N];       // 稠密图用邻接矩阵存储比较好, g[a][b]存储的是a到b的距离
int dist[N];       // 存储i结点到源点的距离
bool st[N];        // 用于标记到i节点的最短路径是否已经确定, 如果已经确定st[i] == true
int n, m;          // n为点的个数, m为边的个数

int dijkstra()
{
    memset(dist, 0x3f, sizeof(dist)); // 将源点到每个点之间的距离初始化为无穷大
    dist[1] = 0;                      // 源点到自己的距离为0

    // 每一次循环都能确定一个点的最短距离
    for (int i = 0; i < n; i++) // n次迭代，每次寻找不在st中距离最近的点t
    {
        int t = -1; // 便于更新第一个点, 不用特判
        // 第一轮循环, 寻找与源点最近的点(且该点是没有找到最短路径的点)
        for (int j = 1; j <= n; j++)
        {
            // 如果j结点还没有找到最短路径 且 (t是源点 或 j的路径比t小)
            if (!st[j] && (t == -1 || dist[j] < dist[t]))
            {
                t = j; // 更新当前最小的dist[t]
            }
        }
        st[t] = true; // 标记t的最短路已经找到了

        // 第二轮循环, 更新与t邻接的点的最短路
        for (int j = 1; j <= n; j++)
        {
            dist[j] = min(dist[j], dist[t] + g[t][j]);
            // dist[j]是j点到源点的最短路径, 就是要取 从源点直接到j 与 从源点到离源点最近的点t加上t到j的距离 这两者的最小值, 即为j到源点的最短路径
            // 所谓dijstra算法使用了**贪心**的思想, 就贪心在这里
        }

        if (dist[n] == 0x3f3f3f3f)
            return -1; // 如果最后一个顶点n到起点的距离为初始值0x3f3f3f3f, 说明从源点走不到n点
        else
            return dist[n]; // 返回1号结点到n号结点的最短距离
    }
}

int main()
{
    cin >> n >> m;
    memset(g, 0x3f, sizeof(g)); // 两点间的距离初始化, 由于求的是最小值, 所以初始化为无穷大

    // 输入邻接点之间的距离
    while (m--)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        g[x][y] = min(g[x][y], z); // 题干中提到存在重边, 重边中取最小值
    }

    cout << dijkstra() << endl;

    return 0;
}