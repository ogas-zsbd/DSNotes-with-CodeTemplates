#include <iostream>  // 输入输出流库
#include <queue>     // 队列库，用于层次遍历
#include <string>    // 字符串库
#include <algorithm> // 算法库，提供如 std::lower_bound 和 std::find 等函数
#include <memory>    // 智能指针库
#include <vector>    // 向量库

using namespace std; // 使用标准命名空间

const int M = 2; // 最大键数为 M * 2，即 4

string key_words[1001]; // 键值对应的字符串（最多 1001 个键）

// 前向声明类
class Node;
class InternalNode;
class LeafNode;

// 节点基类
class Node
{
public:
    Node(bool isLeaf);          // 构造函数
    virtual ~Node() = default;  // 虚析构函数，允许派生类使用自定义析构函数
    virtual void print() const; // 打印节点内容的虚函数

    Node *getSibling(int &flag);    // 获取当前节点的兄弟节点
    InternalNode *parent = nullptr; // 指向父节点的指针
    vector<int> keys;               // 存储节点中的键值
    bool isLeaf;                    // 是否为叶节点的标志
};

// 节点构造函数
Node::Node(bool isLeaf) : isLeaf(isLeaf) {}

// 获取兄弟节点
Node *Node::getSibling(int &flag)
{
    // 如果没有父节点，返回 nullptr
    if (!parent)
        return nullptr;

    // 查找当前节点在父节点中的位置
    for (int i = 0; i <= parent->keys.size(); i++)
    {
        // 如果当前节点是父节点的子节点
        if (parent->children[i] == this)
        {
            // 如果是最后一个子节点，返回左兄弟节点
            if (i == parent->keys.size())
            {
                flag = 1;                       // 设置标志位
                return parent->children[i - 1]; // 左兄弟节点
            }
            else
            {
                flag = 2;                       // 设置标志位
                return parent->children[i + 1]; // 右兄弟节点
            }
        }
    }
    return nullptr; // 没有兄弟节点
}

// 打印节点内容
void Node::print() const
{
    // 遍历节点中的所有键值
    for (int i = 0; i < keys.size(); i++)
    {
        cout << "(" << keys[i] << "," << key_words[keys[i]] << ") "; // 打印键值及其对应的字符串
        if (i >= keys.size() - 1)
        {
            cout << " | "; // 分隔符
        }
    }
}

// 内部节点类，继承自 Node
class InternalNode : public Node
{
public:
    InternalNode();                            // 构造函数
    ~InternalNode() override = default;        // 虚析构函数
    bool insert(int key, Node *child);         // 插入键值和子节点
    bool remove(int key);                      // 删除键值
    int split(InternalNode *sibling, int key); // 分裂节点
    bool merge(InternalNode *sibling);         // 合并节点
    bool redistribute(InternalNode *sibling);  // 重新分配节点
    vector<Node *> children;                   // 存储子节点的智能指针
};

// 内部节点构造函数
InternalNode::InternalNode() : Node(false) {}

// 插入键值和子节点
bool InternalNode::insert(int key, Node *child)
{
    // 查找插入位置
    auto it = lower_bound(keys.begin(), keys.end(), key);
    int index = distance(keys.begin(), it);                     // 计算插入索引
    keys.insert(it, key);                                       // 插入键值
    children.insert(children.begin() + index + 1, move(child)); // 插入子节点
    return true;
}

// 删除键值
bool InternalNode::remove(int key)
{
    // 查找键值
    auto it = find(keys.begin(), keys.end(), key);
    if (it == keys.end())
        return false;                             // 键值不存在
    int index = distance(keys.begin(), it);       // 计算索引
    keys.erase(it);                               // 删除键值
    children.erase(children.begin() + index + 1); // 删除对应子节点
    return true;
}

// 分裂节点
int InternalNode::split(InternalNode *sibling, int key)
{
    InternalNode *sibling = new InternalNode; // 创建新节点
    int midIndex = keys.size() / 2;           // 计算中间索引

    // 如果键值大于中间键值
    if (key > keys[midIndex])
    {
        sibling->keys.assign(keys.begin() + midIndex + 1, keys.end());                                                     // 复制后半部分键值
        sibling->children.assign(make_move_iterator(children.begin() + midIndex + 1), make_move_iterator(children.end())); // 复制后半部分子节点
    }
    else
    {
        sibling->keys.assign(keys.begin() + midIndex, keys.end());                                                     // 复制后半部分键值
        sibling->children.assign(make_move_iterator(children.begin() + midIndex), make_move_iterator(children.end())); // 复制后半部分子节点
        sibling->children.front()->parent = sibling;                                                                   // 更新子节点的父节点
    }

    keys.resize(midIndex);         // 缩减当前节点的键值
    children.resize(midIndex + 1); // 缩减当前节点的子节点
    return sibling->keys.front();  // 返回新节点的最小键值
}

// 合并节点
bool InternalNode::merge(InternalNode *sibling)
{
    // 如果合并后键值数目大于最大值，不能合并
    if (keys.size() + sibling->keys.size() > M * 2)
        return false;

    // 合并键值和子节点
    keys.insert(keys.end(), sibling->keys.begin(), sibling->keys.end());
    children.insert(children.end(), make_move_iterator(sibling->children.begin()), make_move_iterator(sibling->children.end()));
    return true;
}

// 重新分配节点
bool InternalNode::redistribute(InternalNode *sibling)
{
    // 如果兄弟节点的键值数目少于当前节点
    if (sibling->keys.size() < keys.size())
    {
        sibling->keys.insert(sibling->keys.begin(), keys.back());                   // 将当前节点的最后一个键值插入兄弟节点
        sibling->children.insert(sibling->children.begin(), move(children.back())); // 将当前节点的最后一个子节点插入兄弟节点
        keys.pop_back();                                                            // 移除当前节点的最后一个键值
        children.pop_back();                                                        // 移除当前节点的最后一个子节点
    }
    else
    {
        keys.push_back(sibling->keys.front());               // 将兄弟节点的第一个键值插入当前节点
        children.push_back(move(sibling->children.front())); // 将兄弟节点的第一个子节点插入当前节点
        sibling->keys.erase(sibling->keys.begin());          // 移除兄弟节点的第一个键值
        sibling->children.erase(sibling->children.begin());  // 移除兄弟节点的第一个子节点
    }
    return true;
}

// 叶子节点类，继承自 Node
class LeafNode : public Node
{
public:
    LeafNode();                                     // 构造函数
    ~LeafNode() override = default;                 // 虚析构函数
    bool insert(int key);                           // 插入键值
    bool remove(int key);                           // 删除键值
    int split(LeafNode *sibling);                   // 分裂节点
    bool merge(LeafNode *sibling);                  // 合并节点
    LeafNode *prev = nullptr;                       // 指向前一个叶子节点的指针
    LeafNode *next = nullptr;                       // 指向下一个叶子节点的指针
    bool LeafNode::redistribute(LeafNode *sibling); // 重新分配叶子节点中的键值
};

// 叶子节点构造函数
LeafNode::LeafNode() : Node(true) {}

// 插入键值
bool LeafNode::insert(int key)
{
    // 查找插入位置
    auto it = lower_bound(keys.begin(), keys.end(), key);
    keys.insert(it, key); // 插入键值
    return true;
}

// 删除键值
bool LeafNode::remove(int key)
{
    // 查找键值
    auto it = find(keys.begin(), keys.end(), key);
    if (it == keys.end())
        return false; // 键值不存在
    keys.erase(it);   // 删除键值
    return true;
}

// 分裂节点
int LeafNode::split(LeafNode *sibling)
{
    LeafNode *sibling = new LeafNode;                          // 创建新节点
    int midIndex = keys.size() / 2;                            // 计算中间索引
    sibling->keys.assign(keys.begin() + midIndex, keys.end()); // 复制后半部分键值
    keys.resize(midIndex);                                     // 缩减当前节点的键值
    sibling->next = next;                                      // 更新新节点的下一个指针
    next = sibling;                                            // 更新当前节点的下一个指针
    sibling->prev = this;                                      // 更新新节点的前一个指针
    return sibling->keys.front();                              // 返回新节点的最小键值
}

// 合并节点
bool LeafNode::merge(LeafNode *sibling)
{
    // 如果合并后键值数目大于最大值，不能合并
    if (keys.size() + sibling->keys.size() > M * 2)
        return false;

    // 合并键值和更新指针
    keys.insert(keys.end(), sibling->keys.begin(), sibling->keys.end());
    next = sibling->next;
    if (next)
        next->prev = this; // 更新下一个叶子节点的前一个指针
    return true;
}

// 重新分配叶子节点中的键值
bool LeafNode::redistribute(LeafNode *sibling)
{
    if (sibling->keys.size() < keys.size())
    {
        // 如果兄弟节点的键值数目少于当前节点
        // 将当前节点的最后一个键值插入兄弟节点
        sibling->keys.insert(sibling->keys.begin(), keys.back());
        keys.pop_back(); // 移除当前节点的最后一个键值
    }
    else
    {
        // 否则，将兄弟节点的第一个键值插入当前节点
        keys.push_back(sibling->keys.front());
        sibling->keys.erase(sibling->keys.begin()); // 移除兄弟节点的第一个键值
    }
    return true;
}

// B+ 树类
class BPlusTree
{
public:
    BPlusTree();                              // 构造函数
    ~BPlusTree() = default;                   // 虚析构函数
    bool search(int key, string &path) const; // 查找键值
    bool insert(int key);                     // 插入键值
    bool remove(int key);                     // 删除键值
    void print() const;                       // 打印树结构

private:
    LeafNode *findLeaf(int key) const;                           // 查找包含键值的叶子节点
    bool addNode(InternalNode *parent, int key, Node *newChild); // 添加子节点
    bool removeNode(InternalNode *parent, int key);              // 删除子节点
    Node *root;                                                  // 根节点
};

// B+ 树构造函数
BPlusTree::BPlusTree() : root(nullptr) {}

// 查找键值
bool BPlusTree::search(int key, string &path) const
{
    path = "Search path: "; // 初始化路径字符串
    Node *p = root;         // 从根节点开始
    while (p && !p->isLeaf)
    {                                                     // 遍历到叶子节点
        InternalNode *q = static_cast<InternalNode *>(p); // 转换为内部节点
        int i = 0;
        for (i = 0; i < q->keys.size(); i++)
        {
            if (key < q->keys[i])
                break; // 找到适当的子节点
        }
        path += to_string(q->keys[i > 0 ? i - 1 : i]) + " --> "; // 更新路径
        p = q->children[i];                                      // 移动到下一个节点
    }
    if (!p)
        return false;                                                  // 没有找到节点
    path += to_string(p->keys.front());                                // 更新路径
    return find(p->keys.begin(), p->keys.end(), key) != p->keys.end(); // 检查键值是否存在
}

// 查找包含键值的叶子节点
LeafNode *BPlusTree::findLeaf(int key) const
{
    Node *p = root; // 从根节点开始
    while (p && !p->isLeaf)
    {                                                     // 遍历到叶子节点
        InternalNode *q = static_cast<InternalNode *>(p); // 转换为内部节点
        int i = 0;
        for (i = 0; i < q->keys.size(); i++)
        {
            if (key < q->keys[i])
                break; // 找到适当的子节点
        }
        p = q->children[i]; // 移动到下一个节点
    }
    return static_cast<LeafNode *>(p); // 返回叶子节点
}

// 插入键值
bool BPlusTree::insert(int key)
{
    string path;
    if (search(key, path))
        return false;               // 如果键值已存在
    LeafNode *leaf = findLeaf(key); // 查找适当的叶子节点
    if (!leaf)
    {
        LeafNode *leaf = new LeafNode;        // 创建新的根节点
        leaf = static_cast<LeafNode *>(root); // 转换为叶子节点
    }
    if (leaf->keys.size() < M * 2)
    {
        leaf->insert(key); // 在叶子节点中插入键值
        return true;
    }
    LeafNode *sibling;
    int newKey = leaf->split(sibling); // 分裂叶子节点
    if (key < newKey)
    {
        leaf->insert(key); // 在原叶子节点中插入键值
    }
    else
    {
        sibling->insert(key); // 在新叶子节点中插入键值
    }
    InternalNode *parent = static_cast<InternalNode *>(leaf->parent);

    if (!parent)
    {
        // 创建新的内部节点，并显式转换为 unique_ptr<Node>
        InternalNode *newParent = new InternalNode;

        newParent->keys.push_back(newKey);                 // 插入新键值
        newParent->children.push_back(std::move(root));    // 插入旧根节点
        newParent->children.push_back(std::move(sibling)); // 插入新叶子节点

        // 更新根节点并进行显式类型转换
        root = move(newParent);
        return true;
    }
    return addNode(parent, newKey, move(sibling)); // 递归添加新叶子节点
}

// 添加子节点
bool BPlusTree::addNode(InternalNode *parent, int key, Node *newChild)
{
    if (parent->keys.size() < M * 2)
    {
        parent->insert(key, move(newChild)); // 在父节点中插入新子节点
        return true;
    }
    InternalNode *sibling;
    int newKey = parent->split(sibling, key); // 分裂父节点
    if (key < newKey)
    {
        parent->insert(key, move(newChild)); // 在父节点中插入新子节点
    }
    else
    {
        sibling->insert(key, move(newChild)); // 在新父节点中插入新子节点
    }
    if (!parent->parent)
    {
        InternalNode *newRoot = new InternalNode;   // 创建新的根节点
        newRoot->keys.push_back(newKey);            // 插入新键值
        newRoot->children.push_back(move(parent));  // 插入旧父节点
        newRoot->children.push_back(move(sibling)); // 插入新父节点
        root = move(newRoot);                       // 更新根节点
        return true;
    }
    return addNode(parent->parent, newKey, move(sibling)); // 递归添加新子节点
}

// 删除键值
bool BPlusTree::remove(int key)
{
    string path;
    if (!search(key, path))
        return false;               // 如果键值不存在
    LeafNode *leaf = findLeaf(key); // 查找包含键值的叶子节点
    if (!leaf)
        return false;  // 如果未找到叶子节点
    leaf->remove(key); // 删除键值
    if (leaf->keys.size() >= M || !leaf->parent)
        return true; // 如果键值数目足够或没有父节点
    int flag = 0;
    LeafNode *sibling = static_cast<LeafNode *>(leaf->getSibling(flag)); // 获取兄弟节点
    if (flag == 1)
    {
        if (!sibling->merge(leaf))
        {                                // 合并兄弟节点
            sibling->redistribute(leaf); // 重新分配键值
        }
    }
    else
    {
        if (!leaf->merge(sibling))
        {                                // 合并兄弟节点
            leaf->redistribute(sibling); // 重新分配键值
        }
    }
    return removeNode(static_cast<InternalNode *>(leaf->parent), key); // 从父节点中删除键值
}

// 从父节点中删除键值
bool BPlusTree::removeNode(InternalNode *parent, int key)
{
    if (parent->keys.size() >= M || !parent->parent)
        return true; // 如果键值数目足够或没有父节点
    int flag = 0;
    InternalNode *sibling = static_cast<InternalNode *>(parent->getSibling(flag)); // 获取兄弟节点
    if (flag == 1)
    {
        if (!sibling->merge(parent))
        {                                  // 合并兄弟节点
            sibling->redistribute(parent); // 重新分配键值
        }
    }
    else
    {
        if (!parent->merge(sibling))
        {                                  // 合并兄弟节点
            parent->redistribute(sibling); // 重新分配键值
        }
    }
    return removeNode((parent->parent), key); // 递归删除
}

// 打印树结构
void BPlusTree::print() const
{
    if (!root)
        return; // 如果树为空

    queue<const Node *> q; // 使用队列进行层次遍历
    q.push(root);          // 将根节点加入队列

    while (!q.empty())
    {
        int size = q.size(); // 当前层节点数

        for (int i = 0; i < size; ++i)
        {
            const Node *p = q.front(); // 获取队首节点
            q.pop();                   // 移除队首节点
            p->print();                // 打印节点内容

            // 如果节点不是叶子节点，处理其子节点
            if (!p->isLeaf)
            {
                const InternalNode *internalNode = static_cast<const InternalNode *>(p); // 转换为内部节点
                for (const auto &child : internalNode->children)
                {
                    q.push(child); // 将子节点加入队列，使用裸指针
                }
            }
        }
        cout << endl; // 打印当前层的分隔线
    }
}

// 本篇基本是GPT生成的, 等实力到了会重写一篇