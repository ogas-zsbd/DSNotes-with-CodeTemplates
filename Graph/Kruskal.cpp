#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100010;
int p[N]; // 保存并查集

struct E
{
    int a;
    int b;
    int w;
    // 重载小于号, 通过边进行排序
    bool operator<(const E &r)
    {
        return this->w < r.w;
    }
} edge[N * 2];

int res = 0; // 记录最小生成树的权重

int n, m; // n个顶点, m条边
int cnt = 0;
// 并查集找祖宗
int find(int a)
{
    if (p[a] != a)
        p[a] = find(a); // 祖宗的祖宗是自己, p[a]记录a结点的父节点, 从a结点开始一直网上找, 直到找到祖宗结点为止
    return p[a];
}

void kruskal()
{
    // 依次尝试加入每条边
    for (int i = 1; i <= m; i++)
    {
        // 我们是通过这个来判断是否存在回路的--并查集
        int pa = find(edge[i].a); // a点所在集合
        int pb = find(edge[i].b); // b点所在集合
        if (pa != pb)             // 如果a与b不在一个集合中
        {
            res += edge[i].w; // ab间的边放入生成树中
            p[pa] = pb;       // 将ab放入同一个集合中
            cnt++;            // 生成树中的边++
        }
    }
}

int main()
{
    cin >> n >> m; // 输入点和边的个数

    // 初始化并查集, 最初每个点自己就是一个不同的集合
    for (int i = 1; i <= n; i++)
    {
        p[i] = i;
    }

    // 读入每条边
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        edge[i] = {a, b, c};
    }

    // 将edge按边长排序, 从小到大
    sort(edge + 1, edge + m + 1);

    // kruskal算法建立最小生成树
    kruskal();

    // 如果保留的边数小于n-1, 则这个图不能生成一棵最小生成树
    if (cnt < n - 1)
    {
        cout << "impossible" << endl;
        return 0;
    }

    cout << res; // 输出最小生成树的权重和

    return 0;
}