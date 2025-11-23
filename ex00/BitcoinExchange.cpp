#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>

bool BitcoinExchange::parseLine(const std::string& line, std::string& date, double& value)
{
    size_t pos = line.find("|");
    if (pos == std::string::npos)
        return false;
    std::string date_str = line.substr(0, pos);
    std::string value_str = line.substr(pos + 1);
    size_t first = date_str.find_first_not_of(" \t\n\r");
    size_t last = date_str.find_last_not_of(" \t\n\r");
    if (first == std::string::npos)
        return false;
    date = date_str.substr(first, last - first + 1);
    std::stringstream ss(value_str);
    if (!(ss >> value))
    {
        //if conv fail
        return false;
    }    
    return true;
}

bool BitcoinExchange::isValidDate(const std::string &date)
{
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7) // skip tiret
            continue;
        if (!isdigit(date[i]))
            return false;
    }
    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());
    if (year < 2009)
        return false;
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;
    if (month == 2 && day > 29)
        return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    return true;
}

bool BitcoinExchange::isValideValue(double value)
{
    return (value >= 0 && value <= 1000);
}

double BitcoinExchange::findRate(const std::string &date)
{
    std::map<std::string, double>::iterator it = data.lower_bound(date);
    if (it != data.end() && it->first == date)
        return it->second;

    if (it == data.begin())
        throw std::runtime_error("Error: date is before all records");
    --it;
    return it->second;
}


BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    *this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
        data = other.data;
    return *this;
}

BitcoinExchange::~BitcoinExchange(){}


void BitcoinExchange::loadDatabase(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open database file.");
    std::string line;
    std::getline(file, line);
    while(std::getline(file,line))
    {
        size_t pos = line.find(',');
        if (pos == std::string::npos)
            continue;
        std::string date = line.substr(0, pos);
        std::string value_str = line.substr(pos + 1);
        double value = atof(value_str.c_str());
        data[date] = value;
    }
}

void BitcoinExchange::processInput(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::string date;
        double value;
        if (!parseLine(line, date,value))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (!isValidDate(date))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (value < 0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000)
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }
        try
        {
            double rate = findRate(date);
            double result = value * rate;
            std::cout << date << " => " << value << " = " << result << std::endl;
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}