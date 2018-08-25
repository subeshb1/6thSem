#ifndef ENFA_H
#define ENFA_H
#include "fastate.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>
#include "headers/utils.h"
#include <set>
class ENFA
{
  public:
    ENFA(FAState *start)
    {
        this->start = start;
    }
    bool test(std::string str, int (*getAlphabet)(int))
    {
        std::set<FAState *> current = {this->start};
        for (auto i = str.begin(); i != str.end(); ++i)
        {
            auto alphabet = getAlphabet(*i);
            current = utils::nonDeterTrans(utils::eclose(current), alphabet);
        }
        return utils::hasFinal(current);
    }

  private:
    FAState *start;
};

#endif // ENFA_H
