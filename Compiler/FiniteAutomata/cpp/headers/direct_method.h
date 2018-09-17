
#if !defined(DIRECT_METHOD_H)
#define DIRECT_METHOD_H
#include <algorithm>
#include "fastate.h"
#include "utils.h"
#include <iostream>
#include <set>
#include <iterator>
#include <deque>
#include <unordered_map>
struct Node
{
    bool nullable;
    std::set<int> firstPos;
    std::set<int> lastPos;
    Node(bool nullable = true, std::set<int> firstPos = {}, std::set<int> lastPos = {})
    {
        this->nullable = nullable;
        this->firstPos = firstPos;
        this->lastPos = lastPos;
    }
};

Node *kleeneClosure(Node *op1)
{
    auto node = new Node();
    node->firstPos = op1->firstPos;
    node->lastPos = op1->lastPos;
    delete op1;
    return node;
}
Node *unionPlus(Node *op1, Node *op2)
{

    auto node = new Node(op1->nullable || op2->nullable);
    std::set_union(op1->firstPos.begin(), op1->firstPos.end(), op2->firstPos.begin(), op2->firstPos.end(), std::inserter(node->firstPos, node->firstPos.begin()));
    std::set_union(op1->lastPos.begin(), op1->lastPos.end(), op2->lastPos.begin(), op2->lastPos.end(), std::inserter(node->lastPos, node->lastPos.begin()));
    delete op1;
    delete op2;
    return node;
}
Node *concat(Node *op1, Node *op2)
{
    auto node = new Node(op1->nullable && op2->nullable);
    if (op1->nullable)
        std::set_union(op1->firstPos.begin(), op1->firstPos.end(), op2->firstPos.begin(), op2->firstPos.end(), std::inserter(node->firstPos, node->firstPos.begin()));
    else
        node->firstPos = op1->firstPos;
    if (op2->nullable)
        std::set_union(op1->lastPos.begin(), op1->lastPos.end(), op2->lastPos.begin(), op2->lastPos.end(), std::inserter(node->lastPos, node->lastPos.begin()));
    else
        node->lastPos = op2->lastPos;
    delete op1;
    delete op2;
    return node;
}

FAState *nodesToSate(std::set<int> startSet, std::vector<std::pair<int, std::set<int>>> nodes, int alphabetLength)
{
    auto start = std::make_pair(utils::nodeSetToString(startSet), std::make_pair(0, startSet));
    std::vector<std::pair<int, std::set<int>>> transitions;
    std::unordered_map<std::string, std::pair<int, std::set<int>>> sets = {start};
    std::deque<std::pair<std::string, std::pair<int, std::set<int>>>> remaining = {start};

    int counter = 0;
    while (!remaining.empty())
    {
        auto mark = remaining.front();
        remaining.pop_front();
        for (int i = 0; i < alphabetLength; i++)
        {
            auto set = utils::nodeTrans(mark.second.second, nodes, i);
            auto key = utils::nodeSetToString(set);
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

            dStates[i]->transitions.push_back({dStates.at(transitions[i * alphabetLength + j].first)});
        }

        dStates[i]->isFinal = std::any_of(transitions[i * alphabetLength].second.begin(), transitions[i * alphabetLength].second.end(), [&nodes](int a) {
            return nodes[a].first == -1;
        });
    }

    std::cout << "Number of Transitions: " << transitions.size() << std::endl
              << "Number of States(DFA): " << dStates.size() << std::endl
              << "Number of Alphabet: " << alphabetLength << std::endl;
    return dStates[0];
}

std::pair<FAState *, std::set<int>> directMethod(std::pair<std::string, std::set<int>> pair)
{
    auto totalStates = 0;
    auto postfix = pair.first;
    auto alphabetSet = pair.second;
    auto alphabet = pair.second.size();
    std::vector<std::pair<int, std::set<int>>> nodes;
    auto counter = 0;

    auto getAlphabet = [alphabetSet](int a) {
        int j = 0;
        for (auto i = alphabetSet.begin(); i != alphabetSet.end(); ++i, ++j)
        {
            if (a == *i)
                return j;
        }
        return -1;
    };
    std::vector<Node *> stack;
    for (auto i = postfix.begin(); i != postfix.end(); ++i)
    {
        if (utils::isOperand(*i))
        {
            if (*i == '#')
            {
                auto node = new Node();
                stack.push_back(node);
            }
            else
            {
                int pos = counter++;
                auto node = new Node(false);
                node->lastPos.insert(pos);
                node->firstPos.insert(pos);
                std::set<int> set = {};
                nodes.push_back(std::make_pair(getAlphabet(*i), set));
                stack.push_back(node);
            }
        }
        else if (*i == '*')
        {
            auto op = stack.back();
            stack.pop_back();
            stack.push_back(kleeneClosure(op));
            totalStates += 2;
            for (auto pos : op->lastPos)
            {
                nodes[pos].second.insert(op->firstPos.begin(), op->firstPos.end());
            }
        }
        else if (*i == '.')
        {
            auto op1 = stack.back();
            stack.pop_back();
            auto op2 = stack.back();
            stack.pop_back();

            for (auto pos : op2->lastPos)
            {
                nodes[pos].second.insert(op1->firstPos.begin(), op1->firstPos.end());
            }
            stack.push_back(concat(op2, op1));
        }
        else if (*i == '|')
        {
            auto op1 = stack.back();
            stack.pop_back();
            auto op2 = stack.back();
            stack.pop_back();
            stack.push_back(unionPlus(op2, op1));
        }
    }
    auto rootNode = stack.front();
    std::cout << "Stack Size " << stack.size() << std::endl;
    std::cout << "Root First Pos: " << rootNode->firstPos.size() << std::endl;
    std::cout << "Root Last Pos: " << rootNode->lastPos.size() << std::endl;
    return std::make_pair(nodesToSate(rootNode->firstPos, nodes, alphabet), alphabetSet);
}

#endif // DIRECT_METHOD_H
