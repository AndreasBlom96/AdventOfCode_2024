#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include "../Common/utils.h"
#include "day05.h"
#include <chrono>

namespace day05{
using namespace std;

int solve_A(string input){
    int ans = 0;
    vector<string> lines;
    lines = utils::ReadAllLines(input);
    /*for(string line : lines){
        cout << line << endl;
    } */

    //get the data/rules first
    vector<pair<int,int>> rules;
    vector<vector<int>> data;
    for(string line : lines){
        bool make_rules = true;
        if(line.find("|") == string::npos) make_rules = false;
        if(make_rules){
            //make pair
            int first = stoi(line);
            int second = stoi(line.substr(line.find("|")+1));
            rules.push_back(pair<int,int> (first,second));
            //cout << "first: " << first << " second: " << second << endl;
        }
        else if(line != ""){
            //line is now comma separated list of number
            int index = 0;
            vector<int> subData;
            while(true){
                size_t pos = line.find(",");
                subData.push_back(stoi(line));
                line = line.substr(pos+1);
                if(pos == string::npos) break;
                index++;
            }
            data.push_back(subData);
        }
    }

    //For every line of data, check all rules
    bool ok;
    for (vector<int> v : data)
    {
        ok = true;
        for(pair<int,int> r : rules){
            //check rule
            if(check_rule(r, v) != true){
                ok = false;
                break;
            }
        }
        if(ok)ans+=v[v.size()/2];
    }    
    return ans;
}

bool check_rule(pair<int,int> rule, vector<int> dataLine){
    //check if both exist and save their index
    auto first_index = find(dataLine.begin(),dataLine.end(),rule.first);
    auto second_index = find(dataLine.begin(),dataLine.end(),rule.second);
    if(first_index == dataLine.end() or second_index == dataLine.end()) return true;

    //both exists, now we check if rule holds!
    if(first_index < second_index) return true;

    //Else return false
    return false;
}

int solve_B(string input){
    int ans = 0;
    vector<string> lines;
    lines = utils::ReadAllLines(input);
    /*for(string line : lines){
        cout << line << endl;
    } */

    //get the data/rules first
    vector<pair<int,int>> rules;
    vector<vector<int>> data;
    for(string line : lines){
        bool make_rules = true;
        if(line.find("|") == string::npos) make_rules = false;
        if(make_rules){
            //make pair
            int first = stoi(line);
            int second = stoi(line.substr(line.find("|")+1));
            rules.push_back(pair<int,int> (first,second));
            //cout << "first: " << first << " second: " << second << endl;
        }
        else if(line != ""){
            //line is now comma separated list of number
            int index = 0;
            vector<int> subData;
            while(true){
                size_t pos = line.find(",");
                subData.push_back(stoi(line));
                line = line.substr(pos+1);
                if(pos == string::npos) break;
                index++;
            }
            data.push_back(subData);
        }
    }

    //For every line of data, check all rules
    bool add;
    for (vector<int> v : data)
    {
        add = false;
        while(true){
            bool flag_OK = true;
            for(pair<int,int> r : rules){
                //check rule
                if(check_rule(r, v) != true){
                    add = true;
                    flag_OK = false;
                    //fix this rule
                    switch_vector_elemet(&v, r);
                }
            }
            if(flag_OK) break;
        }
        if(add) ans += v[v.size()/2];
    }    

    return ans;
}

void switch_vector_elemet(vector<int>* v, pair<int,int> p){
    int temp = *find(v->begin(), v->end(), p.first);
    *find(v->begin(), v->end(), p.first) = *find(v->begin(),v->end(), p.second);
    *find(v->begin(),v->end(), p.second) = temp;
}



} //end of namspace



int main(int argc, char* argv[]){
    std::string input = INPUT_DAY_5;
    int result;
    if (argc >= 3 and std::string(argv[2]) == "example")
    {
        input = INPUT_DAY_5_example;
    }
    
    if (argc >= 2)  
    {
        std::string part = argv[1];
        if (part == "A")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day05::solve_A(input);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            std::cout << "it took: " << duration.count() << "ms" << std::endl;
            std::cout << "answer is -> " << result << std::endl;
            return result;
        }
        else if (part == "B")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day05::solve_B(input);
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