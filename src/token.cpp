/* token.cpp */

#include "token.h"

Token::Token(const std::string &value, Type type) 
    : type( type ),
      value( value )
{

}

const std::string &Token::getValue() const {
    return value;
}

Token::Type Token::getType() const {
    return type;
}


