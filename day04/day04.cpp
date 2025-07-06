#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Common/utils.h"
#include "day04.h"

std::ifstream inFile;
using namespace std;

int solve_A(std::string input){
    int ans = 0;
    vector<std::string> lines;
    lines = utils::ReadAllLines(input);
    for(string line : lines){
        cout << line << endl;
    }
    vector<string> lines_copy = lines;

    cout << "rows: " << lines.size() << endl;
    cout << "columns: " << lines[0].length() << endl;

    //double for loop to loop through all coordinates
    for(int row = 0; row < lines.size() ; row++){
        for(int column = 0; column < lines[row].length(); column++)
        {
            //--------Check XMAS forward-------
            if(lines[row].find("XMAS",column) == column){
                //cout << "found forward XMAS at: " << row << "," << column << endl;
                ans++;
            }
            //-------------done-----------------

            //-----Check XMAS Backwards (SAMX)-------
            if(lines[row].find("SAMX",column) == column){
                //cout << "found Backwards XMAS at: " << row << "," << column << endl;
                ans++;
            }
            //------------done------------------

            //-----Check XMAS Down/Up---------
            // check if there is enough rows down
            if (row+3 < lines.size())
            {
                string temp ="....";
                for (int i = 0; i < 4; i++)
                {
                    temp[i] = lines[row+i][column];
                }
                //cout << "temp: " << temp << ",  at-> " << row << "," << column << endl;
                if (temp == "XMAS" or temp == "SAMX")
                {
                    //cout << "found XMAS Down (or XMAS up): " << row << "," << column << endl;
                    ans++;
                }   
            }
            //------------------------------


            //-----Check XMAS diagonal right ---------
            if (row+3 < lines.size() and column+3 < lines[row].length())
            {
                string temp ="....";
                for (int i = 0; i < 4; i++)
                {
                    temp[i] = lines[row+i][column+i];
                }
                //cout << "temp: " << temp << ",  at-> " << row << "," << column << endl;
                if (temp == "XMAS" or temp == "SAMX")
                {
                    //cout << "found XMAS right down/up: " << row << "," << column << endl;
                    ans++;
                }   
            }
            //----------done--------------------

            //-----Check XMAS diagonal left ---------
            if (row+3 < lines.size() and column-3 >= 0)
            {
                string temp ="....";
                for (int i = 0; i < 4; i++)
                {
                    temp[i] = lines[row+i][column-i];
                }
                //cout << "temp: " << temp << ",  at-> " << row << "," << column << endl;
                if (temp == "XMAS" or temp == "SAMX")
                {
                    //cout << "found XMAS left down/up: " << row << "," << column << endl;
                    ans++;
                }   
            }
            //----------done--------------------
            
        }
        
        //cout << "done with row:" << row << endl;
    }


    return ans;
}

int solve_B(string input){
    int ans = 0;
    vector<std::string> lines;
    lines = utils::ReadAllLines(input);
    for(string line : lines){
        cout << line << endl;
    }
    vector<string> lines_copy = lines;

    cout << "rows: " << lines.size() << endl;
    cout << "columns: " << lines[0].length() << endl;

    bool right_diag = false;
    bool left_diag =false;
    for (int row = 0; row < lines.size(); row++){
        for (int column = 0; column < lines[row].length(); column++){
            if ((row != 0 and row < lines.size()-1) and (column != 0 and column < lines[row].length()-1))
            {
                //find a 'A' then see if MAS is diagonal :) 
                if (lines[row][column] == 'A')
                {
                    //check if M and S are diagonal
                    string temp_u_r = "...";
                    string temp_u_l = "...";
                    for (int i = 0; i < 3; i++)
                    {
                        temp_u_r[i] = lines[row+i-1][column-i+1];
                        temp_u_l[i] = lines[row-1+i][column+i-1];
                    }
                    //cout << "temp: " << temp_u_r << ",  at-> " << row << "," << column << endl;
                    //cout << "temp: " << temp_u_l << ",  at-> " << row << "," << column << endl;
                    if ((temp_u_l == "MAS" or temp_u_l == "SAM") and (temp_u_r == "MAS" or temp_u_r == "SAM"))
                    {
                        //cout << "found MAS " << row << "," << column << endl;
                        ans++;
                    } 
                }
                
            }
        }
    }
    return ans;
}

int main(){
    cout << solve_A("C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day04.txt") << std::endl;
    cout << solve_B("C:\\Users\\anblo\\Documents\\CodingProjects\\AoC_Uni\\inputs\\day04.txt") << endl;
}