#include <iostream>
#include <string>
#include <cstring>

using namespace std;

#define maxsize 20

class String
{
public:
    void initStr(String *p);                         // 初始化串
    int getLen(String *p);                           // 获取串的长度
    void createStr(String *p);                       // 创建串
    bool emptyStr(String *p);                        // 判断串是否为空
    void printfStr(String *p);                       // 输出串
    void strAssign(String *p, char temp[]);          // 生成一个其值等于字符串chars的串
    void strCopy(String *p1, String *p2);            // 如果p2不为空，就由串p2复制得串p1
    void clearStr(String *p);                        // 将串S清空
    int strCompare(String *p1, String *p2);          // 比较两串大小 p1 < p2 返回-1
    String *concat(String *p1, String *p2);          // 连接两串，返回链接的结果
    void insertStr(String *p1, int pos, String *p2); // 在p1串的pos位置上插入一个p2串，返回插入的结果
    void deleteStr(String *p, int i, int j);         // 删除子串，从p1中删除第i个字符开始的长度为j的子串
    String *substr(String *p, int i, int j);         // 返回串p中第i个字符起长度为j的子串
    int getIndex(String *p1, String *p2);            // p1 p2均为非空串，若p1中存在子串与p2相等，返回位置。否则，返回0,(朴素的模式匹配算法)
    void getNext(String *p, int *next);              // KMP算法中获取next数组
private:
    char data[maxsize];
    int length;
};

void String::initStr(String *p)
{
    p->length = 0;
}

int String::getLen(String *p)
{
    int i = 0;
    while (p->data[i] != '\0')
    {
        i++;
    }
    return i;
}

void String::createStr(String *p)
{
    cin >> p->data;
    p->length = getLen(p);
}

bool String::emptyStr(String *p)
{
    if (p->length == 0)
    {
        puts("字符串为空");
        return true;
    }
    else
    {
        puts("字符串非空");
        return false;
    }
}

void String::printfStr(String *p)
{
    if (emptyStr(p) == true)
        puts("字符串为空");
    else
    {
        for (int i = 0; i < p->length; i++)
            cout << p->data[i];
        puts("");
    }
}

void String::strAssign(String *p, char temp[])
{
    int i;
    for (i = 0; temp[i] != '\0'; i++)
        p->data[i] = temp[i];
    p->length = i;
}

void String::strCopy(String *p1, String *p2)
{
    int i;
    for (i = 0; i < p2->length; i++)
        p1->data[i] = p2->data[i];
    p1->length = p2->length;
}

void String::clearStr(String *p)
{
    int i;
    for (i = 0; i < p->length; i++)
        p->data[i] = '\0';
    p->length = 0;
}

int String::strCompare(String *p1, String *p2)
{
    int i = 0;
    while ((p1->data[i] == p2->data[i]) && p1->data[i] != '\0' && p2->data[i] != '\0')
    {
        i++;
    }
    int res = p1->data[i] - p2->data[i]; // res < 0 p1 < p2; res == 0 p1 == p2; res > 0 p1 > p2;
    return res;
}

String *String::concat(String *p1, String *p2)
{
    // TODO: 判断两串加起来是否会超出上限
    int i, j;
    String *t;
    for (i = 0; i < p1->length; i++)
        t->data[i] = p1->data[i];
    for (j = 0; j < p2->length; j++)
        t->data[j + i] = p2->data[i];
    t->data[j] = '\0';
    t->length = p1->length + p2->length;

    return t;
}

void String::insertStr(String *p1, int pos, String *p2)
{
    // TODO: 判断插入后是否会超出上限
    // 此处假设插入后不会超出上限
    int i;
    // 为要插入的串留出位置，也就是把pos及其后面的子串向后移p2->length
    for (i = p1->length - 1; i >= pos; i--)
    {
        p1->data[i + p2->length] = p1->data[i];
    }
    for (int j = 0; i < p2->length; j++)
    {
        i++;
        p1->data[i] = p2->data[j];
    }
    p1->data[p1->length + p2->length] = '\0';
    p1->length += p2->length;
}

void String::deleteStr(String *p, int i, int j)
{
    if (i < 0 || i > p->length || i - 1 + j > p->length)
    {
        puts("删除的位置不对");
        return;
    }
    for (int k = i - 1; k < p->length - j; k++)
    {
        p->data[k] = p->data[k + j];
    }
    p->data[p->length] = '\0';
}

String *String::substr(String *p, int i, int j)
{
    if (i < 1 || i > p->length || i - 1 + j > p->length)
    {
        puts("没有这个子串，长度不足");
        return NULL;
    }
    String *str2 = new String;
    int k;
    for (k = 0; k < j; k++)
    {
        str2->data[k] = p->data[i - 1];
        i++;
    }
    str2->length = j;
    str2->data[j] = '\0';
    return str2;
}

int String::getIndex(String *p1, String *p2)
{
    int i = 1;
    while (i <= p1->length - p2->length + 1)
    {
        String *temp = substr(p1, i, p2->length);
        if (strCompare(temp, p2) != 0)
        {
            i++;
        }
        else
        {
            return i;
        }
    }
    puts("找不到这个子串");
    return -1;
}

void String::getNext(String *p, int *next)
{
    // p字符串的下标从1开始
    next[0] = 0;
    next[1] = 0; // 只取一个字符的时候next[1]为0
    for (int i = 2, j = 0; i <= getLen(p); i++)
    {
        while (j != 0 && p->data[i] != p->data[j + 1])
            j = next[j];
        if (p->data[i] == p->data[j + 1])
            j++;
        next[i] = j;
    }
}