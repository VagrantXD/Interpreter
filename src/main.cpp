/* main.cpp */

#include <iostream>

#include "parser.h"
#include "expression.h"

int main() {
    auto parser = new Parser;

    while(true) {
        std::cout << "Введите выражение, или exit для выхода из приложения." << std::endl;
        std::cout << "Ввод: ";
        std::string str;
        std::getline(std::cin, str);

        if(str == "exit") break;

        auto expr = parser->parse( str );

        if( !expr ) {
            std::cout << "Error!" << std::endl;
            continue;
        }

        try {
            double ans = expr->calculate();
            std::cout << "Answer: " << ans << std::endl;
        } catch(const char *e) {
            std::cout << "Error, function not found!" << std::endl;
            
        } 

        std::cout << std::endl;

        delete expr;
    }

    delete parser;

    return 0;
}
