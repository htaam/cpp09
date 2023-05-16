#include "RPN.hpp"

RPN ::RPN ()
{
    std::cout << "Default constructor" << std::endl;
}

RPN::RPN (const RPN &a)
{
	this->operator=(a);
}

RPN::~RPN ()
{
        std::cout << "Default destructor" << std::endl;
}

RPN & RPN::operator = (const RPN &a)
{
	(void)a;
	return (*this);
}

int RPN::CalculateResult(int n1, int n2, char oper)
{
    switch(oper)
    {
        case '+':
            return(n1 + n2);
        case '-':
            return(n2 - n1);
        case '*':
            return (n1 * n2);
        case '/':
        {
            if (n2 == 0)
                throw std::invalid_argument("Exception: Dividing by zero \n");
            return (n2/n1);
        }   
    }
    return (0);
}

void RPN::ReadInput(std::string input)
{
    std::string ope = "+/*-";
    size_t op, num;
    op = num = 0;
    int count = 0;
    for (size_t i = 0; i < input.length(); i++)
    {
        if(isdigit(input[i]))
        {
            num++;
            this->_numbers.push(input[i] - '0');
        }
        else if (ope.find(input[i]) != std::string::npos)
        {
            op++;
            int n1 = _numbers.top();
            _numbers.pop();
            cont++;
            if (!_numbers.pop())
                _numbers.top() = CalculateResult(n1, _numbers.top(), input[i]);
            else   
                throw std::invalid_argument("Number of operators less or greater then numbers\n");
        }
        else if (isspace(input[i]))
            continue;
        else
            throw std::invalid_argument("Error\n");
            
    }
}