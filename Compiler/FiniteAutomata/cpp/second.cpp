#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <functional>
#include <algorithm>

#include "dfa.h"
#include "fastate.h"
#include "nfa.h"
#include "enfa.h"

int main(int argc, char const *argv[])
{
    std::ifstream file(argv[1]);
    auto getAlphabet = [](int a) {
        if (a == 97)
            return 1;
        return 2;
    };

    auto *q0 = new FAState();
    auto *q1 = new FAState();
    auto *q2 = new FAState();
    auto *q3 = new FAState();
    auto *q4 = new FAState();
    auto *q5 = new FAState();
    auto *q6 = new FAState();
    auto *q7 = new FAState();
    auto *q8 = new FAState();

    q0->transitions = {
        {q1, q7}, {}, {}};
    q1->transitions = {
        {q2, q4}, {}, {}};
    q2->transitions = {
        {}, {q3}, {}};
    q3->transitions = {
        {q6}, {}, {}};
    q4->transitions = {
        {}, {}, {q5}};
    q5->transitions = {
        {q6}, {}, {}};
    q6->transitions = {
        {q1, q7}, {}, {}};
    q7->transitions = {
        {}, {q8}, {}};
    q8->transitions = {
        {}, {}, {}};

    q8->isFinal = true;

    std::string test;

    auto start = std::chrono::system_clock::now();
    getline(file, test);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time to Load "
              << " ints : " << diff.count() << " s\n";

    ENFA a(q0);

    start = std::chrono::system_clock::now();
    std::cout << (a.test(test, getAlphabet) ? "true" : "false") << std::endl;
    end = std::chrono::system_clock::now();
    diff = end - start;
    std::cout << "Time to Test "
              << " ints : " << diff.count() << " s\n";
    return 0;
}