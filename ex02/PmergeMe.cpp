// containers: deque, vector
#include "PmergeMe.hpp"
#include <cstddef>

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
