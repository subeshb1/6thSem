#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <functional>
#include <algorithm>
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

class DFA
{
  public:
    DFA(FAState *start)
    {
        this->start = start;
    }
    bool test(std::string str, auto getAlphabet)
    {
        auto current = this->start;
        auto length = str.length();
        std::cout << "Length: " << length << std::endl;
        for (unsigned int i = 0; i < length; i++)
        {
            auto alphabet = getAlphabet(str.at(i));
            current = current->transitions[alphabet][0];
        }

        return current->isFinal;
    }

  private:
    FAState *start;
};
class NFA
{
  public:
    NFA(FAState *start)
    {
        this->start = start;
    }
    bool test(std::string str, auto getAlphabet)
    {
        std::vector<FAState *> current = {this->start};
        auto length = str.length();
        std::cout << "Length: " << length << std::endl;
        for (unsigned int i = 0; i < length; i++)
        {
            auto alphabet = getAlphabet(str.at(i));
            std::vector<FAState *>::size_type size = current.size();
            for (std::vector<FAState *>::size_type i = 0; i < size; ++i)
            {
                auto transTo = current[i]->transitions[alphabet][0];
            }
            // std::find(vector.begin(), vector.end(), item) != vector.end()
        }

        return current->isFinal;
    }

  private:
    FAState *start;
};

int main(int argc, char const *argv[])
{
    std::ifstream file(argv[1]);
    auto getAlphabet = [](char a) {
        if (a == 'a')
            return 0;
        else
            return 1;
    };
    auto *q0 = new FAState();
    auto *q1 = new FAState();
    q0->name = "q0";
    q1->name = "q1";
    q0->transitions = {
        {q1}, {q0}};
    q1->transitions = {
        {q1}, {q0}};
    q1->isFinal = true;
    std::string test;
    auto start = std::chrono::system_clock::now();
    getline(file, test);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time to Load "
              << " ints : " << diff.count() << " s\n";
    DFA a(q0);
    start = std::chrono::system_clock::now();
    std::cout << (a.test(test, getAlphabet) ? "true" : "false") << std::endl;
    end = std::chrono::system_clock::now();
    diff = end - start;
    std::cout << "Time to Test "
              << " ints : " << diff.count() << " s\n";
    return 0;
}