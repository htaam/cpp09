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
    inputFile.close();
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
    int year;
	int month;
	int day;

    sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);
    int prday = day - 1;
    int prmonth = month;
    int pryear = year;

    if (prday == 0)
	{
        prmonth = month - 1;
        if (prmonth == 0)
		{
            prmonth = 12;
            pryear = year - 1;
            if (pryear < 2009)
                return "Invalid date!";
        }
        switch (prmonth)
		{
            case 2:
                if (pryear % 4 == 0 && (pryear % 100 != 0 || pryear % 400 == 0))
				{
                    prday = 29;
                }
				else
				{
                    prday = 28;
                }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                prday = 30;
                break;
            default:
                prday = 31;
        }
    }
    std::string prev_date = to_string(pryear) + "-";
    if (prmonth < 10)
        prev_date += "0" + to_string(prmonth);
    else
        prev_date += to_string(prmonth);
    if (prday < 10)
        prev_date += "-0" + to_string(prday);
    else
        prev_date += "-" + to_string(prday);
    return (prev_date);
}

bool BitcoinExchange::validateDate(const std::string &date)
{
    if (date.length() !=10)
        return false;
    int year, month, day;
    char separator1, separator2;
    std::istringstream ss(date);

    ss >> year >> separator1 >> month >> separator2 >> day;
    if (ss.fail() || separator1 != '-' || separator2 != '-' ||
        year < 0 || month <1 || month > 12 || day < 1 || day > 31){
        return false;}
    bool leap_year = ((year % 4 == 0) && (year % 100 !=0)) || (year %400 == 0);
    if ((month == 2 && (leap_year ? day > 29 : day > 28)) ||
        ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30))
	{
        std::cout << "idil" << std::endl;
        return false;
    }
    return (true);
}

bool BitcoinExchange::validateValue(std::string& value)
{
    try
    {
        to_float(value);
    }
    catch(const std::invalid_argument& e)
    {
        return (false);
    }
    return true;
}

void BitcoinExchange::printMap(void)
{
    std::map<std::string, double>::const_iterator it;
    for (it = this->data.begin(); it != this->data.end(); ++it)
    {
        std::cout<<it->first << "=" << it->second << " ";
    }
    std::cout << std::endl;
}
    
