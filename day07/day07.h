#pragma once
#include <string>
#include <vector>

std::string INPUT_DAY_7 = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day07.txt";
std::string INPUT_DAY_7_example = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day07_example.txt";

namespace day07{
    unsigned long long applyOps(const std::vector<unsigned long long> &nums, int mask);
}
