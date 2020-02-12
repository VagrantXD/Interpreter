/* parser.cpp */

#include <iostream>
#include <cctype>
#include "expression.h"
#include "parser.h"

Parser::Parser() 
    : state( State::LeftBracketState ),
      bracketCount( 0 ),
      current("(")
{
    handles.push_back(&Parser::leftBracketHandle);
    handles.push_back(&Parser::rightBracketHandle);
    handles.push_back(&Parser::numberHandle); 
    handles.push_back(&Parser::funcHandle);
    handles.push_back(&Parser::operatorHandle);
    handles.push_back(&Parser::errorHandle);
}

Expression *Parser::parse(const std::string &expression) {
    expr = new Expression();

    for(auto &x : expression) {
        bool iserror = false;

        if( x == ' ') continue;

        state = (this->*handles[ state ])(x);

        if(iserror) {
            return nullptr;
        }
    }

    if( state == State::ErrorState )
        return nullptr;

    expr->addToken(current);
    expr->addToken(")");

    return expr;
}

bool Parser::isLeftBracket(char ch) {
    return ch == '(';
}

bool Parser::isRightBracket(char ch) {
    return ch == ')';
}

bool Parser::isOperator(char ch) {
    return (ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') || (ch == '^');
}

Parser::State Parser::leftBracketHandle(char ch) {
    pushCurrent(ch);

    if( isLeftBracket(ch) ) {
        bracketCount--; 
        return State::LeftBracketState;
    }

    if( std::isdigit(ch) ) {
        return State::NumberState;
    }

    if( std::isalpha(ch) ) {
        return State::FuncState;
    }

    if( isOperator(ch) ) {
        return State::OperatorState;
    }

    return State::ErrorState;
}

Parser::State Parser::rightBracketHandle(char ch) {
    pushCurrent(ch);

    if( isOperator(ch) ) {
        return State::OperatorState;
    }

    if( isRightBracket(ch) ) {
        bracketCount++;
        return State::RightBracketState;
    }

    return State::ErrorState;
}

Parser::State Parser::operatorHandle(char ch) {
    pushCurrent(ch);

    if( isLeftBracket(ch) ) {
        bracketCount--;
        return State::LeftBracketState;
    }

    if( std::isdigit(ch) ) {
        return State::NumberState;
    }

    if( std::isalpha(ch) ) {
        return State::FuncState;
    }

    return State::ErrorState;
}

Parser::State Parser::numberHandle(char ch) {
    if( isOperator(ch) ) { 
        pushCurrent(ch);
        return State::OperatorState; 
    }

    if( isRightBracket(ch) ) {
        pushCurrent(ch);
        return State::RightBracketState;
    }

    if( std::isdigit(ch) || ch == '.' ) {
        current += ch; 
        return State::NumberState; 
    }

    return State::ErrorState;
}

Parser::State Parser::funcHandle(char ch) {
    if( std::isalpha(ch) ) {
        current += ch;
        return State::FuncState;
    }

    if( isLeftBracket(ch) ) {
        pushCurrent(ch);
        return State::LeftBracketState;
    }

    return State::ErrorState;
}

Parser::State Parser::errorHandle(char ch) {
    return State::ErrorState;
}

void Parser::pushCurrent(char ch) {
    expr->addToken(current);
    current = ch;
}
