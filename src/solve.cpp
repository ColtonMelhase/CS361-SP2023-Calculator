#include "constants.h"
#include <string>
#include <deque>
#include <iostream>

using std::cout;
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
            RightParenThesis,
            Unary,
            Unknown,
        };

        Type type;
        std::string str;
        int precedence;
        bool rightAssociative;
        bool unary = false;

        Token (Type t, std::string s, int prec = -1, bool ra = false, bool unary = false) {
            type = t;
            str = s;
            precedence = prec;
            rightAssociative = ra;
        }
};

/*
expressionToTokens takes expression string and tokenizes each
element of the equation (numbers, operators, functions, variables, etc).
Returns deque of tokens that can now be processed by the shunting yard algorithm

WIP
*/
std::deque<Token> expressionToTokens(std::string expr) {
    std::deque<Token> tokens;

    for(const auto* p = expr.c_str(); *p; ++p) {
        if(isblank(*p)) {
            //nothing
        } else if(isdigit(*p)) {
            const auto* b = p;
            while(isdigit(*p)) {
                ++p;
            }
            const auto s = std::string(b, p);
            tokens.push_back(Token {Token::Type::Number, s});
            --p;
        } else {
            Token::Type t = Token::Type::Unknown;
            char c = *p;
            int precedence = -1;
            bool rightAssociative = false;
            bool unary = false;

            switch(c) {
                default:
                    break;
                case '(': t = Token::Type::LeftParenthesis; break;
                case ')': t = Token::Type::RightParenThesis; break;
                case '^': t = Token::Type::Operator; precedence = 4; rightAssociative = true; break;
                case '*': t = Token::Type::Operator; precedence = 3; break;
                case '/': t = Token::Type::Operator; precedence = 3; break;
                case '+': t = Token::Type::Operator; precedence = 2; break;
                case '-':
                    //if the '-' is the first token, after an operator, or after a left-parenthesis
                    if(tokens.empty() || tokens.back().type == Token::Type::Operator || tokens.back().type == Token::Type::LeftParenthesis) {
                        //then its a unary '-' (negative sign)
                        unary = true;
                        c = 'm';
                        t = Token::Type::Operator;
                        precedence = 5;
                    }
                    else {
                        t = Token::Type::Operator;
                        precedence = 2;
                    }
                    break;
            }
            auto s = std::string(1, c);
            tokens.push_back(Token {t, s, precedence, rightAssociative, unary});
        }
    }

    return tokens;
}

/*
debug function to test tokenizer

string test = "-59+4*5/2-110"
->
['m', '59', '+', '4', '*', '5', '/', '2', '-', '110']
*/
void printDeque(std::deque<Token> dq) {
    cout << "[";
    for(int i = 0; i < dq.size(); i++) {
        cout << "'" + dq.at(i).str;
        if(i != dq.size()-1) {
            cout <<  "', ";
        } else {
            cout << "'";
        }
    }
    cout << "]";
}