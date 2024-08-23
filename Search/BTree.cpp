#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class BTree
{
private:
    // 定义节点结构体
    struct Node
    {
        vector<int> keys;        // 存储节点中的键
        vector<Node *> children; // 存储子节点的指针
    };

    using ChildPosition = pair<Node *, int>; // 表示子节点位置的类型

    Node *root; // 指向根节点的指针
    int t;      // B 树的最小度数（t ≥ 2）

    // 分裂节点 x 的第 i 个子节点
    void splitChild(Node *x, int i);
    // 插入键 k 到非满节点 x 中
    void insertNonFull(Node *x, int k);
    // 在节点 p 中搜索键 k
    ChildPosition search(Node *p, int k);
    // 查找节点 x 中第 i 个键的前驱
    ChildPosition predecessor(Node *x, int i);
    // 查找节点 x 中第 i 个键的后继
    ChildPosition successor(Node *x, int i);
    // 找到以 p 为根的子树中的最小值
    Node *minimum(Node *p);
    // 找到以 p 为根的子树中的最大值
    Node *maximum(Node *p);
    // 合并节点 y 到 x 中，并删除节点 z 所指向的键
    void combine(Node *x, Node *y, ChildPosition z);
    // 从节点 x 中删除键 k
    void remove(Node *x, int k);
    // 中序遍历节点 p
    void inorderWalk(Node *p);

public:
    // 构造函数
    BTree(int deg) : root(new Node), t(deg >= 2 ? deg : 2) {}
    // 析构函数
    ~BTree() { delete root; }
    // 插入键 k
    void insert(int k);
    // 删除键 k
    void remove(int k) { remove(root, k); }
    // 搜索键 k 是否存在
    bool search(int k) { return (search(root, k).first != nullptr); }
    // 返回最小值
    int minimum() { return minimum(root)->keys[0]; }
    // 返回最大值
    int maximum() { return root->keys.back(); }
    // 中序遍历
    void inorderWalk() { inorderWalk(root); }
};

// 分裂结点x的第i个子节点
void BTree::splitChild(Node *x, int i)
{ // 使用这个函数的状况是: 插入一个新的结点后, 可能使得某些结点的元素数目超过作为B树的上限, 需要分裂

    Node *y = x->children[i]; // y是将要被分裂的子节点
    Node *z = new Node;       // 新分裂出来的结点, 包含y的后半部分

    // 将y的后半部分键复制到z
    z->keys.assign(y->keys.begin() + t, y->keys.end());

    // 如果y不是叶子结点, 将y的后半部分的子节点指针也复制到z
    if (!y->children.empty())
    {
        z->children.assign(y->children.begin() + t, y->children.end());
        y->children.resize(t); // 删除已经复制到z的指针
    }

    // 将y的中间键上移到x中, 并将z插入到x的子节点中
    x->keys.insert(x->keys.begin() + i, y->keys[t - 1]);
    x->children.insert(x->children.begin() + i + 1, z);

    // 缩减y的键的数量, 使其成为一个合法的B树结点
    y->keys.resize(t - 1);
}

// 插入键k到非满结点x中
void BTree::insertNonFull(Node *x, int k)
{
    int i = x->keys.size() - 1; // 从结点的最后一个键值开始比较

    // 检查当前结点是否为叶子结点(没有子节点)
    if (x->children.empty())
    {
        // 找到插入位置, 从右往左找到第一个比k小的键值的位置
        while (i >= 0 && k < x->keys[i])
        {
            --i;
        }
        // 找到了位置就在适当位置插入键值k
        x->keys.insert(x->keys.begin() + i + 1, k);
    }
    else // 如果x不是叶子结点, 则找到合适的子节点递归地插入
    {
        while (i >= 0 && k < x->keys[i])
        {
            --i;
        }
        ++i; // ++ 之后便是k应该插入的子节点的索引

        // 检查要插入的子结点是否已满
        if (x->children[i]->keys.size() == 2 * t - 1)
        {
            // 如果子结点已满, 分裂子节点
            splitChild(x, i);
            // 分裂后重新确定要插入的位置
            if (k > x->keys[i])
            {
                ++i;
            }
        }

        // 递归地将键k插入到合适的子节点
        insertNonFull(x->children[i], k);
    }
}

// 插入键值k
void BTree::insert(int k)
{
    Node *r = root; // 获取根节点

    // 如果根节点已满(即包含2*t-1个键)
    if (r->keys.size() == 2 * t - 1)
    {
        Node *s = new Node;
        root = s;

        // 将原来的根节点r作为新的根节点s的第一个子节点
        s->children.push_back(r);

        // 分裂原来的根节点r, 调整B树的结构(会多一层)
        splitChild(s, 0);

        // 在新的根节点s中插入键值k
        insertNonFull(s, k);
    }
    else // 如果根节点未满, 直接在根节点r中插入键值k
    {
        insertNonFull(r, k);
    }
}

// 在结点p中搜索键k
BTree::ChildPosition BTree::search(Node *p, int k)
{
    int i = 0;

    // 遍历结点p的键, 找到第一个大于等于k的位置
    while (i < p->keys.size() && k > p->keys[i])
        ++i;

    // 如果找到了键k, 返回它在结点p中的位置
    if (i < p->keys.size() && k == p->keys[i])
        return make_pair(p, i); // 返回结点p和键的位置i

    // 如果p是叶子结点且没有找到键k, 返回空指针
    else if (p->children.empty())
        return make_pair(nullptr, 0); // k不存在于树中, 返回空指针和0

    // 如果p不是叶子结点, 则继续递归搜索
    else
        return search(p->children[i], k);
}

// 找到以p为根的子树中的最小值
BTree::Node *BTree::minimum(Node *p)
{
    // 继续向左子树下探, 直到到达叶子结点
    while (!p->children.empty())
    {
        // 将当前结点更新为最左侧的叶子结点
        p = p->children[0];
    }

    // 返回最终的叶子结点, 这个叶子结点包含的最小的键值
    return p;
}

// 找到以p为根的子树的最大值
BTree::Node *BTree::maximum(Node *p)
{
    // 一直往右子树走, 直到到达叶子结点
    while (!p->children.empty())
    {
        // 当前结点更新为最右侧的子节点
        p = p->children.back();
    }

    // 返回最终的叶子结点, 这个叶子结点包含了最大的键值
    return p;
}

// 查找结点x中第i个键的前驱
//
// 前驱是小于给定键值的最大键值
// 如果结点x中第i个键右左子树, 那前驱键值就是左子树中的最大键值
// 否则, 前驱可能是同一个结点的前一个键, 或是遍历回父节点链中找到的键
BTree::ChildPosition BTree::predecessor(Node *x, int i)
{
    // 1. 如果存在左子树, 前驱是左子树中的最大值
    if (!x->children.empty())
    {
        // 访问目标键值左侧的子节点, 并在其子树中找到最大值
        x = maximum(x->children[i]);
        // 返回包含最大值的结点及其位置
        return make_pair(x, x->keys.size() - 1);
    }
    else if (i != 0) // 2. 如果目标键值不是第一个键值, 那么前驱是同一个结点中的前一个键
    {
        // 返回目标键值在当前结点中前一个位置的键
        return make_pair(x, i - 1);
    }

    // 3. 如果目标键是第一个键值且没有左子树, 需要从根节点往下回溯查找前驱
    int key = x->keys[i];
    Node *y = root;
    vector<ChildPosition> stk;
    // 从根节点开始找, 找到目标键值所在的结点路径, 并键路径压入栈中
    while (true)
    {
        // 如果找到的键值等于目标键值, 结束查找
        if (y->keys[0] == key)
            break;

        // 查找下一个子节点的位置
        for (int i = 0; i < y->keys.size() && key > y->keys[i]; ++i)
        {
        }
        // 将当前结点压入栈中
        stk.push_back(make_pair(y, i));
        // 继续在下一个子节点中查找
        y = y->children[i];
    }
    ChildPosition p;
    // 从栈中弹出结点, 查找前驱键值
    while (!stk.empty())
    {
        p = stk.back();
        stk.pop_back();
        // 如果当前结点不是第一个键值, 前驱是当前结点的一个键
        if (p.second != 0)
            return p;
    }

    // 4. 如果没有找到前驱, 返回空指针和0
    return make_pair(nullptr, 0);
}

// 茶渣结点x中第i个键的后继
BTree::ChildPosition BTree::successor(Node *x, int i)
{
    // 1. 如果x不是叶子结点, 后继在x的第i+1个叶子结点的最小键
    if (!x->children.empty())
    {
        // 找到子树中的最小结点
        x = minimum(x->children[i + 1]);
        // 返回这个最小结点及其第一个键
        return make_pair(x, 0);
    }
    else if (i != x->keys.size() - 1) // 2. 如果x是叶子结点, 且i不是最后一个键(那么这个结点中的下一个键就是后继)
    {
        // 返回下一个键
        return make_pair(x, i + 1);
    }

    // 3. 如果上面的条件都不满足, 说明速妖在树种上溯查找后继
    int key = x->keys[i];      // 保存当前键值
    Node *y = root;            // 从根节点开始向下查找
    vector<ChildPosition> stk; // 用于跟踪路径的栈
    // 找到对应键值的结点, 构建路径栈
    while (true)
    {
        // 找到了目标键就跳出循环
        if (y->keys.back() == key)
            break;
        // 找到目标键值在结点中的位置
        for (int i = 0; i < y->keys.size() && key > y->keys[i]; ++i)
        {
        }
        stk.push_back(make_pair(y, i)); // 将路径上的结点和位置入栈
        y = y->children[i];             // 移动到下一个子节点
    }
    ChildPosition p;
    // 从栈中回溯查找后继
    while (!stk.empty())
    {
        p = stk.back();                       // 取出路径中的结点
        stk.pop_back();                       // 移除取出的结点
        if (p.second != p.first->keys.size()) // 如果档期那系欸但还有未访问到的键
        {
            return p; // 返回未访问键的结点及其位置
        }
    }

    // 4. 如果没有找到后缀, 返回空
    return make_pair(nullptr, 0);
}

// 合并结点y到x中, 并删除结点z所指向的键
// 当删除结点的时候遇上下溢出(也就是结点数目小于m/2上取整时)会用到
void BTree::combine(Node *x, Node *y, ChildPosition z)
{
    // 将z.first结点中的z.second位置的键移到结点x中
    x->keys.push_back(z.first->keys[z.second]);

    // 将结点y中的所有键合并到x中
    for (int i = 0; i < t - 1; i++)
    {
        x->keys.push_back(y->keys[i]);
    }

    // 如果x有子节点, 将y的子节点合并到x中
    if (!x->children.empty())
    {
        x->children.insert(x->children.end(), y->children.begin(), y->children.end());
    }

    // 删除y结点, 释放内存
    delete y;

    // 从父节点z.first中删除z.second位置的键
    z.first->keys.erase(z.first->keys.begin() + z.second);

    // 从父节点z.first中删除z.second+1位置的结点指针
    z.first->children.erase(z.first->children.begin() + z.second + 1);

    // 如果父节点z.first已经没有键了, 更新根节点并删除z.first
    if (z.first->keys.empty())
    {
        root = z.first->children[z.second];
        delete z.first;
    }
}

// 从结点x中删除键k
void BTree::remove(Node *x, int k)
{
    // 初始化索引i, 用于在结点x中查找键k
    int i = 0;

    // 在结点x中查找键k的位置
    // 循环直到找到键k或达到结点x的末尾
    while (i < x->keys.size() && k > x->keys[i])
        ++i;

    // 检查是否找到了键k
    if (i < x->keys.size() && k == x->keys[i])
    {
        // true则为键k在结点x中, 需要根据结点x的来信进行处理

        // 情况一: 结点x是叶节点
        if (x->children.empty())
        {
            // 直接从叶子结点中删除键k
            x->keys.erase(x->keys.begin() + i);
        }
        else
        {
            // 情况二: 结点x是内部结点, 需要通过前驱和后继来删除键k
            // 如果左子节点有足够的键, 使用前驱替换键k 并递归删除前驱
            if (x->children[i]->keys.size() >= t)
            {
                // 找到键k的前驱
                ChildPosition pred = predecessor(x, i);
                // 用前驱替换键k
                x->keys[i] = pred.first->keys[pred.second];
                // 递归删除前驱
                remove(pred.first, pred.first->keys[pred.second]);
            }
            // 如果左子节点的键不足, 但是右子节点有足够的键, 使用后继替换键k, 并递归删除后继
            else if (x->children[i + 1]->keys.size() >= t)
            {
                // 找到键k的后继
                ChildPosition succ = successor(x, i);
                // 用后继替换键k
                x->keys[i] = succ.first->keys[succ.second];
                // 递归删除后继
                remove(succ.first, succ.first->keys[succ.second]);
            }
            // 如果左右子结点都没有足够的键, 则合并两个子节点
            else
            {
                // 合并键k的左右子节点
                combine(x->children[i], x->children[i + 1], make_pair(x, i));
                // 递归删除合并后的子节点中的键k
                remove(x->children[i], k);
            }
        }
    }
    // 情况三: 键k不再结点x中, 需要递归进入适当的子树
    else
    {
        // 如果结点x是叶节点, 那么没有子树, 键k也就不存在
        if (x->children.empty())
        {
            cout << "Key:" << k << " does not exist in this B-Tree" << endl;
            return;
        }

        // 检查是否是最后一个子节点
        bool isLastChild = (i == x->keys.size());

        // 如果目标子节点只有t-1个键, 需要合并或借用来保证有删除后足够的键
        if (x->children[i]->keys.size() == t - 1)
        {
            // 如果左兄弟有足够多的键, 就从左兄弟借一个键
            if (i != 0 && x->children[i - 1]->keys.size() >= t)
            {
                // 从左兄弟借一个键
                Node *child = x->children[i];
                Node *leftSibling = x->children[i - 1];

                // 将左兄弟的最后一个键移动道子节点child的开始
                child->keys.insert(child->keys.begin(), x->keys[i - 1]);
                // 将左兄弟的最后一个键移动到结点x的位置i - 1
                x->keys[i - 1] = leftSibling->keys.back();
                // 删除左兄弟的最后一个键
                leftSibling->keys.pop_back();

                // 如果左兄弟有子节点, 也需要移动子节点
                if (!leftSibling->children.empty())
                {
                    child->children.insert(child->children.begin(), leftSibling->children.back());
                    leftSibling->children.pop_back();
                }
            }
            // 如果左兄弟键不够, 但右兄弟有足够多的键, 从右兄弟借一个键
            else if (i != x->keys.size() && x->children[i + 1]->keys.size() >= t)
            {
                // 从右节点借一个键
                Node *child = x->children[i];
                Node *rightSibling = x->children[i + 1];

                // 将右兄弟的第一个键移动到子节点child的末尾
                child->keys.push_back(x->keys[i]);
                // 将右兄弟的第一个键移动到结点x的位置i
                x->keys[i] = rightSibling->keys.front();
                // 删除右兄弟的第一个键
                rightSibling->keys.erase(rightSibling->keys.begin());

                // 如果有子节点, 也要移动子节点
                if (!rightSibling->children.empty())
                {
                    child->children.push_back(rightSibling->children.front());
                    rightSibling->children.erase(rightSibling->children.begin());
                }
            }
            // 两边的兄弟结点都不够, 就只能合并子节点了
            else
            {
                // 合并子节点
                if (i != x->keys.size())
                {
                    combine(x->children[i], x->children[i + 1], make_pair(x, i));
                }
                else
                {
                    combine(x->children[i - 1], x->children[i], make_pair(x, i - 1));
                }
            }
        }

        // 递归删除目标键
        if (isLastChild && i > x->keys.size())
        {
            remove(x->children[i - 1], k);
        }
        else
        {
            remove(x->children[i], k);
        }
    }
}

// 中序遍历结点P
void BTree::inorderWalk(Node *p)
{
    int i;
    for (i = 0; i < p->keys.size(); i++)
    {
        if (!p->children.empty())
        {
            inorderWalk(p->children[i]);
        }
        cout << p->keys[i] << " ";
    }
    if (!p->children.empty())
    {
        inorderWalk(p->children[i]);
    }
}