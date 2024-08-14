#include <iostream>

using namespace std;

const int N = 210, INF = 1e9;
int n, m, Q; // n是点的个数, m是边的个数, Q是询问最短路径的次数
int d[N][N]; // 存储i到j的距离, 本来应该是三维数组, 根据动态规划中的技巧优化到二维

void floyd()
{
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                // 动态规划的思想
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}

int main()
{
    cin >> n >> m >> Q;

    // 初始化d数组
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                d[i][j] = 0;
            else
                d[i][j] = INF;
        }
    }

    // 存入邻接点之间的距离
    while (m--)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        d[a][b] = min(d[a][b], c); // 可能有重边, 保留最小的一条边
    }

    floyd();

    while (Q--)
    {
        int a, b;
        scanf("%d%d", &a, &b);

        int t = d[a][b];
        if (t > INF / 2)
            cout << "impossible" << endl; // INF / 2 是因为有负权边的存在, 如果走不通也有可能走了点负权边而减小
        else
            cout << t << endl;
    }

    return 0;
}