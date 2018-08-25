#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>
#include <fstream>
struct Tuples
{
    std::vector<std::string> states;
    std::vector<std::string> alphabets;
    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> transitions;
    std::string startState;
    std::vector<std::string> finalStates;
    explicit Tuples()
    {
        this->states = {};
        this->alphabets = {};
        this->transitions = {};
        this->startState = "";
        this->finalStates = {};
    }
    explicit Tuples(auto states, auto alphabets, auto transitions, auto startState, auto finalStates)
    {
        this->states = states;
        this->alphabets = alphabets;
        this->transitions = transitions;
        this->startState = startState;
        this->finalStates = finalStates;
    }
};

class DFA
{
  public:
    DFA(Tuples tuple)
    {
        this->tuple = tuple;
    }

    bool test(std::string str)
    {
        auto current = this->tuple.startState;
        auto length = str.length();
        for (unsigned int i = 0; i < length; i++)
        {
            auto alphabet = std::string(1, str.at(i));
            current = this->tuple.transitions[current][alphabet][0];
        }
        std::cout << length << " " << current;
        return true;
    }

  private:
    Tuples tuple;
};

int main(int argc, char const *argv[])
{
    /* code */
    Tuples a;
    a.states = {"q1", "q2"};
    a.alphabets = {"a", "b"};
    a.transitions = {
        {"q1", {
                   {"a", {"q1"}},
                   {"b", {"q2"}},
               }},
        {"q2", {
                   {"a", {"q2"}},
                   {"b", {"q1"}},
               }},
    };
    a.startState = "q1";
    std::ifstream file(argv[1]);
    std::string test;
    auto start = std::chrono::system_clock::now();
    getline(file, test);
    auto end = std::chrono::system_clock::now();
    auto length = test.length();
    std::cout << "Length: " << length << std::endl;
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time to Load "
              << " ints : " << diff.count() << " s\n";

    // ENFA a(q0);

    start = std::chrono::system_clock::now();
    DFA dfa(a);
    std::cout << (dfa.test(test) ? "true" : "false") << std::endl;
    end = std::chrono::system_clock::now();
    diff = end - start;
    std::cout << "Time to Test "
              << " ints : " << diff.count() << " s\n";

    return 0;
}
//