#if !defined(UTILS_H)
#define UTILS_H
#include <set>
#include "../fastate.h"
#include <set>
#include <iostream>
namespace utils
{
template <typename container, typename lamb>
auto inContainer_if(container c, lamb pred)
{
    return std::find_if(c.begin(), c.end(), pred);
}
std::set<FAState *> eclose(std::set<FAState *> states)
{
    std::set<FAState *> set = {};
    while (!states.empty())
    {
        auto eTrans = (*states.begin())->transitions[0];
        set.insert(*states.begin());
        states.erase(states.begin());
        for (auto &state : eTrans)
        {
            if (set.find(state) == set.end() && states.find(state) == states.end())
                states.insert(state);
        }
    }
    return set;
}
std::set<FAState *> nonDeterTrans(std::set<FAState *> current, int alphabet)
{
    std::set<FAState *> set = {};
    for (auto &state : current)
    {
        auto transStates = state->transitions[alphabet];
        set.insert(transStates.begin(), transStates.end());
    }
    return set;
}

bool hasFinal(std::set<FAState *> states)
{
    return std::find_if(states.begin(), states.end(), [](FAState *state) {
               return state->isFinal;
           }) != states.end();
}
template <typename T>
bool setCompare(std::set<T> s1, std::set<T> s2)
{
    std::vector<T> v_symDifference;

    std::set_symmetric_difference(
        s1.begin(), s1.end(),
        s2.begin(), s2.end(),
        std::back_inserter(v_symDifference));
    return !(bool)v_symDifference.size();
}
} // namespace utils

#endif // UTILS_H                                                                                                                                  \
       // std::set<FAState *> eclose(std::set<FAState *> states)                                                                                   \
       // {                                                                                                                                        \
       //     std::set<FAState *> set = {};                                                                                                        \
       //     while (!states.empty())                                                                                                              \
       //     {                                                                                                                                    \
       //         auto eTrans = (*states.begin())->transitions[0];                                                                                 \
       //         set.push_back(*states.begin());                                                                                                  \
       //         states.erase(states.begin());                                                                                                    \
       //         for (auto state : eTrans)                                                                                                        \
       //         {                                                                                                                                \
       //             if (std::find(set.begin(), set.end(), state) == set.end() && std::find(states.begin(), states.end(), state) == states.end()) \
       //                 states.push_back(state);                                                                                                 \
       //         }                                                                                                                                \
       //     }                                                                                                                                    \
       //     return set;                                                                                                                          \
       // }                                                                                                                                        \
       // std::set<FAState *> nonDeterTrans(std::set<FAState *> current, int alphabet)                                                             \
       // {                                                                                                                                        \
       //     std::set<FAState *> set = {};                                                                                                        \
       //     for (auto state : current)                                                                                                           \
       //     {                                                                                                                                    \
       //         auto transStates = state->transitions[alphabet];                                                                                 \
       //         set.insert(transStates.begin(), transStates.end());                                                                              \
       //     }                                                                                                                                    \
       //     std::set<FAState *> v(set.begin(), set.end());                                                                                       \
       //     return v;                                                                                                                            \
       // }

// bool hasFinal(std::set<FAState *> states)
// {
//     return std::find_if(states.begin(), states.end(), [](FAState *state) {
//                return state->isFinal;
//            }) != states.end();
// }