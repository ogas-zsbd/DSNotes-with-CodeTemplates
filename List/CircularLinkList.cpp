#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

// 循环链表的结点
template <typename T>
class ListNode
{
public:
    T data;          // 存放结点数据
    ListNode *next;  // 后继结点指针
    ListNode *prior; // 前驱结点指针

    // 默认构造函数
    ListNode() : data(T()), next(nullptr), prior(nullptr) {}

    // 带参数的构造函数
    ListNode(T value, ListNode<T> *n = nullptr, ListNode<T> *p = nullptr) : data(value), next(n), prior(p) {}
};

// 循环链表
template <typename T>
class CircularLinkList
{
public:
    CircularLinkList();         // 初始化
    ~CircularLinkList();        // 销毁
    void clear();               // 清空链表
    bool isEmpty();             // 判空
    int length();               // 求长度
    T getElement(int i);        // 查找第i个位置的元素
    int locateElement(T item);  // 定位某个元素的位置
    T getPredecessor(int i);    // 获取第i个位置的前驱元素
    T getSuccessor(int i);      // 获取第i个位置的后继元素
    void insert(int i, T item); // 插入元素到第i个位置
    void remove(int i);         // 删除第i个位置的元素
    void insertToEnd(T item);   // 添加数据项成为线性表的最后一个元素
    void insertToHead(T item);  // 添加数据项成为线性表的第一个元素
    ListNode<T> *getHead();     // 获取头节点指针
    ListNode<T> *getTail();     // 获取尾结点指针
    void display();             // 遍历输出线性表
    vector<T> toArray();        // 将链表转化为数组

private:
    ListNode<T> *head; // 头节点指针
    ListNode<T> *tail; // 尾节点指针
    int len;           // 链表长度
};

// 构造函数
template <typename T>
CircularLinkList<T>::CircularLinkList()
{
    head = new ListNode<T>(); // 创建头节点
    tail = new ListNode<T>(); // 创建尾节点
    // 初始化头尾结点的指针, 使其具有循环的特性
    head->next = tail;
    tail->next = head;
    head->prior = tail;
    tail->prior = head;
    len = 0;
}

// 析构函数
template <typename T>
CircularLinkList<T>::~CircularLinkList()
{
    clear();
    delete head; // 删除头节点
    delete tail; // 删除尾节点
}

// 获取头节点指针
template <typename T>
ListNode<T> *CircularLinkList<T>::getHead()
{
    return head;
}

// 获取尾结点指针
template <typename T>
ListNode<T> *CircularLinkList<T>::getTail()
{
    return tail;
}

// 清空链表
template <typename T>
void CircularLinkList<T>::clear()
{
    while (!isEmpty())
    {
        remove(1); // 从头节点开始删除, 直到空为止
    }
}

// 判空
template <typename T>
bool CircularLinkList<T>::isEmpty()
{
    return len == 0;
}

// 求长度
template <typename T>
int CircularLinkList<T>::length()
{
    return len;
}

// 查找某个位置的元素
template <typename T>
T CircularLinkList<T>::getElement(int i)
{
    try
    {
        // 链表中的元素在[1,len]范围内, 其余抛出异常
        if (i < 1 || i > len)
        {
            throw out_of_range("索引超出范围");
            system("pause");
        }
        // 从头开始遍历链表找出第i个位置的元素
        ListNode<T> *current = head->next;
        for (int j = 1; j < i; j++)
        {
            current = current->next;
        }
        return current->data;
    }
    catch (const exception &e)
    {
        cout << "发生异常: " << e.what() << "，位置: " << __FILE__ << "，行号: " << __LINE__ << endl;
        system("pause");
        throw; // 重新抛出异常
    }
}

// 定位某个元素的位置
template <typename T>
int CircularLinkList<T>::locateElement(T item)
{
    if (isEmpty())
    {
        puts("这是一个空表");
        return -1;
    }
    // 从头开始遍历链表, 找出data==item的结点
    ListNode<T> *current = head->next;
    for (int i = 1; i <= len; i++)
    {
        if (current->data == item)
            return i;
        current = current->next;
    }
    return -1; // 未找到
}

// 求前驱元素
template <typename T>
T CircularLinkList<T>::getPredecessor(int i)
{
    try
    {
        if (i < 1 || i > len)
        {
            throw out_of_range("索引超出范围");
            system("pause");
        }
        // 对头节点的特判
        if (i == 1)
        {
            return tail->prior->data; // 由于是循环双向链表, 第一个元素的前驱是最后一个元素
        }
        ListNode<T> *current = head->next;
        for (int j = 1; j < i; j++)
        {
            current = current->next;
        }
        return current->prior->data;
    }
    catch (const exception &e)
    {
        cout << "发生异常: " << e.what() << "，位置: " << __FILE__ << "，行号: " << __LINE__ << endl;
        system("pause");
        throw; // 重新抛出异常
    }
}

// 求后继元素
template <typename T>
T CircularLinkList<T>::getSuccessor(int i)
{
    try
    {
        if (i < 1 || i > len)
        {
            throw out_of_range("索引超出范围");
            system("pause");
        }
        // 对最后一个元素的特判
        if (i == len)
        {
            return head->next->data; // 由于是循环双向链表, 最后一个元素的后继是第一个元素
        }
        ListNode<T> *current = head->next;
        for (int j = 1; j < i; j++)
        {
            current = current->next;
        }
        return current->next->data;
    }
    catch (const exception &e)
    {
        cout << "发生异常: " << e.what() << "，位置: " << __FILE__ << "，行号: " << __LINE__ << endl;
        system("pause");
        throw; // 重新抛出异常
    }
}

// 插入
template <typename T>
void CircularLinkList<T>::insert(int i, T item)
{
    try
    {
        if (i < 1 || i > len + 1)
        {
            throw out_of_range("插入位置超出范围");
            system("pause");
        }

        // 在链表长度+1的位置即是在链表尾部插入, 由于我们存储了尾结点指针, 所以能以O(1)的方式插入
        if (i == len + 1)
        {
            ListNode<T> *newNode = new ListNode<T>(item);
            newNode->next = tail;
            newNode->prior = tail->prior;
            tail->prior->next = newNode;
            tail->prior = newNode;

            len++;
            return;
        }

        ListNode<T> *newNode = new ListNode<T>(item);
        ListNode<T> *current = head;
        for (int j = 1; j < i; j++)
        {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prior = current;
        current->next->prior = newNode;
        current->next = newNode;
        len++;
    }
    catch (const exception &e)
    {
        cout << "发生异常: " << e.what() << "，位置: " << __FILE__ << "，行号: " << __LINE__ << endl;
        system("pause");
        throw; // 重新抛出异常
    }
}

// 删除
template <typename T>
void CircularLinkList<T>::remove(int i)
{
    try
    {
        if (i < 1 || i > len)
        {
            throw out_of_range("删除位置超出范围");
            system("pause");
        }

        // 删除同理, 如果我们要删除最后一个结点, 由于我们存储了尾结点指针, 所以可以用O(1)的时间删除
        if (i == len)
        {
            ListNode<T> *toDelete;
            ListNode<T> *current = tail->prior->prior;
            toDelete = tail->prior;
            current->next = tail;
            tail->prior = current;
            delete toDelete;
            len--;
            return;
        }

        ListNode<T> *toDelete;
        ListNode<T> *current = head;
        for (int j = 1; j < i; j++)
        {
            current = current->next;
        }
        toDelete = current->next;
        current->next = toDelete->next;
        toDelete->next->prior = current;
        delete toDelete;
        len--;
    }
    catch (const exception &e)
    {
        cout << "发生异常: " << e.what() << "，位置: " << __FILE__ << "，行号: " << __LINE__ << endl;
        system("pause");
        throw; // 重新抛出异常
    }
}

// 遍历输出线性表
template <typename T>
void CircularLinkList<T>::display()
{
    if (isEmpty())
    {
        puts("这是一个空表");
        return;
    }
    ListNode<T> *current = head->next;
    while (current != tail)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// 添加数据项成为线性表的第一个元素
template <typename T>
void CircularLinkList<T>::insertToHead(T item)
{
    insert(1, item);
}

// 添加数据项成为线性表的最后一个元素
template <typename T>
void CircularLinkList<T>::insertToEnd(T item)
{
    insert(len + 1, item);
}

// 将链表转换为数组
template <typename T>
vector<T> CircularLinkList<T>::toArray()
{
    vector<T> result;
    if (isEmpty())
    {
        return result;
    }
    ListNode<T> *current = head->next;
    while (current != tail)
    {
        result.push_back(current->data);
        current = current->next;
    }
    return result;
}