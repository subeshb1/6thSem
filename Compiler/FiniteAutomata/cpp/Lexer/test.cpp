#include "lexer.h"
#include <iostream>
#include "../headers/utils.h"
#include "../headers/direct_method.h"
#include "../headers/re_to_postfix.h"
#include "../headers/direct_method.h"
#include "../headers/dfa.h"
#include "../headers/fastate.h"
#include "../headers/nfa.h"
#include "../headers/enfa.h"
#include "../headers/enfatodfa.h"
#include <set>
#include "../headers/re_to_postfix.h"
#include "../headers/postfix_re_to_enfa.h"

bool number(std::string s)
{
  // a-> digit b-> '.'
  auto pregex = reToPostfix("((aa*((baa*)|#))|(baa*))((c(d|e|#)aa*)|#)$");
  std::cout << pregex.first;
  auto startState = directMethod(pregex);
  auto alphabetSet = pregex.second;

  auto getAlphabet = [](int a) {
    if (a >= '0' && a <= '9')
      return 0;
    if (a == '.')
      return 1;
    if (a == 'e')
      return 2;
    if (a == '+')
      return 3;
    if (a == '-')
      return 4;
    return -1;
  };
  DFA a(startState.first);

  std::cout << (a.test(s, getAlphabet) ? "ACCEPTED" : "REJECTED") << std::endl;
}

int main(int argc, char const *argv[])
{

  // auto callback = []() {
  //   Lexer a("dummy.cpp");
  //   a.allTokens();
  // };
  int a = .1;
  // utils::withTime(callback, "Syntax Analysis");
  std::cout << number("1001") << std::endl;
  std::cout << number("1e") << std::endl;
  std::cout << number("1e1") << std::endl;
  std::cout << number("1.100") << std::endl;
  std::cout << number("1.100e-1") << std::endl;
  std::cout << number(".1") << std::endl;
  std::cout << number(".1e10") << std::endl;
  std::cout << number(".1e") << std::endl;
  /* code */
  return 0;
}
