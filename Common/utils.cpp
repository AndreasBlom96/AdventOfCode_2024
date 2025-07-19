#include <iostream>
#include <fstream>
#include "utils.h"
#include <string>

namespace utils {

std::vector<std::string> ReadAllLines(std::string input){
    std::ifstream inFile;
    std::vector<std::string> lines;

    inFile.open(input);
    if (!inFile) {
        std::cout << "Unable to open file datafile.txt" << std::endl;
        return lines;
    }
    
    std::string temp;

    while(getline(inFile ,temp))
    {
        lines.push_back(temp);
    }
    return lines;
}

bool checkInBounds(int row, int col, const std::vector<std::string> &map){
    return (row >= 0 && row < map.size() && col >= 0 && col < map[row].length());
}

}