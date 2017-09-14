#include "KnapsackBranchBound.h"

#include <algorithm>
#include <functional>
#include <utility>
#include <iostream>
#include <stdexcept>

void KnapsackBranchBoundSolver::search_tree(std::vector<size_t>& sorted_indices,
                                            size_t i,
                                            size_t discrepancies_remaining,
                                            int64_t weight_remaining,
                                            uint32_t total_value,
                                            int64_t optimal_bound,
                                            KnapsackSolution& solution)
{
    // Sack overfilled, this should never happen!
    if (weight_remaining < 0)
    {
        throw std::runtime_error("Knapsack overfilled");
    }

    // Prune if the optimal bound is worse than the previous best solution
    if (optimal_bound < best_val)
    {
        return;
    }

    // Examined all items or sack is exactly full; we have a possible solution
    if (weight_remaining == 0 || i >= sorted_indices.size())
    {
        if (total_value > best_val)
        {
            best_val = total_value;
            best_solution = solution;
        }
        return;
    }

    size_t index = sorted_indices[i];
    const KnapsackItem& item = inst.items[index];

    // Follow the heuristic -- if the item fits, add it.
    if (weight_remaining >= item.weight)
    {
        {
            KnapsackSolution item_added_solution = { solution };
            item_added_solution.selected_items[index] = true;

            search_tree(sorted_indices,
                        i+1,
                        discrepancies_remaining,
                        weight_remaining - item.weight,
                        total_value + item.value,
                        optimal_bound,
                        item_added_solution);
        }

        // If any discrepancies remain, try NOT adding this item:
        if (discrepancies_remaining > 0)
        {
            search_tree(sorted_indices,
                        i+1,
                        discrepancies_remaining - 1,
                        weight_remaining,
                        total_value,
                        optimal_bound - item.value,
                        solution);
        }
    }
    else
    {
        // Otherwise, don't add the item. No point in making a discrepancy move in this case.
        search_tree(sorted_indices,
                    i+1,
                    discrepancies_remaining,
                    weight_remaining,
                    total_value,
                    optimal_bound - item.value,
                    solution);
    }
}

KnapsackSolution KnapsackBranchBoundSolver::solve_internal()
{
    KnapsackSolution sol(inst);

    // Sort according to value density
    std::vector<size_t> sorted_indices;
    sorted_indices.reserve(inst.num_items);

    for(size_t i = 0; i < inst.num_items; ++i)
    {
        sorted_indices.push_back(i);
    }

    std::sort(sorted_indices.begin(),
              sorted_indices.end(),
              [&inst = inst] (size_t a, size_t b) -> bool
              {
                  return ((float) inst.items[a].value / inst.items[a].weight) >
                      ((float) inst.items[b].value / inst.items[b].weight);
              }
              );

    best_val = 0;
    upper_bound = 0;
    best_solution = KnapsackSolution(inst);

    // Starting upper bound assumes we take everything
    for (const auto& item : inst.items)
    {
        upper_bound += item.value;
    }

    // Use iterative deepening: on the first pass, we allow 0 deviations,
    // next we allow 1, etc. Allow only a few discrepancies; after this it gets too slow!
    for (size_t d = 0; d <= 7; ++d)
    {
        KnapsackSolution temp_solution = { inst };
        search_tree(sorted_indices,
                    0,
                    d,
                    inst.capacity,
                    0,
                    upper_bound,
                    temp_solution);
    }

    sol = best_solution;
    sol.is_optimal = true;
    sol.is_valid_solution = true;

    return sol;
}
