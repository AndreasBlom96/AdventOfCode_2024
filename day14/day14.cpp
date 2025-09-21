#include <string>
#include "../common/utils.h"
#include <iostream>
#include <chrono>
#include "day14.h"
#include "helperClass.h"

namespace day14{
    using namespace std;
    unsigned long long solve_A(string input){
        unsigned long long ans = 0;
        vector<string> lines = utils::ReadAllLines(input);

        Board b = Board(7,11);
        if(input.find("example") == string::npos){
            b = Board(103,101);
        } 
       
        //parse input
        for(string line : lines){
            Robot R;
            int posX = stoi(line.substr(line.find("=")+1));
            int posY = stoi(line.substr(line.find(",")+1));
            int velX = stoi(line.substr(line.rfind("=")+1));
            int velY = stoi(line.substr(line.rfind(",")+1));
            R.pos = make_pair(posX, posY);
            R.vel = make_pair(velX, velY);
            b.addRobot(R);
        }
        
        //b.print();
        b.step(100);
        //b.print();
        ans = b.split_and_count();
        //b.print();

        return ans;
    }

    unsigned long long solve_B(string input){
        int ans = 0;

        vector<string> lines = utils::ReadAllLines(input);

        Board b = Board(7,11);
        if(input.find("example") == string::npos){
            b = Board(103,101);
        } 
       
        //parse input
        for(string line : lines){
            Robot R;
            int posX = stoi(line.substr(line.find("=")+1));
            int posY = stoi(line.substr(line.find(",")+1));
            int velX = stoi(line.substr(line.rfind("=")+1));
            int velY = stoi(line.substr(line.rfind(",")+1));
            R.pos = make_pair(posX, posY);
            R.vel = make_pair(velX, velY);
            b.addRobot(R);
        }
        
        //b.print();
        ans = b.easter_egg();
        b.print();

        return ans;
    }

}



int main(int argc, char* argv[]){
    std::string input = INPUT_DAY_14;
    unsigned long long result;
    if (argc >= 3 and std::string(argv[2]) == "example")
    {
        input = INPUT_DAY_14_example;
    }
    
    if (argc >= 2)  
    {
        std::string part = argv[1];
        if (part == "A")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day14::solve_A(input);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            std::cout << "it took: " << duration.count() << "ms" << std::endl;
            std::cout << "answer is -> " << result << std::endl;
            return result;
        }
        else if (part == "B")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day14::solve_B(input);
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