#ifndef NFA_H
#define NFA_H
#include "fastate.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <functional>
#include <algorithm>

class NFA
{
  public:
    NFA(FAState *start)
    {
        this->start = start;
    }
    bool test(std::string str, int (*getAlphabet)(int))
    {
        std::vector<FAState *> current = {this->start};
        auto length = str.length();
        std::cout << "Length: " << length << std::endl;
        for (unsigned int i = 0; i < length; i++)
        {
            auto alphabet = getAlphabet(str.at(i));
            std::vector<FAState *> next = {};
            for (auto state : current)
            {
                auto transStates = state->transitions[alphabet];
                for (auto state1 : transStates)
                {
                    if (std::find(next.begin(), next.end(), state1) == next.end())
                        next.push_back(state1);
                }
            }
            current = next;
        }
        return std::find_if(current.begin(), current.end(), [](FAState *state) {
                   return state->isFinal;
               }) != current.end();
    }

  private:
    FAState *start;
};

#endif