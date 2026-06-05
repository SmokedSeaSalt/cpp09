#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>

auto jacobsSequence(size_t n) -> size_t;

// auto formPairs(std::vector<int>& list, std::vector<int>& winners, std::vector<int>& losers) -> void;
// auto sort(std::vector<int>& vec) -> void;
// auto sortRecursive(std::vector<int>& winners, std::vector<int>& losers) -> void;
// auto insertion(std::vector<int>& winners, std::vector<int>& losers) -> std::vector<int>;
// auto matchLosers(std::vector<int>& unsortedLosers, std::vector<int>& unsortedWinners, std::vector<int>& sortedWinners) -> std::vector<int>;

template<typename Container>
auto formPairs(Container& list, Container& winners, Container& losers) -> void;

template<typename Container>
auto sort(Container& container) -> void;

template<typename Container>
auto sortRecursive(Container& winners, Container& losers) -> void;

template<typename Container>
auto insertion(Container& winners, Container& losers) -> Container;

template<typename Container>
auto matchLosers(Container& unsortedLosers, Container& unsortedWinners, Container& sortedWinners) -> Container;

#include "PmergeMe.tpp"

#endif // PMERGEME_HPP