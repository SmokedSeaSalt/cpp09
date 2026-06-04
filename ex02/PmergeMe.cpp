// containers: deque, vector
#include <vector>

/// @brief sort the winners and loser pairs into the winners.
/// @param winners starts with winner pairs. ends with sorted winners+losers.
/// @param losers loserpairs to be inserted.
void sort(std::vector<int>& winners, std::vector<int>& losers)
{
    if (winners.size() <= 1)
        return; // winners is sorted

    std::vector<int> next_winners;
    std::vector<int> next_losers;

    //pair up the current winners into winner and loser pairs
    size_t winnerLen = winners.size();
    for (size_t i = 0; i + 1 < winnerLen; i += 2)
    {
        int a = winners[i];
        int b = winners[i + 1];
        if (a > b)
        {
            next_winners.push_back(a);
            next_losers.push_back(b);
        }
        else
        {
            next_winners.push_back(b);
            next_losers.push_back(a);
        }
    }
    if (winnerLen % 2 == 1)
        next_losers.push_back(winners.back());

    //sort current winners list -> next_winners will be same as winners list but sorted
    sort(next_winners, next_losers);

    //create sortedLosers losers to match with winners pair locations
    std::vector<int> sortedlosers;
    for (int& x : next_winners)
    {
        for (size_t i = 0; i < winnerLen; i++)
        {
            if (x == winners[i])
                sortedlosers.push_back(losers[i]);
        }
    }
    if (losers.size() % 2 == 1)
        sortedlosers.push_back(losers.back());

    //insert losers into winners




    winners = next_winners;


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



3 1 2 8 4 5 9 6 7

3 8 5 9    (larger)
1 2 4 6 7   (smaller)

3 5 8 9    (S)
1 4 2 9 7  (s)

std::pair<int, int>

0 , 1 , 2^2 - 1 = 3, 2^3 - 3 = 5, 2^4 - 5 = 11 ,

2^i - prev