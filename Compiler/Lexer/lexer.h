
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
#include "headers/direct_method.h"
#include "headers/dfa.h"
#include "headers/fastate.h"
#include "headers/nfa.h"
#include "headers/enfa.h"
#include "headers/enfatodfa.h"
#include <set>
#include "headers/re_to_postfix.h"
#include "headers/postfix_re_to_enfa.h"
#include "lexer-utils.h"

typedef enum
{
  KEYWORD,
  IDENTIFIER,
  BOOLEAN,
  NUMBER,
  STRING,
  REGEXP,
  OPERATOR,
  DELIMETER,
  COMMENT,
  UNDEF,
  EOT
} TokenType;
std::string arr[11] =
    {
        "KEYWORD",
        "IDENTIFIER",
        "BOOLEAN",
        "NUMBER",
        "STRING",
        "REGEXP",
        "OPERATOR",
        "DELIMETER",
        "COMMENT",
        "UNDEF",
        "EOT"};

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
 * 
*/
  Lexer()
  {
    this->tokenCount = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    this->position = 0;
    this->line = 1;
    this->column = 1;
  }

  /**
 * @constructor
 * @params {string} file = file name
*/
  Lexer(std::string fileName)
  {
    this->tokenCount = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    this->position = 0;
    this->line = 1;
    this->column = 1;
    file.open(fileName);

    if (!file)
      throw "Can't Open File";
    std::stringstream buffer;
    buffer << file.rdbuf();
    this->input = buffer.str();
    // std::cout << this->input;
  }

  /**
   * summary - sets input
   * @method
   * @setter
  */
  void setInput(std::string input)
  {
    this->input = input;
  }
  /**
   * summary - returns next token in sequence pointed by line  number and column number
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
      return processDigit();
    }
    else if (lex::isStringOrChar(character))
    {
      return processStringChar();
    }
    else if (lex::isDelimeter(character))
    {
      return processDelimeter();
    }
    else if (character == '/')
    {
      if ((position + 1) < input.length())
      {
        const auto nextChar = input.at(position + 1);
        if (nextChar == '/')
          return processSingleLineComment();
        if (nextChar == '*')
          return processMultiLineComment();
      }
      // if (position > 0 && !lex::isAlphabet(input.at(position)) && !lex::isDigit(input.at(position)))
      // {
      //   return processRegExp();
      // }
      // return processOperator();
    }
    else if (lex::isOperator(character))
    {
      return processOperator();
    }
    tokenCount[UNDEF]++;
    position++;
    column++;
    // If any invalid character is found or no matches found
    return std::make_shared<Token>(UNDEF, "", line, column);
  }

  /**
   * summary - returns single line comment
   * @method
   * @return {std::shared_ptr<Token>} - A Token
  */
  std::shared_ptr<Token> processSingleLineComment()
  {
    std::string comment = "";
    auto startColumn = column;
    char character = input.at(position);
    while (character != '\n')
    {
      comment += character;

      if (++position >= input.length())
        break;
      character = input.at(position);
    }
    position++;
    column = 1;
    line += 1;
    tokenCount[COMMENT]++;
    return std::make_shared<Token>(COMMENT, comment, line - 1, startColumn);
  }
  /**
   * summary - returns multi line comment
   * @method
   * @return {std::shared_ptr<Token>} - A Token
  */
  std::shared_ptr<Token> processMultiLineComment()
  {
    std::string comment = "";
    auto startColumn = column;
    auto startLine = line;
    char character;
    auto currentState = lex::MULTILINE_FSM;
    do
    {
      character = input.at(position);
      // std::cout << character;
      if (character == '\n')
      {
        line++;
        column = 1;
      }
      comment += character;
      column++;

      if (++position >= input.length())
        break;

      currentState = DFA::next(currentState, lex::getMultiLineAlphabet, character);

    } while (!currentState->isFinal);

    tokenCount[COMMENT]++;
    return std::make_shared<Token>(COMMENT, comment, startLine, startColumn);
  }

  /**
   * summary - returns an identifier or a keyword using lookahead
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

    char nextChar = input.at(lookAhead);

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
    {
      tokenCount[KEYWORD]++;
      return std::make_shared<Token>(KEYWORD, word, line, startColNum);
    }
    tokenCount[IDENTIFIER]++;
    return std::make_shared<Token>(IDENTIFIER, word, line, startColNum);
  }

  /**
   * summary - returns Delimeter tokens
   * @method processDelimeter
   * @return {Token}
  */
  std::shared_ptr<Token>
  processDelimeter()
  {
    std::string delim = "";
    delim += input.at(position++);
    tokenCount[DELIMETER]++;
    return std::make_shared<Token>(DELIMETER, delim, line, column++);
  }
  /**
   * summary - returns Operators token
   * @method processOperator
   * @return {Token}
  */
  std::shared_ptr<Token> processOperator()
  {
    std::string oper = "";
    oper += input.at(position++);
    tokenCount[OPERATOR]++;
    return std::make_shared<Token>(OPERATOR, oper, line, column++);
  }

  /**
   * summary - returns Number Token 
   * @method processDigit
   * @return {Token}
  */
  std::shared_ptr<Token> processStringChar()
  {
    std::string literal = "";
    auto lookAhead = this->position;
    auto column = this->column;

    const auto quote = input.at(position);
    literal += quote;
    char character;
    do
    {
      if (++lookAhead >= input.length())
      {
        break;
      }
      character = input.at(lookAhead);

      if (character == '\n')
      {
        position = lookAhead + 1;
        line += 1;
        column = 1;
        return std::make_shared<Token>(UNDEF, literal, line, column);
      }
      literal += character;

    } while (character != quote);

    this->position = lookAhead + 1;
    this->column += literal.length();
    tokenCount[STRING]++;
    return std::make_shared<Token>(STRING, literal, line, column);
  }
  /**
   * summary - returns Number Token 
   * @method processDigit
   * @return {Token}
  */
  std::shared_ptr<Token> processDigit()
  {
    std::string number = "";
    auto lookAhead = this->position;
    auto column = this->column;
    auto position = this->position;
    auto currentState = lex::NUMBER_FSM;
    do
    {
      if (lookAhead >= input.length())
        break;
      auto character = input.at(lookAhead);
      currentState = DFA::next(currentState, lex::getNumberAlphabet, character);

      if (currentState->isFinal)
      {
        position = lookAhead;
      }
      number += character;
      ++lookAhead;

    } while (!currentState->isRejected);

    std::string acceptedNumber = number.substr(0, position - this->position + 1);
    this->position = position + 1;
    this->column += acceptedNumber.length();
    tokenCount[NUMBER]++;
    return std::make_shared<Token>(NUMBER, acceptedNumber, line, column);
  }

  /**
   * summary - Skips all white space incrementing column and line count
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
   * summary - Prints out all the token
   * @method
  */
  void allTokens()
  {
    std::ofstream file("log.txt");
    auto token = nextToken();
    while (token->type != EOT)
    {
      if (token->type != UNDEF)
      {
        file << std::endl
             << "TOKEN" << std::endl;
        file << "TYPE: " << arr[token->type] << std::endl;
        file << "VALUE: " << token->value << std::endl;
        file << "LINE: " << token->line << std::endl;
        file << "COLUMN: " << token->column << std::endl;
      }
      token = nextToken();
    }

    std::cout << "SUMMARRY" << std::endl;
    for (size_t i = 0; i < tokenCount.size(); i++)
    {
      std::cout << arr[i] << "COUNT: " << tokenCount[i] << std::endl;
    }
    std::cout << std::endl
              << "TOTAL TOKENS COUNT: "
              << std::accumulate(tokenCount.begin(), tokenCount.end(), 0) << std::endl;
  }

  void toHTML()
  {
    std::ofstream file("output.html");
    file << " <div class=\"snippet\"> <style scoped> * { margin: 0; padding: 0; box-sizing: border-box; font-family: monospace; } .KEYWORD { color: #45a1ce; } .IDENTIFIER { color: black; } .NUMBER { color: purple; } .OPERATOR { color: #eaaf00; } .DELIMETER { color: #0004b7; } .STRING { color: green; } .COMMENT { color: #5050ff; font-style: italic; } .UNDEF { text-decoration: underline; color: red; } .snippet { background: white; padding: 10px; display: flex; align-items: stretch; overflow: auto; } .snippet .line div::after { content: \".\" } .snippet .line { padding-right: 10px; height: 100%; border-right: 2px solid red; user-select: none; } pre { padding-left: 1em; } </style><div class=\"line\"> <div>1</div> <div>2</div> <div>3</div> <div>4</div> <div>5</div> <div>6</div> <div>7</div> <div>8</div> <div>9</div> <div>10</div> <div>11</div> <div>12</div> </div><pre>";
    auto token = nextToken();
    int line = 1;
    int column = 1;

    auto addLine = [&](int l) mutable {
      const auto diff = l - line;
      for (int i = 0; i < diff; i++)
      {
        file << "\n";
      }
      line = l;
      column = 1;
    };
    auto addColumn = [&](int col) mutable {
      const auto diff = col - column;
      for (int i = 0; i < diff; i++)
      {
        file << " ";
      }
    };
    while (token->type != EOT)
    {

      if (line != token->line)
        addLine(token->line);
      if (column != token->column)
        addColumn(token->column);
      file << "<span class=\"" << arr[token->type] << "\">" << token->value << "</span>";
      column = token->column + token->value.length();

      token = nextToken();
    }
    file << "</pre></div>";
    file.close();
  }

  std::string toString()
  {
    std::stringstream file;
    file << " <div class=\"snippet\"> <style scoped> * { margin: 0; padding: 0; box-sizing: border-box; font-family: monospace; } .KEYWORD { color: #45a1ce; } .IDENTIFIER { color: black; } .NUMBER { color: purple; } .OPERATOR { color: #eaaf00; } .DELIMETER { color: #0004b7; } .STRING { color: green; } .COMMENT { color: #5050ff; font-style: italic; } .UNDEF { text-decoration: underline; color: red; } .snippet { background: white; padding: 10px; display: flex; align-items: stretch; overflow: auto; } .snippet .line div::after { content: \".\" } .snippet .line { padding-right: 10px; height: 100%; border-right: 2px solid red; user-select: none; } pre { padding-left: 1em; } </style><div class=\"line\"> <div>1</div> <div>2</div> <div>3</div> <div>4</div> <div>5</div> <div>6</div> <div>7</div> <div>8</div> <div>9</div> <div>10</div> <div>11</div> <div>12</div> </div><pre>";
    auto token = nextToken();
    int line = 1;
    int column = 1;

    auto addLine = [&](int l) mutable {
      const auto diff = l - line;
      for (int i = 0; i < diff; i++)
      {
        file << "\n";
      }
      line = l;
      column = 1;
    };
    auto addColumn = [&](int col) mutable {
      const auto diff = col - column;
      for (int i = 0; i < diff; i++)
      {
        file << " ";
      }
    };
    while (token->type != EOT)
    {

      if (line != token->line)
        addLine(token->line);
      if (column != token->column)
        addColumn(token->column);
      file << "<span class=\"" << arr[token->type] << "\">" << token->value << "</span>";
      column = token->column + token->value.length();

      token = nextToken();
    }
    file << "</pre></div>";
    std::string data = file.str();
    return data;
  }

private:
  std::ifstream file;
  int position;
  int line;
  int column;
  std::string input;
  std::vector<long> tokenCount;
};

#endif // LEXER_H
