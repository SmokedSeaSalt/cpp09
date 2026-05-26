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
        std::map<std::string, float> data_;

        BitcoinExchange();

        auto parseFile(const std::string& filename) -> std::map<std::string, float>;
        auto parseLine(std::string line, std::string& date, float& value) -> bool;

        static auto trimWS(std::string str) -> std::string;
        static auto isValidDate(std::string date) -> bool;

};

#endif // BITCOINEXCHANGE_HPP