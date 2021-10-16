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
    int playerNum, playAiNum;
    int winLine = 3, line; 
    int winlineNum;
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
    // int fc = 0;
    Player player1, player2, *player;
    Player aiplay1, aiplay2, *aiplay;
    std::vector<std::vector<int>> winStrategy{
        {1, 2, 3},
        {1, 4, 7},
        {1, 5, 9},
        {2, 5, 8},
        {3, 6, 9},
        {3, 5, 7},
        {4, 5, 6},
        {7, 8, 9}
    };
    void SwitchPlayerSymbol();
    void SetNeuDir();
    void Move();
    void EnterMove();
    void StartGame();
    void RestartGame();
    void WinText();
    void Replay();
    void WhoPlayText();
    void HowToPlayText();
    void FinalWinText();
    int SearchWinline(Player* player);
    int CheckWinline(Player* player);
    void AIGame();
    void AIMove(Player& ai, Player& human);
    std::pair<std::pair<int, int>, int> MiniMax(int indx, int f, std::vector<int> free, Player play, Player human, Player ai);
    public:
    Game();
    
};