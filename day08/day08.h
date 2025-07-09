#pragma once
#include <string>
#include <vector>
#include<iostream>

std::string INPUT_DAY_8 = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day08.txt";
std::string INPUT_DAY_8_example = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day08_example.txt";

struct antenna
{
    int row,col;
    char freq;
};
// Overload operator<< for antenna
std::ostream& operator<<(std::ostream& os, const antenna& a) {
    os << a.freq << "(row=" << a.row << ", col=" << a.col << ")";
    return os;
}

namespace day08{
    int solve_A(std::string input);
    int solve_B(std::string input);
    int find_k(antenna a, antenna b);
    int distance(antenna a, antenna b);
    bool check_bounds(std::vector<std::string> &map, int row, int col);

}