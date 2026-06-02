#include <expected>
#include <string>

enum class Operation
{
	ADD,
	SUB,
	DIV,
	MUL,
	ERR,
};

auto calculateExpression(const std::string& expression) -> std::expected<long, std::string>;

auto isWhitespace(const char& c) -> bool;
auto getOperation(const char& c) -> Operation;