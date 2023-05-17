#include "constants.h"
#include <string>
#include <deque>

/*
Token class
To store necessary information for shunting yard algorithm
*/
class Token {
    public:

        enum class Type {
            Number,
            Constant,
            Variable,
            Operator,
            Function,
            LeftParenthesis,
            RightParenThesis
        };

        Type type;
        std::string str;
        int precedence;
        bool rightAssociative;

        Token (Type t, std::string s, int prec = -1, bool ra = false) {
            type = t;
            str = s;
            precedence = prec;
            rightAssociative = ra;
        }
};

std::deque<Token> expressionToTokens(std::string expr) {
    std::deque<Token> tokens;
}