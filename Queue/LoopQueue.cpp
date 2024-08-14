#include <iostream>

using namespace std;

template <typename T>
class LoopQueue
{
public:
    LoopQueue(int c = 10);
    ~LoopQueue();

    bool isEmpty(); // 队列的判空
    int getSize();  // 获取队列的大小
    void push(T t); // 入堆
    void pop();     // 出队
    T getFront();   // 获取队头

private:
    int capacity;
    int begin;
    int end;
    T *queue;
};

template <typename T>
LoopQueue<T>::LoopQueue(int c = 10) : capacity(c), begin(0), end(0), queue(NULL)
{
    queue = new T[capacity];
}

template <typename T>
LoopQueue<T>::~LoopQueue()
{
    delete[] queue;
}

template <typename T>
bool LoopQueue<T>::isEmpty()
{
    if (begin == end)
        return false;
    return true;
}

template <typename T>
int LoopQueue<T>::getSize()
{
    return (end - begin + capacity) % capacity; // 因为是循环队列，有end < begin的情况，所以要通过 + capacity） % capacity 来得正数的size
}

template <typename T>
void LoopQueue<T>::push(T t)
{
    if ((end + 1) % capacity == begin) // 判断队列是否已满  end + 1 % capacity 是插入完这个元素之后，下一个要插的位置，因为是循环队列，所以要 % capacity来保证在数组范围之内
    {
        puts("队列已满！");
    }
    else
    {
        queue[end] = t;
        end = (end + 1) % capacity; // 如果是无限长的队列，那么end = end + 1，但是这是循环队列，要保证end在数组范围之内，所以要 % capacity
    }
}

template <typename T>
void LoopQueue<T>::pop()
{
    if (end == begin) // 判断队列是否为空
    {
        puts("队列为空！");
    }
    else
    {
        begin = (begin + 1) % capacity; // 队头往下一个位置进一位
    }
}

template <typename T>
T LoopQueue<T>::getFront()
{
    if (end == begin)
    {
        puts("队列为空！");
        return false;
    }
    return queue[begin];
}