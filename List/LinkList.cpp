#include <iostream>
#include <cstdio>

using namespace std;

// TODO: 利用模板再把类型优化一下

// 线性表-单链表的结点
class ListNode
{
public:
    int data;       // 存放结点数据（数据域）
    ListNode *next; // 下一个结点指针（指针域）

    // 构造函数
    ListNode()
    {
        next = NULL;
        data = 0;
    }
};

// 线性表-单链表
class LinkList
{
public:
    ListNode *head;                                      // 头节点指针
    int len;                                             // 链表长度
    LinkList();                                          // 构造函数
    ~LinkList();                                         // 析构函数
    void addNodeToEnd(int x);                            // 在链表的最后插入数据x
    ListNode *getPointer(int i);                         // 查找并返回第i个结点的指针
    void getData(int i);                                 // 打印第i个结点的数据
    void insertNode(int i, int item);                    // 在第i个位置插入一个data为item的结点
    void deleteNode(int i);                              // 删除第i个结点
    void displayAllNodes();                              // 打印单链表中的所有结点
    void swapNodes(int pa, int pb);                      // 将单链表中第pa、pb个两个结点互换
    void sortForLinkList();                              // 单链表的排序
    LinkList mergeLinkLists(LinkList &La, LinkList &Lb); // 合并两个单链表，生成一个新的单链表并返回
    void deleteLinkList(LinkList &L);                    // 单链表的整表删除
};

// 构造函数
LinkList::LinkList()
{
    head = new ListNode(); // 在构造函数中创造头节点
    len = 0;               // 只有头节点，长度为零（头节点不算长度）
}

// 析构函数
LinkList::~LinkList()
{
    head = NULL; // 头指针指向空即为把这个表置空
}

// 在链表的最后插入数据x
void LinkList::addNodeToEnd(int x)
{
    ListNode *l = new ListNode(); // 创建一个新节点
    l->data = x;                  // 该节点的数据域存入数据
    if (head->next == NULL)       // 如果还没有一个结点，把新增的结点作为头指针指向的下一个结点
    {
        head->next = l;
    }
    else
    {
        ListNode *p; // 新建一个p作为迭代器，从头指针开始沿着链表找，直到找到结尾（NULL）为止
        p = head;
        for (int k = 1; k <= len; k++)
        {
            p = p->next; // 把p的下一个结点中的指针赋给p
        }
        p->next = l; // 找到最末尾，把最后一个结点的指针指向新加入的指针（新建的指针自带一个指向NULL的指针）
    }

    len++; // 插入一个结点之后，链表的长度++
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

// 打印第i个结点的数据
void LinkList::getData(int i)
{
    if ((i <= 0) || (i > len))
    {
        puts("输出位置错误");
    }
    else
    {
        int x;
        x = getPointer(i)->data;
        printf("第 %d 个结点存储的数据是：%d \n", i, x);
    }
}

// 在第i个位置插入一个data为item的结点
void LinkList::insertNode(int i, int item)
{
    if ((i <= 0) || (i > len))
    {
        puts("插入位置错误");
    }
    else
    {
        ListNode *l = new ListNode(); // 为要插入的创建一个新节点；
        l->data = item;               // 新结点的data是要插入的数据
        l->next = getPointer(i);      // 新节点的指针是原来第i个位置上的结点的指针
        getPointer(i - 1)->next = l;  // 原来第i个结点的前一个结点，也就是第i - 1个结点的指针要指向新加入的结点
        len++;                        // 新加了一个结点，链表长度++
    }
}

// 删除第i个结点
void LinkList::deleteNode(int i)
{
    if ((i <= 0) || (i > len))
    {
        puts("删除位置错误");
    }
    else
    {
        ListNode *nodeToDelete = getPointer(i);
        if (i == 1)
        {
            head->next = getPointer(2);
        }
        else if (i == len)
        {
            getPointer(i - 1)->next = NULL;
        }
        else
        {
            getPointer(i - 1)->next = getPointer(i + 1); // 把i的上一个结点点的指针指向i的下一个结点，就会在遍历中自动跳过第i个结点，相当于删除了第i个结点
        }
        delete nodeToDelete; // 释放被删除结点的内存
        len--;               // 删除了一个结点，链表的长度--
    }
}

// 打印单链表中的所有结点
void LinkList::displayAllNodes()
{
    ListNode *p;
    p = head;
    while (p->next != NULL)
    {
        p = p->next;
        cout << p->data << " ";
    }
    puts("");
}

// 将单链表中第pa、pb个两个结点互换
void LinkList::swapNodes(int pa, int pb)
{
    if (pa != pb && pa > 0 && pa <= len && pb > 0 && pb <= len) // 当两个结点的位置都合法时
    {
        // 获取pa、pb两个结点
        ListNode *p = getPointer(pa);
        ListNode *q = getPointer(pb);

        // 获取pa、pb的前驱结点（因为要改变交换结点和前一个结点的指针，所以需要前驱结点
        // GPT优化之后的代码，挺简洁的就抄了过来，把大量的ifelse判断转化成了三目的运算，之后可以借鉴
        ListNode *p_before = (pa == 1) ? NULL : getPointer(pa - 1); // 如果pa是第一个结点，p的前驱结点就是NULL，不是第一个的话，前驱是pa - 1
        ListNode *q_before = (pb == 1) ? NULL : getPointer(pb - 1);

        // 更新前驱结点的指针（指向交换后的结点）
        if (p_before)
            p_before->next = q; // if (p_before) 等价于 if (p_before != NULL)
        else
            head = q;
        if (q_before)
            q_before->next = p;
        else
            head = p;

        // 交换结点的指针
        ListNode *temp = p->next;
        p->next = q->next;
        q->next = temp;
    }
    else
        puts("结点不合法");
}

// 单链表的排序
void LinkList::sortForLinkList()
{
    // TODO: 把冒泡排序能否替换为更高效的排序
    for (int i = 1; i <= len; i++)
        for (int j = i; j <= len; j++)
            if (getPointer(i)->data > getPointer(j)->data)
                swapNodes(i, j);
}

// 合并两个单链表，生成一个新的单链表并返回
LinkList LinkList::mergeLinkLists(LinkList &La, LinkList &Lb)
{
    LinkList L; // 结果数组

    // 将La里的结点逐个插入L中
    ListNode *p;
    p = La.head;
    for (int i = 1; i <= La.len; i++)
    {
        p = p->next;
        L.insertNode(i, p->data);
    }

    // 将Lb里的结点逐个插入L中（采用了类似的头插法，Lb的第一个插入L的第一个位置，之后继续插入，Lb的最后一个的下一个是La的第一个）
    p = Lb.head;
    for (int i = 1; i <= Lb.len; i++)
    {
        p = p->next;
        L.insertNode(i, p->data);
    }

    // 给L排序
    L.sortForLinkList();

    return L;
}

// 单链表的整表删除
void LinkList::deleteLinkList(LinkList &L)
{
    ListNode *p;
    ListNode *q;
    p = head->next; // p指向第一个结点
    while (p != NULL)
    {
        q = p->next;
        delete p;
        p = q;
    }
    head = NULL; // 头指针置为空
}