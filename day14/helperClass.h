#pragma once
#include <vector>

class Robot{
    private:

    public:
    std::pair<int,int> pos;
    std::pair<int,int> vel;
};


class Board{
    private:

    public:
    std::vector<int> grid;
    int rows;
    int columns;
    std::vector<Robot> robots;

    Board(int rows, int columns);
    int getPoint(int r, int c);
    int setPoint(int r, int c, int value);
    bool addRobot(Robot R);
    void step(int times);
    void print();
    unsigned long long split_and_cound();
};