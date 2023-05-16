#include "RPN.hpp"
#include <iomanip>

int main(int ac, char *av[])
{
    if (ac != 2)
    {
        std::cerr << "Error\n";
        return (0);
    }
    else
    {
        RPN obj;
        try
        {
            obj.ReadInput(av[1]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what();
        }

    }
}
