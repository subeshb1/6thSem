

#if !defined(LEXER_UTILS_H)
#define LEXER_UTILS_H
#include <set>
#include <algorithm>
#include <string>
namespace lex
{
const std::set<std::string> keyWords = {"asm", "else", "new", "this", "auto", "enum", "operator", "throw", "bool", "explicit", "private", "true", "break", "export", "protected", "try", "case", "extern", "public", "typedef", "catch", "false", "register", "typeid", "char", "float", "reinterpret_cast", "typename", "class", "for", "return", "union", "const", "friend", "short", "unsigned", "const_cast", "goto", "signed", "using", "continue", "if", "sizeof", "virtual", "default", "inline", "static", "void", "delete", "int", "static_cast", "volatile", "do", "long", "struct", "wchar_t", "double", "mutable", "switch", "while", "dynamic_cast", "namespace", "template", "elif", "endif", "ifdef", "ifndef", "define", "undef", "include", "line", "error", "pragma", "defined"};

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
bool isStringOrChar(char a)
{
    return a == '\'' || a == '"';
}
bool isKeyWord(std::string keyWord)
{
    return keyWords.find(keyWord) != keyWords.end();
}

FAState *numberFSM()
{
    // a-> digit b-> '.'
    auto pregex = reToPostfix("((aa*((baa*)|#))|(baa*))((c(d|e|#)aa*)|#)$");
    auto startState = directMethod(pregex);
    return startState.first;
}
FAState *stringFSM()
{
    // a-> "" b-> any
    auto pregex = reToPostfix("ab*a");
    auto startState = directMethod(pregex);
    return startState.first;
}

const auto NUMBER_FSM = numberFSM();
const auto STRING_FSM = stringFSM();

int getNumberAlphabet(int a)
{
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
}
int getStringAlphabet(int a)
{
    if (a == '\'')
        return 0;
    return 1;
}
int getCharAlphabet(int a)
{
    if (a == '"')
        return 0;
    return 1;
}

} // namespace lex

#endif // LEXER_UTILS_H
