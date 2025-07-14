#pragma once
#include <string>
#include <vector>
#include <iostream>

std::string INPUT_DAY_09 = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day09.txt";
std::string INPUT_DAY_09_example = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day09_example.txt";

namespace day09{
    unsigned long long solve_A(std::string input);
    unsigned long long solve_B(std::string input);
}

struct block{
    int ID;
    int index;
    int length;
};

std::ostream& operator<<(std::ostream& os, const block& b){
    return os << "b(" << b.ID  << ", " << b.index << ", " << b.length << ")"; 
}