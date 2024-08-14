#include <iostream>

using namespace std;

template <typename T>
class Node
{
public:
    Node(T t) : value(t), next(NULL) {}
    Node() = default;

    T value;
    Node<T> *next;
};

template <typename T>
class LinkQueue
{
public:
    LinkQueue();
    ~LinkQueue();

    bool isEmpty();
    int getSize();
    void pop();
    void push(T t);
    T getFront();

private:
    Node<T> *phead;
    Node<T> *pend;
    int cnt;
};

template <typename T>
LinkQueue<T>::LinkQueue() : phead(NULL), pend(NULL), cnt(0)
{
    phead = new Node<T>();
    pend = phead;
    cnt = 0;
}

template <typename T>
LinkQueue<T>::~LinkQueue()
{
    while (phead->next != NULL) // 遍历删除这个链表
    {
        Node<T> *pnode = phead;
        phead = phead->next;
        delete pnode; // 释放当前结点的内存
    }
}

template <typename T>
bool LinkQueue<T>::isEmpty()
{
    return cnt == 0;
}

template <typename T>
int LinkQueue<T>::getSize()
{
    return cnt;
}

// 在队尾插入
template <typename T>
void LinkQueue<T>::push(T t)
{
    Node<T> *pnode = new Node<T>(t); // 创建一个新的结点，并以pnode指针指向它
    pend->next = pnode;
    pend = pnode;
    cnt++;
}

// 在队首弹出
template <typename T>
void LinkQueue<T>::pop()
{
    if (cnt == 0)
    {
        puts("队列为空！");
    }
    else
    {
        Node<T> *pnode = phead->next;
        phead->next = phead->next->next;
        delete pnode;
        cnt--;
    }
}

// 获取队首元素
template <typename T>
T LinkQueue<T>::getFront()
{
    return phead->next->value;
};