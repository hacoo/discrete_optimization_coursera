
#include <sstream>
#include <cstdio>
#include <stdexcept>
#include <iostream>
#include "Knapsack.h"

KnapsackInst knapsackinst_from_input_lines(const std::vector<std::string>& input_lines)
{
    if (input_lines.size() < 2)
    {
        throw std::runtime_error("Too few input lines");
    }

    uint32_t num_items = 0;
    uint32_t capacity = 0;
    uint32_t args_found = 0;

    args_found = std::sscanf(input_lines[0].c_str(), "%u %u", &num_items, &capacity);

    if (args_found != 2)
    {
        throw std::runtime_error("Input line did not match spec");
    }

    std::vector<KnapsackItem> items;
    items.reserve(num_items);

    for(size_t i = 1; i < input_lines.size(); ++i)
    {
        const std::string& line = input_lines[i];
        uint32_t value = 0;
        uint32_t weight = 0;
        args_found = std::sscanf(line.c_str(), "%u %u", &value, &weight);

        if (args_found != 2)
        {
            throw std::runtime_error("Input line did not match spec");
        }

        items.emplace_back(value, weight);
    }

    if (items.size() != num_items)
    {
        throw std::runtime_error("Wrong number of input items found");
    }

    return KnapsackInst(capacity, items);
}

std::string KnapsackSolver::solution_string()
{
    std::stringstream sstr;
    uint32_t total_value = 0;
    KnapsackSolution solution = solve();

    for (size_t i = 0; i < inst.num_items; ++i)
    {
        if (solution.selected_items[i])
        {
            total_value += inst.items[i].value;
        }
    }

    sstr << total_value << " " << solution.is_optimal << std::endl;

    for (size_t i = 0; i < inst.num_items; ++i)
    {
        sstr << solution.selected_items[i] << " ";
    }

    sstr << std::endl;

    return sstr.str();
}

KnapsackSolution KnapsackSolver::solve()
{
    if (!solution.is_valid_solution || !solution.should_repeat)
    {
        solution = solve_internal();
    }

    return solution;
}
