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
    for(int k = 0; k< times; k++){
        for(int i = 0; i<robots.size(); i++){
            int r = robots[i].pos.second;
            int c = robots[i].pos.first;
            setPoint(r,c, getPoint(r,c)-1);
            int new_r = r + robots[i].vel.second;
            int new_c = c + robots[i].vel.first;
            if(new_r >= rows) new_r = new_r % rows;
            if(new_r < 0) new_r += rows;
            if(new_c >= columns) new_c = new_c % columns;
            if(new_c < 0) new_c += columns;
            setPoint(new_r, new_c, getPoint(new_r,new_c)+1);
            robots[i].pos.first = new_c;
            robots[i].pos.second = new_r;
        }
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