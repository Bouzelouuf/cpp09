#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib> 

class BitcoinExchange
{
    private:
        std::map<std::string, double> data;
        // map pour tri auto par date
    private:
        bool parseLine(const std::string& line, std::string& date, double& value);
        bool isValidDate(const std::string &date);
        bool isValideValue(double value);
        double findRate(const std::string &date);
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();
        void loadDatabase(const std::string& filename);
        void processInput(const std::string& filename);
};
#endif