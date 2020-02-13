/* parser.h */

#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "token.h"

class Expression;

class Parser {
    public:
        Parser();

        enum State { LeftBracketState, RightBracketState, NumberState, FuncState, OperatorState, ErrorState, UnaryOperatorState };

        Expression *parse(const std::string &expression);

        static bool isLeftBracket(char ch);
        static bool isRightBracket(char ch);
        static bool isOperator(char ch);

    private:
        State leftBracketHandle(char ch);
        State rightBracketHandle(char ch);
        State operatorHandle(char ch);
        State numberHandle(char ch);
        State funcHandle(char ch);
        State errorHandle(char ch);
        State unaryOperatorHandle(char ch);

        void pushCurrent(char ch, Token::Type type);

    private:
        State state;
        std::vector< State (Parser::*)(char) > handles;

        int bracketCount;
        std::string current;

        Expression *expr;
};

#endif // PARSER_H
