/*
 * @Author: OGAS 2970143166@qq.com
 * @Date: 2024-10-08 16:30:35
 * @LastEditors: OGAS 2970143166@qq.com
 * @LastEditTime: 2024-10-11 20:49:46
 * @FilePath: \Lab2\src\postCal.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once
#include "in2post.h"
#include "tools.h"
#include <cmath>
#include <vector>
#include <string>

using namespace std;

// 执行二元运算: 例如 1 + 1 返回2
double binaryOperation(double num1, double num2, string opt)
{
    if (opt == "+")
        return num1 + num2;
    if (opt == "-")
        return num1 - num2;
    if (opt == "*")
        return num1 * num2;
    if (opt == "/")
    {
        if (num2 == 0)
        {
            throw runtime_error("不能被0除");
            system("pause");
        }
        return num1 / num2;
    }
    if (opt == "^") return pow(num1, num2);
    throw runtime_error("非法运算符");
    system("pause");
}

// 后缀表达式的计算
double calculatePostfix(vector<string> postfix)
{
    LinkStack<double> numStack;

    // 遍历后缀表达式的字符串
    for (string &token : postfix)
    {
        if (isOpt(token)) // 如果遍历到了运算符, 就要从栈中取出两个数字进行运算, 并将结果压入栈中
        {
            // 由于我们考虑的都是二元运算, 所以如果栈中都没有两个数字, 那么就不能进行二元运算, 这个表达式本身就是错误的
            if (numStack.getSize() < 2)
            {
                throw runtime_error("表达式不合法, 没有足够的数字进行二元运算");
                system("pause");
            }
            // 表达式合法就继续进行运算
            // 从栈中取出两个元素, 先取出的在运算符的右边
            double num2 = numStack.getTop(); // 先取出元素
            numStack.pop();                  // 再将取出的元素弹出栈
            double num1 = numStack.getTop(); // 先取出元素
            numStack.pop();                  // 再将取出的元素弹出栈

            // 进行二元运算
            double res = binaryOperation(num1, num2, token);

            // 将二元运算的结果入栈
            numStack.push(res);
        }
        else // 如果遍历到数字就将数字入栈
        {
            numStack.push(stod(token)); // stod 用于将string中的字符转译成浮点数
        }
    }

    // 如果遍历完了整个后缀表达式中的字符串, 栈中还有>1(除结果以外还有其他数字)或者=0(根本没计算)的情况, 说明表达式不合法
    if (numStack.getSize() != 1)
    {
        throw runtime_error("结果错误, 表达式不合法");
        system("pause");
    }
    // 如果遍历完后缀表达式, 栈中只剩下一个数字, 这就是结果
    return numStack.getTop();
}