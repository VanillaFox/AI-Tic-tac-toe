#pragma once
#include <iostream>
#include <vector>
#include "player.h"

class Map{
    std::vector<std::vector<std::string>> table;
    std::vector<std::string>::iterator iter;
    int strNumber, colNumber;
    const int startStr = 1, startCol = 1;
    const int intervBetwStrs = 4, intervBetwCols = 1;
    std::string curSymbol, cursor = "@", playerSym;
    void MoveLeft();
    void Left();
    void MoveRight();
    void Right();
    void MoveUp();
    void Up();
    void MoveDown();
    void Down();
    void NewLine();
    void MoveToColomn();
    void SetSym(Player a);
    void SetCursor();
    void SetSymbol();
    void Choice();
    int Position();

    public:
    Map();
    void Move(char a);
    void PrintTable();
};