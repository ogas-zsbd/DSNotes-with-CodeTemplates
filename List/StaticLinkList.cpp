#include <iostream>

using namespace std;

// TODO: 利用模板再把类型优化一下

const int MAXSIZE = 1000; // 存储空间初始分配量

class node
{
public:
    int cur; // 游标（cursor），为零时表示无指向（类似于空指针）
    int data;
};

class staticLinkList
{
private:
    node space[MAXSIZE];
    int len = 0;

public:
    void initList();                  // 初始化静态链表状态
    int newNode();                    // 模拟实现一个new一个node（new返回的是地址，用指针接收，自己实现的newnode也是返回一个数组下标，二者是类似的）
    void deleteNode(int i);           // 模拟实现delete一个node
    void insertItem(int i, int item); // 插入一个元素
    void deleteItem(int i);           // 删除一个元素
};

// 初始化静态链表状态
void staticLinkList::initList()
{
    int i;
    for (int i = 0; i < MAXSIZE - 1; i++) // 把数组第一个到倒数第一个的指针都赋为后继结点的数组下标
    {
        space[i].cur = i + 1; // 每个结点的指针都指向后继结点的数组下标
    }
    space[MAXSIZE - 1].cur = 0; // 最后一个结点的指针指向NULL
}

// 获取备用链表的首个下标（申请内存空间new）
int staticLinkList::newNode()
{
    int i = space[0].cur; // 获取备用链表的首个下标
    if (space[0].cur != 0)
    {
        space[0].cur = space[i].cur;
    }
    return i;
}

// 插入一个元素
void staticLinkList::insertItem(int i, int item)
{
    if (i < 0 || i > MAXSIZE)
    {
        puts("插入位置错误");
        return;
    }
    int pnew = newNode();
    if (i == 1) // 头插需要特判，因为末尾的等效于头指针的cur指向第一个元素
    {
        space[pnew].cur = space[MAXSIZE - 1].cur;
        space[MAXSIZE - 1].cur = pnew;
        space[pnew].data = item;
        len++;
    }
    else
    {
        int temp = space[MAXSIZE - 1].cur; // 创建一个迭代器参与循环，因为末尾的指针指向第一个元素，所以将其赋给temp
        for (int k = 1; k < i - 1; k++)
        {
            temp = space[temp].cur; // 将temp移到插入位置的前一个元素的下标
        }
        space[pnew].cur = space[temp].cur; // i的前一个位置元素的指针原来指向原来在i上的元素，在i位置上插入了一个新的元素之后就应该是新插入元素的指针指向原来在i这个位置上的元素
        space[temp].cur = pnew;            // 将新元素的下标赋给原来第i个位置的前一个的元素的cur
        space[pnew].data = item;
        len++;
    }
}

// 模拟实现delete一个node
void staticLinkList::deleteNode(int i)
{
    space[i].cur = space[0].cur; // 将当前备用链表的首个下标赋给将要释放的元素的游标，也就是说，这个被释放的元素将称为备用链表的首个元素。
    space[0].cur = i;            // 将被释放的元素的下标最为备用链表的首个下标
}

// 删除一个元素
void staticLinkList::deleteItem(int i)
{
    if (i < 0 || i > MAXSIZE - 2)
    {
        puts("插入位置错误");
        return;
    }
    if (i = 1) // 头删（删除第一个元素）需要特判，因为只需通过MAXSIZE - 1找到头就行了
    {
        int first = space[MAXSIZE - 1].cur;        // space[MAXSIZE - 1].cur存放的是静态链表第一个元素的下标，将其赋给first
        space[MAXSIZE - 1].cur = space[first].cur; // 将下标为first的指向的下标赋给MAXSIZE - 1的，相当于头指针指向了原来的第二个元素
        deleteNode(first);                         // 释放被删除的元素
        len--;                                     // 长度--
        return;
    }
    int temp = space[MAXSIZE - 1].cur; // 创建一个迭代器参与循环
    for (int k = 1; k < i - 1; k++)    // 一直沿着链表找找到i为止
    {
        temp = space[temp].cur;
    }
    // 删除方法和上面头删是一样的
    int pos = space[temp].cur;        // 将要删除位置的下标赋给pos
    space[temp].cur = space[pos].cur; // 将要删除位置的指针指向的位置赋给前一个的cur（也就是说从前一个开始跳过了要删除的位置）
    deleteNode(pos);                  // 释放删除位置的空间
    len--;                            // 长度--
    return;
}