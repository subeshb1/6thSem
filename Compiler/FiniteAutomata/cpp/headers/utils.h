#if !defined(UTILS_H)
#define UTILS_H
#include <set>
#include "../fastate.h"
#include <set>
#include <iostream>
#include <chrono>
#include <string>
#include <numeric>
namespace utils
{

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

bool isOperand(char x)
{
    return (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z') || (x >= '0' && x <= '9') || x == '#' || x == '$' ? true : false;
}

bool isOperator(char x)
{
    return (x == '.' || x == '*' || x == '|') ? true : false;
}

int precedence(char op)
{
    switch (op)
    {
    case '*':
        return 4;
    case '.':
        return 3;
    case '|':
        return 2;
    default:
        return 1;
    }
}

template <typename T>
void withTime(T callback, std::string task = "Task")
{
    std::cout << "\n-----" << task << "-----" << std::endl;
    auto start = std::chrono::system_clock::now();
    callback();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << task << " Completed In: " << diff.count() << " s\n";
}

std::string stateSetToString(std::set<FAState *> set)
{
    if (!set.size())
        return "###";
    std::vector<FAState *> v(set.begin(), set.end());
    std::sort(v.begin(), v.end(), [](FAState *state1, FAState *state2) {
        return state1->name < state2->name;
    });
    return std::accumulate(std::next(v.begin()), v.end(), v[0]->name, [](std::string acc, FAState *state) {
        return acc + "-" + state->name;
    });
}

std::string nodeSetToString(std::set<int> set)
{
    if (!set.size())
        return "###";
    std::vector<int> v(set.begin(), set.end());
    return std::accumulate(std::next(v.begin()), v.end(), std::to_string(v[0]), [](std::string acc, int name) {
        return acc + "-" + std::to_string(name);
    });
}

std::set<int> nodeTrans(std::set<int> &set, std::vector<std::pair<int, std::set<int>>> &nodes, int alphabet)
{
    std::set<int> next;
    for (auto pos : set)
    {
        if (nodes[pos].first == alphabet)
        {
            next.insert(nodes[pos].second.begin(), nodes[pos].second.end());
        }
    }
    return next;
}

} // namespace utils

#endif // UTILS_H