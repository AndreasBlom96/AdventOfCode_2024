#include <string>
#include "../common/utils.h"
#include <iostream>
#include <chrono>
#include "day12.h"
#include <queue>
#include <unordered_set>
#include <algorithm>

namespace day12{
    using namespace std;

    int solve_A(string input){
        int ans = 0;
        vector<string> garden = utils::ReadAllLines(input);

        vector<region> regions;
        unordered_set<pair<int,int> , utils::pair_hash> visited;
        //walker! walking the region
        for(int row = 0; row < garden.size(); row++){
            for(int col = 0; col < garden[row].length(); col++){
                
                if(visited.contains(pair{row,col})) continue;
                visited.insert(make_pair(row, col));

                garden_point gp{row, col, 0};
                gp.neighbours = check_n(gp, garden);

                queue<garden_point> queue;
                queue.push(gp);                
                vector<garden_point> g;
                
                while(!queue.empty()){
                    garden_point q = queue.front(); queue.pop();
                    g.push_back(q);
                    
                    //check for possible valid neighbours (at the same time check perimeter?)
                    add_valid_neighbours(q, queue, garden, visited);
                }
                region r{g, garden[row][col]};
                regions.push_back(r); 
            }
        }

        for(int i = 0; i< regions.size(); i++){
            int area = regions[i].getSize();
            int perimeter = regions[i].getPerimeter();
            //cout << "type: " << regions[i].type << ", area: " << area << ", perimeter: " << perimeter << endl;
            ans += area * perimeter;
        }
        return ans;
    }

    int check_n( const garden_point gp, const auto &garden){
        int res = 0;
        vector<pair<int,int>> dir = {{-1,0}, {0,1}, {1,0}, {0, -1}};
        for(pair<int,int> p : dir){
            pair<int,int> step = p + make_pair(gp.row, gp.col);
            if(!utils::checkInBounds(step.first, step.second, garden) or garden[step.first][step.second] != garden[gp.row][gp.col]){
                res++;
            }
        }
        return res;
    }

    void add_valid_neighbours(const auto q, auto &queue, const auto &garden, auto &v){
        vector<pair<int,int>> dir = {{-1,0}, {0,1}, {1,0}, {0, -1}};
        for(pair<int,int> p : dir){
            pair<int,int> step = p + make_pair(q.row, q.col);
            if(v.contains(step)) continue;
            if(utils::checkInBounds(step.first, step.second, garden) && garden[q.row][q.col] == garden[step.first][step.second]){
                garden_point temp{step.first, step.second, 0};
                temp.neighbours = check_n(temp, garden);
                queue.push(temp);
                v.insert(make_pair(temp.row, temp.col));
            }
        }
        return;
    }

    int check_inner_corners(const garden_point q, const vector<string> &garden){
        int res = 0;
        auto c = garden[q.row][q.col];
        vector<pair<int,int>> dir = {{-1,-1}, {-1,1}, {1,-1}, {1,1}};
        auto q_pair = make_pair(q.row, q.col);
        

        //find diagonal elements that makes an inner corner in the region
        for(pair<int,int> p : dir){
            auto step = p + q_pair;
            bool first= false;
            if(utils::checkInBounds(step.first, step.second, garden) && garden[step.first][step.second] == c){
                if(utils::checkInBounds(step.first, q.col, garden) && garden[step.first][q.col] != c ){
                    res++;
                    first = true;
                }
                if(utils::checkInBounds(q.row, step.second, garden) && garden[q.row][step.second] != c){
                    if(first){
                        res--;
                    } else {
                        res++;
                    }
                }
            }
        }

        return res;
    }

    int check_outer_corners( const garden_point gp, const vector<string> &garden){
        bool corner = false;
        int res = 0;
        vector<pair<int,int>> dir = {{-1,0}, {0,1}, {1,0}, {0, -1}, {-1, 0}};
        for(pair<int,int> p : dir){
            pair<int,int> step = p + make_pair(gp.row, gp.col);
            if(!utils::checkInBounds(step.first, step.second, garden) or garden[step.first][step.second] != garden[gp.row][gp.col]){
                if(corner) res++;
                corner = true;
            } else {
                corner = false;
            }
        }
        return res;
    }
    
    int solve_B(string input){
        int ans = 0;
        vector<string> garden = utils::ReadAllLines(input);

        vector<region> regions;
        unordered_set<pair<int,int> , utils::pair_hash> visited;
        //walker! walking the region
        for(int row = 0; row < garden.size(); row++){
            for(int col = 0; col < garden[row].length(); col++){
                
                if(visited.contains(pair{row,col})) continue;
                visited.insert(make_pair(row, col));

                garden_point gp{row, col, 0};
                gp.neighbours = check_n(gp, garden);

                queue<garden_point> queue;
                queue.push(gp);                
                vector<garden_point> g;
                
                while(!queue.empty()){
                    garden_point q = queue.front(); queue.pop();
                    g.push_back(q);
                    
                    //check for possible valid neighbours (at the same time check perimeter?)
                    add_valid_neighbours(q, queue, garden, visited);
                }
                region r{g, garden[row][col]};
                regions.push_back(r); 
            }
        }

        for(int i = 0; i< regions.size(); i++){
            int area = regions[i].getSize();
            int sumInner = 0;
            int sumOuter = 0;
            for(garden_point gp : regions[i].points){
                sumInner += check_inner_corners(gp, garden);
                sumOuter += check_outer_corners(gp, garden);
            }
            sumInner /= 2;
            //cout << area << " * (" << sumInner << " + " << sumOuter << ")" << endl;
            ans += area * (sumInner+sumOuter);
        }

        return ans;
    }

}



int main(int argc, char* argv[]){
    std::string input = INPUT_DAY_12;
    unsigned long long result;
    if (argc >= 3 and std::string(argv[2]) == "example")
    {
        input = INPUT_DAY_12_example;
    }
    
    if (argc >= 2)  
    {
        std::string part = argv[1];
        if (part == "A")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day12::solve_A(input);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            std::cout << "it took: " << duration.count() << "ms" << std::endl;
            std::cout << "answer is -> " << result << std::endl;
            return result;
        }
        else if (part == "B")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day12::solve_B(input);
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