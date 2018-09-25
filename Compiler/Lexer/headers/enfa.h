#ifndef ENFA_H
#define ENFA_H
#include "fastate.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>
#include "utils.h"
#include <set>
class ENFA
{
  public:
    ENFA(FAState *start)
    {
        this->start = start;
    }
    // bool test(std::string str, auto getAlphabet)
    // {
    //     std::set<FAState *> current = {this->start};
    //     current = utils::eclose(current);
    //     for (auto i = str.begin(); i != str.end(); ++i)
    //     {
    //         auto alphabet = getAlphabet(*i);
    //         current = utils::eclose(utils::nonDeterTrans(current, alphabet));
    //     }
    //     return utils::hasFinal(current);
    // }

  private:
    FAState *start;
};

#endif // ENFA_H
