#ifndef MAIN_HPP
#define MAIN_HPP

#include <vector>
#include <deque>

auto runTest(std::vector<int>& vec, std::deque<int>& deq) -> void;
auto parseInput(int argc, char* argv[], std::vector<int>& vec, std::deque<int>& deq) -> int;

#endif // MAIN_HPP