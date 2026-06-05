// containers: deque, vector
#include "PmergeMe.hpp"
#include <algorithm>
#include <print>
#include <vector>

auto formPairs(std::vector<int>& list, std::vector<int>& winners, std::vector<int>& losers) -> void
{
    // pair up the current winners into winner and loser pairs
    size_t winnerLen = list.size();
    for (size_t i = 0; i + 1 < winnerLen; i += 2)
    {
        int a = list[i];
        int b = list[i + 1];
        if (a > b)
        {
            winners.push_back(a);
            losers.push_back(b);
        }
        else
        {
            winners.push_back(b);
            losers.push_back(a);
        }
    }
    if (winnerLen % 2 == 1)
        losers.push_back(list.back());

    std::println("Current Winners: {}", winners);
    std::println("Current Losers: {}", losers);
}

auto sort(std::vector<int>& vec) -> void
{
    std::vector<int> nextWinners;
    std::vector<int> nextLosers;

    formPairs(vec, nextWinners, nextLosers);

    // sort current winners list -> nextWinners will be same as winners list but sorted
    sortRecursive(nextWinners, nextLosers);

    vec = nextWinners;
}

/// @brief sort the winners and loser pairs into the winners.
/// @param winners starts with winner pairs. ends with sorted winners+losers.
/// @param losers loserpairs to be inserted. ends empty.
auto sortRecursive(std::vector<int>& winners, std::vector<int>& losers) -> void
{
    std::vector<int> finalSorted;
    if (winners.size() <= 1)
    {
        for (size_t idx = 0; idx < losers.size(); idx++)
        {
            finalSorted = winners;
            finalSorted.insert(
                std::lower_bound(finalSorted.begin(), finalSorted.end(), losers[idx]), losers[idx]);
        }
        winners = finalSorted;
        return;
    }

    std::vector<int> nextWinners;
    std::vector<int> nextLosers;

    formPairs(winners, nextWinners, nextLosers);

    // sort current winners list -> nextWinners will be same as winners list but sorted
    sortRecursive(nextWinners, nextLosers);

    // create sortedLosers losers to match with winners pair locations
    std::vector<int> sortedlosers;
    size_t           winnerLen = winners.size();
    for (int& x : nextWinners)
    {
        for (size_t i = 0; i < winnerLen; i++)
        {
            if (x == winners[i])
                sortedlosers.push_back(losers[i]);
        }
    }
    if (losers.size() != winners.size())
        sortedlosers.push_back(losers.back());

    // insert losers into winners
    finalSorted = nextWinners;

    // check jabobsSequence to start inserting
    // get start and end for search area
    // insert value
    size_t level = 1;
    for (; jacobsSequence(level) < sortedlosers.size(); level++)
    {
        for (size_t idx = jacobsSequence(level); idx > jacobsSequence(level - 1); idx--)
        {
            // get search area;
            std::vector<int>::iterator endSearchIt = finalSorted.begin();
            if (idx < nextWinners.size())
            {
                // search for nextWinners[idx] in finalSorted.
                while (endSearchIt != finalSorted.end() && *endSearchIt != nextWinners[idx])
                    endSearchIt++;
            }
            else
            {
                // search entire range
                endSearchIt = finalSorted.end();
            }
            // insert sortedlosers[idx] into finalSorted from finalSorted.begin() till endSearchIt
            finalSorted.insert(
                std::lower_bound(finalSorted.begin(), endSearchIt, sortedlosers[idx]),
                sortedlosers[idx]);
            std::println("inserted {} into finalSorted", sortedlosers[idx]);
        }
    }

    winners = finalSorted;
}

auto jacobsSequence(size_t n) -> size_t
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    size_t prev = 0, curr = 1;
    for (size_t i = 2; i <= n; ++i)
    {
        size_t next = curr + 2 * prev;
        prev        = curr;
        curr        = next;
    }
    return curr;
}

// sort(winners, losers):
//     if len(list) <= 1:
//         return list              ← base case

//    winners = [max of each pair]
//    losers  = [min of each pair]

//    sorted_winners = sort_winners(winners)   ← THE recursive call (half the size)

//    # Now insert losers (and the odd element) into sorted_winners
//    # using binary search in Jacobsthal order
//    return insert_all(sorted_winners, losers, odd_element)
