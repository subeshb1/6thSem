#include "lexer.h"
#include <iostream>
#include "../headers/utils.h"

int main(int argc, char const *argv[])
{

  auto callback = []() {
    Lexer a("dummy.cpp");
    a.allTokens();
  };

  utils::withTime(callback, "Syntax Analysis");

  /* code */
  return 0;
}
