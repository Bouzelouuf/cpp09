#include "RPN.hpp"
#include <cctype>

RPN::RPN(){}

RPN::~RPN(){}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
        _stack = other._stack;
    return *this;
}

RPN::RPN(const RPN &other)
{
    *this = other;
}

bool RPN::isNumber(const std::string &token)
{
    if (token.length() != 1)
        return false;
    return isdigit(token[0]);
}

bool RPN::isOperator(const std::string &token)
{
    if (token == "+" || token == "-" || token == "*" || token == "/")
        return true;
    return false;
}

void RPN::parseArgv(const std::string& expression)
{
    std::stringstream ss(expression);
    std::string token;
    while (ss >> token)
    {
        if (isNumber(token))
        {
            _stack.push(atoi(token.c_str()));
        }
        else if (isOperator(token))
        {
            if (_stack.size() < 2)
            {
                std::cerr << "Error" << std::endl;
                return;
            }
            int b = _stack.top();//top return le top
            _stack.pop(); // retire le top 
            // top + pop = return + delete value du top
            int a = _stack.top();
            _stack.pop();
            int result;
            if (token == "+")
                result = a + b;
            else if (token == "-")
                result = a - b;
            else if (token == "*")
                result = a * b;
            else if (token == "/")
            {
                if (b == 0)
                {
                    std::cerr << "Error" << std::endl;
                    return;
                }
                result = a / b; 
            }
            _stack.push(result);
        }
        else
        {
            std::cerr << "Error" << std::endl;
            return;
        }
    }
    if (_stack.size() != 1)
    {
        std::cerr << "Error" << std::endl;
        return;
    }
    std::cout << _stack.top() << std::endl;
}
