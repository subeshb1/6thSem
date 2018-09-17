
#if !defined(RE_TO_POSTFIX)
#define RE_TO_POSTFIX
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include "utils.h"

std::pair<std::string, std::set<int>> reToPostfix(std::string re)
{
    std::cout << "RE Length: " << re.size() << std::endl;
    std::string postfix = "";
    std::vector<char> stack;
    std::set<int> alphabetSet;
    auto prevChar = ' ';
    for (auto i = re.begin(); i != re.end(); ++i)
    {

        if (utils::isOperand(*i))
        {
            if (*i != '#' && *i!= '$')
                alphabetSet.insert(*i);
            if (utils::isOperand(prevChar) || prevChar == '*' || prevChar == ')')
            {
                char c = '.';
                while (!stack.empty() && utils::precedence(c) <= utils::precedence(stack.back()))
                {
                    postfix += stack.back();
                    stack.pop_back();
                }
                stack.push_back(c);
            }
            postfix += *i;
        }
        else if (utils::isOperator(*i))
        {
            while (!stack.empty() && utils::precedence(*i) <= utils::precedence(stack.back()))
            {
                postfix += stack.back();
                stack.pop_back();
            }
            stack.push_back(*i);
        }
        else if (*i == '(')
        {
            if (utils::isOperand(prevChar) || prevChar == '*' || prevChar == ')')
            {
                char c = '.';
                while (!stack.empty() && utils::precedence(c) <= utils::precedence(stack.back()))
                {
                    postfix += stack.back();
                    stack.pop_back();
                }
                stack.push_back(c);
            }
            stack.push_back(*i);
        }
        else
        {
            
            while (!stack.empty() && stack.back() != '(')
            {
                postfix += stack.back();
                stack.pop_back();
            }
            if (stack.back() == '(')
                stack.pop_back();
        }
        prevChar = *i;
    }
    while (!stack.empty())
    {
        postfix += stack.back();
        stack.pop_back();
    }
    return std::make_pair(postfix, alphabetSet);
}
#endif // RE_TO_POSTFIX
