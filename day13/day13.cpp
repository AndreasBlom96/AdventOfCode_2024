#include <string>
#include "../common/utils.h"
#include <iostream>
#include <chrono>
#include "day13.h"

class machine{
    public:
    std::pair<int,int> button_a;
    std::pair<int,int> button_b;
    std::pair<unsigned long long, unsigned long long> prize;

    machine(std::pair<int,int> a, std::pair<int,int> b, std::pair<unsigned long long, unsigned long long> prize) 
    : button_a(a), button_b(b), prize(prize){}

    unsigned long long getCost(unsigned long long numA, unsigned long long numB) const {
        return 3*numA + numB;
    }

    bool checkPrize(unsigned long long numA, unsigned long long numB) const {
        return (numA * button_a.first + numB * button_b.first == prize.first) && 
        (numA * button_a.second + numB * button_b.second == prize.second);
    }

    std::pair<long long ,bool> find_solution(){
        //four crucial test. it seems like it doesnt matter which test i do? i get same answer every time?
        auto [first, second] = helper_solution(button_a.first, button_b.first, prize.first, true);
        int costA = getCost(first, second);
        /*
        auto [a, b] = helper_solution(button_b.first, button_a.first, prize.first, false);
        int costB = getCost(a, b);
        auto [firstB, secondB] = helper_solution(button_a.second, button_b.second, prize.second, true);
        int costC = getCost(firstB, secondB);
        auto [aB, bB] = helper_solution(button_b.second, button_a.second, prize.second, false);
        int costD = getCost(aB, bB);
        */
       
        if(first == -1) return std::make_pair(-1, false);
        return std::make_pair(costA,true);
    }

    std::pair<long long, long long> helper_solution(int first, int second, unsigned long long prize, bool A_is_first){
        unsigned long long start = prize % first;
        long long first_multiplier = prize / first;
        if(first_multiplier > 100){
            first_multiplier = 100;
            start = prize - first_multiplier * first;
        }
        while(first_multiplier >= 0){
            if(start % second == 0){
                // found matching, I DONT KNOW WHAT IS A AND B???
                unsigned long long second_multiplier = start / second;
                if(A_is_first){
                    if(checkPrize(first_multiplier, second_multiplier))
                    {
                        return std::make_pair(first_multiplier, second_multiplier);
                    }  
                } else {
                    if (checkPrize(second_multiplier, first_multiplier))
                    {
                        return std::make_pair(second_multiplier, first_multiplier);
                    }
                    
                }
                
            }
            start += first;
            first_multiplier--;
        }
        return std::make_pair(-1,-1);
    }
  
    std::pair<long long, long long> solve_diophantine(){
        long long a1,a2,b1,b2,p1,p2, LCM;
        a1 = button_a.first;
        a2 = button_a.second;
        b1 = button_b.first;
        b2 = button_b.second;
        p1 = prize.first;
        p2 = prize.second;
        LCM = a1 * a2;

        long long new_b1 = a2 * b1;
        long long new_b2 = a1 * b2;
        long long new_p1 = a2 * p1;
        long long new_p2 = a1 * p2;

        new_b2 -= new_b1;
        new_p2 -= new_p1;

        bool ok =  true;
        if(new_p2 % new_b2 != 0){
            //std::cout << "Integer solution doesnt exist!" << std::endl;
            ok = false;
            return std::make_pair(-1,-1);
        } 

        new_p2 /= new_b2;
        new_b2 = 1;
         
        new_p1 -= (new_p2 * new_b1);
        if(new_p1 % LCM != 0){
            //std::cout << "Integer solution doesnt exist!" << std::endl;
            ok = false;
            return std::make_pair(-1,-1);
        }
        new_p1 /= LCM;
        
        if(!checkPrize(new_p1, new_p2)) std::cout << "something weird happend here!" << std::endl;
        return std::make_pair(new_p1, new_p2);
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
                //cout << "found solution: price -> " << result.first << endl;
                ans += result.first; 
            }
        }
        return ans;
    }

    unsigned long long solve_B(string input){
        unsigned long long ans = 0;
        vector<string> lines = utils::ReadAllLines(input);

        pair<int,int> A;
        pair<int,int> B;
        pair<unsigned long long, unsigned long long> p;
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
                p.first = stoull(line.substr(line.find("=") +1));
                p.second = stoull(line.substr(line.rfind("=") +1));
                p.first += 10000000000000;
                p.second += 10000000000000;
                machine m = machine(A,B,p);
                machines.push_back(m);
            }
        }

        //pair<int,bool> result;
        for(machine m : machines){
            auto result = m.solve_diophantine();
            if(result.first != -1){
                //cout << "found solution: -> " << result.first << ", " << result.second << endl;
                ans += m.getCost(result.first, result.second); 
            }
        }
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