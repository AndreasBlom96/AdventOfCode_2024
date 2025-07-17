#include <string>
#include "../common/utils.h"
#include <iostream>
#include <chrono>
#include "day11.h"
#include <algorithm>


namespace day11{
    using namespace std;
    int solve_A(string input){
        int ans = 0;
        string line = utils::ReadAllLines(input)[0];
        vector<string> stones;

        size_t index;
        while(true){
            index = line.find(' ');
            if(index == string::npos) break;
            stones.push_back(line.substr(0,index));
            line = line.substr(index +1);
        }
        stones.push_back(line);

        for(string s : stones){
            cout << s << endl;
        }

        map<pair<string, int>, unsigned long long> memo;
        for(int i = 0; i < stones.size(); i++){
            ans += recursive_stones(stones[i], 25, memo);
        }
        return ans;
    }

    void remove_leading_zeroes(string &s){
        while(s.length() > 1 and s[0] == '0'){
            s = s.substr(1);
        }
    }

    unsigned long long recursive_stones( const string s, const int depth, map<pair<string,int>, unsigned long long> &p){
        vector<string> v;
        string temp;
        if(depth == 0) return 1;

        auto it = p.find(make_pair(s, depth));
        if(it != p.end()) return it -> second;

        if(s == "0"){
            v.push_back("1");
        } else if (s.length() % 2 == 0){
            int half = s.length()/2;
            string se = s.substr(half);
            remove_leading_zeroes(se);
            v.push_back(s.substr(0,half));
            v.push_back(se);
        } else {
            v.push_back(to_string(stoull(s) * 2024));
        }
        unsigned long long sum = 0;
        for(int i = 0; i < v.size(); i++){
            sum += recursive_stones(v[i], depth -1, p);
        }
        p.insert({make_pair(s,  depth), sum});
        return sum;
    }

    unsigned long long solve_B(string input){
        unsigned long long ans = 0;
        string line = utils::ReadAllLines(input)[0];
        vector<string> stones;

        size_t index;
        while(true){
            index = line.find(' ');
            if(index == string::npos) break;
            stones.push_back(line.substr(0,index));
            line = line.substr(index +1);
        }
        stones.push_back(line);

        for(string s : stones){
            cout << s << endl;
        }

        map<pair<string, int>, unsigned long long> memo;
        for(int i = 0; i<stones.size(); i++){
            ans += recursive_stones(stones[i], 75, memo);
        }

        return ans;
    }

}



int main(int argc, char* argv[]){
    std::string input = INPUT_DAY_11;
    unsigned long long result;
    if (argc >= 3 and std::string(argv[2]) == "example")
    {
        input = INPUT_DAY_11_example;
    }
    
    if (argc >= 2)  
    {
        std::string part = argv[1];
        if (part == "A")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day11::solve_A(input);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            std::cout << "it took: " << duration.count() << "ms" << std::endl;
            std::cout << "answer is -> " << result << std::endl;
            return result;
        }
        else if (part == "B")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day11::solve_B(input);
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