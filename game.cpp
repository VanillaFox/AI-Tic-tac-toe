#include "game.h"
#include "input.h"
#include "player.h"
#include "map.h"

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
            default:
                dir = NEUTRAL;
                break;
        }
    }
}

void Game::SetNeuDir(){
    dir = NEUTRAL;
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
            if(CheckWinnner()) break;
            SwitchPlayerSymbol();
            SetNeuDir();
            break;

        default:
            SetNeuDir();
    }
}

void Game::SwitchPlayerSymbol(){
    if(playerNumber)
        player = &player2;
    else
        player = &player1;
    playerNumber = (playerNumber + 1) % 2;
}

Game::Game():gameOver(false), playerNumber(1), player1(X), player2(O){
    player = &player1;
    StartGame();
}

void Game::StartGame(){
    map.PrintTable();
    while(!gameOver){
        int r = std::system("clear");
        std::cout << "Now is " << player->Symbol() << "'s step!\n";
        EnterMove();
        Move();
        map.PrintTable();
        usleep(7700);
        if(winGame){
            std::cout << player->Symbol() << " is win!\n" << "Want to replay? [y/n] ";
            std::cin >> choice;
            if(choice == "N" || choice == "n") gameOver = true;
            else RestartGame();
        }
    }
    std::cout << "EXIT!\n";
}

void Game::RestartGame(){
    player1.ClearAll();
    player2.ClearAll();
    player = &player1;
    winGame = false;
    map.RestartMap();
}


int Game::Win(){
    bool win;
    for(int i = 0; i < winStrategy.size(); i++){
        win = true;
        std::vector<int>::iterator it;
        for(int j = 0; j < winLine; j++){
            it = std::find(player->Positions()->begin(), player->Positions()->end(), winStrategy[i][j]);
            if(it == player->Positions()->end()) win = false;
        }
        if(win){    
            return i + 1;
        }
    }
    return false;
}

bool Game::CheckWinnner(){
    if(player->Count() > 2) winGame = Win();
    return winGame;
}
