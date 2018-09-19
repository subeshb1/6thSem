
#if !defined(LEXER_H)
#define LEXER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <functional>
#include <algorithm>
#include <iterator>
#include "../headers/direct_method.h"
#include "../headers/dfa.h"
#include "../headers/fastate.h"
#include "../headers/nfa.h"
#include "../headers/enfa.h"
#include "../headers/enfatodfa.h"
#include <set>
#include "../headers/re_to_postfix.h"
#include "../headers/postfix_re_to_enfa.h"
#include "lexer-utils.h"

typedef enum
{
  IDENTIFIER,
  NUMBER,
  KEYWORD,
  LITERAL,
  OPERATOR,
  EOT,
  PUNCTUATOR,
  UNDEF
} TokenType;
std::string arr[8] =
    {
        "IDENTIFIER",
        "NUMBER",
        "KEYWORD",
        "LITERAL",
        "OPERATOR",
        "EOT",
        "PUNCTUATOR",
        "UNDEF"};

struct Token
{

  Token(TokenType type, std::string value = "EMPTY", long line = 0, long column = 0, std::string extra = "")
  {
    this->column = column;
    this->value = value;
    this->line = line;
    this->type = type;
    this->extra = extra;
  }
  TokenType type;
  std::string value;
  std::string extra;
  long line;
  long column;
};

/** Class Lexer
 * summary - Receives a file name as an input and generates nextToken on method call.
 * **/
class Lexer
{
public:
  /**
 * @constructor
 * @params {string} file = file name
*/
  Lexer(std::string fileName)
  {

    this->position = 0;
    this->line = 0;
    this->column = 0;
    file.open(fileName);

    if (!file)
      throw "Can't Open File";
    std::stringstream buffer;
    buffer << file.rdbuf();
    this->input = buffer.str();
    std::cout << this->input;
  }
  /**
   * summarry - returns next token in sequence pointed by line  number and column number
   * @method
   * @return {std::shared_ptr<Token>} - A Token
  */
  std::shared_ptr<Token> nextToken()
  {
    // Checking if the scanning is complete
    if (position >= input.length())
    {
      //End
      return std::make_shared<Token>(EOT);
    }
    char character = input.at(position);
    if (lex::isAlphabet(character))
    {
      // return processAlphabet();
    }
    else if (lex::isDigit(character))
    {
      // return processDigit();
    }
    else if (lex::isDelimeter(character))
    {
      // return processDelimeter();
    }
    else if (lex::isOperator(character))
    {
      // return processOperator();
    }

    // If any invalid character is found or no matches found
    return std::make_shared<Token>(UNDEF, character, line, column);
  }

  std::shared_ptr<Token> processAlphabet()
  {
    long lookAhead = position;
    long startColNum = column;

    std::string word = "";
    word += input.at(lookAhead);
    char nextChar = input.at(++lookAhead);
    while (lex::isAlphabet(nextChar) && lex::isDigit(nextChar))
    {
      word += nextChar;
      if (++lookAhead >= input.length())
        break;
      nextChar = input.at(lookAhead);
    }
    position = lookAhead;
    column += lookAhead;
    if (lex::isKeyWord(word))
      return std::make_shared<Token>(KEYWORD, word, line, startColNum);
    return std::make_shared<Token>(IDENTIFIER, word, line, startColNum);
    }

private:
  std::ifstream file;
  int position;
  int line;
  int column;
  std::string input;
};

#endif // LEXER_H
