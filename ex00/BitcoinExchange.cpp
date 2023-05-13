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
    data = rhs.data;
    return(*this);
}


double BitcoinExchange::to_double(std::string& input)
{
	std::istringstream ss(input);
	double res;
	ss >> res;
	return (res);
}

float BitcoinExchange::to_float(std::string& input)
{
	std::istringstream ss(input);
	float res;
	ss >> res;
	return (res);
}

std::string BitcoinExchange::to_string(int & value) 
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

void BitcoinExchange::readData()
{
    std::ifstream file;
    file.open("data.csv");
    if (!file.is_open())
        throw std::runtime_error("Could not open data.csv");
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string date, rate;
        std::getline(ss, date, ',');
        std::getline(ss, rate, ',');
        this->data[date] = to_double(rate);
    }
}

void BitcoinExchange::validateInput(char *file)
{
    std::ifstream inputFile(file);
    if (!inputFile)
        throw std::runtime_error("Could not open input file");
    
    std::string firstLine;
    std::getline(inputFile,firstLine);
    if (firstLine.compare("date | value"))
        throw std::runtime_error("Error: Format expected on first line: 'date | value'.");

    std::string line;

    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        std::string date, value;
        char separator;

        if (!(iss >> date >> separator >> value) || separator != '|')
            std::cout << "Error: bad input => "+date << std::endl;
        else if (!validateDate(date) || !validateValue(value))
            std::cout << "Error: bad input => "+date << std::endl;
        else if (to_double(value) < 0)
            std::cout << "Error: not a positive number" << std::endl;
        else if(to_double(value) > 1000)
			std::cout << "Error: too large a number." << std::endl;
		else if (to_double(value) < 1000 || to_double(value) > 0)
        {
            double mult= to_double(value) * findRate(date);
            std::cout << date << " => " << value << " = " << mult << std::endl;
        }
        else
            std::cout << "Error: bad input => " << date << std::endl;
    }
    inputFile.close()
}

double BitcoinExchange::findRate(std::string date){
    if(this->data[date])
        return this->data[date];
    else
    {
        std::string prev_day =  moveDataBackOneDay(date);
        if (!prev_day.compare("Invalid date!"))
            return (0);
        return (findRate(prev_day));
    }
}

std::string BitcoinExchange::moveDataBackOneDay(const std::string &date)
{
    
}