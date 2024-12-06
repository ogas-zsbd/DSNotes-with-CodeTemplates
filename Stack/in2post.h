
/*
 * @Author: OGAS 2970143166@qq.com
 * @Date: 2024-10-08 16:29:11
 * @LastEditors: OGAS 2970143166@qq.com
 * @LastEditTime: 2024-10-11 19:16:40
 * @FilePath: \Lab2\src\in2post.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once
#include <string>
#include <vector>
#include "LinkStack.h"
#include "tools.h"
using namespace std;

namespace in2post
{
    // 将中缀表达式转换为后缀表达式 (可以输入一个带空格的中缀表达式字符串)
    vector<string> infixToPostfix(const string &infix)
    {
        // 将输入的字符串中的空格去掉
        vector<string> tokens = splitString(infix);

        vector<string> postfix;     // 后缀表达式的串, 作为结果串返回
        LinkStack<string> optStack; // 存储转换过程中的运算符

        // 遍历中缀表达式
        for (const string &token : tokens)
        {
            if (isOpt(token)) // 遍历到了操作符, 就入栈
            {
                // 如果栈为空(不需要比较优先级) 或者 栈顶是左括号(需要等待右括号匹配) 或者 栈顶是优先级比当前操作符低的操作符
                while (!optStack.isEmpty() && optStack.getTop() != "(" && getOptPriority(optStack.getTop()) >= getOptPriority(token))
                {
                    // 将栈顶的操作符弹出并加入后缀表达式
                    postfix.push_back(optStack.getTop());
                    optStack.pop();
                }
                // 将当前操作符入栈
                optStack.push(token);
            }
            else if (token == "(")
            {
                optStack.push(token);
            }
            else if (token == ")")
            {
                // 如果遇到右括号, 就一直弹出栈顶元素, 直到与其匹配的左括号被弹出
                // 因为括号的优先级是最高的
                while (!optStack.isEmpty() && optStack.getTop() != "(")
                {
                    postfix.push_back(optStack.getTop());
                    optStack.pop();
                }
                // 弹出左括号
                if (!optStack.isEmpty() && optStack.getTop() == "(")
                {
                    optStack.pop();
                    // 后缀表达式中没有括号, 所以括号不用加入到后缀表达式中
                }
                else
                {
                    // 如果没有匹配的左括号, 说明输入的表达式有误
                    throw runtime_error("括号不匹配");
                }
            }
            else // 剩下的都是数字了, 直接加入到后缀表达式中
            {
                postfix.push_back(token);
            }
        }

        // 再将栈中剩余的符号加入到后缀表达式中
        while (!optStack.isEmpty())
        {
            if (optStack.getTop() == "(")
            {
                // 如果最后到栈中还有左括号在栈顶, 说明表达式有无
                throw runtime_error("括号不匹配");
            }
            postfix.push_back(optStack.getTop());
            optStack.pop();
        }

        return postfix;
    }
}
