#pragma once

#include "Knapsack.h"

// Branch / bound knapsack solver. Explores tree of possible decisions, using bounding
// techniques to prune some branches before exploration. This solver is optimal.
//
// Uses a limited discrepancy method WRT the greedy value-density strategy. That is,
// it will first explore branches that do not deviate from the greedy value-density strategy,
// then explores deviating branches.
//
// Given an input with max capcity K and n items, this solver will use O(n) space.
// The runtime depends on how many branches are pruned; in the worst case, nothing is pruned,
// and the runtime is O(2^n).
class KnapsackBranchBoundSolver : public KnapsackSolver
{
public:

    KnapsackBranchBoundSolver(const KnapsackInst& inst)
        :
        KnapsackSolver(inst),
        best_solution(inst)
    { }


protected:

    virtual KnapsackSolution solve_internal() override;

    void search_tree(std::vector<size_t>& sorted_indices,
                     size_t i,
                     size_t discrepancies_remaining,
                     int64_t weight_remaining,
                     uint32_t total_value,
                     int64_t optimal_bound,
                     KnapsackSolution& solution);

protected:
    uint32_t upper_bound;
    uint32_t best_val;
    KnapsackSolution best_solution;
};
