#include "main.hpp"
#include "RPN.hpp"
#include <expected>
#include <print>
#include "terminalOutput.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::println(stderr, "Usage: ./RPN \"<expression>\"");
        return -1;
    }
    if (std::string(argv[1]) == "test")
    {
        runTests();
        return 1;
    }
    std::expected<long, std::string> ret = calculateExpression(argv[1]);
    if (!ret.has_value())
    {
        std::println(stderr, "Error: {}", ret.error());
        return -1;
    }
    std::println("Result: {}", ret.value());
    return 1;
}

auto runTests() -> void
{
    for (const TestCase& test : testCases)
    {
		std::println("{}Testcase: {}{}", C_BLUE, test.input, C_END);
		std::println("Expected: {}", test.expected);
		std::print("Got: ");
        std::expected<long, std::string> ret = calculateExpression(test.input);
        if (!ret.has_value())
        {
            std::println("Error: {}", ret.error());
            continue;
        }
        std::println("Result: {}", ret.value());
    }
}
