#ifndef DFA_H
#define DFA_H
#include "fastate.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <functional>
#include <algorithm>

class DFA
{
  public:
    DFA(FAState *start)
    {
        this->start = start;
    }
    bool test(std::string str, auto getAlphabet)
    {
        auto current = this->start;
        auto length = str.length();
        std::cout << "Length: " << length << std::endl;
        for (unsigned int i = 0; i < length; i++)
        {
            auto alphabet = getAlphabet(str[i]);
            if(alphabet == -1) return false;
            current = current->transitions[alphabet][0];
        }

        return current->isFinal;
    }

  private:
    FAState *start;
};
#endif