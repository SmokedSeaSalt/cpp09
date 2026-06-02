#include "BitcoinExchange.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <print>
#include <sstream>
#include <string>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& filename)
{
    this->dataBase_ = parseFile(filename);
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : dataBase_{other.dataBase_} {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this == &other)
        return *this;
    this->dataBase_ = other.dataBase_;
    return *this;
}

auto BitcoinExchange::printTrades(const std::string& filename) -> void
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::println(stderr, "Error: could not open file {}.", filename);
        return;
    }

    std::string line;
    int         lineNum = 0;
    while (std::getline(file, line))
    {
        lineNum++;
        if (lineNum == 1)
            continue;

        // Skip empty lines and comments
        if (line.empty() || line[0] == '#')
            continue;

        std::string date;
        float       value;
        if (parseTradesLine(line, date, value, lineNum) == true)
        {
            if (value <= 0.0)
            {
                std::println(stderr, "Error: not a positive value.", filename);
                continue;
            }
            if (value > 1000.0)
            {
                std::println(stderr, "Error: too large a value.", filename);
                continue;
            }
            std::map<std::string, float>::const_iterator printDate = getCorrectDate(date);
            if (printDate == this->dataBase_.end())
            {
                std::println(stderr, "Error: Date: {} to early for database.", date);
                continue;
            }
            std::println("{} => {} = {}", date, value, value * printDate->second);
        }
    }

    file.close();

    return;
}

/// @brief Get the trade value associated with the given date.
/// @brief Will get the actual date or the first known date before.
/// @param data Database to get the date from
/// @param date Date to lookup in the database
/// @return Iterator to the database entry.
auto BitcoinExchange::getCorrectDate(std::string date)
    -> std::map<std::string, float>::const_iterator
{
    std::map<std::string, float>::const_iterator it = this->dataBase_.lower_bound(date);

    // check for exact match
    if (it != this->dataBase_.end() && it->first == date)
        return it;

    // date is before every entry
    if (it == this->dataBase_.begin())
        return this->dataBase_.end();

    // return date before lower_bound to get prev. date
    return --it;
}

auto BitcoinExchange::parseFile(const std::string& filename) -> std::map<std::string, float>
{
    std::map<std::string, float> result;

    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::println(stderr, "Error: could not open file.", filename);
        return result;
    }

    std::string line;
    int         lineNum = 0;
    while (std::getline(file, line))
    {
        lineNum++;
        if (lineNum == 1)
            continue;

        // Skip empty lines and comments
        if (line.empty() || line[0] == '#')
            continue;

        std::string date;
        float       value;
        if (parseDatabaseLine(line, date, value, lineNum) == true)
        {
            if (result.contains(date))
            {
                std::println(stderr, "Error: Duplicate date {}, skipping line {}.", date, line);
                continue;
            }
            result[date] = value;
        }
    }

    file.close();

    return result;
}

auto BitcoinExchange::parseTradesLine(std::string line, std::string& date, float& value,
                                      int lineNum) -> bool
{
    // split line
    std::size_t it = line.find('|');
    if (it == std::string::npos)
    {
        std::println(stderr, "Error: Invalid Entry: {}, skipping line {}.", line, lineNum);
        return false;
    }
    date                 = trimWS(line.substr(0, it));
    std::string valueStr = trimWS(line.substr(it + 1));

    if (!isValidDate(date))
    {
        std::println(stderr, "Error: Invalid Date: {}, skipping line {}.", date, lineNum);
        return false;
    }

    // convert and validate float
    try
    {
        value = std::stof(valueStr);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}

/// @brief Parse a line of a Exchange file.
/// @param line The line to parse.
/// @param date a valid date to fill.
/// @param value a valid value to fill.
/// @return true if line is valid. false if line is invalid.
auto BitcoinExchange::parseDatabaseLine(std::string line, std::string& date, float& value,
                                        int lineNum) -> bool
{
    // split line
    std::size_t it = line.find(',');
    if (it == std::string::npos)
    {
        std::println(stderr, "Error: Invalid Entry: {}, skipping line {}.", line, lineNum);
        return false;
    }
    date                 = trimWS(line.substr(0, it));
    std::string valueStr = trimWS(line.substr(it + 1));

    if (!isValidDate(date))
    {
        std::println(stderr, "Error: Invalid Date: {}, skipping line {}.", date, lineNum);
        return false;
    }

    // convert and validate float
    try
    {
        value = std::stof(valueStr);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
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

auto BitcoinExchange::isLeapYear(int y) -> bool
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

auto BitcoinExchange::isValidDate(const std::string& date) -> bool
{
    // Must be exactly "YYYY-MM-DD"
    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;

    for (int i = 0; i < 10; ++i)
    {
        if (i == 4 || i == 7)
            continue;
        if (!isdigit(date[i]))
            return false;
    }

    int year  = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day   = std::stoi(date.substr(8, 2));

    if (year < 1 || month < 1 || month > 12 || day < 1)
        return false;

    const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int       maxDay        = daysInMonth[month - 1];
    if (month == 2 && isLeapYear(year))
        maxDay = 29;

    return day <= maxDay;
}