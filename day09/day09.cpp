#include <string>
#include "../common/utils.h"
#include <iostream>
#include <chrono>
#include "day09.h"
#include <algorithm>

namespace day09{
    using namespace std;
    unsigned long long solve_A(string input){
        unsigned long long ans = 0;
        ifstream file;
        string line;
        file.open(input);
        if(!file){
            cout << "cant open file" << endl;
            return ans;
        }
        getline(file, line);

        if(line.length() < 25)cout << line << endl;

        bool freeSpace = false;
        vector<block> memory;
        vector<block> freeMemory;
        int ID = 0;
        int index = 0;
        for (int i = 0; i < line.length(); i++)
        {
            block b;
            b.index = index;
            b.length = line[i] - '0';
            if(freeSpace){
                freeSpace = false;
                b.ID = -1;
                if(b.length == 0)continue;
                freeMemory.push_back(b);
            } else {
                freeSpace = true;
                b.ID = ID;
                ID++;
                //if(b.length == 0)continue;
                memory.push_back(b);
            }
            index += line[i] - '0';
        }

        /*
        cout << "memory!" << endl;
        for(int i = 0; i < memory.size(); i++){
            cout << memory[i] << endl;
        }
        cout << endl;

        cout << "free memeory" << endl;
        for(int i = 0; i < freeMemory.size(); i++){
            cout << freeMemory[i] << endl;
        }
        */

        //memory ok! 
        for(int i = 0; i < freeMemory.size(); i++){
            //case same length
            block &f = freeMemory[i];
            block b = memory.back();
            if(f.index > b.index)break;
            if(f.length == b.length){
                b.index = f.index;
                f.length = 0;
                memory.insert(memory.begin(), b);
                memory.pop_back();
            } else if (f.length > b.length){
                //wtf am i going to do here!
                b.index = f.index;
                memory.insert(memory.begin(), b);
                memory.pop_back();
                f.length -= b.length;
                f.index += b.length;
                i--;
            } else if(f.length < b.length){
                block c;
                c.ID = b.ID;
                c.index = f.index;
                c.length = f.length;
                memory.insert(memory.begin(),c);
                memory.pop_back();
                b.length -= f.length;
                memory.push_back(b);
                f.length = 0;
            }
            
        }

        //check ans
        for(int i = 0; i < memory.size(); i++){
            block b = memory[i];
            for (int k = 0; k < b.length; k++)
            {
                //cout << "index: " << b.index + k << " ID: " << b.ID << endl;  
                ans += (b.index + k) * b.ID;
            }
        }

        return ans;
    }

    int solve_B(string input){
        int ans = 0;

        return ans;
    }

}



int main(int argc, char* argv[]){
    std::string input = INPUT_DAY_09;
    unsigned long long result;
    if (argc >= 3 and std::string(argv[2]) == "example")
    {
        input = INPUT_DAY_09_example;
    }
    
    if (argc >= 2)  
    {
        std::string part = argv[1];
        if (part == "A")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day09::solve_A(input);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            std::cout << "it took: " << duration.count() << "ms" << std::endl;
            std::cout << "answer is -> " << result << std::endl;
            return result;
        }
        else if (part == "B")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day09::solve_B(input);
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