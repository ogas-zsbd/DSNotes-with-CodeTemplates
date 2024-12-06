/*
 * @Author: OGAS 2970143166@qq.com
 * @Date: 2024-11-08 22:23:29
 * @LastEditors: OGAS 2970143166@qq.com
 * @LastEditTime: 2024-11-08 22:39:06
 * @FilePath: \Lab4\src\SeqBinaryTree.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

template <class T>
class SeqBinaryTree
{
public:
    vector<T> tree; // 存储二叉树的树, 为了符合公式, 索引从1开始

    // 构造二叉树
    void createBinaryTree(int n)
    {
        tree.resize(n + 1); // 树的大小为n, 但是下标从1开始所以n+1
        cout << "请输入" << n << "个结点的值, 顺序按照满二叉树的顺序: " << endl;
        for (int i = 1; i <= n; i++)
            cin >> tree[i];
    }

    // 先序遍历
    void preOrder(int index)
    {
        if (index > tree.size())
            return;                 // 越界就是遍历完了
        cout << tree[index] << " "; // 输出当前结点
        preOrder(index * 2);        // 遍历左子树 (左子树结点下标为index * 2)
        preOrder(index * 2 + 1);    // 遍历右子树 (右子树结点下标为index * 2 + 1)
    }
};

// 测试
int main()
{
    // 设置终端输出的字符集为UTF-8
    SetConsoleOutputCP(CP_UTF8);
    // 设置终端输入的字符集为UTF-8
    SetConsoleCP(CP_UTF8);

    SeqBinaryTree<int> tree;
    tree.createBinaryTree(7); // 创建一个有七个结点的二叉树
    tree.preOrder(1);         // 从一号开始遍历

    system("pause");
    return 0;
}