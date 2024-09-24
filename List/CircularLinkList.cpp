#include <iostream>

using namespace std;

// 循环链表的结点
template <typename T>
class ListNode
{
public:
    T data;         // 存放结点数据
    ListNode *next; // 下一个结点指针

    // 构造函数
    ListNode(T value) : data(value), next(nullptr) {}
};

// 循环链表
template <typename T>
class CircularLinkList
{
public:
    CircularLinkList();          // 初始化
    ~CircularLinkList();         // 销毁
    void clear();                // 清空链表
    bool isEmpty();              // 判空
    int length();                // 求长度
    T getElement(int i);         // 查找某个位置的元素
    int locateElement(T &item);  // 定位某个元素的位置
    void insert(int i, T &item); // 插入
    void remove(int i);          // 删除
    T getPredecessor(int i);     // 求前驱元素
    T getSuccessor(int i);       // 求后继元素
    void display();              // 遍历输出线性表

private:
    ListNode<T> *head; // 头节点指针
    ListNode<T> *tail; // 尾节点指针
    int len;           // 链表长度
};

// 构造函数
template <typename T>
CircularLinkList<T>::CircularLinkList()
{
    head = nullptr;
    tail = nullptr;
    len = 0;
}

// 析构函数
template <typename T>
CircularLinkList<T>::~CircularLinkList()
{
    clear();
}

// 清空链表
template <typename T>
void CircularLinkList<T>::clear()
{
    while (!isEmpty())
    {
        remove(1);
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
    if (i < 1 || i > len)
        throw out_of_range("索引超出范围");
    ListNode<T> *current = head;
    for (int j = 1; j < i; j++)
    {
        current = current->next;
    }
    return current->data;
}

// 定位某个元素的位置
template <typename T>
int CircularLinkList<T>::locateElement(T &item)
{
    if (isEmpty())
        return -1;
    ListNode<T> *current = head;
    for (int i = 1; i <= len; i++)
    {
        if (current->data == item)
            return i;
        current = current->next;
    }
    return -1; // 未找到
}

// 插入
template <typename T>
void CircularLinkList<T>::insert(int i, T &item)
{
    if (i < 1 || i > len + 1)
        throw out_of_range("插入位置超出范围");
    ListNode<T> *newNode = new ListNode<T>(item);

    if (i == 1) // 在头部插入
    {
        if (isEmpty())
        {
            head = tail = newNode;
            tail->next = head; // 循环链表
        }
        else
        {
            newNode->next = head;
            head = newNode;
            tail->next = head; // 更新尾指针
        }
    }
    else // 在其他位置插入
    {
        ListNode<T> *current = head;
        for (int j = 1; j < i - 1; j++)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        if (i == len + 1) // 插入到末尾，更新尾指针
        {
            tail = newNode;
        }
    }
    len++;
}

// 删除
template <typename T>
void CircularLinkList<T>::remove(int i)
{
    if (i < 1 || i > len)
        throw out_of_range("删除位置超出范围");

    ListNode<T> *toDelete;
    if (i == 1) // 删除头结点
    {
        toDelete = head;
        if (len == 1) // 只有一个节点
        {
            head = tail = nullptr;
        }
        else
        {
            head = head->next;
            tail->next = head; // 更新尾指针
        }
    }
    else // 删除其他节点
    {
        ListNode<T> *current = head;
        for (int j = 1; j < i - 1; j++)
        {
            current = current->next;
        }
        toDelete = current->next;
        current->next = toDelete->next;
        if (i == len) // 删除尾节点，更新尾指针
        {
            tail = current;
        }
    }
    delete toDelete;
    len--;
}

// 求前驱元素
template <typename T>
T CircularLinkList<T>::getPredecessor(int i)
{
    if (i < 1 || i > len)
        throw out_of_range("索引超出范围");
    if (i == 1)
        return tail->data; // 循环特性
    ListNode<T> *current = head;
    for (int j = 1; j < i - 1; j++)
    {
        current = current->next;
    }
    return current->data;
}

// 求后继元素
template <typename T>
T CircularLinkList<T>::getSuccessor(int i)
{
    if (i < 1 || i > len)
        throw out_of_range("索引超出范围");
    if (i == len)
        return head->data; // 循环特性
    ListNode<T> *current = head;
    for (int j = 1; j < i; j++)
    {
        current = current->next;
    }
    return current->next->data;
}

// 遍历输出线性表
template <typename T>
void CircularLinkList<T>::display()
{
    if (isEmpty())
        return;
    ListNode<T> *current = head;
    do
    {
        cout << current->data << " ";
        current = current->next;
    } while (current != head);
    cout << endl;
}
