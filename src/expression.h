/* expression.h */

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <vector>
#include <string>

class Expression {

    public:
        Expression();
        ~Expression();

    public:
        void addToken(const std::string &token);

        const std::vector< std::string > *getTokens() const { return tokens; }
    
    private:
        std::vector< std::string > *tokens;

};

#endif // EXPRESSION
