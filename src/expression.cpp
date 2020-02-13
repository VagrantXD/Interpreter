/* expression */

#include <iostream>
#include <cmath>

#include "expression.h"

Expression::Expression() 
    :tokens( new std::vector< Token > )
{
    operationPriority = new std::map<std::string, int> { 
        {"+", 1}, 
        {"-", 1}, 
        {"*", 2}, 
        {"/", 2}, 
        {"^", 3},
        {"cos", 10 },
        {"sin", 10 },
        {"tg", 10 },
        {"ctg", 10 },
        {"atg", 10 },
        {"exp", 10 },
        {"ln", 10 },
        {"abs", 10 }
    };
}

Expression::~Expression() {
    delete tokens;
}

double Expression::calculate() {
    auto expr = new Expression;
    std::stack< Token > stack;
    std::stack< Token > resultStack;
    stack.push( tokens->front() );

    auto it = tokens->begin();
    it++;

    while( !stack.empty() ) {
        if( it != tokens->end() ) {
            if( it->getType() == Token::Type::Constant ) {
                expr->addToken(*it++);
                continue;
            } 

            if( it->getType() == Token::Type::LeftBracket ) {
                stack.push(*it++);
                continue;
            }

            if( it->getType() == Token::Type::RightBracket ) {
                auto top = stack.top();
                stack.pop();
                while( top.getType() != Token::Type::LeftBracket ) {
                    expr->addToken( top );
                    top = stack.top();
                    stack.pop();
                }
                it++;
                continue;
            }

            bool operatorAndFunc = (it->getType() == Token::Type::Operator) ||
                (it->getType() == Token::Type::Func) ||
                (it->getType() == Token::Type::UnaryOperator);

            if( operatorAndFunc ) {
                auto itPriority = (*operationPriority)[ it->getValue() ];
                auto top = stack.top();

                while( operatorAndFunc ) { 
                    auto topPriority = (*operationPriority)[ top.getValue() ];
                    if(topPriority > itPriority) {
                        stack.pop();
                        expr->addToken( top );
                        top = stack.top();
                    }
                    else {
                        break; 
                    }
                }
                stack.push( *it );

                it++;
                continue;
            } 

            if( it->getType() == Token::Type::Func ) {
                expr->addToken( *it++ );
                continue;
            }
        } // if
    } // while

    for( auto &x : *expr->getTokens() )
        std::cout << x.getValue() << " ";
    std::cout << std::endl;

    return 0.0;
}

void Expression::addToken(const Token &token) {
    tokens->push_back( token );
}

void Expression::counting(std::stack< Token > &stack, const Token &currentOperator) {
    auto first = std::stod( stack.top().getValue() );
    stack.pop();

    if( currentOperator.getType() == Token::Type::Operator ) {
        auto second = std::stod( stack.top().getValue() );
        stack.pop();

        if( currentOperator.getValue() == "+" ) {
            stack.push( Token( std::to_string(first + second), Token::Type::Constant ) );
            return;
        }

        if( currentOperator.getValue() == "-" ) {
            stack.push( Token( std::to_string(first - second), Token::Type::Constant ) );
            return;
        }

        if( currentOperator.getValue() == "*" ) {
            stack.push( Token( std::to_string(first * second), Token::Type::Constant ) );
            return;
        }

        if( currentOperator.getValue() == "/" ) {
            stack.push( Token( std::to_string(first * second), Token::Type::Constant ) );
            return;
        }

        if( currentOperator.getValue() == "^" ) {
            stack.push( Token( std::to_string( std::pow(first, second) ), Token::Type::Constant ) );
            return;
        }
    }
}
