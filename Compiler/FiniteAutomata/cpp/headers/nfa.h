#ifndef NFA_H
#define NFA_H
#include "fastate.h"
#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <chrono>
#include <functional>
#include <algorithm>
#include "utils.h"
class NFA
{
  public:
    NFA(FAState *start)
    {
        this->start = start;
    }
    bool test(std::string str, int (*getAlphabet)(int))
    {
        std::set<FAState *> current = {this->start};
        for (auto i = str.begin(); i != str.end(); ++i)
        {
            auto alphabet = getAlphabet(*i);
            current = utils::nonDeterTrans(current, alphabet);
        }
       return utils::hasFinal(current);
    }

  private:
    FAState *start;
};

#endif