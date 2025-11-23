#include "RPN.hpp"
#include <iostream>

int main(int ac, char **av)
{
    if (ac == 2)
    {
        RPN rpn;
        rpn.parseArgv(av[1]);
    }
    else
    {
        std::cout << "String, with two values (1 - 9) , and an operator (ex: 7 6 *)" << std::endl;
    }
}