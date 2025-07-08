#pragma once
#include <string>
#include <vector>

std::string INPUT_DAY_8 = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day08.txt";
std::string INPUT_DAY_8_example = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day08_example.txt";

struct antenna
{
    int row,col;
    char freq;
};


namespace day08{
    int solve_A(std::string input);
    int solve_B(std::string input);

}