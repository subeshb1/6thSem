#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <functional>
#include <algorithm>
#include <iterator>

#include "dfa.h"
#include "fastate.h"
#include "nfa.h"
#include "enfa.h"
#include "enfatodfa.h"
#include <set>
#include <emscripten/emscripten.h>

int main(int argc, char const *argv[])
{

    // std::ifstream file(argv[1]);
    std::ifstream file("test.cpp");
    auto getAlphabet = [](int a) {
        if (a == 97)
            return 0;
        return 1;
    };

    auto q0 = new FAState();
    auto q1 = new FAState();
    auto q2 = new FAState();
    auto q3 = new FAState();
    auto q4 = new FAState();
    auto q5 = new FAState();
    auto q6 = new FAState();
    auto q7 = new FAState();
    auto q8 = new FAState();
    auto q9 = new FAState();
    auto q10 = new FAState();

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
        {}, {}, {q9}};
    q9->transitions = {
        {}, {}, {q10}};
    q10->transitions = {
        {}, {}, {}};
    q10->isFinal = true;

    EnfaToDfa conv(q0);

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
    DFA a(conv.toDfa(2));
    std::cout << (a.test(test, getAlphabet) ? "true" : "false") << std::endl;
    end = std::chrono::system_clock::now();
    diff = end - start;
    std::cout << "Time to Test "
              << " ints : " << diff.count() << " s\n";
    return 0;
}
extern "C" int EMSCRIPTEN_KEEPALIVE testString(std::string test)
{
    auto getAlphabet = [](int a) {
        if (a == 97)
            return 0;
        return 1;
    };
    auto q0 = new FAState();
    auto q1 = new FAState();
    auto q2 = new FAState();
    auto q3 = new FAState();
    auto q4 = new FAState();
    auto q5 = new FAState();
    auto q6 = new FAState();
    auto q7 = new FAState();
    auto q8 = new FAState();
    auto q9 = new FAState();
    auto q10 = new FAState();

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
        {}, {}, {q9}};
    q9->transitions = {
        {}, {}, {q10}};
    q10->transitions = {
        {}, {}, {}};
    q10->isFinal = true;

    EnfaToDfa conv(q0);

    auto start = std::chrono::system_clock::now();
    DFA a(conv.toDfa(2));
    const auto result = a.test("ab", getAlphabet);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Time to Test "
              << " ints : " << diff.count() << " s\n";
    std::cout << result << " " << test << " \n";
    return result;
}
