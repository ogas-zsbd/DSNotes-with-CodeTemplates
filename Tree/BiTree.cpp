#include <iostream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

// 二叉树结点
class BiTreeNode
{
public:
    char data;              // 结点存储的数据
    BiTreeNode *LeftChild;  // 左子树指针
    BiTreeNode *RightChild; // 右子树指针

    // 构造函数
    BiTreeNode() : LeftChild(nullptr), RightChild(nullptr) {}
};

// 二叉树类
class BiTree
{
private:
    BiTreeNode *root; // 根节点指针
    int pos;
    string strTree;

    BiTreeNode *CreateBiTree();
    void preOrder(BiTreeNode *t);
    void inOrder(BiTreeNode *t);
    void postOrder(BiTreeNode *t);

public:
    BiTree();
    void CreateTree(string TreeArray); // 利用前序遍历结果创建树
    void preOrder();                   // 前序遍历
    void inOrder();                    // 中序遍历
    void postOrder();                  // 后序遍历
};
//----------------
// 实现前面声明的函数

BiTree::BiTree()
{
    pos = 0;
    strTree = "";
}

// 定义先序遍历函数
void BiTree::preOrder() // 在public中, 提供公共接口, 在公共接口内调用私有的preorder
{
    preOrder(root); // 从root开始遍历
}
void BiTree::preOrder(BiTreeNode *t)
{
    if (t != nullptr)
    {
        cout << t->data << " ";  // 输出这个结点存储的数据
        preOrder(t->LeftChild);  // 树的精髓在于**递归**
        preOrder(t->RightChild); // 一直沿着左边走, 直到这个结点的左边走完了才开始走右边, 但是走了右边还是沿着左边走
    }
    else
        return;
}

// 定义中序遍历函数
void BiTree::inOrder() // 在public中, 提供公共接口, 在公共接口内调用私有的inOrder
{
    inOrder(root);
}
void BiTree::inOrder(BiTreeNode *t)
{
    if (t != nullptr)
    {
        inOrder(t->LeftChild);
        cout << t->data; // 与前序遍历的区别
        inOrder(t->RightChild);
    }
    else
        return;
}

// 定义序遍历函数
void BiTree::postOrder() // 在public中, 提供公共接口, 在公共接口内调用私有的postOrder
{
    postOrder(root);
}
void BiTree::postOrder(BiTreeNode *t)
{
    if (t != nullptr)
    {
        postOrder(t->LeftChild);
        postOrder(t->RightChild);
        cout << t->data << " "; // 与前序遍历的区别
    }
    else
        return;
}

// 构造二叉树, 利用先序遍历结构来构造
void BiTree::CreateTree(string TreeArray) // 共有函数, 对外接口
{
    pos = 0;
    strTree.assign(TreeArray);
    root = CreateBiTree();
}
// 递归建树, 私有函数, 类内实现
BiTreeNode *BiTree::CreateBiTree()
{
    BiTreeNode *t;
    char c;
    c = strTree[pos++];
    if (c == '#')
        t = nullptr;
    else
    {
        t = new BiTreeNode();
        t->data = c;                    // 生成根节点
        t->LeftChild = CreateBiTree();  // 构造该节点的右子树
        t->RightChild = CreateBiTree(); // 构造该节点的左子树
    }
    return t;
}