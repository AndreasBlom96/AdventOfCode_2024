#pragma once
#include <string>
#include <vector>
#include<iostream>
#include <utility>

std::string INPUT_DAY_10 = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day10.txt";
std::string INPUT_DAY_10_example = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day10_example.txt";

namespace day10{
    int solve_A(std::string input);
    int solve_B(std::string input);
    int recursePath(std::vector<std::string> &map, std::pair<int,int> head, int depth, std::vector<std::pair<int,int>> &v);
}

enum path{
    UP,
    RIGHT,
    DOWN,
    LEFT
};