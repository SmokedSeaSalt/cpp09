#include "main.hpp"
#include "PmergeMe.hpp"
#include "terminalOutput.hpp"
#include <algorithm>
#include <chrono>
#include <deque>
#include <print>
#include <ranges>
#include <set>
#include <string>
#include <vector>

// get input
// parse input
// check input for positive only intagers (0 is not positive)
// check input for only unique entries

// sort container A
// sort container B

// display results

// what happens without any inputs.
// what happens with only 1 intager to sort?

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::println(stderr, "Usage: ./PmergeMe <N1> [N2] [N3] ...");
        return -1;
    }

    std::vector<int> vectorContainer;
    std::deque<int>  dequeContainer;

    if (parseInput(argc, argv, vectorContainer, dequeContainer) < 0)
        return -1;

    runTest(vectorContainer, dequeContainer);
}

auto parseInput(int argc, char* argv[], std::vector<int>& vec, std::deque<int>& deq) -> int
{
    std::vector<std::string> input(argv + 1, argv + argc);

    for (const std::string& s : input)
    {
        try
        {
            int val = std::stoi(s);
            if (val <= 0)
            {
                std::println(stderr, "{}Only positive intagers allowed.{}", C_RED, C_END);
                return -1;
            }
            vec.push_back(val);
            deq.push_back(val);
        }
        catch (...)
        {
            std::println(stderr,
                         "{}Error found converting input to ints. Please check input arguments.{}",
                         C_RED, C_END);
            return -1;
        }
    }
    std::set<int> dupTest(vec.begin(), vec.end());
    if (dupTest.size() != deq.size())
    {
        std::println(stderr, "{}Duplicate input elements found. Please check input arguments.{}",
                     C_RED, C_END);
        return -1;
    }
    return 1;
}

auto printContainerContent(std::vector<int>& vec, std::string when) -> void
{
    if (vec.size() > 5)
    {
        std::print("{}: {}", when, vec | std::views::take(5));
        std::println("[...]");
    }
    else
        std::println("{}: {}", when, vec);
}

auto printContainerContent(std::deque<int>& deq, std::string when) -> void
{
    if (deq.size() > 5)
    {
        std::print("{}: {}", when, deq | std::views::take(5));
        std::println("[...]");
    }
    else
        std::println("{}: {}", when, deq);
}

auto runTest(std::vector<int>& vec, std::deque<int>& deq) -> void
{
    std::println("{}==Vector=={}", C_BLUE, C_END);
    printContainerContent(vec, "Before");

    auto time = std::chrono::high_resolution_clock::now();
    // create firs pairs
    sort(vec);
    // std::sort(vec.begin(), vec.end());
    auto elapsed = std::chrono::high_resolution_clock::now() - time;
    printContainerContent(vec, "After");

    std::println("Time to process a range of {} elements with std::vector : {}", vec.size(),
                 elapsed);

    std::println("{}==Deque=={}", C_BLUE, C_END);
    printContainerContent(deq, "Before");

    time = std::chrono::high_resolution_clock::now();
    // create first pairs
    // sort
    std::sort(deq.begin(), deq.end());
    elapsed = std::chrono::high_resolution_clock::now() - time;
    printContainerContent(deq, "After");

    std::println("Time to process a range of {} elements with std::deque : {}", deq.size(),
                 elapsed);
}
