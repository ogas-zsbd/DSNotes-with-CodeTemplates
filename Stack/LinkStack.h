#include <iostream>

using namespace std;

template <typename T>
class Node
{
private:
    Node(T t) : value(t), next(NULL){};
    Node() : next(NULL){};

public:
    T value;
    Node<T> *next;
};

template <typename T>
class LinkStack
{
public:
    LinkStack();
    ~LinkStack();
    bool isEmpty();
    int getSize();
    void push(T t);
    void pop();
    T getTop();

private:
    Node<T> *top;
    int cnt;
};

// 获取栈的大小
template <typename T>
int LinkStack<T>::getSize()
{
    return cnt;
}

// 判断栈是否为空
template <typename T>
bool LinkStack<T>::isEmpty()
{
    return cnt == 0;
}

// 入栈
template <typename T>
void LinkStack<T>::push(T t)
{
    Node<T> *pnode = new Node<T>(t);
    pnode->next = top->next;
    top->next = pnode;
    cnt++;
}

// 出栈
template <typename T>
void LinkStack<T>::pop()
{
    if (top->next != NULL) // 只有栈非空才能出栈
    {
        Node<T> *pdel = top->next;
        top->next = top->next->next; // top的指针指向栈顶的下一个，相当于top指针往下移
        delete pdel;                 // 删除出栈的结点
        cnt--;                       // 栈的长度--
    }
}

// 获取栈顶元素
template <typename T>
T LinkStack<T>::getTop()
{
    if (top->next != NULL)
    {
        return top->next->value;
    }
}