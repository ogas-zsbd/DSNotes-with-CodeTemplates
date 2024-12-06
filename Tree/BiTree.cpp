#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <limits>

using namespace std;

// 二叉树结点类
template <typename T>
class BinaryTreeNode
{
public:
    T data;
    BinaryTreeNode<T> *left;  // 左子树指针
    BinaryTreeNode<T> *right; // 右子树指针
    BinaryTreeNode() : data(0), left(NULL), right(NULL) {}
};

// 二叉树类
template <typename T>
class BinaryTree
{
public:
    BinaryTreeNode<T> *root; // 根节点指针

    void createBinaryTree(BinaryTreeNode<T> *&node);      // 创建二叉树
    void preOrder(BinaryTreeNode<T> *node);               // 先序遍历
    void inOrder(BinaryTreeNode<T> *node);                // 中序遍历
    void postOrder(BinaryTreeNode<T> *node);              // 后序遍历
    void levelOrder(BinaryTreeNode<T> *node);             // 层序遍历
    int countNodes(BinaryTreeNode<T> *node);              // 统计结点个数
    int countLeaves(BinaryTreeNode<T> *node);             // 统计叶子结点个数
    int getDepth(BinaryTreeNode<T> *node);                // 获取树的深度
    void destroy(BinaryTreeNode<T> *&node);               // 销毁二叉树
    BinaryTreeNode<T> *copyTree(BinaryTreeNode<T> *node); // 复制二叉树
    void swapSubtrees(BinaryTreeNode<T> *node);           // 左右子树交换
};

template <typename T>
void BinaryTree<T>::createBinaryTree(BinaryTreeNode<T> *&node)
{
    string input;
    cout << "请输入结点值(输入'NULL'表示空结点): ";
    cin >> input;

    // 判断是否有空结点
    if (input == "NULL")
    {
        node = nullptr;
        return;
    }

    // 如果不是空结点就创建新的结点存入二叉树中
    T nodeValue;
    istringstream(input) >> nodeValue;

    if (cin.fail())
    {
        cerr << "输入无效, 请重新输入一个有效值: " << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        createBinaryTree(node); // 目前还未进行任何操作, 重新调用输入函数即可
        return;
    }

    // 创建结点, 并递归创建左右子树
    node = new BinaryTreeNode<T>;
    createBinaryTree(node->left);
    createBinaryTree(node->right);
}

template <typename T>
void BinaryTree<T>::preOrder(BinaryTreeNode<T> *node)
{
    if (node != nullptr)
    {
        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
}

template <typename T>
void BinaryTree<T>::inOrder(BinaryTreeNode<T> *node)
{
    if (node != nullptr)
    {
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }
}

template <typename T>
void BinaryTree<T>::postOrder(BinaryTreeNode<T> *node)
{
    if (node != nullptr)
    {
        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }
}

template <typename T>
void BinaryTree<T>::levelOrder(BinaryTreeNode<T> *node)
{
    queue<BinaryTreeNode<T> *> q;
    q.push(node);

    while (!q.empty()) // 当队列为空时就是遍历完了
    {
        BinaryTreeNode<T> *temp = q.front();
        q.pop();
        cout << temp->data << " ";
        if (temp->left != nullptr)
        {
            q.push(temp->left);
        }
        if (temp->right != nullptr)
        {
            q.push(temp->right);
        }
    }
}

template <typename T>
int BinaryTree<T>::countNodes(BinaryTreeNode<T> *node)
{
    if (node == nullptr)
        return 0;
    return 1 + countNodes(node->left) + countNodes(node->right); // 树的精髓在于递归, 递归算出左右子树的结点个数, 加上根结点就是整个树的结点个数
}

template <typename T>
int BinaryTree<T>::countLeaves(BinaryTreeNode<T> *node)
{
    if (node == nullptr)
        return 0;
    if (node->left == nullptr && node->right == nullptr)
        return 1;                                              // 左右指针均为空, 说明这个就是叶子结点
    return countLeaves(node->left) + countLeaves(node->right); // 同样, 递归算出左右子树的叶子结点个数
}

template <typename T>
int BinaryTree<T>::getDepth(BinaryTreeNode<T> *node)
{
    if (node == nullptr)
        return 0;
    return 1 + max(getDepth(node->left), getDepth(node->right)); // 树的深度等于左右子树深度的最大值加一, 同样, 递归是树的精髓
}

template <typename T>
void BinaryTree<T>::destroy(BinaryTreeNode<T> *&node)
{
    if (node != nullptr)
    {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

template <typename T>
BinaryTreeNode<T> *BinaryTree<T>::copyTree(BinaryTreeNode<T> *node)
{
    if (node == nullptr)
        return nullptr;
    BinaryTreeNode<T> *newNode = new BinaryTreeNode<T>(node->data);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
}

template <typename T>
void BinaryTree<T>::swapSubtrees(BinaryTreeNode<T> *node)
{
    if (node != nullptr)
    {
        swap(node->left, node->right);
        swapSubtrees(node->left);
        swapSubtrees(node->right);
    }
}