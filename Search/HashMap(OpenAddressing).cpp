#include <iostream>
#include <vector>

using namespace std;

class HashMap
{
private:
    const int N = 200003;       // 哈希表大小, 选择大于200000的质数以减少冲突
    const int INF = 0x3f3f3f3f; // 用于表示空位置的特殊值
    vector<int> h;              // 哈希表数组

public:
    HashMap();
    // 在哈希表中查找key的位置, 如果x存在则返回值, 如果不存在则返回它应该插入的位置
    int find(int key);
    // 向哈希表中插入key
    void insert(int key);

private:
    // 计算哈希值
    int hash(int key);
};

// 构造函数, 初始化哈希表
HashMap::HashMap() : h(N, INF) {}

// 计算哈希值
int HashMap::hash(int key)
{
    return (key % N + N) % N;
}

// 在哈希表中查找key的位置
int HashMap::find(int key)
{
    int t = hash(key); // 计算哈希值
    while (h[t] != INF && h[t] != key)
    {
        t++;        // 移动到下一个位置
        if (t == N) // 如果超出数组范围, 就从头开始寻找
        {
            t = 0;
        }
    }

    // 如果找到key, 则返回其位置, 如果未找到, 则返回它应该插入的位置
    return t;
}

// 向哈希表中插入key
void HashMap::insert(int key)
{
    int pos = find(key); // 查找key应该插入的位置

    // 插入key到空位
    if (h[pos] == INF)
        h[pos] = key;
}