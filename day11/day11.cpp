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

        for(int blink = 0; blink < 25; blink++){
            cout << "blink: " << blink << endl;
            for(int i = 0; i<stones.size(); i++){
                string s = stones[i];
                if(s == "0"){
                    stones[i] = "1";
                } else if(s.length() % 2 == 0){
                    //split even, removing leading zeroes
                    int l = s.length();
                    int half = l/2;
                    string temp = s.substr(0, half);
                    stones[i] = temp;

                    temp = s.substr(half);
                    remove_leading_zeroes(temp);
                    auto it = stones.begin();
                    it += i+1;
                    stones.insert(it, temp);
                    i++;
                } else {
                    stones[i] = to_string(stoull(s) * 2024);
                }
            }
        }

        ans = stones.size();
        return ans;
    }

    void remove_leading_zeroes(string &s){
        while(s.length() > 1 and s[0] == '0'){
            s = s.substr(1);
        }
    }

    int solve_B(string input){
        int ans = 0;

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