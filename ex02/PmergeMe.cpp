// containers: list, vector

#include <list>

/// @brief create pairs. The first element will always be the bigger one
/// @param list
/// @return list with pairs.
auto form_pairs(std::list<unsigned int> list) -> std::list<std::pair<unsigned int, unsigned int>>
{
    std::list<std::pair<unsigned int, unsigned>> pairs;

    size_t listLen = list.size();
    while (listLen >= 2)
    {
        unsigned int p1 = list.front();
        list.pop_front();
        unsigned int p2 = list.front();
        list.pop_front();

        std::pair<unsigned int, unsigned> pair;
        if (p1 > p2)
            pair = std::make_pair(p1, p2);
        else
            pair = std::make_pair(p2, p1);
        // add to comp counter

        pairs.push_back(pair);
        listLen -= 2;
    }

    return pairs;
}

/// @brief sort the list using merge-insertion
/// @param list	the global list to sort
/// @param idxToSort the indexes to sort in this iteration
/// @return a list where the given indexes are sorted
void sort(std::list<unsigned int>& winners, std::list<unsigned int>& losers)
{
    if (winners.size() <= 1)
        return; // winners is sorted

    std::list<unsigned int> next_winners;
    std::list<unsigned int> next_losers;


}

// sort(list):
//     if len(list) <= 1:
//         return list              ← base case

//    pairs = form_pairs(list)     ← pair up, keep odd element aside
//    winners = [max of each pair]
//    losers  = [min of each pair]

//    sorted_winners = sort_winners(winners)   ← THE recursive call (half the size)

//    # Now insert losers (and the odd element) into sorted_winners
//    # using binary search in Jacobsthal order
//    return insert_all(sorted_winners, losers, odd_element)