#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cstddef>

auto jacobsSequence(size_t n) -> size_t;

template <typename Container>
auto formPairs(Container& list, Container& winners, Container& losers) -> void;

template <typename Container>
auto sort(Container& container) -> void;

template <typename Container>
auto sortRecursive(Container& winners, Container& losers) -> void;

template <typename Container>
auto insertion(Container& winners, Container& losers) -> Container;

template <typename Container>
auto matchLosers(Container& unsortedLosers, Container& unsortedWinners, Container& sortedWinners) -> Container;

#include "PmergeMe.tpp"

#endif // PMERGEME_HPP