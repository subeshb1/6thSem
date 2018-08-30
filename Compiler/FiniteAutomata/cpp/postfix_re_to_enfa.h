#if !defined(POSTFIX_RE_TO_ENFA_H)
#define POSTFIX_RE_TO_ENFA_H
#include "fastate.h"
#include "headers/utils.h"
#include <iostream>
auto enfaState(int alphabet)
{
    static int i = 0;
    auto state = new FAState();
    for (int i = 0; i <= alphabet; ++i)
    {
        state->transitions.push_back({});
    }
    state->name = std::to_string(i++);
    return state;
}

std::pair<FAState *, FAState *> kleeneClosure(std::pair<FAState *, FAState *> op, int alphabet)
{
    auto start = enfaState(alphabet);
    auto end = enfaState(alphabet);
    start->transitions[0] = {op.first, end};
    op.second->transitions[0].push_back(end);
    op.second->transitions[0].push_back(op.first);
    
    return std::make_pair(start, end);
}
std::pair<FAState *, FAState *> concat(std::pair<FAState *, FAState *> op1, std::pair<FAState *, FAState *> op2, int alphabet)
{   
    op1.second->transitions[0].push_back(op2.first);
    return std::make_pair(op1.first, op2.second);
}
std::pair<FAState *, FAState *> unionPlus(std::pair<FAState *, FAState *> op1, std::pair<FAState *, FAState *> op2, int alphabet)
{
    auto start = enfaState(alphabet);
    auto end = enfaState(alphabet);

    start->transitions[0].push_back(op1.first);
    start->transitions[0].push_back(op2.first);
    op1.second->transitions[0].push_back(end);
    op2.second->transitions[0].push_back(end);
    return std::make_pair(start, end);
}

std::pair<FAState *, std::set<int>> postfixToEnfa(std::pair<std::string, std::set<int>> pair)
{
    auto totalStates = 0;
    auto postfix = pair.first;
    auto alphabetSet = pair.second;
    auto alphabet = pair.second.size();
    if (!postfix.size())
    {
        auto state = enfaState(alphabet);
        state->isFinal = true;
        std::set<int> al;
        return std::make_pair(state, al);
    }
    auto getAlphabet = [alphabetSet](int a) {
        if (a == '#')
            return 0;
        int j = 1;
        for (auto i = alphabetSet.begin(); i != alphabetSet.end(); ++i, ++j)
        {
            if (a == *i)
                return j;
        }
        return -1;
    };
    std::vector<std::pair<FAState *, FAState *>> stack;
    for (auto i = postfix.begin(); i != postfix.end(); ++i)
    {
        if (utils::isOperand(*i))
        {
            auto start = enfaState(alphabet);
            auto end = enfaState(alphabet);
            auto alpha = getAlphabet(*i);
            start->transitions[alpha].push_back(end);
            stack.push_back(std::make_pair(start, end));
            totalStates += 2;
        }
        else if (*i == '*')
        {
            auto op = stack.back();
            stack.pop_back();
            stack.push_back(kleeneClosure(op, alphabet));
            totalStates += 2;
        }
        else if (*i == '.')
        {
            auto op1 = stack.back();
            stack.pop_back();
            auto op2 = stack.back();
            stack.pop_back();
            stack.push_back(concat(op2, op1, alphabet));
        }
        else if (*i == '|')
        {
            auto op1 = stack.back();
            stack.pop_back();
            auto op2 = stack.back();
            stack.pop_back();
            stack.push_back(unionPlus(op2, op1, alphabet));
            totalStates += 2;
        }
    }
    auto base = stack.back();
    base.second->isFinal = true;
    std::cout << "Total Number of States(ENFA): " << totalStates << std::endl;
    return std::make_pair(base.first, alphabetSet);
}

#endif // POSTFIX_RE_TO_ENFA_H