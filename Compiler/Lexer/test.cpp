#include "lexer.h"
#include <iostream>
#include "headers/utils.h"
#include "headers/direct_method.h"
#include "headers/re_to_postfix.h"
#include "headers/direct_method.h"
#include "headers/dfa.h"
#include "headers/fastate.h"
#include "headers/nfa.h"
#include "headers/enfa.h"
#include "headers/enfatodfa.h"
#include <set>
#include "headers/re_to_postfix.h"
#include "headers/postfix_re_to_enfa.h"
#include <cstring>
#include <string>
#include <emscripten/emscripten.h>
extern "C"
{
  char *EMSCRIPTEN_KEEPALIVE callMePlease(const char *name)
  {

    Lexer a;
    fflush(stdin);
    a.setInput(name);
    const std::string data = a.toString();
    char *str = new char[data.length() + 1];
    // const
    // std::cout << data << std::endl;
    std::strcpy(str, data.c_str());
    return str;
  }
}
// const char *callMePlease(const char *name)
// {

//   Lexer a;
//   fflush(stdin);
//   a.setInput(name);
//   fflush(stdin);
//   const std::string data = a.toString();
//   std::cout << data << std::endl;
//   return data.c_str();
// }
int main(int argc, char const *argv[])
{

  // Lexer a("dummy.js");

  // a.allTokens();
  // Lexer b("dummy.js");
  // b.toHTML();
  std::cout << callMePlease("FIRST asdaskldh asdn klasjdk ajslkd jalksdj lkasjd lkasjdk jakls ");
  // a.toHTML();
  return 0;
}
