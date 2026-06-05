#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>

auto formPairs(std::vector<int>& list, std::vector<int>& winners, std::vector<int>& losers) -> void;
auto sort(std::vector<int>& vec) -> void;
auto sortRecursive(std::vector<int>& winners, std::vector<int>& losers) -> void;
auto jacobsSequence(size_t n) -> size_t;

#endif // PMERGEME_HPP