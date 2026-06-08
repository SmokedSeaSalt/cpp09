
#include <algorithm>
#include <cstddef>

// sort(winners, losers):
//     if len(list) <= 1:
//         return list + inserted losers

//    nextWinners = [max of each pair]
//    nextLosers  = [min of each pair]

//    sorted_winners = sortRecursive(nextWinners)

//    map losers to sorted_winners
//    insert losers (and the odd element) into sorted_winners
//    return;
//    winners now contains sorted list of winners+losers for this recursion

template <typename Container>
auto sort(Container& vec) -> void
{
    Container nextWinners;
    Container nextLosers;

    formPairs(vec, nextWinners, nextLosers);

    // sort current winners list -> nextWinners will be same as winners list but sorted
    sortRecursive(nextWinners, nextLosers);

    vec = nextWinners;
}

/// @brief sort the winners and loser pairs into the winners.
/// @param winners starts with winner pairs. ends with sorted winners+losers.
/// @param losers loserpairs to be inserted. ends empty.
template <typename Container>
auto sortRecursive(Container& winners, Container& losers) -> void
{
    Container finalSorted;
    if (winners.size() <= 1)
    {
        finalSorted = winners;
        for (size_t idx = 0; idx < losers.size(); idx++)
        {
            finalSorted.insert(
                std::lower_bound(finalSorted.begin(), finalSorted.end(), losers[idx]), losers[idx]);
        }
        winners = finalSorted;
        return;
    }

    Container nextWinners;
    Container nextLosers;

    formPairs(winners, nextWinners, nextLosers);

    // sort current winners list -> nextWinners will be same as winners list but sorted
    sortRecursive(nextWinners, nextLosers);

    // create sortedLosers losers to match with winners pair locations
    Container sortedlosers = matchLosers(losers, winners, nextWinners);

    // insert losers into winners
    winners = insertion(nextWinners, sortedlosers);
}

template <typename Container>
auto formPairs(Container& list, Container& winners, Container& losers) -> void
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
}

template <typename Container>
auto matchLosers(Container& unsortedLosers, Container& unsortedWinners, Container& sortedWinners) -> Container
{
    Container sortedlosers;
    size_t    winnerLen = unsortedWinners.size();
    for (int& x : sortedWinners)
    {
        for (size_t i = 0; i < winnerLen; i++)
        {
            if (x == unsortedWinners[i])
                sortedlosers.push_back(unsortedLosers[i]);
        }
    }
    if (unsortedLosers.size() != unsortedWinners.size())
        sortedlosers.push_back(unsortedLosers.back());
    return sortedlosers;
}

template <typename Container>
auto insertion(Container& winners, Container& losers) -> Container
{
    Container finalSorted = winners;
    // do level 1 insert. This will always be the same
    finalSorted.insert(finalSorted.begin(), losers.front());

    // check jabobsSequence to start inserting
    size_t level = 2;
    for (; jacobsSequence(level - 1) < losers.size(); level++)
    {
        for (size_t idx = jacobsSequence(level) - 1; idx > jacobsSequence(level - 1) - 1; idx--)
        {
            if (idx >= losers.size())
                continue;
            // get search area;
            typename Container::iterator endSearchIt = finalSorted.begin();
            if (idx < winners.size())
            {
                // search for winners[idx] in finalSorted.
                while (endSearchIt != finalSorted.end() && *endSearchIt != winners[idx])
                    endSearchIt++;
            }
            else
            {
                // search entire range
                endSearchIt = finalSorted.end();
            }
            // insert losers[idx] into finalSorted from finalSorted.begin() till endSearchIt
            finalSorted.insert(std::lower_bound(finalSorted.begin(), endSearchIt, losers[idx]), losers[idx]);
        }
    }
    return finalSorted;
}