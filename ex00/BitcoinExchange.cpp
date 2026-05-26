#include "BitcoinExchange.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& filename) {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {}

auto BitcoinExchange::printTrades(const std::string& filename) -> void {}

auto BitcoinExchange::parseFile(const std::string& filename) -> std::map<std::string, float>
{
    std::map<std::string, float> result;

    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file \"" << filename << "\"\n";
        return result;
    }

    std::string line;
    int         lineNum = 0;
    while (std::getline(file, line))
    {
        lineNum++;

        // Skip empty lines and comments
        if (line.empty() || line[0] == '#')
            continue;

        std::string date;
        float       value;
        if (parseLine(line, date, value) == true)
        {
            if (result.contains(date))
            {
                std::cerr << "Duplicate date, skipping entry" << std::endl;
                continue;
            }
            result[date] = value;
        }
    }

    return result;
}

/// @brief Parse a line of a Exchange file.
/// @param line The line to parse.
/// @param date a valid date to fill.
/// @param value a valid value to fill.
/// @return true if line is valid. false if line is invalid.
auto BitcoinExchange::parseLine(std::string line, std::string& date, float& value) -> bool
{
    // split line
    std::size_t it = line.find('|');
    if (it == std::string::npos)
    {
        std::cerr << "Invalid Entry: " << line << ", skipping line" << std::endl;
        return false;
    }
    date                 = trimWS(line.substr(0, it));
    std::string valueStr = trimWS(line.substr(it + 1));

    // validate date

    // convert and validate float
}

auto BitcoinExchange::trimWS(std::string str) -> std::string
{
    std::size_t start = str.find_first_not_of(" \t\r\n");
    std::size_t end   = str.find_last_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
    else
        return str.substr(start, end - start + 1);
}

auto BitcoinExchange::isValidDate(std::string date) -> bool
{
    std::istringstream          in{std::move(date)};
    std::chrono::year_month_day ymd;
    in >> std::chrono::parse("%F", ymd);
    return !in.fail();
}