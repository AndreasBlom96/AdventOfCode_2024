#include "helperClass.h"
#include <vector>
#include <iostream>


Board::Board(int rows, int columns): rows(rows), columns(columns), grid(rows * columns, 0){};

int Board::getPoint(int r, int c){
    if(r < rows and r >= 0 and c >= 0 and c < columns) return grid[r*columns + c];
    std::cout << "trying to access data outside of grid!" << std::endl;
    return -1;
}

int Board::setPoint(int r, int c, int value){
    if(r < rows and r >= 0 and c >= 0 and c < columns){
        grid[r*columns + c] = value;
        return 1;
    } 
    return -1; 
}

bool Board::addRobot(Robot R){
    int r = R.pos.second;
    int c = R.pos.first;
    if(r < rows and r >= 0 and c < columns and c >= 0){
        robots.push_back(R);
        grid[r * columns + c] += 1;
        return true;
    } 
    return false;
}

void Board::step(int times){
        for(int i = 0; i<robots.size(); i++){
            int r = robots[i].pos.second;
            int c = robots[i].pos.first;
            setPoint(r,c, getPoint(r,c)-1);
            int new_r = (rows + (r + robots[i].vel.second * times) % rows) % rows;
            int new_c = (columns + (c + robots[i].vel.first * times) % columns) % columns;
            setPoint(new_r, new_c, getPoint(new_r,new_c)+1);
            robots[i].pos.first = new_c;
            robots[i].pos.second = new_r;
        }
}

void Board::print(){
    for(int i=0; i<grid.size(); i++){
        if(i % columns == 0) std::cout << std::endl;
        if(grid[i] == 0){
            std::cout << '.';
        } else if(grid[i] == -1) {
            std::cout << " ";
        } else {
            std::cout << grid[i];
        }
    }
    std::cout << "\n" << std::endl;
}

unsigned long long Board::split_and_count(){
    unsigned long long result = 0;
    long long q1 = 0;
    long long q2 = 0;
    long long q3 = 0;
    long long q4 = 0;
    //split
    int split_c = (columns/2);
    int split_r = (rows/2);

    for(int r = 0; r<rows;r++){
        for(int c=0; c<columns; c++){
            if(r==split_r){
                setPoint(r,c, -1);
            } else if (c==split_c)
            {
                setPoint(r,c,-1);
            }

            if(r < split_r and c < split_c) q1 += getPoint(r,c);
            if(r < split_r and c > split_c) q2 += getPoint(r,c);
            if(r > split_r and c < split_c) q3 += getPoint(r,c);
            if(r > split_r and c > split_c) q4 += getPoint(r,c);
        }
    }
    return q1*q2*q3*q4;
}

long long Board::easter_egg(){
    std::vector<int> numX;
    std::vector<int> numY;
    int limit = 20;
    long long count = 0;
    bool foundX = false;
    bool foundY = false;
    while(!(foundX && foundY)){
        
        foundX = false;
        foundY = false;
        numX = std::vector<int>(columns, 0);
        numY = std::vector<int>(rows, 0);
        step(1);
        count++;

        for(Robot R : robots){
            ++numX[R.pos.first];
            ++numY[R.pos.second];
        }
        for(int i : numX){
            if(i >= limit){
                foundX = true;
            }
        }
        for(int i : numY){
            if(i >= limit){
                foundY = true;
            }
        }
        if(count >= 20000) break;
    }
    return count;
}