#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

std::string INPUT_DAY_15 = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day15.txt";
std::string INPUT_DAY_15_example = "C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day15_example.txt";

#define WALL '#'
#define ROBOT '@'
#define CRATE 'O'
#define CRATE_Left '['
#define CRATE_RIGHT ']'

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
    Map(Robot *r)
        : robot(r) {};
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

    struct PairHash
    {
        std::size_t operator()(const std::pair<int,int>& p) const noexcept {
            return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
        }
    };

    void print_map(std::unordered_map<std::pair<int,int>, char, PairHash> &grid){
        // find min and max values
        int max_row = 0;
        int max_col = 0;

        for(auto [pos, val] : grid){
            max_row = std::max(max_row, pos.first);
            max_col = std::max(max_col, pos.second);
        }

        for(int r = 0; r <= max_row; r++){
            for (int c = 0; c <= max_col; c++)
            {
                auto it = grid.find({r,c});
                if(it != grid.end()){
                    std::cout << it->second;
                }     
            }
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }

    /*
    split this to two functions!
    one can move?
    and one move
    */
    bool recursive_move_b(
        char dir,
        int current_row,
        int current_col,
        char type,
        std::unordered_map<std::pair<int,int>,char, PairHash> &grid,
        Robot *r
        ){
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
        std::pair<int,int> next_pos = {new_row, new_col};

        char next_obj = grid[next_pos];

        if(next_obj == WALL){
            return false;
        }

        if((next_obj == CRATE_Left or next_obj == CRATE_RIGHT) and col == 0){
            int sec_col = (next_obj == CRATE_Left) ? 1 : -1;
            if(recursive_move_b(dir, new_row, new_col, CRATE, grid, r) and (recursive_move_b(dir, new_row, new_col + sec_col, CRATE, grid, r))){
                char current_symbol = grid[{current_row, current_col}];
                char other_symbol = grid[{current_row, current_col + sec_col}];
                grid[{current_row, current_col}] = '.';
                grid[{current_row, current_col + sec_col}] = '.';
                grid[{new_row, new_col}] = current_symbol;
                grid[{new_row, new_col + sec_col}] = other_symbol;
                if(type == ROBOT){
                    r->row = new_row;
                    r->column = new_col;
                }
                return true;
            }
        } else if (next_obj == CRATE_Left  or  next_obj == CRATE_RIGHT)
        {
            if (recursive_move_b(dir, new_row, new_col, CRATE, grid, r))
            {
                char current_symbol = grid[{current_row, current_col}];
                grid[next_pos] = current_symbol;
                grid[{current_row, current_col}] = '.';
                if(type == ROBOT){
                    r->row = new_row;
                    r->column = new_col;
                }
                return true;
            }
            
        }

        if(next_obj == '.'){
            char symbol = grid[{current_row, current_col}];
            grid[{current_row, current_col}] = '.';
            grid[{new_row, new_col}] = symbol;
            if(type == ROBOT){
                    r->row = new_row;
                    r->column = new_col;
                }
            return true;
        }

        return false;
    }
}



