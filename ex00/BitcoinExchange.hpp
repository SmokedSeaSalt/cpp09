#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
    public:
        BitcoinExchange(const std::string& filename);
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        auto printTrades(const std::string& filename) -> void;

    private:
        std::map<std::string, float> dataBase_;

        BitcoinExchange();

        auto parseFile(const std::string& filename) -> std::map<std::string, float>;
        auto parseDatabaseLine(std::string line, std::string& date, float& value, int lineNum) -> bool;
        auto parseTradesLine(std::string line, std::string& date, float& value, int lineNum) -> bool;

        auto getCorrectDate(std::string date) -> std::map<std::string, float>::const_iterator;

        static auto trimWS(std::string str) -> std::string;
        static auto isValidDate(const std::string &date) -> bool;
        static auto isLeapYear(int year) -> bool;

};

#endif // BITCOINEXCHANGE_HPP