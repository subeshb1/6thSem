#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <functional>
#include <algorithm>
#include <iterator>

#include "dfa.h"
#include "fastate.h"
#include "nfa.h"
#include "enfa.h"
#include "enfatodfa.h"
#include <set>
#include "re_to_postfix.h"
#include "postfix_re_to_enfa.h"
// #include <emscripten/emscripten.h>

void regExp(std::string regex,std::string test)
{
    auto call = [regex, test]() { 
        auto pregex = reToPostfix(regex);
        std::cout << pregex.first << std::endl;
        std::cout << pregex.second.size() << std::endl;
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
    utils::withTime(call, "Running Input");
}
int main(int argc, char const *argv[])
{
    if (argc > 1)
    {
        std::string regex = argv[1];
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
        regExp(regex,test);
    }
    return 0;
}
