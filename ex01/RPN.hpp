#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
class RPN
{
    private:
        std::stack<int> _stack;
        bool isNumber(const std::string& token);
        bool isOperator(const std::string& token);
    public:
        RPN();
        ~RPN();
        RPN& operator=(const RPN& other);
        RPN(const RPN &other);
        void parseArgv(const std::string& expression);
};

#endif