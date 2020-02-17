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
    std::stack< Token > stack;
    std::stack< double > resultStack;
    stack.push( tokens->front() );

    auto it = tokens->begin();
    it++;

    while( it != tokens->end() ) {
        if( it->getType() == Token::Type::Constant ) {
            resultStack.push( std::stod( it->getValue() ) );
            ++it;
            continue;
        } // if 

        if( it->getType() == Token::Type::LeftBracket ) {
            stack.push(*it++);
            continue;
        } // if

        if( it->getType() == Token::Type::RightBracket ) {
            auto top = stack.top();
            stack.pop();
            while( top.getType() != Token::Type::LeftBracket ) {
                if( isOperatorOrFunc( top ) ) {       
                    if( !counting(resultStack, top) ) {
                        throw "Error!";
                    }
                }
                else {
                    resultStack.push( std::stod( top.getValue() ) );
                }
                top = stack.top();
                stack.pop();
            }
            it++;
            continue;
        } // if

        if( isOperatorOrFunc( *it ) ) {
            auto itPriority = (*operationPriority)[ it->getValue() ];
            auto top = stack.top();

            while( isOperatorOrFunc( *it ) ) { 
                auto topPriority = (*operationPriority)[ top.getValue() ];
                if(topPriority >= itPriority) {
                    stack.pop();
                    if( !counting( resultStack, top ) ) {
                        throw "Error!";    
                    }
                    top = stack.top();
                }
                else {
                    break; 
                }
            }
            stack.push( *it );

            it++;
            continue;
        } // if
    } // while

    return resultStack.top();
}

void Expression::addToken(const Token &token) {
    tokens->push_back( token );
}

bool Expression::counting(std::stack< double > &stack, const Token &currentOperator) {

    double first = 0;
    if( !stack.empty() ) { 
        first = stack.top();
        stack.pop();
    }

    if( currentOperator.getType() == Token::Type::Operator ) {
        auto second = stack.top();
        stack.pop();

        if( currentOperator.getValue() == "+" ) {
            stack.push( second + first );
            return true;
        }

        if( currentOperator.getValue() == "-" ) {
            stack.push( second - first );
            return true;
        }

        if( currentOperator.getValue() == "*" ) {
            stack.push( second * first );
            return true;
        }

        if( currentOperator.getValue() == "/" ) {
            stack.push( second / first );
            return true;
        }

        if( currentOperator.getValue() == "^" ) {
            stack.push( std::pow(second, first) );
            return true;
        }
    }

    if( currentOperator.getType() == Token::Type::UnaryOperator ) {
        if( currentOperator.getValue() == "+" ) {
            stack.push( +first );
            return true;
        }

        if( currentOperator.getValue() == "-" ) {
            stack.push( -first ); 
            return true;
        }
    } 

    if( currentOperator.getType() == Token::Type::Func ) {
        if( currentOperator.getValue() == "sin" ) {
            stack.push( std::sin(first) );
            return true;
        }

        if( currentOperator.getValue() == "cos" ) {
            stack.push( std::cos(first) );
            return true;
        }

        if( currentOperator.getValue() == "tg" ) {
            stack.push( std::tan(first) );
            return true;
        }

        if( currentOperator.getValue() == "ctg" ) {
            stack.push( std::cos(first) / std::sin(first) );
            return true;
        }

        if( currentOperator.getValue() == "atg" ) {
            stack.push( std::atan(first) );
            return true;
        }

        if( currentOperator.getValue() == "exp" ) {
            stack.push( std::exp(first) );
            return true;
        }

        if( currentOperator.getValue() == "ln" ) {
            stack.push( std::log(first) );
            return true;
        }

        if( currentOperator.getValue() == "abs" ) {
            stack.push( std::abs(first) );
            return true;
        }
    }

    return false;
}

bool Expression::isOperatorOrFunc(const Token &token) const {
    return ( token.getType() == Token::Type::Operator ) ||
        ( token.getType() == Token::Type::UnaryOperator ) ||
        ( token.getType() == Token::Type::Func );
}
