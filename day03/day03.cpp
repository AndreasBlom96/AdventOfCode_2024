#include <iostream>
#include <fstream>
#include <string>
#include "../Common/utils.h"

int find_mul(std::string string_to_check);
std::ifstream inFile;
//namespace _2024_day03{

//}

//using namespace _2024_day03;

int solve_part_A(std::string input){
    int answer=0;
    inFile.open(input);
    if (!inFile) {
        std::cout << "Unable to open file datafile.txt" << std::endl;
        return answer;
    }

    std::string temp;
    int index;
    while(getline (inFile, temp)){
        //std::cout << temp << std::endl;
        while (temp.find("mul(",0) != temp.npos)
        {
            //std::cout << temp << std::endl;
            index=temp.find("mul(",0);
            //std::cout << "index -> " << index << std::endl;

            //extracting first number
            char* endptr = nullptr;
            std::string substr =  temp.substr(index+4);
            int first = std::strtol(substr.c_str(), &endptr, 10);
            //std::cout << "First number:" << first << " end char: " << *endptr <<  std::endl;
            if (first > 999 or *endptr != ',')
            {
                temp = substr;
                continue;
            }
            
            //relative index is the length of the number!
            int relative_index = endptr - substr.c_str() + 1;
            substr =  temp.substr(index+4+relative_index);
            //std::cout << "rel_index ->" << relative_index << std::endl;

            //extract second number
            int second = std::strtol(substr.c_str(), &endptr, 10);
            //std::cout << "second number: " << second << " ends with: " << *endptr << std::endl;
            if (second > 999 or *endptr != ')')
            {
                temp = substr;
                continue;
            }
            

            answer += first*second;
            temp = substr;
        }  
    }


    inFile.close();
    return answer;
}


int solve_part_B(std::string input){
    int answer=0;
    inFile.open(input);
    if (!inFile) {
        std::cout << "Unable to open file datafile.txt" << std::endl;
        return answer;
    }

    std::string temp;
    std::string subtemp;
    bool do_ = true;
    int index;
    size_t en_index;
    while(getline (inFile, temp)){
        //std::cout << temp << std::endl;
        bool running = true;
        while(running)
        {
            std::cout << "new substring to process!" << std::endl;
            std::cout << "before: " << temp << std::endl;
            if (do_)
            {
                /* find first don't() */
                en_index = temp.find("don't()");
                if (en_index == std::string::npos) {
                    // No more don't(), do rest of line
                    answer += find_mul(temp);
                    break;
                }   
                subtemp = temp.substr(0,en_index);
                answer += find_mul(subtemp);
                temp.erase(0,en_index + 7);
                std::cout << "after: " << temp << std::endl;
                std::cout << "setting do to false" << std::endl;
                do_ = false;  
            } else {
                //find first do()
                en_index = temp.find("do()");
                if (en_index == std::string::npos) {
                    // No more do(), do rest of line
                    break;
                }
                temp.erase(0,en_index + 4);
                std::cout << "after: " << temp << std::endl;
                std::cout << "setting do to true" << std::endl;
                do_ = true;
            }
         
            std::cout << "finished this subline" << std::endl;
            std::cout << " " << std::endl;
        }
    }
    inFile.close();
    return answer;
}

int find_mul(std::string string_to_check){
    std::cout << "finding mul for: " << string_to_check << std::endl;
    int add = 0;
    int index;
    while (string_to_check.find("mul(") != std::string::npos)
    {
        std::cout << " " << std::endl;
        index=string_to_check.find("mul(",0);
        std::cout << "mul index: " << index << std::endl;

        //extracting first number
        char* endptr = nullptr;
        std::string substr =  string_to_check.substr(index+4);
        int first = std::strtol(substr.c_str(), &endptr, 10);
        //std::cout << "First number:" << first << " end char: " << *endptr <<  std::endl;
        if (first > 999 or *endptr != ',')
        {
            string_to_check[index]='x';
            //string_to_check.erase(index,4);
            std::cout << "illegal first number" << std::endl;
            continue;
        }

        //relative index is the length of the number!
        int relative_index = endptr - substr.c_str() + 1;
        substr =  string_to_check.substr(index+4+relative_index);

        //extract second number
        int second = std::strtol(substr.c_str(), &endptr, 10);
        //std::cout << "second number: " << second << " ends with: " << *endptr << std::endl;
        if (second > 999 or *endptr != ')')
        {
            std::cout << "illegal second number" << std::endl;
            string_to_check[index]='x';
            //string_to_check.erase(index,4);
            continue;
        }

        std::cout << "multiplying " << first << " * " << second << std::endl;
        add += first * second;
        string_to_check[index]='x';
        //string_to_check.erase(index,4);
    }
    std::cout << " " << std::endl;
    return add;
}   

int main(int, char**){
    std::cout << "Starting day 3!\n";
    std::cout << solve_part_A("C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day03.txt")<<std::endl;
    std::cout << solve_part_B("C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day03.txt")<<std::endl;
    std::cout << solve_part_B("C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day03_exampleB.txt")<<std::endl;
}