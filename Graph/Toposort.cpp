#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100010;
int e[N], ne[N], idx; // 邻接表存储图
int h[N];
int q[N], hh = 0, tt = -1; // 用队列保存入度为0的点, 也就是能够输出的点
int n, m;                  // n为顶点个数, m为边的数目
int d[N];                  // 保存各个顶点的入度

// 把保存边的操作封装成一个函数
// 相当于单链表的头插法?
void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
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
            int b = e[i];  // a有一条边指向b
            d[b]--;        // 删除从a到b的边之后, b的入度--
            if (d[b] == 0) // 如果b的入度减为零
            {
                q[++tt] = b; // 入度为0的点加入队列
            }
        }
    }

    // 如果队列中的点的个数与图中点的个数相同, 则是这个AOV网可以进行拓扑排序
    if (tt == n - 1)
    {
        for (int i = 0; i < n; i++) // 队列中保存了所有入度为0的点, 依次输出
        {
            cout << q[i] << " ";
        }
    }
    else // 如果队列中点的个数与图中点的个数不相同, 则该AOV网不能进行拓扑排序
    {
        cout << -1; // 输出-1, 代表不能进行拓扑排序
    }
}

int main()
{
    cin >> n >> m;            // 保存点的个数和边的个数
    memset(h, -1, sizeof(h)); // 初始化邻接矩阵
    while (m--)               // 依次读入m条边
    {
        int a, b;
        scanf("%d%d", &a, &b);
        d[b]++;    // 存入的是a到b的边, 所以b的入度++
        add(a, b); // 构建邻接表
    }

    toposort(); // 进行拓扑排序

    return 0;
}
