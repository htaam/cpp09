#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <algorithm>
#include <iostream>

class BitcoinExchange{
    public:
        ~BitcoinExchange( void ); /* Destructor */
        BitcoinExchange( BitcoinExchange const& src ); /* Destructor */

        BitcoinExchange &operator =( BitcoinExchange const& rhs);

        void build(void);
        void input(std::string file);
        void print(std::string key, std:: string value);
    
    private:
        BitcoinExchange(void);
        std::map<std::string, float> _rates;
        
}


#endif