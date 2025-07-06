#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

std::string INPUT_DAY_5 = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day05.txt";
std::string INPUT_DAY_5_example = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day05_example.txt";
namespace day05{

    int solve_A(std::string input);
    int solve_B(std::string input);
    bool check_rule(std::pair<int,int> rule, std::vector<int> dataLine);
    void switch_vector_elemet(std::vector<int>* v, std::pair<int,int> p);

}