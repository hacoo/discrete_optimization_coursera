#pragma once

#include "Knapsack.h"

// Greedy Knapsack solver. Greedily takes items by value density, until capacity is reached.
// For some item i with value vi and weight wi, the value density of i is (float) vi / wi.
//
// This solver is very fast, but the quality is low. It is NOT guaranteed to produce an
// optimal solution, and many inputs may yield very poor results. The algorithm is deterministic.
//
// Given n items an a maximum capacity K, this solver will run in O(n) time and use O(n) space.
// Thus, it has excellent performance in both time an space.
class KnapsackGreedySolver : public KnapsackSolver
{
public:

    KnapsackGreedySolver(const KnapsackInst& inst)
        :
        KnapsackSolver(inst)
    { }

protected:
    virtual KnapsackSolution solve_internal() override;

};
