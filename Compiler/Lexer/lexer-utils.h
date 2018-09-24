

#if !defined(LEXER_UTILS_H)
#define LEXER_UTILS_H
#include <set>
#include <algorithm>
#include <string>
namespace lex
{
const std::set<std::string> keyWords = {"abstract", "else", "instanceof", "super", "boolean", "enum", "int", "switch", "break", "export", "interface", "synchronized", "byte", "extends", "let", "this", "case", "false", "long", "throw", "catch", "final", "native", "throws", "char", "finally", "new", "transient", "class", "float", "null", "true", "const", "for", "package", "try", "continue", "function", "private", "typeof", "debugger", "goto", "protected", "var", "default", "if", "public", "void", "delete", "implements", "return", "volatile", "do", "import", "short", "while", "double", "in", "static", "with"};

bool isDigit(char a)
{
    return (a >= '0' && a <= '9');
}

bool isAlphabet(char a)
{
    return (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || a == '_' || a == '$';
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
int getNumberAlphabet(int a)
{
    // Zero
    if (a == '0')
        return 0;
    // b binary
    if (a == '1')
        return 1;
    // c octal
    if (a >= '2' && a <= '7')
        return 2;
    // d dec
    if (a == '8' || a == '9')
        return 3;
    // e hex
    if (a != 'b' && a != 'B' && a != 'e' && a != 'E' && ((a >= 'a' && a <= 'f') || (a >= 'A' && a <= 'F')))
        return 4;
    // f binary
    if (a == 'b' || a == 'B')
        return 5;
    // g octal
    if (a == 'o' || a == 'O')
        return 6;
    // h hex
    if (a == 'x' || a == 'X')
        return 7;
    // i Dot
    if (a == '.')
        return 8;
    // j Dot
    if (a == 'e' || a == 'E')
        return 9;
    // k sign
    if (a == '-' || a == '+')
        return 10;
    return -1;
}

int getMultiLineAlphabet(int a)
{
    if (a == '/')
        return 0;
    if (a == '*')
        return 1;
    return 2;
}
FAState *numberFSM()
{
    // Zero
    const std::string r0 = "a";
    // binary
    const std::string r0t1 = "(a|b)";
    // decimal
    const std::string r0t9 = "(a|b|c|d)";
    // decimal without 0
    const std::string r1t9 = "(b|c|d)";
    // octal
    const std::string r0t7 = "(a|b|c)";
    // hex
    const std::string r0tf = "(a|b|c|d|e|j|f)";
    // '.'
    const std::string dot = "i";
    // Exponent
    const std::string exp = "j";
    // binary notation
    const std::string bin = "f";
    // octal notation
    const std::string oct = "g";
    // hex notation
    const std::string hex = "h";
    // plus or minus notation
    const std::string pm = "k";

    // auto pregex = reToPostfix("(((((((b|c|d)(a|b|c|d)*)|a)((i(a|b|c|d)(a|b|c|d)*)|#))|(i(a|b|c|d)(a|b|c|d)*))((j(k|#)(a|b|c|d)(a|b|c|d)*)|#))|(af(a|b)(a|b)*)|(a(g|#)(a|b|c)(a|b|c)*)|(ah(a|b|c|d|e|j|f)(a|b|c|d|e|j|f)*))$");
    auto pregex = reToPostfix("((((((" +
                              r1t9 + r0t9 +
                              "*)|" + r0 +
                              ")((" + dot + r0t9 + r0t9 +
                              "*)|#))|(" + dot + r0t9 + r0t9 + "*))((" + exp +
                              "(" + pm +
                              "|#)" + r0t9 + r0t9 +
                              "*)|#))|(" +
                              r0 + bin + r0t1 + r0t1 +
                              "*)|(" + r0 +
                              "(" + oct +
                              "|#)" + r0t7 + r0t7 +
                              "*)|(" + r0 + hex + r0tf + r0tf +
                              "*))$");

    auto startState = directMethod(pregex);

    return startState.first;
}

/***
 * FAState *stringFSM()
 *{
 *    // a-> "" b-> any
 *    auto pregex = reToPostfix("ab*a");
 *    auto startState = directMethod(pregex);
 *    return startState.first;
 * **/

FAState *multiLineCommentFSM()
{
    auto pregex = reToPostfix("(abc*ba)$");
    auto startState = directMethod(pregex);
    DFA a(startState.first);
    std::cout << a.test("/**/",getMultiLineAlphabet);
    return startState.first;
}

// DFA
const auto NUMBER_FSM = numberFSM();
const auto MULTILINE_FSM = multiLineCommentFSM();
} // namespace lex

#endif // LEXER_UTILS_H
