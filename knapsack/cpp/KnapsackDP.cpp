#include "KnapsackDP.h"

#include <algorithm>
#include <functional>
#include <utility>
#include <iostream>
#include <unistd.h>
#include <cstring>

uint64_t KnapsackDPSolver::getTotalSystemMemory()
{
    uint64_t pages = sysconf(_SC_PHYS_PAGES);
    uint64_t page_size = sysconf(_SC_PAGE_SIZE);
    return pages * page_size;
}

void KnapsackDPSolver::DP_fill_row(uint32_t* DP_tab, size_t row, size_t max_col)
{
    size_t thisrow = row * max_col;
    size_t lastrow = (row-1) * max_col;

    uint32_t weight = inst.items[row-1].weight;
    uint32_t value = inst.items[row-1].value;

    for (size_t cap = 0; cap < max_col; ++cap)
    {
        // For each capacity, make the choice whether to add this item. If
        // the item doesn't fit, we never add it. Otherwise, try adding it;
        // otherwise, add according to the recurrence relation.
        DP_tab[thisrow + cap] = weight <= cap ?
            std::max(DP_tab[lastrow + cap], DP_tab[lastrow + cap-weight] + value) :
            DP_tab[lastrow + cap];
    }
}

KnapsackSolution KnapsackDPSolver::solve_internal()
{
    KnapsackSolution sol(inst);
    size_t nitem = inst.num_items;
    size_t cap = inst.capacity;
    size_t max_row = nitem + 1;
    size_t max_col = cap + 1;


    // DP solution IS optimal (but may requires O(capacity * num_items)) memory
    sol.is_optimal = true;

    uint64_t table_bytes = max_row * max_col * 4;

    if (table_bytes > getTotalSystemMemory() - (uint64_t)1024*1024*1024*4)
    {
        throw NotEnoughMemoryError("Not enough memory to allocate dynamic-programming table");
    }

    // allocate DP table where:
    // - the row i represents the number of items
    // - the col j represents the capacity of the knapsack
    // - any element at some index [i][j] represents the optimal total value for
    //   a knapsack with j, where, of the num_items total items, only the
    //   first i items may be selected.
    uint32_t* DP_tab = new uint32_t[max_row * max_col];
    memset(DP_tab, 0, max_row * max_col * sizeof(uint32_t));

    // Table is filled according to the following recurrence relation:
    //
    // For item i, with weight wi and value vi:
    //
    //   DP_tab[i][j] = max(DP_tab[i-1][j], DP_tab[i-1][j-wi] + vi)
    //
    // Thus, filling in an element of the table requires only elements from the
    // previous row, and we can fill the table one row at a time.
    // Row 0 is already filled in during initialization.
    // Note that the lecture slides suggest filling in one column at a time. However,
    // I flipped the table for better cache locality :)
    for (size_t r = 1; r < max_row; ++r)
    {
        DP_fill_row(DP_tab, r, max_col);
    }

    // Now, trace back through the table:
    uint32_t r = max_row - 1;
    uint32_t c = max_col - 1;

    while(true)
    {
        if (r == 0)
        {
            break;
        }

        uint32_t current_value = DP_tab[r*max_col + c];
        uint32_t next_value = DP_tab[(r-1)*max_col + c];

        if (current_value == next_value)
        {
            // This item wasn't taken, go straight to the previous row
            --r;
        }
        else
        {
            // This item was taken, trace diagonally and mark item as taken
            sol.selected_items[r-1] = true;

            uint32_t weight = inst.items[r-1].weight;
            --r;
            c -= weight;
        }
    }

    sol.is_valid_solution = true;

    delete[] DP_tab;
    return sol;
}
