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
    int winlineNum, gameMode;
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
    Player player1, player2, *curPlayer;
    Player *aiplay, *human;
    Player ai, player;
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
    void AIMove(Player& ai, Player& human);
    void SwitchPlayerSymbol();
    void SetNeuDir();
    void Move();
    void EnterMove();
    void StartGame();
    void RestartGame();
    void WinText();
    void Replay();
    void HelloText();
    void WhoPlayText();
    void HowToPlayText();
    void FinalWinText();
    void WhoAI();
    void WhoForWhomText();
    bool CheckWinline();
    int Start();
    int SearchWinline(Player* player);
    int Winline(Player* player);
    std::pair<std::pair<int, int>, int> MiniMax(int indx, int f, std::vector<int> free, Player play, Player human, Player ai);
    public:
    Game();  
};