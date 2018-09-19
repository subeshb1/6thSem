

#if !defined(LEXER_UTILS_H)
#define LEXER_UTILS_H
#include <vector>
#include <algorithm>
#include <string>
namespace lex
{

bool isDigit(char a)
{
    return (a >= '0' && a <= '9');
}

bool isAlphabet(char a)
{
    return (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || a == '_';
}

bool isWhiteSpace(char a)
{
    return a == ' ' || a == '\t' || a == '\n' || a == '\b' || a == '\r' || a == '\v';
}

bool isDelimeter(char a)
{
    return a == '{' || a == '}' || a == '[' || a == ']' || a == '(' || a == ')' || a == ',' || a == ';' || a == ':' || a == '#' || a == '.';
}

bool isOperator(char a)
{
    return a == '+' || a == '-' || a == '*' || a == '/' || a == '^' || a == '%' || a == '!' || a == '&' || a == '?' || a == '|' || a == '~' || a == '>' || a == '=' || a == '<';
}

bool isKeyWord(std::string keyWord)
{
    const std::vector<std::string> keyWords = {"asm", "else", "new", "this", "auto", "enum", "operator", "throw", "bool", "explicit", "private", "true", "break", "export", "protected", "try", "case", "extern", "public", "typedef", "catch", "false", "register", "typeid", "char", "float", "reinterpret_cast", "typename", "class", "for", "return", "union", "const", "friend", "short", "unsigned", "const_cast", "goto", "signed", "using", "continue", "if", "sizeof", "virtual", "default", "inline", "static", "void", "delete", "int", "static_cast", "volatile", "do", "long", "struct", "wchar_t", "double", "mutable", "switch", "while", "dynamic_cast", "namespace", "template"};
    return std::find(keyWords.begin(), keyWords.end(), keyWord) != keyWords.end();
}
} // namespace lex

#endif // LEXER_UTILS_H
