#include "KnapsackGreedy.h"

#include <algorithm>
#include <functional>
#include <utility>
#include <iostream>

KnapsackSolution KnapsackGreedySolver::solve_internal()
{
    KnapsackSolution sol(inst);

    // Greedy solution is not guaranteed to be optimal
    sol.is_optimal = false;

    std::vector<size_t> sorted_indices;
    sorted_indices.reserve(inst.num_items);

    for(size_t i = 0; i < inst.num_items; ++i)
    {
        sorted_indices.push_back(i);
    }

    // Use 'value-density' solution
    std::sort(sorted_indices.begin(),
              sorted_indices.end(),
              [&inst = inst] (size_t a, size_t b) -> bool
              {
                  return ((float) inst.items[a].value / inst.items[a].weight) >
                      ((float) inst.items[b].value / inst.items[b].weight);
              }
              );

    uint32_t weight_taken = 0;
    for (size_t index : sorted_indices)
    {
        const KnapsackItem& item = inst.items[index];

        if (weight_taken + item.weight <= inst.capacity)
        {
            weight_taken += item.weight;
            sol.selected_items[index] = true;
        }
    }

    sol.is_valid_solution = true;
    return sol;
}
