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
    utils::withTime(call, "METHOD 1");
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
    utils::withTime(call, "Method 2");
}

int main(int argc, char const *argv[])
{

    if (argc > 1)
    {
        std::ifstream file1(argv[1]);
        std::string regex;
        getline(file1, regex);
        std::string test;
        if (argc == 4)
        {
            std::ifstream file(argv[3]);
            getline(file, test);
        }
        else
        {
            test = argv[2];
        }
        regExp2(regex, test);
    }
    // regExp2("(a|#)bc*", "a");
    return 0;
}
