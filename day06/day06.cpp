#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include "../Common/utils.h"
#include "day06.h"
#include <chrono>




namespace day06{
    using namespace std;

    int solve_A(string input){
        int ans = 0;
        vector<string> lines = utils::ReadAllLines(input);
        /*for(string line : lines){
            cout << line << endl;
        }*/
        cout << endl;
        //find obstacles and guard
        pair<int,int> guard;
        vector<pair<int,int>> obstacles;
        for(size_t row=0; row < lines.size(); row++){
            for(size_t col=0; col < lines[row].size(); col++){
                if(lines[row][col] == '#') obstacles.push_back(make_pair(row,col));
                if(lines[row][col]=='^'){
                    guard = make_pair(row,col);
                    lines[row][col] = 'X';
                } 
            }
        }
        string direction = "UP";
        while (walk_until_stop(&lines, &guard, obstacles, direction) != true)
        {
            if (direction == "UP")
            {
                direction = "RIGHT";
            } else if (direction == "RIGHT")
            {
                direction = "DOWN";
            } else if (direction == "DOWN")
            {
                direction = "LEFT";
            } else if (direction == "LEFT")
            {
                direction = "UP";
            }
            //print_map(lines, &guard);
        }
        //print_map(lines, &guard);

        ans = count_x(&lines);
        return ans;
    }

    bool walk_until_stop(vector<string> *map ,pair<int,int> *guard, vector<pair<int,int>> obst, string dir){
        if (dir  == "UP")
        {
            int row = guard->first;
            int col = guard->second;

            //check if any obst is on same col but smaller row
            pair<int,int> closest(-1,99999);
            for(pair<int,int> p : obst){
                if(p.second == col and p.first < row and p.first > closest.first) closest = p;
            }
            
            for (int i = row-1; i >= 0; i--)
            {
                if(i == closest.first) break;
                (*map)[i][col]='X';
                guard->first = i;
            }
            if(closest.first == -1) return true;
            return false;
        }
        else if (dir  == "RIGHT")
        {
            int row = guard->first;
            int col = guard->second;

            //check if any obst is on same row but bigger col
            pair<int,int> closest(99999,99999);
            for(pair<int,int> p : obst){
                if(p.first == row and p.second > col and p.second < closest.second) closest = p;
            }
            
            for (int i = col+1; i < (*map)[row].length(); i++)
            {
                if(i == closest.second) break;
                (*map)[row][i]='X';
                guard->second = i;
            }
            if(closest.first == 99999) return true;
            return false;
        }
        else if (dir  == "DOWN")
        {
            int row = guard->first;
            int col = guard->second;

            //check if any obst is on same col but smaller row
            pair<int,int> closest(99999,99999);
            for(pair<int,int> p : obst){
                if(p.second == col and p.first > row and p.first < closest.first) closest = p;
            }
            
            for (int i = row; i < map->size(); i++)
            {
                if(i == closest.first) break;
                (*map)[i][col]='X';
                guard->first = i;
            }
            if(closest.first == 99999) return true;
            return false;
        }
        else if (dir  == "LEFT")
        {
            int row = guard->first;
            int col = guard->second;

            //check if any obst is on same row but smaller col
            pair<int,int> closest(99999,-1);
            for(pair<int,int> p : obst){
                if(p.first == row and p.second < col and p.second > closest.second) closest = p;
            }
            
            for (int i = col-1; i >= 0; i--)
            {
                if(i == closest.second) break;
                (*map)[row][i]='X';
                guard->second = i;
            }
            if(closest.first == -1) return true;
            return false;
        }
        return false;
    } 

    void print_map(vector<string> map, pair<int,int> *guard){
        for (size_t i = 0; i < map.size(); i++)
        {
            for (size_t j = 0; j < map[i].length(); j++)
            {
                if(i == guard->first and j==guard->second) map[i][j] = '^';
                cout << map[i][j];
            }
            
            cout << endl;
        }
        cout << endl;
    }

    int count_x(vector<string> *map){
        int count = 0;
        for (size_t i = 0; i < map->size(); i++)
        {
            for (size_t j = 0; j < (*map)[i].length(); j++)
            {
                if((*map)[i][j] == 'X') count++;
            }
            
        }  
        return count;
    }

    bool notOutOfBounds(vector<string> *map, int row, int col){
        int yMax = map->size();
        if(row >= yMax or row < 0) return false;
        int xMax = (*map)[row].length();
        if (col >= xMax or col < 0) return false;
        return true;
    }

    // Direction vectors
    const int dx[4] = { 0, 1, 0, -1 };  // change in column (x)
    const int dy[4] = { -1, 0, 1, 0 };  // change in row (y)

    int walkMap(vector<pair<int,int>> *obs, pair<int,int> g, vector<string> *map, vector<pair<int,int>> *v, bool first){
        int dir = 0;
        int newY;
        int newX;
        vector<point> visited;
        point p;
        p.dir = dir;
        while (notOutOfBounds(map, g.first + dy[dir], g.second + dx[dir]))
        {
            newY = g.first + dy[dir];
            newX = g.second + dx[dir];
            p.row = newY;
            p.col = newX;
            auto o = find(obs->begin(), obs->end(), make_pair(newY, newX));
            if (o == obs->end())
            {
                //no obstacle in front, walk
                g.first = newY;
                g.second = newX;
                (*map)[g.first][g.second] = 'X';
            } else {
                dir = (dir+1) % 4;
                p.dir = dir;
            }
            if(find(visited.begin(), visited.end(), p) != visited.end()){
                //print_map(*map, &g);
                return 1;
            }
            visited.push_back(p);
            if(first) v->push_back(make_pair(p.row, p.col));
        }
        return 0;
    }

    int solve_B(string input){
        int ans = 0;
        vector<string> lines = utils::ReadAllLines(input);
        for(string line : lines){
            cout << line << endl;
        }
        cout << endl;

        //find obstacles and guard
        pair<int,int> guard;
        vector<pair<int,int>> obstacles;
        for(size_t row=0; row < lines.size(); row++){
            for(size_t col=0; col < lines[row].size(); col++){
                if(lines[row][col] == '#') obstacles.push_back(make_pair(row,col));
                if(lines[row][col]=='^'){
                    guard = make_pair(row,col);
                    lines[row][col] = 'X';
                } 
            }
        }
        vector<pair<int,int>> visited;
        vector<string> tempMap = lines;
        vector<pair<int,int>> tempObstacles = obstacles;
        walkMap(&obstacles, guard, &lines, &visited, true);
        for(int r = 0; r < lines.size(); r++){
            for (int c = 0; c < lines[r].length(); c++)
            {
                if(find(visited.begin(), visited.end(), make_pair(r,c)) == visited.end()) continue;;
                //check if point (r,c) is a obsta or guard start pos
                auto obst = find(obstacles.begin(), obstacles.end(), make_pair(r,c));
                tempObstacles = obstacles;
                tempObstacles.push_back(make_pair(r,c));
                tempMap[r][c] = '0';
                if(walkMap(&tempObstacles, guard, &tempMap, &visited, false) == 1){
                    ans++;
                    cout << "found loop at: " << r << "," << c << endl;
               }
               tempMap[r][c] = '.';
            }
            
        }
        return ans;
    }


} //end of namespace



int main(int argc, char* argv[]){
    std::string input = INPUT_DAY_6;
    int result;
    if (argc >= 3 and std::string(argv[2]) == "example")
    {
        input = INPUT_DAY_6_example;
    }
    
    if (argc >= 2)  
    {
        std::string part = argv[1];
        if (part == "A")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day06::solve_A(input);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            std::cout << "it took: " << duration.count() << "ms" << std::endl;
            std::cout << "answer is -> " << result << std::endl;
            return result;
        }
        else if (part == "B")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day06::solve_B(input);
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