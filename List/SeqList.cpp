#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

// TODO: 利用模板再把类型优化一下

class SeqList
{
private:
    int *list;    // 顺序表存储的数组
    int maxsize;  // 最大表长
    int size = 0; // 当前表长

public:
    SeqList();                        // 构造函数
    ~SeqList();                       // 析构函数
    void list_int(int n);             // 输入n个数，并依次存入顺序表从0开始的位置
    int getSize();                    // 返回当前表长
    void insertItem(int i, int item); // 把item插入到顺序表的第i个位置
    void deleteItem(int i);           // 删除顺序表中的第i个数据
    void printItem(int i);            // 打印顺序表中的第i个数据
    void showList();                  // 打印整个顺序表

    void multiInsertItem(int i, int n, int *item); // 从i开始，连续插入来自item数组的n个数据
    void multiDeleteItem(int i, int n);            // 从i开始，将i及其之后的n个数据全部删除
    void sortList();                               // 为顺序表内元素排序
    int *getList();                                // 返回数组
    SeqList mergeList(SeqList &a, SeqList &b);     // 合并两个顺序表
    void circleMoveList(int d, int n);             // 循环排序，类似于abc往后移两位变成cba?
} seqlist;

// 构造函数
// 构造一个顺序表，最大的表长是maxsize，当前表的大小是0，内存中分配maxsize大小的空间
SeqList::SeqList()
{
    maxsize = 1000;
    size = 0;
    list = new int[maxsize];
}

// 析构函数
// 释放list数组的内存
SeqList::~SeqList()
{
    delete[] list;
}

// 初始化顺序表
// 输入n个数，并依次存入顺序表从0开始的位置
void SeqList::list_int(int n)
{
    for (int i = 0; i < n; i++)
    {
        cin >> list[i];
    }
    size = n; // 当前的表长是n
}

// 返回当前表长
int SeqList::getSize()
{
    for (int i = 0; i < 1000; i++)
    {
        // 遍历整个数组，直到找到一个没有被赋过值的，即为表的结尾
        if (list[i] == '\0')
        {
            size = i + 1; // 因为数组是从0开始的，所以size是索引值 + 1
            break;
        }
    }

    return size;
}

// 把item插入到顺序表的第i个位置
void SeqList::insertItem(int i, int item)
{
    // TODO: 加入链表是否已满的判断，已满就不能继续加了（也就是判断数组最后一位是否为空）

    if (i > 0 && i <= size + 1) // 判断插入的位置是否正确：i > 数组的起始0 && i < 当前的表的大小 + 1（也就是在当前末尾插入）
    {                           // 首先把i，以及i后面的所有元素往后移一位（如果是在末尾插入，不用挪后面的位置，也就是不会进入循环）
        for (int k = size; k >= i; k--)
        {
            list[k] = list[k - 1];
        }
        list[i - 1] = item; // 第i个位置即为数组中下标为i - 1，把item存入这个位置
        size++;
    }
    else
        cout << "插入位置错误！" << endl;
}

// 删除顺序表中的第i个数据
void SeqList::deleteItem(int i)
{
    // 判断删除的地方是否合法（和上面插入判断条件有略微不同，因为i不是数组的下标，只需要在0 ~ size之内就行了）
    if (i > 0 && i <= size)
    {
        size--; // 因为删除了一个元素，就先把表的大小减一
        // 从i开始（也就是数组下标的i - 1），将i后面的所有元素向前挪一位（最后一位回被未初始化的数据覆盖掉，所以不用特判）
        for (int k = i - 1; k < size; k++)
        {
            list[k] = list[k + 1];
        }
    }
    else
        cout << "删除位置错误！" << endl;
}

// 打印指定元素
void SeqList::printItem(int i)
{
    // 条件和删除类似
    if (i > 0 && i <= size)
    {
        cout << list[i - 1] << endl;
    }
    else
        puts("不存在这个数据！");
}

// 打印整个顺序表
void SeqList::showList()
{
    cout << "该顺序表的表长是：" << size << endl;
    for (int i = 0; i < size; i++)
    {
        cout << list[i] << " ";
    }
    puts("");
}

// 从i开始，连续插入来自item数组的n个数据
void SeqList::multiInsertItem(int i, int n, int *item)
{
    // TODO: 加入顺序表的空间是否还够n个元素插入的判断（也就是检查maxsize - n - 1是否未被初始化）

    // 检查插入条件类似插入一个元素
    if (i > 0 && i <= size + 1)
    {
        // 把i后面的n个元素都往后移n位，为要插入的空出位置
        for (int k = size + n - 1; k > i; k--)
        {
            list[k] = list[k - n];
        }
        for (int k = i - 1; k < i - 1 + n; k++)
        {
            list[k] = item[k - i + 1];
        }
        size += n; // 插入了n个元素，size += n
    }
    else
        cout << "插入位置错误！" << endl;
}

// 从i开始，将i及其之后的n个数据全部删除
void SeqList::multiDeleteItem(int i, int n)
{
    // TODO: 添加一个条件，i 之后的 n个元素是否会超出maxsize
    // 条件类似删除单个元素
    if (i > 0 && i <= size)
    {
        size -= n; // 删除了n个元素，size就要减n
        // 从第i个开始（数组下标的i - 1），依次将n个之后的数据向前挪n位
        for (int k = i - 1; k < size; k++)
        {
            list[k] = list[k + n];
        }
    }
    else
        puts("删除元素错误！");
}

// 为顺序表内元素排序（从小到大排）
void SeqList::sortList()
{ // TODO: 优化排序算法
    sort(list, list + size);
}

// 返回数组
int *SeqList::getList()
{
    return list; // 数组名相当于指针
}

// 合并两个顺序表
SeqList SeqList::mergeList(SeqList &a, SeqList &b)
{
    SeqList res;
    // 相当于把两个表分别插入res表
    res.multiInsertItem(0, a.getSize(), a.getList()); // 先插入a，从零开始，长度为a的长度，分别将a的元素插入res中
    res.multiInsertItem(a.getSize() + 1, b.getSize(), b.getList());
    // res.sortList();           //按需为新表排序
    return res;
}

// 顺序表循环移位
void SeqList::circleMoveList(int d, int n) // 每个向后移n位，d代表方向，0为左、1为右
{
    // 先创造一个临时的表，先把原表复制到临时表里，然后按照规律把临时表里的数据赋给原表，最后记得把临时表释放
    // 创建临时表
    int *temp = new int[size];
    // 原表复制给临时表
    temp = list;
    // 按照规律赋值
    if (d == 0) // 左移
    {
        for (int i = 0; i < size - n; i++)
        {
            list[i] = temp[i + n]; // 因为是往左移，所以是右边的把左边的给覆盖掉，直到size - n为止，因为temp的前n个被移到末尾去了
        }
        for (int i = size - n; i < size; i++)
        {
            list[i] = temp[i - (size - n)]; // 其实就是temp的前n个赋给list的后n个
        }
    }
    // 释放临时表
    delete[] temp;
}