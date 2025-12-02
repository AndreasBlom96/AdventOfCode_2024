#pragma once
#include <string>
#include <vector>
#include <iostream>

std::string INPUT_DAY_15 = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day15.txt";
std::string INPUT_DAY_15_example = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day15_example.txt";

#define WALL '#'
#define ROBOT '@'
#define CRATE 'O'

class Object{
    public:
    int row, column;

    Object(int r, int c) 
    : row(r), column(c) {};                                                              

};

class Wall: public Object{
    public:
    char type = WALL;
    using Object::Object;
};
class Crate: public Object{
    public:
    char type = CRATE;
    using Object::Object;
};

class Robot: public Object{
    public:
    char type = ROBOT;
    using Object::Object;
};
class Map{
    public:
    int maxRows, maxColumns;
    std::vector<Object> crates;
    std::vector<Object> walls;
    std::vector<std::vector<char>> grid;
    Robot *robot;
    Map(int rmax, int cmax, Robot *r)
        : maxRows(rmax), maxColumns(cmax), robot(r) {};
};


namespace day15{
    unsigned long long solve_A(std::string input);
    unsigned long long solve_B(std::string input);

    bool recursive_move(char dir, std::vector<std::vector<char>> &grid, int current_row, int current_col, char type, Robot *r){
        int col = 0;
        int row = 0;
        switch (dir)
        {
        case '^':
            row = -1;
            break;

        case '>':
            col = 1;
            break;

        case 'v':
            row = 1;
            break;

        case '<':
            col = -1;
            break;

        default:
        std::cout << "error in switch state..." << "\n";
            break;
        }

        int new_col = current_col + col;
        int new_row = current_row + row;
        char next_obj = grid[new_row][new_col];

        if(next_obj == WALL){
            return false;
        } else if (next_obj == '.')
        {
            grid[current_row][current_col] = '.';
            grid[new_row][new_col] = type;
            if(type == ROBOT){
                r->column = new_col;
                r->row = new_row;
            }
            return true;
        }

        if(recursive_move(dir, grid, new_row, new_col, CRATE, r)){
            grid[current_row][current_col] = '.';
            grid[new_row][new_col] = type;
            if(type == ROBOT){
                r->column = new_col;
                r->row = new_row;
            }
            return true;
        }

        return false;
        
    }

    void print_grid(std::vector<std::vector<char>> &grid){

        for(std::vector<char> line : grid){
            for(char c : line){
                std::cout << c;
            }
            std::cout << "\n";
        }
        std::cout << "\n\n\n";
    }

    unsigned long long solve(std::vector<std::vector<char>> &grid){
        unsigned long long ans = 0;
        int row = 0;
        int col;
        for (std::vector v_row : grid){
            col = 0;
            for(char obj : v_row){
                if(obj==CRATE){
                    ans += 100*row + col;
                }
                col++;
            }
            row++;
        }

        return ans;
    }
}

