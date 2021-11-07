#pragma once
#include "player.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using vecString = std::vector<std::string>;

class Map{
    std::vector<vecString> table;
    std::vector<vecString> startTable = {
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
    std::vector<int> StartFreePlaces = {
        1, 2, 3, 4, 5, 6, 7, 8, 9
    };
    vecString::iterator iter;
    int strNumber, colNumber;
    const int startStr = 0, startCol = 0;
    const int firstCol = 3, firstStr = 1;
    const int intervBetwStrs = 4, intervBetwCols = 6;
    std::string curSymbol, cursor = "@", playerSym;
    void MoveToNextCol();
    void MoveLeft();
    void Left();
    void MoveRight();
    void Right();
    void MoveUp();
    void Up();
    void MoveDown();
    void Down();
    void NewLine();
    void SetSym(Player* a);
    void SetCursor();
    void SetCurSym();
    void SetSymByAI(Player* player, int step);
    void PrintVerticalLine(int a);
    void PrintHorizontalLine(int a);
    void PrintLeftLine();
    void PrintRightLine();
    void FillIters();
    int Position();

    public:
    Map();
    void DeletePlace(int a);
    void RandomPlaces();

    void Move(char a);
    void PrintTable();
    bool SetPlayerSym(Player* a);
    void SetSymbol();
    bool FullMap();
    void RestartMap();
    void PrintWinLine(int a);
    void PrintFreePlaces();
    std::vector<int> Places();
    std::vector<std::vector<vecString::iterator>> Iters();
    std::vector<int> FreePlaces();
    std::vector<std::vector<vecString::iterator>> iters;
    std::vector<int> freePlaces;
};