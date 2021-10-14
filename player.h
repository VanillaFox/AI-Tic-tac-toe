#pragma once
#include <iostream>
#include <vector>

class Player{
    std::string symbol;
    std::vector<int> positions;
    int countOfElems, score;

    public:
    void IncreaseScore();
    std::string Symbol();
    std::vector<int>* Positions();
    int Count();
    int Score();
    void AddPosition(int a);
    Player(std::string a);
    Player();
    void ClearAll();
};