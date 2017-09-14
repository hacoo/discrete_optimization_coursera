
#include <iostream>
#include <vector>
#include <string>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <cstdio>
#include <stdexcept>

#include "Knapsack.h"
#include "KnapsackGreedy.h"
#include "KnapsackDP.h"
#include "KnapsackBranchBound.h"

// Read input lines from file at path. Returns the input lines as strings.
std::vector<std::string> get_input_lines(std::string path)
{
    std::ifstream in;
    in.open(path.c_str());
    std::string line;

    if (!std::getline(in, line))
    {
        throw std::runtime_error("Input file was empty");
    }

    uint32_t num_items = 0;
    uint32_t capacity = 0;

    int num_matches = std::sscanf(line.c_str(), "%u %u", &num_items, &capacity);

    if (num_matches != 2)
    {
        throw std::runtime_error("First line of input did not match spec - expected n K");
    }

    std::vector<std::string> lines;
    lines.reserve(num_items + 1);

    size_t num_lines_found = 1;
    lines.push_back(line);

    while(getline(in, line))
    {
        lines.push_back(line);
        ++num_lines_found;
    }

    if(num_lines_found != num_items + 1)
    {
        throw std::runtime_error("Wrong number of lines in input file");
    }

    return lines;
}


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Wrong number of arguments" << std::endl;
        return 1;
    }

    std::string path = { argv[1] };
    std::vector<std::string> lines = get_input_lines(path);
    KnapsackInst inst = knapsackinst_from_input_lines(lines);

    try // Try DP solution first
    {
        KnapsackDPSolver dp_solver = { inst };
        std::cout << dp_solver.solution_string();
    }
    catch (const KnapsackDPSolver::NotEnoughMemoryError e)
    {
        KnapsackBranchBoundSolver bb_solver = { inst };
        std::cout << bb_solver.solution_string();
    }

    return 0;
}
