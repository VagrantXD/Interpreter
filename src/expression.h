/* expression.h */

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <vector>
#include <string>
#include <stack>

#include "token.h"

class Expression {

    public:
        Expression();
        ~Expression();

    public:
        double calculate();

        void addToken(const Token &token);

        const std::vector< Token > *getTokens() const { return tokens; }
    
    private:
        bool counting(std::stack< double > &stack, const Token &currentOperator);

        bool isOperatorOrFunc(const Token &token) const;

    private:
        std::vector< Token > *tokens;
        std::map<std::string, int> *operationPriority;

};

#endif // EXPRESSION
