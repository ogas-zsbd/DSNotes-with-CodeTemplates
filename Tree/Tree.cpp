#include <iostream>

using namespace std;

class TreeNode
{
public:
    int val;
    TreeNode *fstChild;   // 指向第一个子节点
    TreeNode *nxtSibling; // 指向下一个兄弟结点

    TreeNode(int x) : val(x), fstChild(nullptr), nxtSibling(nullptr) {}
};

void createTreeWithChildSibling(TreeNode *&root)
{
    root = new TreeNode(1);
    TreeNode *n1 = new TreeNode(2);
    TreeNode *n2 = new TreeNode(3);
    TreeNode *n3 = new TreeNode(4);
    TreeNode *n4 = new TreeNode(5);

    root->fstChild = n2;
    n2->nxtSibling = n3;
    n3->fstChild = n4;
    n3->nxtSibling = n5;
}
