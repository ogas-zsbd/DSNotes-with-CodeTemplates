#include <iostream>

using namespace std;

const int N = 100010;
const int M = 1000010;

int n, m;
int ne[N];
char s[M], p[N];

int main()
{
    cin >> n >> p + 1 >> m >> s + 1; // 字符数组下标从1开始, 而不是从0 开始!!!

    // 获取next数组
    // i从1开始时因为下标从1开始, ne[0]没有意义, 而ne[1]只有一个字母, 所以ne[1] == 0
    for (int i = 2, j = 0; i <= n; i++)
    {
        while (j != 0 && p[i] != p[j + 1])
            j = ne[j];
        if (p[i] == p[j + 1])
            j++;
        ne[i] = j;
    }

    // 进行KMP匹配
    for (int i = 1, j = 0; i <= m; i++)
    {
        while (j != 0 && s[i] != p[j + 1])
            j = ne[j];
        if (s[i] == p[j + 1])
            j++;
        if (j == n)
        {
            printf("%d", i - n);
            j = ne[j];
        }
    }

    return 0;
}