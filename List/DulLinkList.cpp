#include <iostream>

using namespace std;

// TODO: 利用模板再把类型优化一下

// 循环链表的结点
class ListNode
{
public:
    int data;        // 结点的存放的数据
    ListNode *prior; // 前驱结点的指针
    ListNode *next;  // 后继结点的指针

    // 构造函数
    ListNode()
    {
        prior = NULL;
        next = NULL;
        data = 0;
    }
};

// 循环链表
class LinkList
{
public:
    ListNode *head;                    // 头节点指针
    int len;                           // 链表长度
    LinkList();                        // 构造函数
    void add_to_end(int item);         // 在双向链表末尾添加一个结点
    void insert_node(int i, int item); // 在第i个位置插入一个结点
    ListNode *getPointer(int i);       // 查找并返回第i个结点的指针
    void delete_node(int i);           // 删除第i个位置的结点
};

// 构造函数
LinkList::LinkList()
{
    head = new ListNode(); // new一个结点作为头节点
    len = 0;               // 初始长度为0（头节点不算）
}

// 在双向链表末尾添加一个结点
void LinkList::add_to_end(int item)
{
    ListNode *nn = new ListNode();
    nn->data = item;
    nn->next = head;
    if (head->next == head)
    {
        nn->prior = head;
        head->next = nn;
        head->prior = nn;
    }
    else
    {
        nn->prior = getPointer(len);
        getPointer(len)->next = nn;
        head->prior = nn; // 这里是循环双向链表的特征
    }
    len++;
}

// 查找并返回第i个结点的指针
ListNode *LinkList::getPointer(int i)
{
    if ((i <= 0) || (i > len))
    {
        puts("查询位置错误");
    }
    else
    {
        ListNode *p; // p的作用和addNodeToEnd中的p类似
        p = head;
        for (int k = 1; k <= i; k++)
        {
            p = p->next;
        }
        return p; // 找到第i个结点的指针，并返回这个指针
    }
}

// 在第i个位置插入一个结点
void LinkList::insert_node(int i, int item)
{
    if ((i <= 0) || (i > len))
    {
        puts("插入位置错误");
    }
    if (i == len)
    {
        add_to_end(item);
    }
    else if (i == 1)
    {
        if (len == 0)
        {
            add_to_end(item);
        }
        else
        {
            ListNode *l = new ListNode();
            l->data = item;
            l->prior = head;
            l->next = getPointer(1);
            getPointer(1)->prior = l;
            head->next = l;
            len++;
        }
    }
    else
    {
        ListNode *s = new ListNode(); // 为要插入的创建一个新节点；
        s->data = item;               // 新结点的data是要插入的数据
        s->next = getPointer(i);      // 新节点的指针是原来第i个位置上的结点的指针
        getPointer(i)->prior = s;
        getPointer(i - 1)->next = s;
        s->prior = getPointer(i - 1);
        len++;
    }
}

// 删除第i个位置的结点
void LinkList::delete_node(int i)
{
    if (i <= 0 || i > len)
    {
        puts("删除位置错误");
    }
    else
    {
        if (i == 1)
        {
            if (len == 1)
            {
                head->next = head;
                head->prior = head; // 相当于只有head一个结点，就把所有的指针指向head结点
            }
            else
            {
                head->next = getPointer(2);  // head的next指针绕过1号结点指向2号
                getPointer(2)->prior = head; // 二号的前驱结点指向head
            }
        }
        else if (i == len)
        {
            getPointer(i - 1)->next = head;
            head->prior = getPointer(i - 1);
        }
        else
        {
            getPointer(i - 1)->next = getPointer(i + 1);
            getPointer(i)->prior = getPointer(i - 1);
        }
    }
    len--;
    // TODO: 这样算不算彻底删除这个结点？如何完整删除这个结点？
    delete getPointer(i);
}