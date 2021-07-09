#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
//смена хода

class Game{
    bool game, moveMade, gameOver;
    std::vector<std::string>::iterator location;
    int player, stringOfTable, columnOfTable;
    int countX, countO, winLine = 3;
    std::string curSymbol, playingSymbol;
    std::string X = "X", O = "O", cursor = "@", space = " ";
    enum Dirs{
        NEUTRAL,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ENTER
    };
    Dirs dir;
    std::vector<std::vector<std::string>> table{
        {"       |       |       \n"},
        {"   ", " ", "   |   ", " ", "   |   ", " ", "   \n"},
        {"       |       |       \n"},
        {"-----------------------\n"},
        {"       |       |       \n"},
        {"   ", " ", "   |   ", " ", "   |   ", " ", "   \n"},
        {"       |       |       \n"},
        {"-----------------------\n"},
        {"       |       |       \n"},
        {"   ", " ", "   |   ", " ", "   |   ", " ", "   \n"},
        {"       |       |       \n"}
        };
    std::vector<int> positionX, positionO;
    std::vector<std::vector<int>> winStrategy{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9},
        {1, 5, 9},
        {3, 5, 7}
    };
    
    void PrintTable();
    void SwitchPlayerSymbol();
    void SetPlayerSymbol();
    void BackSymbol();
    void SetCursor();
    void OnBeginningLine();
    void MoveToRightColomn();
    void UpDownMoveCursor(char a);
    void UpDownMove(char a);
    void LeftRightMove(char a);
    void LeftRightMoveCursor(char a);
    void SetNeuDir();
    void SwichPlayer();
    void Move();
    void EnterMove();
    void StartPosition();
    void CheckWinnner(std::string symbol);
    void StartGame();
    bool Win(std::vector<int> positions);
    public:
    Game();
    
};