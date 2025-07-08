#include <string>
#include <chrono>
#include "day08.h"
#include <iostream>
#include <algorithm>
#include "../Common/utils.h"

namespace day08{
    using namespace std;

    int solve_A(string input){
        int ans = 0;
        vector<string> map = utils::ReadAllLines(input);
        vector<antenna> antennas;
        for(int row=0; row < map.size(); row++){
            for(int col =0; col<map[row].length(); col++){
                if(map[row][col] != '.'){
                    //save coordinate of type in vector
                    antennas.push_back(antenna{row, col, map[row][col]});
                }
            }
        }

        vector<char> antennas_types;
        //antennas by type? 
        for (antenna a : antennas)
        {
            if(find(antennas_types.begin(), antennas_types.end(), a.freq) == antennas_types.end()){
                antennas_types.push_back(a.freq);
            }
        }

        //now group antennas
        vector<vector<antenna>> antennas_grouped;
        for (char c : antennas_types)
        {
            vector<antenna> v;
            for (int i = 0; i < antennas.size(); i++)
            {
                if(antennas[i].freq == c) v.push_back(antennas[i]);
            }
            antennas_grouped.push_back(v);
        }
        
        

        return ans;
    }

    int solve_B(string input){
        int ans = 0;

        return ans;
    }

}




int main(int argc, char* argv[]){
    std::string input = INPUT_DAY_8;
    unsigned long long result;
    if (argc >= 3 and std::string(argv[2]) == "example")
    {
        input = INPUT_DAY_8_example;
    }
    
    if (argc >= 2)  
    {
        std::string part = argv[1];
        if (part == "A")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day08::solve_A(input);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            std::cout << "it took: " << duration.count() << "ms" << std::endl;
            std::cout << "answer is -> " << result << std::endl;
            return result;
        }
        else if (part == "B")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day08::solve_B(input);
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