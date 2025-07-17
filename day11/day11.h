#pragma once
#include <string>
#include <vector>
#include<iostream>
#include <map>


std::string INPUT_DAY_11 = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day11.txt";
std::string INPUT_DAY_11_example = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day11_example.txt";

namespace day11{
    int solve_A(std::string input);
    unsigned long long solve_B(std::string input);
    unsigned long long recursive_stones( const std::string s, const int depth, std::map<std::pair<std::string,int>, unsigned long long> &p);
    void remove_leading_zeroes(std::string &s);
}