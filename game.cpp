#include "game.h"
#include "input.h"
#include "player.h"
#include "map.h"


Game::Game():gameOver(false), playerNum(1),
            player1(X), player2(O), winlineNum(0){
    player = &player1;
    StartGame();
}


void Game::StartGame(){
    while(!gameOver){
        int r = std::system("clear");
        WhoPlayText();
        EnterMove();
        Move();
        map.PrintTable();
        usleep(7700);
        if(winlineNum){
            if(winlineNum != 9) player->IncreaseScore();
            WinText();
            Replay();
        }
    }
    FinalWinText();
    // map.PrintFreePlaces();
    std::cout << "EXIT!\n";
}


void Game::EnterMove(){
    if(kbhit()){
        switch (getch()){
            case 'a':
                dir = LEFT;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 'q':
                gameOver = true;
                break;
            case 'e':
                dir = ENTER;
                break;
            case 'r':
                dir = RESTART;
                break;
            case 'h':
                dir = HELP;
                break;
            default:
                dir = NEUTRAL;
                break;
        }
    }
}


void Game::Move(){
    switch(dir){
        case 0:
            break;

        case 1:
            map.Move('u');
            SetNeuDir();
            break;

        case 2:
            map.Move('d');
            SetNeuDir();
            break;

        case 3:
            map.Move('l');
            SetNeuDir();
            break;

        case 4:
            map.Move('r');
            SetNeuDir();
            break;

        case 5:
            if(!map.SetPlayerSym(player)) break;
            line = CheckWinline(player);
            if(line){
                map.PrintWinLine(line);
                break;
            }
            if(map.FullMap()){
                winlineNum = 9;
                break;
            }
            SwitchPlayerSymbol();
            SetNeuDir();
            break;

        case 6:
            RestartGame();
            SetNeuDir();
            break;
        
        case 7:
            HowToPlayText();
            break;

        default:
            SetNeuDir();
            break;
    }
}


void Game::SetNeuDir(){
    dir = NEUTRAL;
}


void Game::SwitchPlayerSymbol(){
    if(playerNum)
        player = &player2;
    else
        player = &player1;
    playerNum = (playerNum + 1) % 2;
}


int Game::SearchWinline(){
    bool win;
    for(int i = 0; i < winStrategy.size(); i++){
        win = true;
        std::vector<int>::iterator it;
        for(int j = 0; j < winLine; j++){
            it = std::find(player->Positions()->begin(), player->Positions()->end(), winStrategy[i][j]);
            if(it == player->Positions()->end()) win = false;
        }
        if(win) return i + 1;
    }
    return 0;
}


int Game::CheckWinline(Player* player){
    if(player->Count() > 2) winlineNum = SearchWinline();
    return winlineNum;
}


void Game::Replay(){
    std::cin >> choice;
    if(choice == "N" || choice == "n") gameOver = true;
    else RestartGame();
}


void Game::RestartGame(){
    player1.ClearAll();
    player2.ClearAll();
    player = &player1;
    playerNum = 1;
    winlineNum = 0;
    map.RestartMap();
}


void Game::HowToPlayText(){
    int r = std::system("clear");
    std::cout << "Use WASD to move;\n";
    std::cout << "Press \"e\" to fix the selection;\n";
    std::cout << "Press \"r\" to restart the game;\n";
    std::cout << "Press \"q\" to exit.\n";
    std::cout << std::endl;
    std::cout << "Press any key to return to the game\n> ";
    std::cin >> choice;
}

void Game::WhoPlayText(){
    std::cout << "Press \"h\" to get help.\n";
    std::cout << std::endl;
    std::cout << "Now is " << player->Symbol() << "'s step!\n";
}


void Game::WinText(){
    if(winlineNum == 9) std::cout << "Draw!\n";
    else std::cout << player->Symbol() << " is won!\n";
    std::cout << "Current score:\n PlayerX: " << player1.Score() << "\n PlayerO: " << player2.Score();
    std::cout << "\nWant to replay? [y/n] ";
}


void Game::FinalWinText(){
    std::cout << std::endl;
    if(player1.Score() == player2.Score()){
        std::cout << "Draw!\n";
        return;
    }
    if(player1.Score() > player2.Score()) player = &player1;
    else player = &player2;
    std::cout << player->Symbol() << " is won!\n";
}


// int Game::MiniMax(std::string winsym, std::vector<int> empidx, std::vector<std::vector<std::vector<std::string>::iterator>> iters){
//     // std::vector<std::vector<std::vector<std::string>::iterator>> newiters = map.Iters();

//     // std::vector<int> moves, emptyidxs = map.FreePlaces();

//     if(CheckWinline(aiplay)){
//         if(aiplay->Symbol() == winsym){
//             return 10;
//         }
//         else{
//             return -10;
//         }
//     }

//     // if()




//     return 0;
// }