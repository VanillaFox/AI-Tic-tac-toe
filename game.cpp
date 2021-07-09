#include "game.h"
#include "input.h"
#include <algorithm>

void Game::PrintTable(){
    for(int i = 0; i < table.size(); i++){
        for(std::vector<std::string>::iterator it = table[i].begin(); it != table[i].end(); it++){
            std::cout << (*it);
        }
    }
}

void Game::BackSymbol(){
    *location = curSymbol;
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
            default:
                dir = NEUTRAL;
                break;
        }
    }
}

void Game::SetCursor(){
    curSymbol = *location;
    *location = cursor;
}

void Game::UpDownMove(char a){
    if(a == 'd')
        stringOfTable += 4;
    else
        stringOfTable -= 4;
}

void Game::OnBeginningLine(){
    location = table[stringOfTable].begin();
    location++;
}

void Game::MoveToRightColomn(){
    int count = 1;
    while(count != columnOfTable){
        location++;
        location++;
        count++;
    }
}

void Game::UpDownMoveCursor(char a){
    BackSymbol();
    UpDownMove(a);
    OnBeginningLine();
    MoveToRightColomn();
    SetCursor();
}

void Game::LeftRightMove(char a){
    if(a == 'l'){
        location--;
        location--;
        columnOfTable--;
    }
    else{
        location++;
        location++;
        columnOfTable++;
    }
}

void Game::LeftRightMoveCursor(char a){
    BackSymbol();
    LeftRightMove(a);
    SetCursor();
}

void Game::SetNeuDir(){
    dir = NEUTRAL;
}

void Game::Move(){
    std::cout << std::endl;
    switch(dir){
        case 0:
            break;

        case 1:
            if(stringOfTable > 1){
                UpDownMoveCursor('u');
            }
            SetNeuDir();
            break;

        case 2:
            if(stringOfTable < 9){
                UpDownMoveCursor('d');
            }
            SetNeuDir();
            break;

        case 3:
            if(columnOfTable != 1){
                LeftRightMoveCursor('l');
            }
            SetNeuDir();
            break;

        case 4:
            if(columnOfTable != 3){
                LeftRightMoveCursor('r');
            }
            SetNeuDir();
            break;

        case 5:
            //закрепление выбора
            SetPlayerSymbol();
            SwitchPlayerSymbol();
            CheckWinnner(curSymbol);
            SetNeuDir();
            break;

        default:
            SetNeuDir();
    }
}

void Game::SetPlayerSymbol(){
    *location = playingSymbol;
    curSymbol = playingSymbol;
}

void Game::SwitchPlayerSymbol(){
    if(player){
        playingSymbol = O;
        countX++;
        positionX.push_back(columnOfTable + stringOfTable - stringOfTable/4 - 1);
    }
    else{
        playingSymbol = X;
        countO++;
        positionO.push_back(columnOfTable + stringOfTable - stringOfTable/4 - 1);
    }
    player = (player + 1) % 2;
}


void Game::StartPosition(){
    stringOfTable = 1;
    player = 1;
    playingSymbol = X;
    columnOfTable = 1;
    OnBeginningLine();
    SetCursor();
}

void Game::SwichPlayer(){}

Game::Game():gameOver(false), countO(0), countX(0){
    StartGame();
}

void Game::StartGame(){
    PrintTable();
    StartPosition();
    while(!gameOver){
        int r = std::system("clear");
        EnterMove();
        Move();
        PrintTable();
        usleep(7700);
    }
    std::cout << "EXIT\n";
}

bool Game::Win(std::vector<int> positions){
    bool win;
    for(int i = 0; i < winStrategy.size(); i++){
        win = true;
        std::vector<int>::iterator it;
        for(int j = 0; j < winLine; j++){
            it = std::find(positions.begin(), positions.end(), winStrategy[i][j]);
            if(it == positions.end()) win = false;
        }
        if(win){
            return win;
        }
    }
    return win;
}

void Game::CheckWinnner(std::string symbol){
    bool check = false, win;
    if((symbol == X && countX > 2) || (symbol == O && countO > 2)){
        if(symbol == X) win = Win(positionX);
        else win = Win(positionO);
        gameOver = win;
        
    }
}

// void Game::