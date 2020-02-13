/* main.cpp */

#include <iostream>

#include "parser.h"
#include "expression.h"

int main() {
    auto parser = new Parser;

    std::string str;
    std::getline(std::cin, str);
    auto expr = parser->parse( str );

    //auto expr = parser->parse("(1.44-5.8 * cos(89)) ^ (exp(78 + 5.32) / 78-989.94)");

    if( expr ) {
        for( auto &x : *expr->getTokens() )
            std::cout << x.getValue() << "\t" << x.getType() << std::endl;
    }
    else {
        std::cout << "Error!" << std::endl;
    }

    expr->calculate();

    delete parser;
    delete expr;

    return 0;
}
