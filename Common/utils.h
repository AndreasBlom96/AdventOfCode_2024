#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>


namespace utils{

std::vector<std::string> ReadAllLines(std::string input);
bool checkInBounds(int row, int col, const std::vector<std::string> &map);

}