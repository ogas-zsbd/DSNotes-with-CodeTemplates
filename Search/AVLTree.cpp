#include <iostream>

using namespace std;

template <class T>
class AVLTreeNode
{
public:
    T key;              // 关键字(键值)
    int height;         // 高度     空的二叉树的高度是0，非空树的高度等于它的最大层次(根的层次为1，根的子节点为第2层，依次类推)。
    AVLTreeNode *left;  // 左子节点
    AVLTreeNode *right; // 右子节点
    AVLTreeNode(T value, AVLTreeNode *l, AVLTreeNode *r) : key(value), height(0), left(l), right(r) {};
};

template <class T>
class AVLTree
{
private:
    AVLTreeNode<T> *root; // 根结点

public:
    AVLTree();
    ~AVLTree();

    // 获取树的高度
    int getHeight();
    // 比较两个值的大小
    int max(int a, int b);

    // 前序遍历"AVL树"
    void preOrder();
    // 中序遍历"AVL树"
    void inOrder();
    // 后序遍历"AVL树"
    void postOrder();

    // (递归实现)查找"AVL树"中键值为key的节点
    AVLTreeNode<T> *search(T key);
    // (非递归实现)查找"AVL树"中键值为key的节点
    AVLTreeNode<T> *iterativeSearch(T key);

    // 查找最小结点：返回最小结点的键值。
    T getMinimum();
    // 查找最大结点：返回最大结点的键值。
    T getMaximum();

    // 将结点(key为节点键值)插入到AVL树中
    void insert(T key);

    // 删除结点(key为节点键值)
    void remove(T key);

    // 销毁AVL树
    void destroy();

    // 打印AVL树
    void print();

private:
    // 获取树的高度
    int getHeight(AVLTreeNode<T> *tree);

    // 前序遍历"AVL树"
    void preOrder(AVLTreeNode<T> *tree);
    // 中序遍历"AVL树"
    void inOrder(AVLTreeNode<T> *tree);
    // 后序遍历"AVL树"
    void postOrder(AVLTreeNode<T> *tree);

    // (递归实现)查找"AVL树x"中键值为key的节点
    AVLTreeNode<T> *search(AVLTreeNode<T> *x, T key) const;
    // (非递归实现)查找"AVL树x"中键值为key的节点
    AVLTreeNode<T> *iterativeSearch(AVLTreeNode<T> *x, T key) const;

    // 查找最小结点：返回tree为根结点的AVL树的最小结点。
    AVLTreeNode<T> *getMinimum(AVLTreeNode<T> *tree);
    // 查找最大结点：返回tree为根结点的AVL树的最大结点。
    AVLTreeNode<T> *getMaximum(AVLTreeNode<T> *tree);

    // LL：左左对应的情况(左单旋转)。
    AVLTreeNode<T> *leftLeftRotation(AVLTreeNode<T> *k2);

    // RR：右右对应的情况(右单旋转)。
    AVLTreeNode<T> *rightRightRotation(AVLTreeNode<T> *k1);

    // LR：左右对应的情况(左双旋转)。
    AVLTreeNode<T> *leftRightRotation(AVLTreeNode<T> *k3);

    // RL：右左对应的情况(右双旋转)。
    AVLTreeNode<T> *rightLeftRotation(AVLTreeNode<T> *k1);

    // 将结点(z)插入到AVL树(tree)中
    AVLTreeNode<T> *insert(AVLTreeNode<T> *&tree, T key);

    // 删除AVL树(tree)中的结点(z)，并返回被删除的结点
    AVLTreeNode<T> *remove(AVLTreeNode<T> *&tree, AVLTreeNode<T> *z);

    // 销毁AVL树
    void destroy(AVLTreeNode<T> *&tree);

    // 打印AVL树
    void print(AVLTreeNode<T> *tree, T key, int direction);
};

// 获取树的高度
template <class T>
int AVLTree<T>::getHeight(AVLTreeNode<T> *tree)
{
    if (tree != nullptr)
        return tree->height;
    return 0;
}
template <class T>
int AVLTree<T>::getHeight()
{
    return getHeight(root);
}

// 比较两个值的大小
template <class T>
int AVLTree<T>::max(int a, int b)
{
    return a > b ? a : b;
}

// 查找最小结点, 返回tree为根节点的AVL树的最小结点
template <class T>
AVLTreeNode<T> *AVLTree<T>::getMinimum(AVLTreeNode<T> *tree)
{
    if (tree == nullptr)
        return nullptr;
    while (tree->left != nullptr)
        tree = tree->left;
    return tree;
}
template <class T>
T AVLTree<T>::getMinimum()
{
    AVLTreeNode<T> *p = getMinimum(root);
    if (p != nullptr)
        return p->key;
    return (T) nullptr;
}

// 查找最大结点, 返回tree为根节点的AVL树的最大结点
template <class T>
AVLTreeNode<T> *AVLTree<T>::getMaximum(AVLTreeNode<T> *tree)
{
    if (tree == nullptr)
        return nullptr;
    while (tree->right != nullptr)
        tree = tree->right;
    return tree;
}
template <class T>
T AVLTree<T>::getMaximum()
{
    AVLTreeNode<T> *p = getMaximum(root);
    if (p != nullptr)
        return p->key;
    return (T) nullptr;
}

// (递归实现)查找AVL树种键值为key的结点
template <class T>
AVLTreeNode<T> *AVLTree<T>::search(AVLTreeNode<T> *x, T key) const
{
    if (x == nullptr || x->key == key)
        return x;
    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);
}
template <class T>
AVLTreeNode<T> *AVLTree<T>::search(T key)
{
    return search(root, key);
}

// (非递归实现)查找AVL树种键值为key的结点
template <class T>
AVLTreeNode<T> *AVLTree<T>::iterativeSearch(AVLTreeNode<T> *x, T key) const
{
    while (x != nullptr && x->key != key)
    {
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}
template <class T>
AVLTreeNode<T> *AVLTree<T>::iterativeSearch(T key)
{
    return iterativeSearch(root, key);
}

// 四种情况下的旋转操作

// LL型的旋转(也是右旋(顺时针旋转)的函数)
template <class T>
AVLTreeNode<T> *AVLTree<T>::leftLeftRotation(AVLTreeNode<T> *k2) // k2代表的是失衡结点
{
    AVLTreeNode<T> *k1;

    k1 = k2->left;        // 记录k1是k2的右子节点
    k2->left = k1->right; // 如果在右旋的过程中有冲突(k1有右子节点), 那么将k1的右子节点成为k2的左子节点
    k1->right = k2;       // 将失衡结点右旋(顺时针旋转), 也就是将失衡结点变成其左子节点的右子节点

    // 旋转后更新高度
    k2->height = max(getHeight(k2->left), getHeight(k2->right)) + 1;
    k1->height = max(getHeight(k1->left), k2->height) + 1;

    return k1; // 返回旋转后的根节点
}

// RR型的旋转(也是左旋(逆时针旋转)的函数)
template <class T>
AVLTreeNode<T> *AVLTree<T>::rightRightRotation(AVLTreeNode<T> *k1)
{
    AVLTreeNode<T> *k2;

    k2 = k1->right;       // 记录k2是k1的右子节点
    k1->right = k2->left; // 如果在左旋的过程中有冲突(k2有左子节点), 那么将k2的左子节点成为k1的右子节点
    k2->left = k1;        // 将失衡结点左旋(逆时针旋转), 也就是将失衡结点变成其右子节点的左子节点

    // 旋转后更新高度
    k1->height = max(getHeight(k1->left), getHeight(k1->right)) + 1;
    k2->height = max(getHeight(k2->right), k1->height) + 1;

    return k2;
}

// LR型的旋转
template <class T>
AVLTreeNode<T> *AVLTree<T>::leftRightRotation(AVLTreeNode<T> *k3) // k3代表的失衡结点
{
    k3->left = rightRightRotation(k3->left); // 失衡结点的左子节点先左旋(逆时针旋转)
    return leftLeftRotation(k3);             // 然后将失衡结点右旋
}

// RL型的旋转
template <class T>
AVLTreeNode<T> *AVLTree<T>::rightLeftRotation(AVLTreeNode<T> *k1)
{
    k1->right = leftLeftRotation(k1->right); // 失衡结点的右子节点先右旋(顺时针旋转)
    return rightRightRotation(k1);           // 然后将失衡结点左旋
}

// 将结点插入到AVL树中, 并返回根节点
template <class T>
AVLTreeNode<T> *AVLTree<T>::insert(AVLTreeNode<T> *&tree, T key)
{
    if (tree = nullptr)
    {
        // 新建结点
        tree = new AVLTreeNode<T>(key, nullptr, nullptr);
        if (tree = nullptr)
        {
            cout << "ERROR: create avltree node failed!" << endl;
            return nullptr;
        }
    }
    else if (key < tree->key) // key 小于根节点的值, 所以应该插入到根节点的左子树
    {
        tree->left = insert(tree->left, key);

        // 插入结点后, 若AVL树失去平衡, 则进行相应的调节
        if (getHeight(tree->left) - getHeight(tree->right) == 2) // 失衡结点BF值==2, 可以判断是LX型
        {
            if (key < tree->left->key) // 也就是插入的结点在失衡结点的左子节点的左子树上, 所以是LL型
            {
                tree = leftLeftRotation(tree); // 使用LL型
            }
            else // 插入结点在失衡结点的左子节点的右子树上, 所以是LR型
            {
                tree = leftRightRotation(tree); // 使用LR型
            }
        }
    }
    else if (key > tree->key) // key 大于根节点的值, 所以应该插入到根节点的右子树
    {
        tree->right = insert(tree->right, key);

        // 插入结点后, 若AVL树失去平衡, 则进行相应的调节
        if (getHeight(tree->left) - getHeight(tree->right) == -2) // 失衡结点BF值==-2, 可以判断是RX型
        {
            if (key > tree->right->key) // 插入的结点在失衡结点的右子节点的右子树上, 也就是RR型
            {
                tree = rightRightRotation(tree); // 使用RR型
            }
            else // 插入结点在失衡结点的右子节点的左子树上, 也就是RL型
            {
                tree = rightLeftRotation(tree); // 使用RL型
            }
        }
    }
    else // key == tree->key 的情况
    {
        cout << "添加失败, 存在相同的结点" << endl;
    }

    tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;

    return tree;
}
template <class T>
void AVLTree<T>::insert(T key)
{
    insert(root, key);
}

// 删除结点
template <class T>
AVLTreeNode<T> *AVLTree<T>::remove(AVLTreeNode<T> *&tree, AVLTreeNode<T> *z) // tree是根节点, z是要删除的结点
{
    // 根为空 或者 没有要删除的结点, 直接返回null
    if (tree == nullptr || z = nullptr)
        return nullptr;

    if (z->key < tree->key) // 待删除的结点在tree的左子树中
    {
        tree->left = remove(tree->left, z);

        // 删除结点后, 如果AVL树失去平衡要进行相应的调节
        if (getHeight(tree->left) - getHeight(tree->right) == -2) // RX型的特征
        {
            AVLTreeNode<T> *r = tree->right;
            if (getHeight(r->left) > getHeight(r->right))
            {
                tree = rightLeftRotation(tree);
            }
            else
            {
                tree = rightRightRotation(tree);
            }
        }
    }
    else if (z->key > tree->key) // 待删除的结点在tree的右子树中
    {
        tree->right = remove(tree->right, z);

        // 删除结点后, 若AVL树失去平衡, 则进行相应的调节
        if (getHeight(tree->left) - getHeight(tree->right) == 2)
        {
            AVLTreeNode<T> *l = tree->left;
            if (getHeight(l->right) > getHeight(l->left))
            {
                tree = leftRightRotation(tree);
            }
            else
            {
                tree = leftLeftRotation(tree);
            }
        }
    }
    else // tree是对应要删除的结点(z->key == tree->key), 删除逻辑类似二叉搜索树中的删除, 但是多了检查平衡性并调整的步骤
    {
        // tree的左右孩子都非空
        if (tree->left != nullptr && tree->right != nullptr)
        {
            if (getHeight(tree->left) > getHeight(tree->right))
            {
                // 如果tree的左子树比右子树高
                // 1. 找出tree的左子树中的最大结点
                // 2. 将该最大结点的值赋给tree
                // 3. 删除该最大结点
                // 这样做可以理解为: 将tree中的左子树中的最大结点 做tree的替身
                // 这样做的好处是: tree是要被删除的结点, 将tree的左子树的最大的结点赋给tree相当于删除了tree, 而这个最大的结点必然在叶子结点上, 删除了这个结点AVL树仍然平衡
                AVlTreeNode<T> *max = getMaximum(tree->left);
                tree->key = max->key;
                tree->left = remove(tree->left, max);
            }
            else
            {
                // 如果tree的左子树不比右子树高(即它们相等, 或右子树比左子树高)
                // 1. 找出tree的右子树中的最小结点
                // 2. 将该最小结点的值赋给tree
                // 3. 删除最小结点
                // 解释类似上面, 这里不再赘述
                AVLTreeNode<T> *min = getMaximum(tree->right);
                tree->key = min->key;
                tree->right = remove(tree->right, min);
            }
        }
        else // 当tree结点只有一个子节点(左子节点或右子节点) 或 tree是一个叶子结点(即没有子节点)
        {
            AVLTreeNode<T> *tmp = tree; // 将当前结点存入tmp
            // 类似平衡二叉树删除结点时的操作
            // - 当tree有左子节点没有右子节点: 直接将左子树接上
            // - 当tree没有左子节点: 将右子树接上
            //      这里合并了两种情况
            //          - tree有右子节点没有左子节点: 直接将右子树接上
            //          - tree是叶子结点: 将右子树接上相当于把空指针接上, 也就是删除了这个结点, 叶子结点的删除是最简单的
            tree = (tree->left != nullptr) ? tree->left : tree->right;
            delete tmp;
        }
    }
    return tree;
}
template <class T>
void AVLTree<T>::remove(T key)
{
    AVLTreeNode<T> *z;
    if ((z = search(root, key)) != nullptr)
        root = remove(root, z);
}