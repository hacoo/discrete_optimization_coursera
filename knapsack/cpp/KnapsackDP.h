#pragma once

#include "Knapsack.h"
#include <stdexcept>


// Solves knapsack problem using dynamic programming. The solution is guaranteed to be optimal.
//
// This solver produces optimal results. However, its runtime is depended on both the number
// of items, and the capacity of the knapsack. On an input with n items and max capacity K, this
// solver will run in O(n*K) time. Worse, it requires O(n*K) space.
//
// This solver is excellent for problems where K is small. However, if K is large, this
// method will run out of memory and crash. In principal, K is exponential in the number of bits used
// to represent it (here, K is an unsigned 32-bit int), so this solver runs in exponential time and space.
class KnapsackDPSolver : public KnapsackSolver
{
public:

    KnapsackDPSolver(const KnapsackInst& inst)
        :
        KnapsackSolver(inst)
    { }

    class NotEnoughMemoryError : public std::runtime_error
    {
    public:
        NotEnoughMemoryError(std::string what)
            :
            runtime_error(what)
        { }
    };

protected:
    virtual KnapsackSolution solve_internal() override;
    uint64_t getTotalSystemMemory();
    void DP_fill_row(uint32_t* DP_tab, size_t row, size_t max_col);
};
