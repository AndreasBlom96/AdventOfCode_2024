#include <string>
#include <chrono>
#include <iostream>
#include "day07.h"
#include "../Common/utils.h"
#include <cmath>

namespace day07{
    using namespace std;
    unsigned long long solve_A(string input){
        unsigned long long ans = 0;
        vector<string> lines = utils::ReadAllLines(input);

        unsigned long long value;
        vector<unsigned long long> values;
        string tempNumbers;
        vector<vector<unsigned long long>> numbers;
        int i=0;
        for (string line : lines)
        {
            vector<unsigned long long> v;
            cout << line << endl;
            int index = line.find(":");
            value = stoll(line);
            values.push_back(value);

            tempNumbers = line.substr(index+2);
            while(tempNumbers.find(" ") != string::npos){
                v.push_back(stoi(tempNumbers));
                index = tempNumbers.find(" ");
                tempNumbers = tempNumbers.substr(index+1);
            }
            v.push_back(stoi(tempNumbers));
            numbers.push_back(v);
            i++;
        }
        cout << endl;
        
        for(int i=0; i < values.size(); i++){
            vector<unsigned long long> numbersToCheck = numbers[i];
            value = values[i];
            //cout << "checking value: " << value << ", with numbers ->" << numbersToCheck[0] << endl;

            int num_of_variations = pow(2,numbersToCheck.size()-1);
            for(int i = 0; i<num_of_variations; i++){
                if(value == applyOps(numbersToCheck, i)){
                    ans += value;
                    cout << "found matching comb!, adding value: " << value << endl;
                    break;
                } 
            }
        }

        return ans;
    }

    unsigned long long applyOps(const vector<unsigned long long> &nums, int mask){
        long long result = nums[0];
        for(int i =1; i < nums.size(); i++){
            if((mask >> i-1) & 1){
                result *= nums[i];
            } else {
                result += nums[i];
            }
        }
        return result;
    }



    unsigned long long solve_B(string input){
        unsigned long long ans = 0;
        vector<string> lines = utils::ReadAllLines(input);

        unsigned long long value;
        vector<unsigned long long> values;
        string tempNumbers;
        vector<vector<unsigned long long>> numbers;
        int i=0;
        for (string line : lines)
        {
            vector<unsigned long long> v;
            cout << line << endl;
            int index = line.find(":");
            value = stoll(line);
            values.push_back(value);

            tempNumbers = line.substr(index+2);
            while(tempNumbers.find(" ") != string::npos){
                v.push_back(stoi(tempNumbers));
                index = tempNumbers.find(" ");
                tempNumbers = tempNumbers.substr(index+1);
            }
            v.push_back(stoi(tempNumbers));
            numbers.push_back(v);
            i++;
        }
        cout << endl;

        for(int i=0; i < values.size(); i++){
            vector<unsigned long long> numbersToCheck = numbers[i];
            value = values[i];
            //cout << "checking value: " << value << ", with numbers ->" << numbersToCheck[0] << endl;

            int num_of_variations = pow(3,numbersToCheck.size()-1);
        }

        return ans;
    }
}


int main(int argc, char* argv[]){
    std::string input = INPUT_DAY_7;
    unsigned long long result;
    if (argc >= 3 and std::string(argv[2]) == "example")
    {
        input = INPUT_DAY_7_example;
    }
    
    if (argc >= 2)  
    {
        std::string part = argv[1];
        if (part == "A")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day07::solve_A(input);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            std::cout << "it took: " << duration.count() << "ms" << std::endl;
            std::cout << "answer is -> " << result << std::endl;
            return result;
        }
        else if (part == "B")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day07::solve_B(input);
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