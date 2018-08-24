#ifndef FASTATE_H
#define FASTATE_H

#include <vector>
#include <string>

struct FAState
{
    std::string name;
    bool isFinal;
    std::vector<std::vector<FAState *>> transitions;
    FAState()
    {
        isFinal = false;
    }
    FAState(auto name, auto transitions, auto isFinal = false)
    {
        this->name = name;
        this->isFinal = isFinal;
        this->transitions = transitions;
    }
};

#endif