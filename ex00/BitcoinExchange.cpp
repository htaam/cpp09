#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void){
    std::cout << "Default constructor" << std::endl;
}

BitcoinExchange::~BitcoinExchange( void ) {
    std::cout << "Default destructor" << std::endl;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const& src){
    *this = src;
}

BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange const& rhs){
    _rates = rhs._rates;
    return(*this);
}

void BitcointExchange::build(void){
    std::ifstream _database;
    _database.open("data.csv");
    if (!_database.is_open()){
        throw std::runtime_error ("Could not pen data file");
    }
    std::string line;
    while (std::getline(_database, line)){
        std::string key = line.substr(0, line.find(','));
        std::string value = line.substr(line.find(',') + 1, line.length() - line.find(','));
        _rates[key] = std::atof(value.c_str());
    }
    _database.close();
}