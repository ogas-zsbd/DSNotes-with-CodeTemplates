#include <iostream>
#include <vector>

using namespace std;

class HashMap
{
private:
    const int N = 100003; // 取大于操作次数的第一个质数，使冲突的概率最小
    vector<int> h;        // 哈希槽
    vector<int> e, ne;    // 数据链和链表指针(拉链寻址法, 拉出来的链(邻接表))
    int idx;              // 当前插入位置的索引

public:
    HashMap();
    ~HashMap() = default;

    // 向哈希表中插入一个值
    void insert(int key);
    // 在哈希表中查找一个值
    bool find(int key);

private:
    // 哈希函数
    int hash(int key);
};

// 构造函数
HashMap::HashMap() : h(N, -1), e(N), ne(N), idx(0) {}

// 哈希函数
int HashMap::hash(int key)
{
    return (key % N + N) % N; // 把原始数据映射到哈希表里的关键步骤, 避免出现负数, 所以mod完之后先加N再modN(这是避免出现负数的常见技巧)
}

// 向哈希表中插入一个数
void HashMap::insert(int key)
{
    int k = hash(key); // 计算哈希值
    e[idx] = key;      // 将x存入当前索引位置(头插法)
    ne[idx] = h[k];    // 将新结点的next指向原来的头节点
    h[k] = idx++;      // 更新头节点为插入位置
}

// 在哈希表中查找一个值
bool HashMap::find(int key)
{
    int k = hash(key);
    for (int i = h[k]; i != -1; i = ne[i]) // 沿着链表查找
    {
        if (e[i] == key)
            return true;
    }
    return false;
}