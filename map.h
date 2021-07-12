#pragma once
#include <iostream>
#include <vector>
#include "player.h"

class Map{
    std::vector<std::vector<std::string>> table;
    std::vector<std::vector<std::string>> startTable = {
        {" ", " ", " ", " ", " ", " ", " | ", " ", " ", " ", " ", " ", " | ", " ", " ", " ", " ", " ", " \n"},
        {" ", " ", " ", " ", " ", " ", " | ", " ", " ", " ", " ", " ", " | ", " ", " ", " ", " ", " ", " \n"},
        {" ", " ", " ", " ", " ", " ", " | ", " ", " ", " ", " ", " ", " | ", " ", " ", " ", " ", " ", " \n"},
        {"-----------------------\n"},
        {" ", " ", " ", " ", " ", " ", " | ", " ", " ", " ", " ", " ", " | ", " ", " ", " ", " ", " ", " \n"},
        {" ", " ", " ", " ", " ", " ", " | ", " ", " ", " ", " ", " ", " | ", " ", " ", " ", " ", " ", " \n"},
        {" ", " ", " ", " ", " ", " ", " | ", " ", " ", " ", " ", " ", " | ", " ", " ", " ", " ", " ", " \n"},
        {"-----------------------\n"},
        {" ", " ", " ", " ", " ", " ", " | ", " ", " ", " ", " ", " ", " | ", " ", " ", " ", " ", " ", " \n"},
        {" ", " ", " ", " ", " ", " ", " | ", " ", " ", " ", " ", " ", " | ", " ", " ", " ", " ", " ", " \n"},
        {" ", " ", " ", " ", " ", " ", " | ", " ", " ", " ", " ", " ", " | ", " ", " ", " ", " ", " ", " \n"}
    };

    std::vector<std::string>::iterator iter;
    int strNumber, colNumber;
    const int startStr = 1, startCol = 3;
    const int intervBetwStrs = 4, intervBetwCols = 6;
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
    void SetSym(Player* a);
    void SetCursor();
    void SetSymbol();
    void Choice();
    void MoveToNextCol();
    void MoveToPrevCol();
    void PrintVerticalLine(int a);
    void PrintHorizontalLine(int a);
    void PrintLeftLine(int a);
    void PrintRightLine(int a);
    int Position();

    public:
    Map();
    void Move(char a);
    void PrintTable();
    bool SetPlayerSym(Player* a);
    void RestartMap();
    void PrintWinLine(int a);

};