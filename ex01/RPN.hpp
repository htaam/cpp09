#ifndef RPN_H
#define RPN_H

#include <iostream>
#include <stack>

class RPN
{
    private:
        std::stack<int>     _numbers;
    public:
        RPN ();
        RPN (const RPN &a);
        ~RPN ();
        RPN & operator = (const RPN &a);

        void    ReadInput(std::string input);
        int     CalculateResult(int n1, int n2, char oper);
};

#endif