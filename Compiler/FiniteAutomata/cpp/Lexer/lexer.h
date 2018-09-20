
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
  DELIMETER,
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
        "DELIMETER",
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
    this->line = 1;
    this->column = 1;
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
    skipWhiteSpace();
    // Checking if the scanning is complete
    if (position >= input.length())
    {
      //End
      return std::make_shared<Token>(EOT);
    }
    char character = input.at(position);
    if (lex::isAlphabet(character))
    {
      return processAlphabet();
    }
    else if (lex::isDigit(character))
    {
      // return processDigit();
    }
    else if (lex::isDelimeter(character))
    {
      return processDelimeter();
    }
    else if (lex::isOperator(character))
    {
      return processOperator();
    }

    position++;
    column++;
    // If any invalid character is found or no matches found
    return std::make_shared<Token>(UNDEF, "", line, column);
  }

  /**
   * summarry - returns an identifier or a keyword using lookahead
   * @method
   * @return {Token}
  */
  std::shared_ptr<Token> processAlphabet()
  {
    //look ahead buffer
    long lookAhead = position;
    //the column pointing identifier start
    long startColNum = column;

    //Containing the word
    std::string word = "";
    word += input.at(lookAhead);

    char nextChar = input.at(++lookAhead);

    // Looking ahead until valid characters
    while (lex::isAlphabet(nextChar) || lex::isDigit(nextChar))
    {
      word += nextChar;
      if (++lookAhead >= input.length())
        break;
      nextChar = input.at(lookAhead);
    }
    //updating new values
    position = lookAhead;
    column += word.length();

    //checking for keyword or identifier
    if (lex::isKeyWord(word))
      return std::make_shared<Token>(KEYWORD, word, line, startColNum);
    return std::make_shared<Token>(IDENTIFIER, word, line, startColNum);
  }

  /**
   * summarry - returns Delimeter tokens
   * @method processDelimeter
   * @return {Token}
  */
  std::shared_ptr<Token> processDelimeter()
  {
    std::string delim = "";
    delim += input.at(position++);
    return std::make_shared<Token>(DELIMETER, delim, line, column++);
  }
  /**
   * summarry - returns Operators token
   * @method processOperator
   * @return {Token}
  */
  std::shared_ptr<Token> processOperator()
  {
    std::string oper = "";
    oper += input.at(position++);
    return std::make_shared<Token>(OPERATOR, oper, line, column++);
  }

  /**
   * summarry - Skips all white space incrementing column and line count
   * @method
  */
  void skipWhiteSpace()
  {
    if (position >= input.length())
      return;
    char currentChar = input.at(position);

    while (lex::isWhiteSpace(currentChar))
    {
      if (currentChar == '\n')
      {
        column = 1;
        line += 1;
      }
      else
      {
        column += 1;
      }
      if (++position >= input.length())
        break;
      currentChar = input.at(position);
    }
  }
  /**
   * summarry - Prints out all the token
   * @method
  */
  void allTokens()
  {
    auto token = nextToken();
    while (token->type != EOT)
    {
      if (token->type != UNDEF)
      {
        std::cout << std::endl
                  << "TOKEN" << std::endl;
        std::cout << "TYPE: " << arr[token->type] << std::endl;
        std::cout << "VALUE: " << token->value << std::endl;
        std::cout << "LINE: " << token->line << std::endl;
        std::cout << "COLUMN: " << token->column << std::endl;
      }
      token = nextToken();
    }
  }

private:
  std::ifstream file;
  int position;
  int line;
  int column;
  std::string input;
};

#endif // LEXER_H
