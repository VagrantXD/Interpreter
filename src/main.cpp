/* main.cpp */

#include <iostream>

#include "parser.h"
#include "expression.h"

int main() {
    auto parser = new Parser;
    std::string str;

    std::getline(std::cin, str);
    auto expr = parser->parse( str );

    if( !expr ) {
        std::cout << "Error!" << std::endl;
    }

    try {
        double ans = expr->calculate();
        std::cout << "Answer: " << ans << std::endl;
    } catch(const char *e) {
        std::cout << "Error, function not found!" << std::endl;
    } 

    delete parser;
    delete expr;

    return 0;
}
