#include "RPN.hpp"
#include <expected>
#include <limits>
#include <stack>
#include <string>

auto calculateExpression(const std::string& expression) -> std::expected<long, std::string>
{
    std::stack<long> resultStack;

    for (const char& c : expression)
    {
        if (isWhitespace(c))
            continue;
        if (isdigit(c))
        {
            resultStack.push(c - '0');
            continue;
        }

        Operation op = getOperation(c);
        if (op == Operation::ERR)
            return std::unexpected("Unsupported token " + std::string(1, c) + ".");
        if (resultStack.size() < 2)
            return std::unexpected(std::string(1, c) +
                                   " does not have enough elements to do operation.");

        long arg1 = resultStack.top();
        resultStack.pop();
        long arg2 = resultStack.top();
        resultStack.pop();

        // todo check overflow?
        // div by zero

        switch (op)
        {
        case Operation::ADD:
            if ((arg2 > 0 && arg1 > std::numeric_limits<long>::max() - arg2) ||
                (arg2 < 0 && arg1 < std::numeric_limits<long>::min() - arg2))
                return std::unexpected("Addition overflow detected.");
            resultStack.push(arg2 + arg1);
            break;

        case Operation::SUB:
            if ((arg1 < 0 && arg2 > std::numeric_limits<long>::max() + arg1) ||
                (arg1 > 0 && arg2 < std::numeric_limits<long>::min() + arg1))
                return std::unexpected("Subtraction underflow detected.");
            resultStack.push(arg2 - arg1);
            break;

        case Operation::DIV:
            if (arg1 == 0)
                return std::unexpected("Devision by 0 detected.");
            resultStack.push(arg2 / arg1);
            break;

        case Operation::MUL:
            if (arg1 != 0 && arg2 != 0)
            {
                if ((arg1 > 0 && arg2 > 0 && arg1 > std::numeric_limits<long>::max() / arg2) ||
                    (arg1 < 0 && arg2 < 0 && arg1 < std::numeric_limits<long>::max() / arg2) ||
                    (arg1 > 0 && arg2 < 0 && arg2 < std::numeric_limits<long>::min() / arg1) ||
                    (arg1 < 0 && arg2 > 0 && arg1 < std::numeric_limits<long>::min() / arg2))
                    return std::unexpected("Multiplication overflow detected.");
            }
            resultStack.push(arg2 * arg1);
            break;

        case Operation::ERR:
            break;
        }
    }

    if (resultStack.size() > 1)
        return std::unexpected("Too many elements left after expression");
    return resultStack.top();
}

auto isWhitespace(const char& c) -> bool
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

auto getOperation(const char& c) -> Operation
{
    if (c == '+')
        return Operation::ADD;
    if (c == '-')
        return Operation::SUB;
    if (c == '/')
        return Operation::DIV;
    if (c == '*')
        return Operation::MUL;
    return Operation::ERR;
}