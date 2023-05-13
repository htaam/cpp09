#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <sstream>
#include <fstream>
#include <map>
#include <exception>
#include <string>
#include <ctime>
#include <utility>
#include <iostream>
#include <algorithm>
#include <iomanip>

class BitcoinExchange{
    public:
        BitcoinExchange(void);
        ~BitcoinExchange( void ); /* Destructor */
        BitcoinExchange( BitcoinExchange const& src ); /* Destructor */
        BitcoinExchange &operator =( BitcoinExchange const& rhs);
        void validateInput(char *file);
        void readData();


    private:
        double findRate(std::string date);
        void printMap();
        std::string moveDataBackOneDay(const std::string& date);
        bool validateDate(const std::string& date);
        bool validateValue(std::string& value);
        std::string to_string(int & value);
        double to_double(std::string & input);
        float to_float (std::string & input);
        
        std::map<std::string, double> data;
        
};


#endif