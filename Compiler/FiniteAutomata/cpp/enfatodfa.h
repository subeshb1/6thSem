
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
  // FAState *toDfa(int alphabetLength)
  // {
  //   auto startSet = utils::eclose({this->start});
  //   auto start = std::make_pair(utils::stateSetToString(startSet), std::make_pair(0, startSet));
  //   std::vector<std::pair<int, std::set<FAState *>>> transitions;
  //   std::unordered_map<std::string, std::pair<int, std::set<FAState *>>> sets = {start};
  //   std::deque<std::pair<std::string, std::pair<int, std::set<FAState *>>>> remaining = {start};

  //   int counter = 0;
  //   while (!remaining.empty())
  //   {
  //     auto mark = remaining.front();
  //     remaining.pop_front();
  //     for (int i = 1; i <= alphabetLength; i++)
  //     {
  //       std::cout << "Enter AlPha: " << mark.second.second.size() << " " << utils::nonDeterTrans(mark.second.second, i).size() << std::endl;
  //       auto set = utils::eclose(utils::nonDeterTrans(mark.second.second, i));
  //       std::cout << "Enter AlPha2: " << set.size() << std::endl;
  //       auto key = utils::stateSetToString(set);
  //       std::cout << "Enter AlPha3: " << key << std::endl;
  //       auto setPair = sets.find(key);
  //       if (setPair != sets.end())
  //       {
  //         std::cout << "Enter Beta" << std::endl;
  //         transitions.push_back(setPair->second);
  //       }
  //       else
  //       {
  //         std::cout << "Enter Theta" << std::endl;
  //         auto statePair = std::make_pair(++counter, set);
  //         auto state = std::make_pair(key, statePair);
  //         sets.insert(state);
  //         transitions.push_back(statePair);
  //         remaining.push_back(state);
  //         std::cout << "Exit Theta" << std::endl;
  //       }
  //     }
  //   }

    

  //   std::vector<FAState *> dStates;
  //   const int dfaLength = sets.size();

  //   for (int i = 0; i < dfaLength; ++i)
  //     dStates.push_back(new FAState());
  //   for (int i = 0; i < dfaLength; ++i)
  //   {
  //     for (int j = 0; j < alphabetLength; ++j)
  //     {
  //       // std::cout << "Enter" << std::endl;
  //       // std::cout << "Transitions: " << transitions.at(i * alphabetLength + j).first << std::endl;
  //       dStates[i]->transitions.push_back({dStates.at(transitions[i * alphabetLength + j].first)});
  //     }
  //     dStates[i]->isFinal = utils::hasFinal(transitions[i].second);
  //   }

  //   std::cout << transitions.size() << " " << dStates.size() << " " << alphabetLength << std::endl;
  //   return dStates[0];
  // }

  FAState *toDfa(int alphabetLength)
  {
    std::deque<std::pair<int, std::set<FAState *>>> dfaStates = {};
    std::vector<int> dfaTrans = {};
    std::deque<std::pair<int, std::set<FAState *>>> states = {
        std::make_pair(0, utils::eclose({this->start}))};
    int counter = 0;
    while (!states.empty())
    {
      auto mark = *states.begin();
      dfaStates.push_back(mark);
      states.pop_front();
      for (int i = 1; i <= alphabetLength; i++)
      {
        auto set = utils::eclose(utils::nonDeterTrans(mark.second, i));
        auto state = std::find_if(dfaStates.begin(), dfaStates.end(), setPred(set));
        if (state != dfaStates.end() || ((state = std::find_if(states.begin(), states.end(), setPred(set))) != states.end()))
        {
          dfaTrans.push_back(state->first);
        }
        else
        {
          dfaTrans.push_back(counter + 1);
          states.push_back(std::make_pair(++counter, set));
        }
      }
    }

    std::vector<FAState *> dStates;
    const int dfaLength = dfaStates.size();

    for (int i = 0; i < dfaLength; ++i)
      dStates.push_back(new FAState());
    for (int i = 0; i < dfaLength; ++i)
    {
      for (int j = 0; j < alphabetLength; ++j)
      {
        dStates[i]->transitions.push_back({dStates.at(dfaTrans[i * alphabetLength + j])});
      }
      dStates[i]->isFinal = utils::hasFinal(dfaStates[i].second);
    }
    std::cout << dfaTrans.size()  << " "<< dStates.size() << " " << alphabetLength  << std::endl;
    return dStates[0];
  }
};

#endif // ENFA_TO_DFA_H
