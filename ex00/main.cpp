#include <print>
#include "BitcoinExchange.hpp"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::println(stderr, "Usage: ./btc <tradeFile>");
		return -1;
	}
	BitcoinExchange exchange{"data.csv"};
	exchange.printTrades(argv[1]);
	return 1;
}