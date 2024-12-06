#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct HuffmanNode
{
    char data;
    int weight;
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(char d, int w) : data(d), weight(w), left(nullptr), right(nullptr) {}
};

// 确认结点的优先级, 权重越小, 优先级越高
struct Compare
{
    bool operator()(HuffmanNode *a, HuffmanNode *b)
    {
        return a->weight > b->weight;
    }
};

class HuffmanTree
{
private:
    HuffmanNode *root;              // 哈夫曼树的根节点
    map<char, string> huffmanCodes; // 存储字符->编码的映射

public:
    HuffmanTree() : root(nullptr) {}
    ~HuffmanTree() { cleanup(root); }

    void generateCodes(HuffmanNode *node, string code); // 递归生成哈夫曼编码
    void cleanup(HuffmanNode *node);                    // 释放哈夫曼树内存
    void buildTree(map<char, int> &weights);            // 根据权重构建哈夫曼树
    string encode(string &text);                        // 将输入文本转换为二进制, 得到二进制串
    string decode(string &binary);                      // 将二进制串转换为文本
    void printCodes();                                  // 打印哈夫曼编码
};

void HuffmanTree::generateCodes(HuffmanNode *node, string code)
{
    if (node == nullptr)
        return;

    // 如果是叶子结点, 则将这个结点的编码加入映射表
    if (node->left == nullptr && node->right == nullptr)
    {
        huffmanCodes[node->data] = code;
    }

    // 递归生成左子树和右子树的编码
    generateCodes(node->left, code + "0");  // 左子树+0
    generateCodes(node->right, code + "1"); // 右子树+1
}

void HuffmanTree::cleanup(HuffmanNode *node)
{
    if (node == nullptr)
        return;
    cleanup(node->left);
    cleanup(node->right);
    delete node;
}

void HuffmanTree::buildTree(map<char, int> &weights)
{
    // 使用优先队列, 按照字符的权重排序
    priority_queue<HuffmanNode *, vector<HuffmanNode *>, Compare> priQue;

    // 将所有字符结点加入优先队列
    for (auto &pair : weights)
    {
        priQue.push(new HuffmanNode(pair.first, pair.second)); // 先创建结点加入队列, 结点间的关系还未建立
    }

    // 构建哈夫曼树
    // 每次从优先队列中取出两个频率最小的点, 合并成一个新的结点, 新结点的频率为两个结点频率之和
    while (priQue.size() > 1)
    {
        // 取出两个点
        HuffmanNode *left = priQue.top();
        priQue.pop();
        HuffmanNode *right = priQue.top();
        priQue.pop();

        // 创建父节点
        HuffmanNode *parent = new HuffmanNode('\0', left->weight + right->weight);
        parent->left = left;
        parent->right = right;

        // 将父节点加入优先队列
        priQue.push(parent);
    }

    // 优先队列中最后一个结点就是根节点
    root = priQue.top();

    // 生成每个字符的哈夫曼编码
    generateCodes(root, "");
}

string HuffmanTree::encode(string &text)
{
    string encoded; // text转换为二进制之后的字符串
    for (char c : text)
    {
        // 查找c这个字符是否存在于映射表中
        if (huffmanCodes.find(c) != huffmanCodes.end()) // 没有一直找到尾就说明存在
        {
            encoded += huffmanCodes[c];
        }
    }
    return encoded;
}

string HuffmanTree::decode(string &binary)
{
    string decoded;              // 将二进制串转换为文本
    HuffmanNode *current = root; // 从根节点开始遍历

    // 遍历二进制串
    for (char c : binary)
    {
        // 如果是0, 则往左子树走
        if (c == '0')
            current = current->left;
        // 如果是1, 则往右子树走
        else if (c == '1')
            current = current->right;

        // 如果到达叶子结点, 将对应的字符加入到结果中, 并将cur重置到根节点, 字符串继续往后遍历, 重新从根节点开始解码
        if (current->left == nullptr && current->right == nullptr)
        {
            decoded += current->data;
            current = root;
        }
    }

    return decoded;
}

void HuffmanTree::printCodes()
{
    for (auto &pair : huffmanCodes)
    {
        cout << pair.first << ": " << pair.second << endl;
    }
}