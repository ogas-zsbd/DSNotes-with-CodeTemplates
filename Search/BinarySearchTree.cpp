#include <iostream>

using namespace std;

// 二叉查找树的结点
template <class T>
class BSTNode
{
public:
    T key;           // 关键字
    BSTNode *left;   // 左子节点
    BSTNode *right;  // 右子节点
    BSTNode *parent; // 父节点

    BSTNode(T value, BSTNode *p, BSTNode *l, BSTNode *r) : key(value), parent(p), left(l), right(r) {};
};

// 二叉查找树
template <class T>
class BSTree
{
private:
    BSTNode<T> *root; // 根节点

public:
    BSTree();
    ~BSTree();

    // 各种遍历

    // 前序遍历二叉树
    void preOrder();
    // 中序遍历二叉树
    void inOrder();
    // 后序遍历二叉树
    void postOrder();

    // 各种查找

    // (递归实现)查找"二叉树"中键值为key的节点
    BSTNode<T> *search(T key);
    // (非递归实现)查找"二叉树"中键值为key的节点
    BSTNode<T> *iterativeSearch(T key);

    // 查找最小结点：返回最小结点的键值。
    T minimum();
    // 查找最大结点：返回最大结点的键值。
    T maximum();

    // 找结点(x)的后继结点。即，查找"二叉树中数据值大于该结点"的"最小结点"。
    BSTNode<T> *successor(BSTNode<T> *x);
    // 找结点(x)的前驱结点。即，查找"二叉树中数据值小于该结点"的"最大结点"。
    BSTNode<T> *predecessor(BSTNode<T> *x);

    // 创建, 删除, 打印

    // 将结点(key为节点键值)插入到二叉树中
    void insert(T key);

    // 删除结点(key为节点键值)
    void remove(T key);

    // 销毁二叉树
    void destroy();

    // 打印二叉树
    void print();

private:
    // 前序遍历"二叉树"
    void preOrder(BSTNode<T> *tree);
    // 中序遍历"二叉树"
    void inOrder(BSTNode<T> *tree);
    // 后序遍历"二叉树"
    void postOrder(BSTNode<T> *tree);

    // (递归实现)查找"二叉树x"中键值为key的节点
    BSTNode<T> *search(BSTNode<T> *x, T key);
    // (非递归实现)查找"二叉树x"中键值为key的节点
    BSTNode<T> *iterativeSearch(BSTNode<T> *x, T key);

    // 查找最小结点：返回tree为根结点的二叉树的最小结点。
    BSTNode<T> *minimum(BSTNode<T> *tree);
    // 查找最大结点：返回tree为根结点的二叉树的最大结点。
    BSTNode<T> *maximum(BSTNode<T> *tree);

    // 将结点(z)插入到二叉树(tree)中
    void insert(BSTNode<T> *&tree, BSTNode<T> *z);

    // 删除二叉树(tree)中的结点(z)，并返回被删除的结点
    BSTNode<T> *remove(BSTNode<T> *&tree, BSTNode<T> *z);

    // 销毁二叉树
    void destroy(BSTNode<T> *&tree);

    // 打印二叉树
    void print(BSTNode<T> *tree, T key, int direction);
};

template <class T>
BSTNode<T> *BSTree<T>::search(BSTNode<T> *x, T key)
{
    if (x == nullptr || x->key == key)
        return x; // 如果找到了相等的值, 或者找到最后还是空则return

    // 使用了类似二分的方法来查找
    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);
}
template <class T>
BSTNode<T> *BSTree<T>::search(T Key)
{
    search(root, key);
    // 这里是公有的接口, 只需要key一个参数更符合直觉, 二上面私有的函数中, 有子树的根节点这个参数更便于递归
}

template <class T>
BSTNode<T> *BSTree<T>::iterativeSearch(BSTNode<T> *x, T key)
{
    while ((x != nullptr) && (x->key != key))
    {
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}
template <class T>
BSTNode<T> *BSTree<T>::iterativeSearch(T key)
{
    iterativeSearch(root, key);
}

// 将结点插入二叉树中
// 参数说明:
//      tree: 二叉树的根节点
//      z: 插入的结点
template <class T>
void BSTree<T>::insert(BSTNode<T> *&tree, BSTNode<T> *z)
{
    BSTNode<T> *y = nullptr; // y用于追踪z的父节点
    BSTNode<T> *x = tree;    // x用于遍历树

    // 查找z插入的位置
    // 类似上面的查找函数
    while (x != nullptr)
    {
        y = x; // y始终保持为x的父节点
        // 这样的判断是根据二叉搜索树的性质决定的, 左子树小, 右子树大
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    // 循环结束后, y是z的父节点, 而x是z应该插入的位置
    z->parent = y; // 将z的父节点设置为y
    if (y == nullptr)
        tree = z; // 如果y为null(即这是棵空树), 那么z就是根节点
    else if (z->key < y->key)
        y->left = z; // 否则根据z与y的大小关系, 将z插入y的左子节点/右子节点
    else
        y->right = z;
}
template <class T>
void BSTree<T>::insert(T key)
{
    BSTNode<T> *z = nullptr;

    // 如果新建结点失败则返回(不过真的有创建失败的情况吗...?)
    if ((z = new BSTNode<T>(key, nullptr, nullptr, nullptr)) == nullptr)
        return;

    insert(root, z);
}

// 查找最小值
template <class T>
BSTNode<T> *BSTree<T>::minimum(BSTNode<T> *tree)
{
    if (tree == nullptr)
        return nullptr;
    while (tree->left != nullptr)
        tree = tree->left;
    return tree;
}
template <class T>
T BSTree<T>::minimum()
{
    BSTNode<T> *p = minimum(root);
    if (p != nullptr)
        return p->key;
    return (T) nullptr;
}
// 查找最大值
template <class T>
BSTNode<T> *BSTree<T>::maximum(BSTNode<T> *tree)
{
    if (tree == NULL)
        return NULL;

    while (tree->right != NULL)
        tree = tree->right;
    return tree;
}

template <class T>
T BSTree<T>::maximum()
{
    BSTNode<T> *p = maximum(mRoot);
    if (p != NULL)
        return p->key;

    return (T)NULL;
}

// 找结点(x)的后继结点, 即查找"二叉树种数据值大于该结点的最小结点"
template <class T>
BSTNode<T> *BSTree<T>::successor(BSTNode<T> *x)
{
    // 如果x存在右子节点, 则x的后继结点为 以其右子节点为根的子树的最小结点
    if (x->right != nullptr)
        return minimum(x->right);

    // 如果x没有右子节点, 则x有以下两种可能
    // 1. x是一个左子节点,  则x的后继结点为它的父节点
    // 2. x是一个右子节点, 则查找x的最低父节点, 并且该父节点要有左子节点, 找到的这个最低父节点就是x的后继结点
    BSTNode<T> *y = x->parent;
    while (y != nullptr && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

// 删除结点(z), 并返回被删除的结点
// 参数说明:
//      tree 二叉树的根节点
//      z 删除的结点
template <class T>
BSTNode<T> *BSTree<T>::remove(BSTNode<T> *&tree, BSTNode<T> *z)
{
    BSTNode *x = nullptr;
    BSTNode *y = nullptr;

    // 1. 确定要删除的结点 y
    if (z->left == nullptr && z->right == nullptr)
        y = z; // 如果z是叶子结点, 就直接删除z
    else
        y = successor(z); // 如果z不是叶子结点, 找到它的后继结点y

    // 2. 确定y的子节点x
    if (y->left != nullptr)
        x = y->left; // 如果y存在左子节点, 将x设为y的左子节点
    else
        x = y->right; // 如果y不存在左子节点, 将x设为y的右子节点

    // 3. 更新x的父节点指针
    if (x != nullptr)
        x->parent = y->parent; // 如果x不为空, 将x的父节点设为y的父节点

    // 4. 更新y的父节点指针(因为y是要被删除的结点, 我们用x来代替y)
    if (y->parent == nullptr)
        tree = x; // 如果y是根节点, 将树的根设为x
    else if (y == y->parent->left)
        y->parent->left = x; // 如果y是左子节点, 将y的父节点的左子节点设为x
    else
        y->parent->left = x; // 如果y是右子节点, 将y的父节点的右子节点设为x

    // 5. 更新z的键值
    if (y != z)
        z->key = y->key;

    return y; // 返回被删除的结点y
}
template <class T>
void BSTree<T>::remove(T key)
{
    BSTNode<T> *z, *node;
    // 1. 查找结点z
    if (z = search(root, key) != nullptr)
    { // 2. 删除结点z
        if (node = remove(root, z) != nullptr)
        { // 3. 释放内存
            delete node;
        }
    }
}