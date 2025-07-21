#include <string>
#include "../common/utils.h"
#include <iostream>
#include <chrono>
#include "day13.h"

class machine{
    private:
    std::pair<int,int> button_a;
    std::pair<int,int> button_b;
    std::pair<int,int> prize;

    public:

    machine(std::pair<int,int> a, std::pair<int,int> b, std::pair<int,int> prize) 
    : button_a(a), button_b(b), prize(prize){}

    unsigned long long getCost(int numA, int numB) const {
        return 3*numA + numB;
    }

    bool checkPrize(int numA, int numB) const {
        return (numA * button_a.first + numB * button_b.first == prize.first) && 
        (numA * button_a.second + numB * button_b.second == prize.second);
    }

    std::string getStarter(){
        std::string result;
        if(prize.first > prize.second){
            result = "f";
        } else {
            result = "s";
        }

        if(result == "f"){
            if(button_a.first > 3*button_b.first){
                result += "a";
            } else {
                result += "b";
            }
        } else if (result == "s")
        {
            if(button_a.second > 3*button_b.second){
                result += "a";
            } else {
                result += "b";
            }
        }
        return result;
    }

    std::pair<int,bool> find_solution(){
        std::string starter = getStarter();
        unsigned long long xA;
        unsigned long long helper;
        unsigned long long tempPrize;
        if(starter[0] == 'f'){
            tempPrize = prize.first;
            if(starter[1] == 'a'){
                xA = button_a.first;
                helper = button_b.first;
            } else {
                xA = button_b.first;
                helper = button_a.first;
            }
        } else {
            tempPrize = prize.second;
            if(starter[1] == 'a'){
                xA = button_a.first;
                helper = button_b.first;
            } else {
                xA = button_b.first;
                helper = button_a.first;
            }
        }

        unsigned long long start = tempPrize % xA;
        int xA_multiplier = tempPrize / xA;
        if(xA_multiplier > 100){
            xA_multiplier = 100;
            start = tempPrize - 100*xA;
        }
        bool success = false;
        while(xA_multiplier > 0){
            if(start % helper == 0){
                // found matching, I DONT KNOW WHAT IS A AND B???
                int numA;
                int numB;
                if(starter[1] == 'a'){
                    numA = xA_multiplier;
                    numB = start / helper;
                } else {
                    numA = start / helper;
                    numB = xA_multiplier;
                }
                if(checkPrize(numA,numB))
                {
                    success = true;
                    return std::make_pair(getCost(numA, numB), success);
                } 
            }
            start += xA;
            xA_multiplier--;
        }

        return std::make_pair(-1,success);
    }

};


namespace day13{
    using namespace std;
    unsigned long long solve_A(string input){
        unsigned long long ans = 0;
        vector<string> lines = utils::ReadAllLines(input);


        pair<int,int> A;
        pair<int,int> B;
        pair<int,int> p;
        vector<machine> machines;
        for(string line : lines){
            if(line.find("A:") != string::npos){
                A.first = stoi(line.substr(line.find("+") +1));
                A.second = stoi(line.substr(line.rfind("+") +1));
            } else if (line.find("B:") != string::npos)
            {
                B.first = stoi(line.substr(line.find("+") +1));
                B.second = stoi(line.substr(line.rfind("+") +1));
            } else if (line.find("Prize:") != string::npos)
            {
                p.first = stoi(line.substr(line.find("=") +1));
                p.second = stoi(line.substr(line.rfind("=") +1));
                machine m = machine(A,B,p);
                machines.push_back(m);
            }
        }
        
        pair<int,bool> result;
        for(machine m : machines){
            result = m.find_solution();
            if(result.second){
                cout << "found solution: price -> " << result.first << endl;
                ans += result.first; 
            }
        }
        return ans;
    }

    unsigned long long solve_B(string input){
        unsigned long long ans = 0;

        return ans;
    }

}








int main(int argc, char* argv[]){
    std::string input = INPUT_DAY_13;
    unsigned long long result;
    if (argc >= 3 and std::string(argv[2]) == "example")
    {
        input = INPUT_DAY_13_example;
    }
    
    if (argc >= 2)  
    {
        std::string part = argv[1];
        if (part == "A")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day13::solve_A(input);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            std::cout << "it took: " << duration.count() << "ms" << std::endl;
            std::cout << "answer is -> " << result << std::endl;
            return result;
        }
        else if (part == "B")
        {
            auto start = std::chrono::high_resolution_clock::now();
            result = day13::solve_B(input);
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