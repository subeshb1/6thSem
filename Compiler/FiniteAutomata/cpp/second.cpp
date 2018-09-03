#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <functional>
#include <algorithm>
#include <iterator>
#include "direct_method.h"
#include "dfa.h"
#include "fastate.h"
#include "nfa.h"
#include "enfa.h"
#include "enfatodfa.h"
#include <set>
#include "re_to_postfix.h"
#include "postfix_re_to_enfa.h"
// #include <emscripten/emscripten.h>

void regExp(std::string regex, std::string test)
{
    auto call = [regex, test]() {
        auto pregex = reToPostfix(regex);
        auto startState = postfixToEnfa(pregex);
        auto alphabetSet = pregex.second;

        auto getAlphabet = [&](int a) {
            int j = 0;
            for (auto i = alphabetSet.begin(); i != alphabetSet.end(); ++i, ++j)
            {
                if (a == *i)
                    return j;
            }
            return -1;
        };
        EnfaToDfa b(startState.first);
        DFA a(b.toDfa(alphabetSet.size()));

        std::cout << (a.test(test, getAlphabet) ? "ACCEPTED" : "REJECTED") << std::endl;
    };
    utils::withTime(call, "THOMSON'S CONSTRUCTION");
}

void regExp2(std::string regex, std::string test)
{
    auto call = [regex, test]() {
        auto pregex = reToPostfix("(" + regex + ")$");
        auto startState = directMethod(pregex);
        auto alphabetSet = pregex.second;
        auto getAlphabet = [&](int a) {
            int j = 0;
            for (auto i = alphabetSet.begin(); i != alphabetSet.end(); ++i, ++j)
            {
                if (a == *i)
                    return j;
            }
            return -1;
        };
        DFA a(startState.first);

        std::cout << (a.test(test, getAlphabet) ? "ACCEPTED" : "REJECTED") << std::endl;
    };
    utils::withTime(call, "Direct Method");
}

bool testIdentifier(std::string s)
{

    auto pregex = reToPostfix("a(a|b)*");
    auto startState = postfixToEnfa(pregex);
    auto alphabetSet = pregex.second;

    auto getAlphabet = [](int a) {
        if (a >= 'a' && a <= 'z' || a >= 'A' && a <= 'Z' || a == '_')
            return 0;
        if (a >= '0' && a <= '9')
            return 1;
        return -1;
    };
    EnfaToDfa b(startState.first);
    DFA a(b.toDfa(alphabetSet.size()));

    std::cout << (a.test(s, getAlphabet) ? "ACCEPTED" : "REJECTED") << std::endl;
}

bool number(std::string s)
{

    auto pregex = reToPostfix("aa*");
    std::cout << pregex.first;
    auto startState = postfixToEnfa(pregex);
    auto alphabetSet = pregex.second;

    auto getAlphabet = [&](int a) {
        if (a >= '0' && a <= '9')
            return 0;
        return -1;
    };
    EnfaToDfa b(startState.first);
    DFA a(b.toDfa(alphabetSet.size()));

    std::cout << (a.test(s, getAlphabet) ? "ACCEPTED" : "REJECTED") << std::endl;
}

bool matchOneLineComments(std::string s)
{
    auto pregex = reToPostfix("aa(a|b)*c");
    std::cout << pregex.first;
    auto startState = postfixToEnfa(pregex);
    auto alphabetSet = pregex.second;
    auto getAlphabet = [&](int a) {
        if (a == '/')
            return 0;
        if (a != '\n')
            return 1;
        return 2;
    };
    EnfaToDfa b(startState.first);
    DFA a(b.toDfa(alphabetSet.size()));

    std::cout << (a.test(s, getAlphabet) ? "ACCEPTED" : "REJECTED") << std::endl;
}

bool matchMultiLineComments(std::string s)
{
    auto pregex = reToPostfix("ab(a|b|c)*ba");
    std::cout << pregex.first;
    auto startState = postfixToEnfa(pregex);
    auto alphabetSet = pregex.second;
    auto getAlphabet = [&](int a) {
        if (a == '/')
            return 0;
        if (a == '*')
            return 1;
        return 2;
    };
    EnfaToDfa b(startState.first);
    DFA a(b.toDfa(alphabetSet.size()));

    std::cout << (a.test(s, getAlphabet) ? "ACCEPTED" : "REJECTED") << std::endl;
}

int main(int argc, char const *argv[])
{
    // testIdentifier(argc>1?argv[1]:"functionName");
    // number(argc > 1 ? argv[1] : "0191");
    matchMultiLineComments("/*Subesh");

    if (argc > 1)
    {
        if (argc == 8)
        {
            std::string type(argv[1]);
            std::string method;
            std::string regex;
            std::string test;
            for (int i = 2; i < 8; i += 2)
            {
                std::string arg1(argv[i]), arg2(argv[i + 1]);
                if (arg1 == "-m")
                {
                    method = arg2;
                }
                else if (arg1 == "-r")
                {

                    if (type == "-f")
                    {
                        std::ifstream file1(arg2);
                        getline(file1, regex);
                        file1.close();
                    }
                    else
                        regex = arg2;
                }
                else if (arg1 == "-t")
                {
                    if (type == "-f")
                    {
                        std::ifstream file(arg2);
                        getline(file, test);
                        file.close();
                    }
                    else
                        test = arg2;
                }
            }

            if (method == "0")
                regExp(regex, test);
            else
                regExp2(regex, test);
        }
        else
        {
            std::cout << "Please pass in correct arguments: \nmatch -f|-a -m <method|0,1> -r <regularEXP|file> -t <testString|file>";
        }
    }

    return 0;
}
