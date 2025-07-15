#include <string>
#include "../common/utils.h"
#include <iostream>
#include <chrono>
#include "day10.h"
#include <algorithm>

namespace day10{
    using namespace std;
    int solve_A(string input){
        int ans = 0;
        vector<string> map = utils::ReadAllLines(input);

        //finding heads
        vector<pair<int,int>> heads;
        for(int i = 0; i<map.size(); i++){
            for(int k = 0; k < map[i].length(); k++){
                if(map[i][k] == '0') heads.push_back(make_pair(i,k));
            }
        }

        //recursive solution
        for(int i = 0; i< heads.size(); i++){
            vector<pair<int,int>> visited;
            ans += recursePath(map, heads[i], 0, visited);
        }
        return ans;
    }

    bool inBounds(const vector<string> &map ,pair<int,int> cord){
        if(cord.first < 0 or cord.first >= map.size()) return false;
        if(cord.second < 0 or cord.second >= map[cord.first].length()) return false;
        return true;
    }

    vector<path> checkPaths(const vector<string> &map ,pair<int,int> cord){
        vector<path> res;
        int a,b;
        if(inBounds(map, make_pair(cord.first-1, cord.second))){
            a = map[cord.first][cord.second] - '0';
            b = map[cord.first-1][cord.second] - '0';
            if( a+1 == b) res.push_back(UP);
        } 

        if(inBounds(map, make_pair(cord.first+1, cord.second))){
            a = map[cord.first][cord.second] - '0';
            b = map[cord.first+1][cord.second] - '0';
            if(a+1 == b) res.push_back(DOWN);
        } 
        if(inBounds(map, make_pair(cord.first, cord.second+1))){
            a = map[cord.first][cord.second] - '0';
            b = map[cord.first][cord.second+1] - '0';
            if(a+1 == b) res.push_back(RIGHT);
        } 
        if(inBounds(map, make_pair(cord.first, cord.second-1))){
            a = map[cord.first][cord.second] - '0';
            b = map[cord.first][cord.second-1] - '0';
            if(a+1 == b) res.push_back(LEFT);
        } 
        return res;
    }

    pair<int,int> step(pair<int,int> p, path q){
        pair<int,int> res = make_pair(p.first, p.second);
        switch(q) {
            case UP:
                res.first -=1;
                break;
            case RIGHT:
                res.second += 1;
                break;
            case DOWN:
                res.first += 1;
                break;
            case LEFT:
                res.second -= 1;
        }   
        return res;
    }

    int recursePath(vector<string> &map, pair<int,int> head, int depth, vector<pair<int,int>> &v){
        int score = 0;
        vector<path> paths = checkPaths(map, head);
        int numPaths = paths.size();
        auto it = find(v.begin(), v.end(), head);
        if(depth == 9 and it == v.end()){
            v.push_back(head);
            return 1;
        } 
        if(numPaths == 0 or it != v.end()) return 0;
        for(int i = 0; i<numPaths; i++){
           score += recursePath(map,step(head,paths[i]),depth+1, v);
        }
        return score;
    }

    int recursePath_B(vector<string> &map, pair<int,int> head, int depth, vector<pair<int,int>> &v){
        int score = 0;
        vector<path> paths = checkPaths(map, head);
        int numPaths = paths.size();
        auto it = find(v.begin(), v.end(), head);
        if(depth == 9 and it == v.end()){
            return 1;
        } 
        if(numPaths == 0 or it != v.end()) return 0;
        for(int i = 0; i<numPaths; i++){
           score += recursePath_B(map,step(head,paths[i]),depth+1, v);
        }
        return score;
    }

    int solve_B(string input){
        int ans = 0;
        vector<string> map = utils::ReadAllLines(input);

        //finding heads
        vector<pair<int,int>> heads;
        for(int i = 0; i<map.size(); i++){
            for(int k = 0; k < map[i].length(); k++){
                if(map[i][k] == '0') heads.push_back(make_pair(i,k));
            }
        }

        //recursive solution
        for(int i = 0; i< heads.size(); i++){
            vector<pair<int,int>> v;
            ans += recursePath_B(map, heads[i], 0, v);
        }
        return ans;
    }

}



int main(int argc, char* argv[]){
    std::string input = INPUT_DAY_10;
    unsigned long long result;
    if (argc >= 3 and std::string(argv[2]) == "example")
    {
        input = INPUT_DAY_10_example;
    }
    
    if (argc >= 2)  
    {
        std::string part = argv[1];
        if (part == "A")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day10::solve_A(input);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            std::cout << "it took: " << duration.count() << "ms" << std::endl;
            std::cout << "answer is -> " << result << std::endl;
            return result;
        }
        else if (part == "B")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day10::solve_B(input);
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