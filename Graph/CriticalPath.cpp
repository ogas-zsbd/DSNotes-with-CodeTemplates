#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 100010;
int e[N], ne[N], w[N], idx;     // 邻接表存储图，w[N]表示边的权重（持续时间）
int h[N], d[N], etv[N], ltv[N]; // etv[N]表示顶点的最早发生时间, ltv[N]表示顶点的最晚发生时间
int q[N], hh = 0, tt = -1;
int n, m;                              // n为顶点个数, m为边的数目
vector<pair<int, int>> critical_edges; // 保存关键路径上的边

// 邻接表中添加边的函数, 相较于toposort中添加了权重w
void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void toposort()
{
    // 初始化队列
    for (int i = 1; i <= n; i++) // 遍历一遍每个点的入度
    {
        if (d[i] == 0) // 如果入度为零, 进入待输出的队列
        {
            q[++tt] = i;
        }
    }

    // 拓扑排序的核心
    //  循环处理队列中的点
    while (tt >= hh)
    {
        int a = q[hh++];                       // 取出对头元素
        for (int i = h[a]; i != -1; i = ne[i]) // 循环删除a点发出的边
        {
            int b = e[i];                        // a有一条边指向b
            d[b]--;                              // 删除从a到b的边之后, b的入度--
            etv[b] = max(etv[b], etv[a] + w[i]); // 计算顶点b的最早发生时间
            if (d[b] == 0)                       // 如果b的入度减为零
            {
                q[++tt] = b; // 入度为0的点加入队列
            }
        }
    }
}

int find_critical_path()
{
    // 初始化ltv数组, 因为后面是min, 所以取0x3f3f3f3f
    memset(ltv, 0x3f, sizeof(ltv));
    ltv[q[tt]] = etv[q[tt]]; // 设置终点的ltv等于etv, 项目的最后一个事件的最晚发生时间就是它的最早发生时间。

    // 逆向遍历之前拓扑排序出的队列, 计算ltv数组
    for (int i = tt; i >= 0; i--)
    {
        int a = q[i];
        for (int j = h[a]; j != -1; j = ne[j])
        {
            int b = e[j];
            ltv[a] = min(ltv[a], ltv[b] - w[j]); // 计算顶点a的最晚发生时间
            // ltv[b] - w[j] 是从顶点 b 的最晚开始时间减去从 a 到 b 的活动持续时间 w[j]，即活动 a -> b 开始的最晚时间。
        }
    }

    int critical_path_weight = 0; // 关键路径的权值

    // 遍历所有边, 找出关键活动, 加入到关键路径中
    for (int i = 1; i <= n; i++)
    {
        for (int j = h[i]; j != -1; j = ne[j])
        {
            int b = e[j];
            int ete = etv[i];        // 活动i-b的最早开始时间，它就是顶点 i 的最早发生时间 ETV。
            int lte = ltv[b] - w[j]; // 活动i-b的最晚开始时间, 即目标顶点 b 的最晚发生时间减去活动的持续时间 w[j]。

            if (ete == lte) // 如果ete == lte, 说明这是关键路径上的关键活动
            {
                critical_edges.push_back({i, b});
                critical_path_weight += w[j]; // 累加权值
            }
        }
    }

    // 如果队列中点的个数与图中点的个数相同, 则可以找到关键路径
    if (tt == n - 1)
    {
        return critical_path_weight; // 返回关键路径的总权值
    }
    else
        return -1; // 返回-1表示图中有环, 无法进行拓扑排序, 也就无法找到关键路径
}

int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof(h)); // 初始化邻接表
    // 读入边
    while (m--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        d[b]++;       // 存入的是a到b的边, 所以b的入度++
        add(a, b, c); // 构建邻接表
    }

    // 进行拓扑排序
    toposort();

    // 得到关键路径及其权值
    int critical_path_weight = find_critical_path();
    if (critical_path_weight == -1)
    {
        cout << "No critical path found, the graph may have a cycle." << endl;
    }
    else
    {
        cout << "Critical path edges: " << endl;
        for (auto edge : critical_edges)
        {
            cout << edge.first << "->" << edge.second << endl;
        }
        cout << "Total weight of critical path: " << critical_path_weight << endl;

        return 0;
    }
}