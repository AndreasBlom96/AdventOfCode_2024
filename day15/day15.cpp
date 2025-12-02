#include <string>
#include "../common/utils.h"
#include <iostream>
#include <chrono>
#include "day15.h"

namespace day15{
    using namespace std;
    unsigned long long solve_A(string input){
        unsigned long long ans = 0;
        
        vector<string> lines = utils::ReadAllLines(input);

        int row=0;
        int col=0;
        vector<char> moves;
        vector<vector<char>> grid;
        int moves_flag=0;
        Robot r(0,0);
        Map m = Map(10,10, &r);
        for(string line : lines){
            col =0;
            vector<char> v;
            for(char c : line){
                if(c == WALL){
                    Wall w = Wall(row, col);
                    v.push_back(c);
                    m.walls.push_back(w);
                }
                else if (c==CRATE)
                {
                    Crate cr = Crate(row, col);
                    v.push_back(c);
                    m.crates.push_back(cr);
                }
                else if (c==ROBOT)
                {
                    r.row = row;
                    r.column = col;
                    v.push_back(c);
                }
                else if (c=='.')
                {
                    v.push_back(c);
                }
                else
                {
                    moves.push_back(c);
                    col--;
                    moves_flag = 1;
                }
                
                col++;
            } //end of inner for loop
            
            if(moves_flag == 0)
            {
                grid.push_back(v);
                row++;
            }
        } // end out outer for loop
        m.grid = grid;


        cout << "init stat:\n";
        print_grid(grid);
        //process moves
        for(char move : moves){
           // cout << "moving- " << move << "\n";
            recursive_move(move, grid, r.row, r.column, ROBOT, &r);
           // print_grid(grid);
        }
        
        print_grid(grid);
        return solve(grid);
    }

    unsigned long long solve_B(string input){
        int ans = 0;

        return ans;
    }

}



int main(int argc, char* argv[]){
    std::string input = INPUT_DAY_15;
    unsigned long long result;
    if (argc >= 3 and std::string(argv[2]) == "example")
    {
        input = INPUT_DAY_15_example;
    }
    
    if (argc >= 2)  
    {
        std::string part = argv[1];
        if (part == "A")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day15::solve_A(input);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            std::cout << "it took: " << duration.count() << "ms" << std::endl;
            std::cout << "answer is -> " << result << std::endl;
            return result;
        }
        else if (part == "B")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day15::solve_B(input);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            std::cout << "it took: " << duration.count() << "ms" << std::endl;
            std::cout << "answer is -> " << result << std::endl;
            return result;
        }
        
        std::cout << "unknown command" << std::endl;
        return -1;
    }
    
}