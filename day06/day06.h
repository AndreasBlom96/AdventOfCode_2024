#pragma once
#include <string>
#include <vector>


std::string INPUT_DAY_6 = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day06.txt";
std::string INPUT_DAY_6_example = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day06_example.txt";

namespace day06{
   int solve_A(std::string input);
   int solve_B(std::string input);
   bool walk_until_stop(std::vector<std::string> *map ,std::pair<int,int> *guard, std::vector<std::pair<int,int>> obst, std::string dir);
   void print_map(std::vector<std::string> map, std::pair<int,int> *guard);
   int count_x(std::vector<std::string> *map);

   struct point
   {
    int row;
    int col;
    int dir;

    bool operator==(const point& other) const {
            return row == other.row && col == other.col && dir == other.dir;
        }
   };
   
}