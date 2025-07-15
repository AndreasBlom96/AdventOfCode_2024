#pragma once
#include <string>
#include <vector>
#include<iostream>

std::string INPUT_DAY_11 = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day11.txt";
std::string INPUT_DAY_11_example = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day11_example.txt";

namespace day11{
    int solve_A(std::string input);
    int solve_B(std::string input);
    void remove_leading_zeroes(std::string &s);
}