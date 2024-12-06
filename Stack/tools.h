/*
 * @Author: OGAS 2970143166@qq.com
 * @Date: 2024-10-09 10:49:16
 * @LastEditors: OGAS 2970143166@qq.com
 * @LastEditTime: 2024-10-11 22:46:00
 * @FilePath: \Lab2\src\tools.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#pragma once
#include <cmath>
#include <vector>
#include <string>

using namespace std;

vector<string> splitString(const string &str)
{
    vector<string> tokens; // 用于存储分割结果的去除空格的结果串
    string token;          // 用于暂时存储空格之间的字符
    // 遍历str每个字符
    for (char c : str)
    {
        // 如果遇到了分隔符 ' ', 说明这个token子串已经录入完成了, 可以加入到结果的tokens中
        if (c == ' ')
        {
            // 如果token中存在字符, 说明确实是录入了
            if (!token.empty())
            {
                // 将当前token子串加入tokens结果串中
                tokens.push_back(token);
                // 将临时的token子串清空, 以备下一个子串使用
                token.clear();
            }
        }
        else // 如果没有遇到分割符, c还是一个合法的字符
        {
            token += c; // 将这个字符加入临时的子字符串中
        }
    }

    // 最后如果临时的子字符串中还有剩余的字符, 加入结果的tokens中
    if (!token.empty())
    {
        tokens.push_back(token);
    }

    return tokens;
}

// 判断是否为操作符: + - * / ^
bool isOpt(const string &token)
{
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}

// 判断操作符的优先级 ^     >     * /     >     + -
int getOptPriority(const string &opt)
{
    if (opt == "^")
        return 3;
    if (opt == "*" || opt == "/")
        return 2;
    if (opt == "+" || opt == "-")
        return 1;
    return 0;
}

// 输出vector
void printVector(const vector<string> &vec)
{
    for (const string &str : vec)
    {
        cout << str << " ";
    }
    cout << endl;
}

// 输入 vector<string> 的函数
vector<string> inputPostfix()
{
    vector<string> vec;
    string input;
    cout << "请输入后缀表达式 (空格分隔各个部分, 例如: 1 1 +)：";
    cin.ignore();        // 忽略之前 cin 输入中的换行符
    getline(cin, input); // 获取整行输入

    // 将输入字符串按照空格切分成多个 token，存入 vector 中
    vec = splitString(input);

    return vec;
}