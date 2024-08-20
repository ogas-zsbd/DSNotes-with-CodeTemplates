#include <iostream>

using namespace std;

bool check(int x) { /* ... */ } // 检查 x 是否满足某种性质

// 区间[l, r]被划分成 [l, mid] 和 [mid + 1, r] 时使用
int binary_search_1(int l, int r)
{
    while (l < r) // 直到缩小到l == r
    {
        int mid = l + r >> 1; // **两种二分模板的区别**
        // tip: a + b >> 1 等效于 (a + b) / 2
        if (check(mid))
            r = mid;
        else
            l = mid + 1; // **两种二分模板的区别**
    }
    return l; // 因为最后l == r, 所以return二者中其一都没问题
}

// 区间[l, r]被划分成[l, mid - 1] 和[mid, r] 时使用
int binary_search_2(int l, int r)
{
    while (l < r)
    {
        int mid = l + r + 1 >> 1; // **两种二分模板的区别**
        if (check(mid))
            l = mid;
        else
            r = mid - 1; // **两种二分模板的区别**
    }
    return l;
}