#include <iostream>

using namespace std;

// TODO: 实现动态开辟数组的大小

template <typename T>
class ArrayStack
{
public:
    ArrayStack(int s = 10); // 默认的栈容量为10
    ~ArrayStack();

    T getTop();     // 获取栈顶元素
    void push(T t); // 入栈
    void pop();     // 出栈
    bool isEmpty(); // 判断是否为空
    int getSize();  // 获取栈的大小

private:
    int top = -1; // 栈顶指针，指向-1代表空栈
    int size = 0; // 栈的最大容量
    T *array;     // 用数组存储栈
};

template <typename T>
ArrayStack<T>::ArrayStack(int s) : size(s), top(-1)
{
    array = new T[size];
}

// 判断是否为空
template <typename T>
bool ArrayStack<T>::isEmpty()
{
    return top == -1; // tp[为-1时栈空，返回true
}

// 返回栈的大小
template <typename T>
int ArrayStack<T>::getSize()
{
    return top + 1; // 因为索引是从零开始，大小是索引 + 1
}

// 入栈
template <typename T>
void ArrayStack<T>::push(T t)
{
    if (top + 1 != size) // 先判断是否栈满
    {
        array[++top] = t; // 先在数组中top的位置上赋予t，然后top++
    }
    else
    {
        puts("栈满！");
    }
}

// 出栈
template <typename T>
void ArrayStack<T>::pop()
{
    if (top + 1 != 0) // 先判断是否为空栈，如果是空就没有元素可以返回
    {
        top--;
    }
    else
    {
        puts("栈空！");
    }
}

// 获取栈顶元素
template <typename T>
T ArrayStack<T>::getTop()
{
    if (top != -1)
    {
        return array[top];
    }
}