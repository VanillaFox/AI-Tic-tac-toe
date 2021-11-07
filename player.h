#pragma once
#include <iostream>
#include <vector>

class Player{
    std::string symbol;
    int countOfElems, score;

    public:
    std::vector<int> positions;

    void IncreaseScore();
    std::string Symbol();
    std::vector<int>* Positions();
    std::vector<int> Pos();
    int Count();
    int Score();
    void AddPosition(int a);
    Player(std::string a);
    Player();
    void ClearAll();
    void DeletePosition(int a);
    void SetSym(std::string a);
};