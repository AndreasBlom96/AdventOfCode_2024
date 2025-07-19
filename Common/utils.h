#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>


namespace utils{

std::vector<std::string> ReadAllLines(std::string input);
bool checkInBounds(int row, int col, const std::vector<std::string> &map);

struct pair_hash{
    template <typename T, typename U>
    std::size_t operator()(const std::pair<T,U> &p) const{
        return (p.first) ^ (p.second << 1);
    }
};

}