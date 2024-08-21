#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int fibonacci_search(vector<int> vec, int key)
{
    sort(vec.begin(), vec.end()); // 先对待查找的数组进行排序, 因为斐波那契查找的前提是有序表
    int n = vec.size();           // 数组大小
    int left = 0, right = n - 1;  // 初始查找的范围
    int mid, i = 0, idx = -1;     // mid为中间点, i为斐波那契数列的索引, idx为结果的索引

    // 生成斐波那契数列, 寻找大于数组长度的最小斐波那契数
    int fib[50]; // 斐波那契数列, 长度为50
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < 50; i++)
    {
        fib[i] = fib[i - 1] + fib[i - 2]; // 生成斐波那契数列
        if (fib[i] > right)               // 找到大于待查找数组长度的斐波那契数
        {
            break;
        }
    }

    // 扩展待查找的数组, 使其长度为刚好大于等于斐波那契数fib[i]
    int *tmp = new int[fib[i] + 1];
    copy(vec.begin(), vec.end(), tmp);       // 将原数组复制到扩展数组
    fill(tmp + n, tmp + fib[i], vec[n - 1]); // 用最后一个元素填充拓展部分
    /*对于上面两行, 一个非常朴素的实现
    for (int j = 0; j < n; j++)
    {

    } for (int j = 0; j < n; j++)
    {
        temp[j] = vec[j];  // 将原数组元素复制到扩展数组
    }
    for (int j = n; j < F[i]; j++)
    {
        temp[j] = vec[n - 1];  // 用最后一个元素填充扩展部分
    }
    */

    // 斐波那契查找实现
    while (left <= right)
    {
        mid = left + fib[i - 1] - 1; // 计算分界线

        if (tmp[mid] > key)
        {
            right = mid - 1; // 目标元素在左半部分
            i -= 2;          // 调整斐波那契数列索引
        }
        else if (tmp[mid] < key)
        {
            left = mid + 1; // 目标元素在右半部分
            i -= 1;         // 调整斐波那契数列索引
        }
        else
        {
            if (mid < n) // 找到目标元素并且确定在原数组范围内(不是拓展出来的)
            {
                idx = mid;
                break;
            }
            else
            {
                right = mid - 1; // 否则继续在左半部分查找
                i -= 2;
            }
        }

        // 检查最后一个可能的位置
        if (idx == -1 && tmp[right] == key)
        {
            idx = right;
        }

        // 如果结果超出原数组, 说明未找到目标
        if (idx >= n)
        {
            idx = -1;
        }

        delete[] tmp; // 释放拓展数组
        tmp = nullptr;
        return idx; // 返回目标元素的索引
    }
}
