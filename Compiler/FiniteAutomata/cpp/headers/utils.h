#if !defined(UTILS_H)
#define UTILS_H
#include <vector>
#include "../fastate.h"
namespace utils
{
std::vector<FAState *> eclose(std::vector<FAState *> states)
{
    std::vector<FAState *> set = {};
    while (!states.empty())
    {
        auto eTrans = (*states.begin())->transitions[0];
        set.push_back(*states.begin());
        states.erase(states.begin());
        for (auto state : eTrans)
        {
            if (std::find(set.begin(), set.end(), state) == set.end() && std::find(states.begin(), states.end(), state) == states.end())
                states.push_back(state);
        }
    }
    return set;
}
} // namespace utils
#endif // UTILS_H
