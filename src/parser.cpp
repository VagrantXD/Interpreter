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
    handles.push_back(&Parser::unaryOperatorHandle);
}

Expression *Parser::parse(const std::string &expression) {
    expr = new Expression();

    for(auto &x : expression) {
        bool iserror = false;

        if( x == ' ') continue;

        state = (this->*handles[ state ])(x);

        if(iserror) {
            delete expr;
            return nullptr;
        }
    }

    state = (this->*handles[state])(')');
    expr->addToken( Token(")", Token::Type::RightBracket) );
    bracketCount++;

    if( (state == State::ErrorState) || (bracketCount != 0) ) {
        delete expr;
        return nullptr;
    }

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
    pushCurrent(ch, Token::Type::LeftBracket);
    bracketCount--; 

    if( isLeftBracket(ch) ) {
        return State::LeftBracketState;
    }

    if( std::isdigit(ch) ) {
        return State::NumberState;
    }

    if( isOperator(ch) ) {
        return State::UnaryOperatorState;
    }

    if( std::isalpha(ch) ) {
        return State::FuncState;
    }

    return State::ErrorState;
}

Parser::State Parser::rightBracketHandle(char ch) {
    pushCurrent(ch, Token::Type::RightBracket);
    bracketCount++;

    if( isOperator(ch) ) {
        return State::OperatorState;
    }

    if( isRightBracket(ch) ) {
        return State::RightBracketState;
    }

    return State::ErrorState;
}

Parser::State Parser::operatorHandle(char ch) {
    pushCurrent(ch, Token::Type::Operator);

    if( isLeftBracket(ch) ) {
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
        pushCurrent(ch, Token::Type::Constant);
        return State::OperatorState; 
    }

    if( isRightBracket(ch) ) {
        pushCurrent(ch, Token::Type::Constant);
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
        pushCurrent(ch, Token::Type::Func);
        return State::LeftBracketState;
    }

    return State::ErrorState;
}

Parser::State Parser::unaryOperatorHandle(char ch) {
    pushCurrent(ch, Token::Type::UnaryOperator);

    if( isLeftBracket(ch) ) {
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

Parser::State Parser::errorHandle(char ch) {
    return State::ErrorState;
}

void Parser::pushCurrent(char ch, Token::Type type) {
    expr->addToken( Token(current, type) );
    current = ch;
}
