
#if !defined(ENFA_TO_DFA_H)
#define ENFA_TO_DFA_H

#include "fastate.h"
#include "headers/utils.h"
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <unordered_map>
//returns a predicate to compare sets
auto setPred(std::set<FAState *> set)
{
  return [set](auto s1) {
    return utils::setCompare(set, s1.second);
  };
}

class EnfaToDfa
{
private:
  FAState *start;

public:
  EnfaToDfa(FAState *start) : start(start) {}
  void setStart(FAState *start)
  {
    this->start = start;
  }
  FAState *toDfa(int alphabetLength)
  {
    auto startSet = utils::eclose({this->start});
    auto start = std::make_pair(utils::stateSetToString(startSet), std::make_pair(0, startSet));
    std::vector<std::pair<int, std::set<FAState *>>> transitions;
    std::unordered_map<std::string, std::pair<int, std::set<FAState *>>> sets = {start};
    std::deque<std::pair<std::string, std::pair<int, std::set<FAState *>>>> remaining = {start};

    int counter = 0;
    while (!remaining.empty())
    {
      auto mark = remaining.front();
      remaining.pop_front();
      for (int i = 1; i <= alphabetLength; i++)
      {
        auto set = utils::eclose(utils::nonDeterTrans(mark.second.second, i));
        auto key = utils::stateSetToString(set);
        auto setPair = sets.find(key);
        if (setPair != sets.end())
        {
          transitions.push_back(std::make_pair(setPair->second.first, mark.second.second));
        }
        else
        {
          auto statePair = std::make_pair(++counter, set);
          auto state = std::make_pair(key, statePair);
          sets.insert(state);
          transitions.push_back(std::make_pair(counter, mark.second.second));
          remaining.push_back(state);
        }
      }
    }

    std::vector<FAState *> dStates;
    const int dfaLength = sets.size();

    for (int i = 0; i < dfaLength; ++i)
      dStates.push_back(new FAState());
    for (int i = 0; i < dfaLength; ++i)
    {
      for (int j = 0; j < alphabetLength; ++j)
      {
        // std::cout << "Enter" << std::endl;
        // std::cout << "Transitions: " << transitions.at(i * alphabetLength + j).first << std::endl;
        dStates[i]->transitions.push_back({dStates.at(transitions[i * alphabetLength + j].first)});
      }

      dStates[i]->isFinal = utils::hasFinal(transitions[i * alphabetLength].second);
      
    }

    std::cout << transitions.size() << " " << dStates.size() << " " << alphabetLength << std::endl;
    return dStates[0];
  }

  
};

#endif // ENFA_TO_DFA_H
