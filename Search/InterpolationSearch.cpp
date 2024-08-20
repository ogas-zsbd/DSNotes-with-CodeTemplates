#include <iostream>

using namespace std;

int interpolation_search(int *a, int n, int key)
{
    int left, right, mid;
    left = 1;             // 定义left下标为首位
    right = n;            // 定义right下标为末尾
    while (left <= right) // 一直循环, 相等则为key的下标
    {
        mid = left + (right - left) * (key - a[left]) / (a[right] - a[left]); // 公式优化的部分
        if (key < a[mid])                                                     // 如果查找值比mid小
        {
            right = mid - 1; // right下标调整到mid前一位
        }
        else if (key > a[mid]) // 如果查找值比mid大
        {
            left = mid + 1; // left下标调整到mid后一位
        }
        else
            return mid; // 相等则为找到了key, 下标为mid
    }

    return 0;
}