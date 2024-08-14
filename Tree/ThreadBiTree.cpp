#include <iostream>

using namespace std;

// 线索二叉树结点类
template <typename T>
class ThreadNode
{
public:
    T data;                                // 结点数据
    ThreadNode<T> *leftChild, *rightChild; // 左/右子节点
    int ltag, rtag;                        // 左右子树标志位
    ThreadNode(const T item) : data(item), leftChild(nullptr), rightChild(nullptr), ltag(0), rtag(0) {}
};

// 线索二叉树类
template <typename T>
class ThreadBiTree
{
public:
    // 构造函数
    ThreadBiTree() : root(nullptr) {}
    ThreadBiTree(T value) : root(nullptr), RefValue(value) {}

    // 使用前序遍历创建二叉树(未线索化)
    void createTree();
    // 中序遍历对创建好的普通二叉树进行**中序线索化**
    void createInThread();
    // 中序线索化二叉树的中序遍历的算法
    void InOrder();
    // 中序线索化二叉树的前序遍历的算法
    void PreOrder();
    // 中序线索二叉树的后序遍历算法
    void PostOrder();

private:
    // 树的根节点
    ThreadNode<T> *root;
    T RefValue;

    // 使用前序遍历创建二叉树(未线索化)
    void createTree(ThreadNode<T> *&subTree);
    // 中序遍历对二叉树进行线索化
    void createInThread(ThreadNode<T> *current, ThreadNode<T> *&pre);
    // 寻找中序下的序列的第一个结点
    ThreadNode<T> *First(ThreadNode<T> *current);
    // 寻找中序下的序列的最后一个结点
    ThreadNode<T> *Last(ThreadNode<T> *current);
    // 寻找中序下的后继结点
    ThreadNode<T> *Next(ThreadNode<T> *current);
    // 寻找中序下的前驱结点
    ThreadNode<T> *Prior(ThreadNode<T> *current);
    // 在中序线索化二叉树中求父节点
    ThreadNode<T> *Parent(ThreadNode<T> *t);
    // 中序线索化二叉树的中序遍历的算法
    void InOrder(ThreadNode<T> *p);
    // 中序线索化二叉树的前序遍历的算法
    void PreOrder(ThreadNode<T> *p);
    // 中序线索二叉树的后序遍历算法
    void PostOrder(ThreadNode<T> *p);
};

//------------
// 实现public接口
template <typename T>
void ThreadBiTree<T>::createTree()
{
    createTree(root);
}

template <typename T>
void ThreadBiTree<T>::createInThread()
{
    ThreadNode<T> *pre = nullptr; // 第一个结点的左子树置为null
    if (root != nullptr)
    {
        createInThread(root, pre);
        // 处理中序遍历的最后一个结点, 最后一个结点的右子树置为空
        pre->rightChild = nullptr pre->rtag = 1;
    }
}

template <typename T>
void ThreadBiTree<T>::InOrder()
{
    InOrder(root);
}

template <typename T>
void ThreadBiTree<T>::PreOrder()
{
    PreOrder(root);
}

template <typename T>
void ThreadBiTree<T>::PostOrder()
{
    PostOrder(root);
}

//---------------------
// 实现函数
template <typename T>
void ThreadBiTree<T>::createTree(ThreadNode<T> *&subTree)
{
    T item;
    if (cin >> item)
    {
        if (item != RefValue)
        {
            subTree = new ThreadNode<T>(item); // 子树的根节点
            if (subTree == nullptr)
            {
                puts("空间分配错误");
                exit(1);
            }
            createTree(subTree->leftChild);  //**递归**创建左子树
            createTree(subTree->rightChild); //**递归**创建右子树
        }
        else
        {
            subTree = nullptr;
        }
    }
}

template <typename T>
void ThreadBiTree<T>::createInThread(ThreadNode<T> *current, ThreadNode<T> *&pre)
{
    if (current == nullptr)
        return;
    createInThread(current->leftChild, pre); // 递归左子树的线索化
    if (current->leftChild = nullptr)
    {
        current->leftChild = pre; // 如果结点左子树为空，则该结点的左孩子指向其前驱结点
        current->ltag = 1;        // 标记LeftChild指针指向了前序结点而非左子节点
    }
    if (pre != nullptr && pre->rightChild == nullptr) // 建立当前结点的后继结点
    {
        pre->rightChild = current;
        pre->rtag = 1;
    }
    pre = current;                            // 用前驱记住当前的结点
    createInThread(current->rightChild, pre); // 递归右子树的线索化
}

template <typename T>
ThreadNode<T> *ThreadBiTree<T>::First(ThreadNode<T> *current)
{
    ThreadNode<T> *p = current;
    while (p->ltag == 0)
    {
        p = p->leftChild;
    }
    return p;
}

template <typename T>
ThreadNode<T> *ThreadBiTree<T>::Next(ThreadNode<T> *current)
{
    ThreadNode<T> *p = current->rightChild;
    if (current->rtag == 0)
    {
        return First(p);
    }
    else
    {
        return p;
    }
}

template <typename T>
ThreadNode<T> *ThreadBiTree<T>::Last(ThreadNode<T> *current)
{
    ThreadNode<T> *p = current;
    while (p->rtag == 0)
    {
        p = p->rightChild;
    }
    return p;
}

template <typename T>
ThreadNode<T> *ThreadBiTree<T>::Last(ThreadNode<T> *current)
{
    ThreadNode<T> *p = current;
    while (p->rtag == 0)
    {
        p = p->rightChild;
    }
    return p;
}

template <typename T>
ThreadNode<T> *ThreadBiTree<T>::Prior(ThreadNode<T> *current)
{
    ThreadNode<T> *p = current->leftChild;
    if (current->rtag == 0)
    {
        return Last(p);
    }
    else
    {
        return p;
    }
}

template <typename T>
ThreadNode<T> *ThreadBiTree<T>::Parent(ThreadNode<T> *t)
{
    ThreadNode<T> *p;
    if (t == root)
        return nullptr; // 根节点无父节点
    for (p = t; p->ltag == 0; p = p->leftChild)
        ; // 求*t为根的中序下的第一个结点p

    // 1. 当p的左子树指向不为空
    if (p->leftChild != nullptr)
    { // 令p为p的左子树指向的结点, 如果此结点不为空 && 此结点的左右指针都不指向t, 将p的右子节点赋给p
        for (p = p->leftChild; p != nullptr && p->leftChild != t && p->rightChild != t; p = p->rightChild)
            ;
    }

    // 2. 上面的for循环循环完了, 由于是p == null终止了循环, 没有找到与t相等的结点, 就是一直找到了中序线索化的第一个结点
    if (p == nullptr || p->leftChild == nullptr)
    {
        // 找到*t为根的中序下的最后一个结点
        for (p = t; p->rtag == 0; p = p->rightChild)
            ;
        // 让p指向最后一个结点指向的结点, 从这个结点开始, 以此判断它的左右子节点是否与t相等
        for (p = p->rightChild; p != nullptr && p->leftChild != t && p->rightChild != t; p->leftChild)
            ;
    }

    return p;
}

template <typename T>
void ThreadBiTree<T>::InOrder(ThreadNode<T> *p)
{
    for (p = First(root); p != nullptr; p = Next(p))
    {
        cout << p->data << " ";
    }
    cout << endl;
}

template <typename T>
void ThreadBiTree<T>::PreOrder(ThreadNode<T> *p)
{
    while (p != nullptr)
    {
        cout << p->data << " ";
        if (p->ltag == 0)
        {
            p = p->leftChild;
        }
        else if (p->rtag == 0)
        {
            p = p->rightChild;
        }
        else
        {
            while (p != nullptr && p->rtag == 1)
            {
                p = p->rightChild;
            }
            if (p != nullptr)
            {
                p = p->rightChild;
            }
        }
    }
    cout << endl;
}

template <typename T>
void ThreadBiTree<T>::PostOrder(ThreadNode<T> *p)
{
    ThreadNode<T> *t = p;
    while (t->ltag == 0 || t->rtag == 0) // 寻找后续第一个结点
    {
        if (t->ltag = 0)
        {
            t = t->leftChild;
        }
        else if (t->rtag == 0)
        {
            t = t->rightChild;
        }
    }
    cout << t->data << " ";
    while ((p == Parent(t) != nullptr)) // 每次先找当前结点的父节点
    {
        if (p->rightChild == t || p->rtag == 1)
        {
            t = p;
        }
        else
        {
            t = p->rightChild;
            while (t->ltag == 0 || t->rtag == 0)
            {
                if (t->ltag == 0)
                {
                    t = t->leftChild;
                }
                else if (t->rtag == 0)
                {
                    t = t->rightChild;
                }
            }
        }
    }
    cout << t->data << " ";
}
