//#include "constants.h"
#include <string>
#include <deque>
#include <vector>
#include <iostream>
#include <math.h>
#include "storage.cpp"

/*
Error codes:
100 - mismatched parenthesis
200 - operator error
300 - function error
400 - token error
500 - unary error
600 - shunting yard error
*/
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
            Unknown,
        };

        Type type;
        std::string str;
        int precedence;
        bool rightAssociative;
        bool unary = false;

        Token(Type type,const std::string& s, int precedence = -1, bool rightAssociative = false, bool unary = false)
        : type { type }
        , str ( s )
        , precedence { precedence }
        , rightAssociative { rightAssociative }
        , unary { unary }
        {}   

        std::string getStr() {
            return str;
        }
};

class Solver {
    public:
        VarStorage storage;
        
        Solver() {
            storage = VarStorage();
        }

        void printDeque(std::deque<Token> dq);
        double solve(const std::string& expr);
    private:
        std::deque<Token> expressionToTokens(std::string expr);
        std::deque<Token> shuntingYard(const std::deque<Token>& tokens);
};
/*
expressionToTokens takes expression string and tokenizes each
element of the equation (numbers, operators, functions, variables, etc).
Returns deque of tokens that can now be processed by the shunting yard algorithm

WIP
*/
std::deque<Token> Solver::expressionToTokens(std::string expr) {
    std::deque<Token> tokens;

    for(const auto* p = expr.c_str(); *p; ++p) {
        if(isblank(*p)) {
            //nothing
        } else if(isdigit(*p)) { //digit
            const auto* b = p;
            while(isdigit(*p) || *p == '.') {
                ++p;
            }
            const auto s = std::string(b, p);
            tokens.push_back(Token {Token::Type::Number, s});
            --p;
        } else if(isalpha(*p)){  //variable or function

            //checking for implied multiplication
            if(!tokens.empty()) {
                switch(tokens.back().type) {
                case Token::Type::Number:
                    tokens.push_back(Token {Token::Type::Operator, "*", 3, false, false});
                break;
                }
            }
            
            //get string
            const auto* b = p;
            while(isalpha(*p) && *p != ',') {
                ++p;
            }
            const auto s = std::string(b, p);
            
            //check if var or function
            if(storage.contains(s)) { //variable
                tokens.push_back(Token{Token::Type::Number, std::to_string(storage.getVarValue(s))});
            }
            else { //function
                tokens.push_back(Token {Token::Type::Function, s, 4, false, false});
            }
            --p;
        } else { //operator
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
                        rightAssociative = true;
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
void Solver::printDeque(std::deque<Token> dq) {
    cout << "[";
    for(int i = 0; i < dq.size(); i++) {
        cout << "'" + dq.at(i).str;
        if(i != dq.size()-1) {
            cout <<  "' ";
        } else {
            cout << "'";
        }
    }
    cout << "]";
}

//shunting yard algorithm
//WIP
//Can go through numbers, parenthesis, operators and functions. Still need to add constant and variable support
std::deque<Token> Solver::shuntingYard(const std::deque<Token>& tokens) {
    std::deque<Token> queue;
    std::vector<Token> stack;

    for(auto token : tokens) {
        switch(token.type) {
            case Token::Type::Number:
                queue.push_back(token);
                break;
            case Token::Type::Variable:
                queue.push_back(token);
                break;
            case Token::Type::Operator: {
                const auto o1 = token;

                while(!stack.empty()) {
                    const auto o2 = stack.back();

                    if((!o1.rightAssociative && o1.precedence <= o2.precedence) ||
                        (o1.rightAssociative && o1.precedence < o2.precedence)) {
                            stack.pop_back();
                            queue.push_back(o2);

                            continue;
                        }
                        break;
                }
                stack.push_back(o1);
            }
            break;
            case Token::Type::Function: {
                const auto o1 = token;

                while(!stack.empty()) {
                    const auto o2 = stack.back();

                    if((!o1.rightAssociative && o1.precedence <= o2.precedence) ||
                        (o1.rightAssociative && o1.precedence < o2.precedence)) {
                            stack.pop_back();
                            queue.push_back(o2);

                            continue;
                        }
                        break;
                }
                stack.push_back(o1);
            }
            break;
            case Token::Type::LeftParenthesis:
                stack.push_back(token);
            break;
            case Token::Type::RightParenThesis: {
                bool match = false;

                while(!stack.empty() && stack.back().type != Token::Type::LeftParenthesis) {
                    queue.push_back(stack.back());
                    stack.pop_back();
                    match = true;
                }

                if(!match && stack.empty()) {
                    printf("\nMismatched parenthesis\n");
                    throw 100;
                }
                stack.pop_back();
            }
            break;
            //case Token::Type::Constant
            default:
                printf("Error: %s", token.str);
                throw 600;
        }
    }

    while(!stack.empty()) {
            if(stack.back().type == Token::Type::LeftParenthesis) {
                printf("\nMismatched parenthesis\n");
                throw 100;
            }

            queue.push_back(std::move(stack.back()));
            stack.pop_back();
    }
    return queue;
}

//TODO solve(const std::string& expr)
double Solver::solve(const std::string& expr) {
    
    cout << "\nSolving expression: " << expr << std::endl;
    
    const auto tokens = expressionToTokens(expr);
    printf("\nTokenized expression:\n");
    printDeque(tokens);
    

    auto queue = shuntingYard(tokens);
    printf("\nPostfix expression:\n");
    printDeque(queue);

    std::vector<double> stack;

    double rhs;
    double lhs;
    double theta;

    while(!queue.empty()) {
        std::string op;

        const auto token = queue.front();
        queue.pop_front();

        switch(token.type) {
            case Token::Type::Number:
                stack.push_back(std::stod(token.str)); // convert token's string to double, push to stack
                op = "Pushing " + token.str;
            break;
            case Token::Type::Operator: {
                //if negative sign
                if(token.unary) {
                    const auto rhs = stack.back();
                    stack.pop_back();
                    //cout << std::endl << "Adding negative to " + std::to_string(rhs);
                    switch(token.str[0]) {
                        case 'm':
                            stack.push_back(-rhs);
                        break;
                        default:
                            throw 500;
                            printf("\nUnary operator error: %s\n", token.str);
                            //exit(0);
                    }
                    op = "Pushing (unary) " + token.str + " " + std::to_string(rhs);
                }
                else {  //operators
                    //get 2 previous numbers
                    rhs = stack.back();
                    stack.pop_back();

                    lhs = stack.back();
                    stack.pop_back();
                    
                    switch(token.str[0]) {
                        case '^':
                            stack.push_back(static_cast<double>(pow(lhs, rhs)));
                        break;
                        case '*':
                            stack.push_back(lhs * rhs);
                        break;
                        case '/':
                            stack.push_back(lhs / rhs);
                        break;
                        case '+':
                            stack.push_back(lhs + rhs);
                        break;
                        case '-':
                            stack.push_back(lhs - rhs);
                        break;
                        default:
                            printf("Operator error: %s", token.str);
                            throw 200;
                            //exit(0);
                    }
                    op = "Pushing " + std::to_string(lhs) + " " + token.str + " " + std::to_string(rhs);
                }
            }
            break;
            case Token::Type::Function:

                theta = stack.back();
                stack.pop_back();

                if(token.str == "sin") {
                    stack.push_back(sin(theta));
                }
                else if(token.str == "cos") {
                    stack.push_back(cos(theta));
                }
                else if(token.str == "tan") {
                    stack.push_back(tan(theta));
                }
                else if(token.str == "asin") {
                    stack.push_back(asin(theta));
                }
                else if(token.str == "acos") {
                    stack.push_back(acos(theta));
                }
                else if(token.str == "atan") {
                    stack.push_back(atan(theta));
                }
                else if(token.str == "ln") {
                    stack.push_back(log(theta));
                }
                else if(token.str == "log") {
                    stack.push_back(log10(theta));
                }
                else {
                    printf("\nFunction Error: %s\n", token.str);
                    throw 300;
                    //exit(0);
                }
                op = "Pushing " + token.str + "(" + std::to_string(theta) + ")";
            break;
            default:
                printf("Token error: %s", token.str);
                throw 400;
                //exit(0);
        }
        cout << std::endl << op;
    }
    //check for implied mutliplication
    while(stack.size() > 1) {
        rhs = stack.back();
        stack.pop_back();

        lhs = stack.back();
        stack.pop_back();

        stack.push_back(lhs * rhs);

        printf("\nPushing implied multiply: %f * %f = %f", lhs, rhs, lhs*rhs);
    }

    //return result
    
    printf("\nResult: %f", stack.back());
    return stack.back();
}


int main() {
    std::string test = "5+5";
    
    Solver solver;
    
    solver.solve(test);
}
