#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include "player.h"
#include "map.h"

class Game{
    bool  gameOver;
    Map map;
    int playerNumber, winLine = 3, line, winNumber;
    std::string X = "X", O = "O", choice;
    enum Dirs{
        NEUTRAL,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ENTER,
        RESTART,
        HELP
    };
    Dirs dir;
    Player player1, player2, *player;
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
    
    void SwitchPlayerSymbol();
    void SetNeuDir();
    void SwichPlayer();
    void Move();
    void EnterMove();
    void StartGame();
    void RestartGame();
    void WinText();
    void Replay();
    void WhoPlayText();
    void HowToPlayText();
    void FinalWinText();
    int Win();
    int CheckWinnner();

    public:
    Game();
    
};