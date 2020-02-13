/* token.h */

#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <map>

class Token {
    public: 
        enum Type { LeftBracket, RightBracket, Operator, UnaryOperator, Constant, Func };

        Token(const std::string &value, Type type);
        
        Type getType() const;
        const std::string &getValue() const;

    private:
        Type type;
        std::string value;

};

#endif // TOKEN_H
