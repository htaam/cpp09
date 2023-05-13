#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>




int main(int argc, char **argv){
    BitcoinExchange exchange;
    
    if (argc != 2)
    {
        std::cout << "Error: Invalid number of arguments." << std::endl;
    }
    try{
        exchange.readData();
        exchange.validateInput(argv[1]);
    }
    catch(std::exception &e){
        std::cerr << e.what() << std::endl;
    }



}