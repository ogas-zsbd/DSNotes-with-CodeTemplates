#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 510;
int g[N][N]; // 存储图
int dt[N];   // 存储各个结点好生成树的距离
int st[N];   // 记录结点是否被加入生成树中
int pre[N];  // 结点的前驱结点
int n, m;    // n个结点, m条边

void prim()
{
    memset(dt, 0x3f, sizeof(dt)); // 初始化距离数组为一个很大的数(0x3f3f3f3f 在 10亿左右)
    int res = 0;
    dt[1] = 0;                  // 从1号结点开始生成
    for (int i = 0; i < n; i++) // 每一次循环都选择一个点加入生成树, 一共n个点
    {
        int t = -1;

        for (int j = 1; j <= n; j++) // 对每个结点进行判断
        {
            if (!st[j] && (t == -1 || dt[j] < dt[t])) // 如果j这个点没有在生成树中, 且到树的距离最短
            {
                t = j; // 将该点加入树中
            }
        }

        // 判断孤立的点 : 如果存在孤立的点, 则不能生成整个图的最小生成树
        if (dt[t] == 0x3f3f3f3f)
        {
            cout << "impossible" << endl;
            return;
        }

        st[t] = 1;                   // 标记该点已经加入树中
        res += dt[t];                // 统计最后最小生成树的权值和
        for (int i = 1; i <= n; i++) // 更新生成树外的点到生成树的距离
        {
            if (dt[i] > g[t][t] && !st[i]) // 从t到i结点的距离小于原来的距离 且i结点不在树中, 则更新
            {
                dt[i] = g[t][i]; // 更新距离
                pre[i] = t;      // 从t到i的距离更短, 所以i的前驱变成t
            }
        }
    }

    cout << res << endl; // 得到生成树的最小权值
}

void getPath() // 输出最小生成树中的各个边
{
    for (int i = n; i > 1; i--) // n个结点, 所以有n-1条边
    {
        cout << i << "-" << pre[i] << endl; // i是结点编号, pre[i]是i结点的前驱结点, 两点链接构成一条边
    }
}

int main()
{
    memset(g, 0x3f, sizeof(g)); // 各个结点之间初始化为很大的数
    cin >> n >> m;              // 输入结点数和边数
    while (m--)
    {
        int a, b, w;
        cin >> a >> b >> w;                  // 输入边的两个顶点和权重
        g[a][b] = g[b][a] = min(g[a][b], w); // 存储权重      (无向图的存储方式: a->b == b->a 的权重)
    }

    prim();    // 求最小生成树
    getPath(); // 输出最小生成树的路径

    return 0;
}