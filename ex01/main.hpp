#include <string>
#include <vector>

auto runTests() -> void;

struct TestCase
{
        std::string input;
        std::string expected;
};

// clang-format off

std::vector<TestCase> testCases = {
	// correct behaviour
	{"1 1 +", "2"},
	{"8 9 * 9 - 9 - 9 - 4 - 1 +", "42"},
	{"7 7 * 7 -", "42"},
	{"1 2 * 2 / 2 * 2 4 - +", "0"},
	// unsupported tokens
	{"(1 + 1)", "Error"},
	// not enough elements
	{"1 1 + +", "Error"},

	// to many elements
	{"1 1 1 +", "Error"},

	// overflow add sub mult
	// add sub takes a veeeerrrryyy big input
	{"9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 *", "Error"},

	// div by zero
	{"0 1 /", "0"},
	{"1 0 /", "Error"},

	// test float result
	{"1 2 /", "0.5"},
};

// clang-format on