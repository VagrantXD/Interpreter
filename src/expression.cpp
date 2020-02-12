/* expression */

#include "expression.h"

Expression::Expression() 
    :tokens( new std::vector< std::string > )
{

}

Expression::~Expression() {
    delete tokens;
}

void Expression::addToken(const std::string &token) {
    tokens->push_back( token );
}
