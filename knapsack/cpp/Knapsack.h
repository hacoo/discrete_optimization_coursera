#pragma once

#include <cstddef>
#include <cstdint>
#include <bitset>
#include <algorithm>
#include <vector>

// Item in the knapsack
class KnapsackItem
{
public:
    KnapsackItem(uint32_t in_value, uint32_t in_weight)
        :
        value(in_value),
        weight(in_weight)
    { }

    KnapsackItem(const KnapsackItem& other)
        :
        value(other.value),
        weight(other.weight)
    { }

    KnapsackItem& operator= (const KnapsackItem& other)
    {
        if (this != &other)
        {
            value = other.value;
            weight = other.weight;
        }
        return *this;
    }

public:
    uint32_t value;
    uint32_t weight;
};

// Instance of the Knapsack problem
class KnapsackInst
{
public:
    KnapsackInst(uint32_t in_capacity, const std::vector<KnapsackItem>& in_items)
        :
        num_items(in_items.size()),
        capacity(in_capacity),
        items(in_items)
    { }

public:

    const uint32_t num_items;
    const uint32_t capacity;
    const std::vector<KnapsackItem> items;
};

// Construct from properly-formatted input strings. Will throw std::runtime_error
// if input lines don't match spec
KnapsackInst knapsackinst_from_input_lines(const std::vector<std::string>& input_lines);


// Solution to the knapsack problem. Not const, may be updated
// in-place as the solution is built.
class KnapsackSolution
{
public:
    KnapsackSolution(const KnapsackInst& inst)
        :
        selected_items(inst.num_items, false),
        is_optimal(false),
        is_valid_solution(false),
        should_repeat(true)
    { }

public:
    // Bit vector indicating which items were selected
    std::vector<bool> selected_items;

    // If true, this is the best possible solution
    bool is_optimal;

    // If true, this solution instance has been solved an is a valid solution
    // (not necessarily the optimal one!)
    bool is_valid_solution;

    // If true, flags to the solver that solve() should be run again,
    // instead of re-using this solution (if this solution is valid)
    bool should_repeat;
};

// Base interface for knapsack solvers
class KnapsackSolver
{
public:
    KnapsackSolver(const KnapsackInst& in_inst)
        :
        inst(in_inst),
        solution(inst)
    {
        solution.is_valid_solution = false;
    }

    KnapsackSolution solve();

    // Solve this instance of the problem and return solution as a string
    // suitable for submission
    std::string solution_string();

protected:

    KnapsackInst inst;
    KnapsackSolution solution;

protected:

    // Does actual solver work
    virtual KnapsackSolution solve_internal() = 0;
};
