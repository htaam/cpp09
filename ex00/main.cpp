#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>




int main(int argc, char **argv){
    BitcoinExchange exchange;
    
    if (argc == 2)
    {
            std::string input_file = argv[1];
            try{
                exchange.build();
                exchange.input(input_file);
            }
            catch(std::exception &e){

            }
    }



}