#include "game.h"
#include "input.h"
#include "player.h"
#include "map.h"

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
                //закрепление выбора
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
            // if(stringOfTable > 1){
            //     UpDownMoveCursor('u');
            // }
            map.Move('u');
            SetNeuDir();
            break;

        case 2:
            // if(stringOfTable < 9){
            //     UpDownMoveCursor('d');
            // }
            map.Move('d');
            SetNeuDir();
            break;

        case 3:
            // if(columnOfTable != 1){
            //     LeftRightMoveCursor('l');
            // }
            map.Move('l');
            SetNeuDir();
            break;

        case 4:
            // if(columnOfTable != 3){
            //     LeftRightMoveCursor('r');
            // }
            map.Move('r');
            SetNeuDir();
            break;

        case 5:
            if(!SetPlayerSymbol()) break;
            CheckWinnner(player->Symbol());
            SwitchPlayerSymbol();
            SetNeuDir();
            break;

        default:
            SetNeuDir();
    }
}

bool Game::SetPlayerSymbol(){
    if(curSymbol == " "){
        *location = player->Symbol();
        curSymbol = player->Symbol();
        //вынести номер позиции в отдельную функцию
        player->AddPosition(columnOfTable + stringOfTable - stringOfTable/4 - 1);
        return true;
    }
    return false;
}

void Game::SwitchPlayerSymbol(){
    if(playerNumber)
        player = &player2;
    else
        player = &player1;
    playerNumber = (playerNumber + 1) % 2;
}


void Game::StartPosition(){
    //stringOfTable = 1;
    playerNumber = 1;

    //columnOfTable = 1;
    //OnBeginningLine();
    //SetCursor();
}


Game::Game():gameOver(false), countO(0), countX(0), player1(X), player2(O){
    player = &player1;
    StartGame();
}

// void Game::StartGame(){
//     PrintTable();
//     StartPosition();
//     while(!gameOver){
//         int r = std::system("clear");
//         std::cout << "Now is " << player->Symbol() << "'s step!\n";
//         EnterMove();
//         Move();
//         PrintTable();
//         if(winGame){
//             std::cout << curSymbol << " is win!\n";
//             std::cout << "Want to replay? [y/n] ";
//             std::cin >> choice;
//             if(choice[0] == 'n' || choice[0] == 'N')
//                 gameOver = true;
//             else 
//                 RestartGame();
//         }
//         usleep(7700);
//     }
//     std::cout << "EXIT\n";
// }

void Game::StartGame(){
    map.PrintTable();
    playerNumber = 1;
    while(!gameOver){
        int r = std::system("clear");
        EnterMove();
        Move();
        map.PrintTable();
        usleep(7700);
    }
}

void Game::RestartGame(){
    player1.ClearAll();
    player2.ClearAll();
    player = &player1;
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
        if(win) return win;
    }
    return win;
}

void Game::CheckWinnner(std::string symbol){
    if(player->Count() > 2){
        winGame = Win(player->Positions());
    }
}
