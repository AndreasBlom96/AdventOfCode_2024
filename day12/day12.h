#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <ranges>
#include <numeric>

std::string INPUT_DAY_12 = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day12.txt";
std::string INPUT_DAY_12_example = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day12_example.txt";

struct garden_point{
    int row, col, neighbours;
};


namespace day12{
    int solve_A(std::string input);
    int solve_B(std::string input);
    void add_valid_neighbours(const auto q, auto &queue, const auto &garden, auto &v);
    int check_n(const garden_point gp, const auto &garden);
}


struct region{
    std::vector<garden_point> points;
    char type;

    int getSize(){
        return points.size();
    }

    int getPerimeter(){
        int sum = std::transform_reduce(
            points.begin(), points.end(),
            0,
            std::plus<>(),
            [](garden_point &gp){return gp.neighbours;}
        );
        return sum;
    }
};

template <typename T, typename U>
std::pair<T, U> operator+(const std::pair<T,U> &l, const std::pair<T,U> &r){
    return std::make_pair(l.first + r.first, l.second + r.second);
}
