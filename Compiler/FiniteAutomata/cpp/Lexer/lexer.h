
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
bool testIdentifier(std::string s)
{

  auto pregex = reToPostfix("a(a|b)*");
  auto startState = postfixToEnfa(pregex);
  auto alphabetSet = pregex.second;

  auto getAlphabet = [](int a) {
    if (a >= 'a' && a <= 'z' || a >= 'A' && a <= 'Z' || a == '_')
      return 0;
    if (a >= '0' && a <= '9')
      return 1;
    return -1;
  };
  EnfaToDfa b(startState.first);
  DFA a(b.toDfa(alphabetSet.size()));

  std::cout << (a.test(s, getAlphabet) ? "ACCEPTED" : "REJECTED") << std::endl;
}

bool number(std::string s)
{

  auto pregex = reToPostfix("aa*");
  std::cout << pregex.first;
  auto startState = postfixToEnfa(pregex);
  auto alphabetSet = pregex.second;

  auto getAlphabet = [&](int a) {
    if (a >= '0' && a <= '9')
      return 0;
    return -1;
  };
  EnfaToDfa b(startState.first);
  DFA a(b.toDfa(alphabetSet.size()));

  std::cout << (a.test(s, getAlphabet) ? "ACCEPTED" : "REJECTED") << std::endl;
}

typedef enum
{
  IDENTIFIER,
  NUMBER,
  KEYWORD,
  OPERATOR,
  ENDOFFILE,
  SPECIALCHARACTER
} TokenType;
std::string arr[6] =
    {
        "IDENTIFIER",
        "NUMBER",
        "KEYWORD",
        "OPERATOR",
        "ENDOFFILE",
        "SPECIALCHARACTER"};
struct Token
{
  Token(TokenType type, std::string value = "EMPTY", long line = 0, long column = 0)
  {
    this->column = column;
    this->value = value;
    this->line = line;
    this->type = type;
  }
  TokenType type;
  std::string value;
  long line;
  long column;
};

/** Class Lexer
 * summary - Receives a file name as an input and generates nextToken on method call.
 * **/
class Lexer
{
private:
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

  std::shared_ptr<Token> nextToken()
  {
    if (position >= input.length())
    {
      return std::shared_ptr<Token>(new Token(ENDOFFILE));
    }
    skipWhiteSpace();
    const char character = input.at(position);
    if (isLetter(character))
    {
      return recognizeID();
    }
    if (isDigit(character))

    {
      std::cout << "Enter";
      return recognizeNumber();
    }
    std::string dat = "";
    dat +=   input.at(position++) ;
    return std::shared_ptr<Token>(new Token(SPECIALCHARACTER, dat     ));
  }
  std::shared_ptr<Token> recognizeID()
  {
    std::string id = "";
    long position = this->position;
    long line = this->line;
    long column = this->column;
    char character = this->input.at(position);
    while (position < this->input.length())
    {
      char character = this->input.at(position);

      if (!(isLetter(character) || isDigit(character)))
      {
        break;
      }

      id += character;
      position += 1;
    }

    this->position += id.length();
    this->column += id.length();

    return std::shared_ptr<Token>(new Token(IDENTIFIER, id, line, column));
  }

  std::shared_ptr<Token> recognizeNumber()
  {
    std::string number = "";
    long position = this->position;
    long line = this->line;
    long column = this->column;
    char character = this->input.at(position);
    while (position < this->input.length())
    {
      char character = this->input.at(position);

      if (!(isDigit(character)))
      {
        break;
      }

      number += character;
      position += 1;
    }

    this->position += number.length();
    this->column += number.length();

    return std::shared_ptr<Token>(new Token(NUMBER, number, line, column));
  }

  bool isDigit(char a)
  {
    return a >= '0' && a <= '9';
  }
  void skipWhiteSpace()
  {

    while (position < input.length() && isWhiteSpace(input.at(position)))
    {
    
      position++;
      if (isNewLine(input.at(position)))
      {
        line += 1;
        column = 0;
      }
      else
        column += 1;
    }
  }

  bool isWhiteSpace(char a)
  {
    return a == ' ' || a == '\t' || a == '\n' || a=='\r';
  }
  bool isLetter(char a)
  {
    return (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || a == '_';
  }
  bool isNewLine(char a)
  {
    return a == '\n' || a=='\r';
  }

  void allTokens()
  {
    auto token = nextToken();

    while (token->type != ENDOFFILE)
    {
      std::cout << std::endl
                << "TOKEN" << std::endl;
      std::cout << "TYPE: " << arr[token->type] << std::endl;
      std::cout << "VALUE: " << token->value << std::endl;
      std::cout << "LINE: " << token->line << std::endl;
      std::cout << "COLUMN: " << token->column << std::endl;
      token = nextToken();
    }
  }

  std::ifstream file;
  int position;
  int line;
  int column;
  std::string input;
};

#endif // LEXER_H
