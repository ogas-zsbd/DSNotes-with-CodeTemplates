
/*
 * @Author: OGAS 2970143166@qq.com
 * @Date: 2024-10-22 17:03:24
 * @LastEditors: OGAS 2970143166@qq.com
 * @LastEditTime: 2024-12-06 23:26:30
 * @FilePath: \learnForDS\Queue\LinkLoopQueue.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>

using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node<T> *next;
    Node(T val) : data(val), next(nullptr) {};
};

template <typename T>
class LinkLoopQue
{
public:
    Node<T> *rear; // 仅使用尾指针

public:
    LinkLoopQue();
    ~LinkLoopQue();

    void clear();       // 置队空
    bool isEmpty();     // 判断队空
    void push(T val);   // 入队
    void pop();         // 出队
    T getFront();       // 获取对头元素
    T getRear();        // 获取队尾元素
    int getSize();      // 获取当前队列大小
    void remove(T val); // 删除指定元素
    void display();     // 打印当前队列
};

template <typename T>
LinkLoopQue<T>::LinkLoopQue()
{
    rear = new Node<T>(0); // 头节点
    rear->next = rear;     // 此时循环队列没有元素，尾指针指向自己
}

template <typename T>
LinkLoopQue<T>::~LinkLoopQue()
{
    clear();
    delete rear;
}

// 清空队列
template <typename T>
void LinkLoopQue<T>::clear()
{
    if (isEmpty())
        return;

    Node<T> *head = rear->next; // 临时保存头节点位置
    Node<T> *cur = head->next;
    while (cur != head)
    {
        Node<T> *delNode = cur;
        cur = cur->next;
        delete delNode;
    }
    rear->next = rear; // 清空之后队列中没有元素, rear->next指向自身.
}

// 队列判空
template <typename T>
bool LinkLoopQue<T>::isEmpty()
{
    return rear->next == rear; // 队列中完全没有元素时, 尾指针->next才会指向自己
}

// 入队
template <typename T>
void LinkLoopQue<T>::push(T val)
{
    Node<T> *newNode = new Node<T>(val);
    newNode->next = rear->next; // 新结点指向头结点
    rear->next = newNode;       // 原队尾指向新结点
    rear = newNode;             // 更新队尾指针
}

// 出队
template <typename T>
void LinkLoopQue<T>::pop()
{
    if (isEmpty())
    {
        throw runtime_error("队列为空");
        system("pause");
    }

    Node<T> *head = rear->next;      // 头结点
    Node<T> *firstNode = head->next; // 队头结点
    head->next = firstNode->next;    // 删除队头结点

    // 如果队列只有一个元素，需要调整rear指针为头结点
    if (firstNode == rear)
    {
        rear = head;
    }

    delete firstNode;
}

// 获取队头元素
template <typename T>
T LinkLoopQue<T>::getFront()
{
    if (isEmpty())
    {
        throw runtime_error("队列为空");
        system("pause");
    }
    return rear->next->next->data;
}

// 获取队尾元素
template <typename T>
T LinkLoopQue<T>::getRear()
{
    if (isEmpty())
    {
        throw runtime_error("队列为空");
        system("pause");
    }
    return rear->data;
}

// 获取当前队列大小
template <typename T>
int LinkLoopQue<T>::getSize()
{
    int size = 0;
    Node<T> *cur = rear->next;
    while (cur != rear)
    {
        size++;
        cur = cur->next;
    }
    return size;
}

// 删除指定元素
template <typename T>
void LinkLoopQue<T>::remove(T val)
{
    if (isEmpty())
    {
        try
        {
            throw runtime_error("队列为空");
        }
        catch (const runtime_error &e)
        {
            cout << e.what() << endl;
            system("pause");
        }
        return;
    }
    Node<T> *cur = rear->next;
    while (cur->next != rear)
    {
        if (cur->next->data == val)
        {
            Node<T> *delNode = cur->next;
            cur->next = delNode->next;
            if (delNode == rear)
            {
                rear = cur; // 更新尾指针
            }
            delete delNode;
            cout << "号码 " << val << " 已移出队列！" << endl;
            return;
        }

        cur = cur->next;
    }
    cout << "未找到号码 " << val << "，无法移除！" << endl;
}

// 打印当前队列
template <typename T>
void LinkLoopQue<T>::display()
{
    if (isEmpty())
    {
        throw runtime_error("队列为空");
        system("pause");
    }
    Node<T> *cur = rear->next->next;
    while (cur != rear->next)
    {
        cout << cur->data << " ";
        cur = cur->next;
    }
    puts("");
}