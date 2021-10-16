#include "game.h"
#include "input.h"
#include "player.h"
#include "map.h"


Game::Game():gameOver(false), playerNum(1),
            player1(X), player2(O), winlineNum(0){
    player = &player1;
    // StartGame();
    AIGame();
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


int Game::SearchWinline(Player* player){
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
    std::cout << "CHECK\n";
    std::cout << player->Count() << std::endl;
    if(player->Count() > 2) winlineNum = SearchWinline(player);
    std::cout << "WINLINE " << winlineNum << std::endl;
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

void Game::AIGame(){
    map.PrintTable();
    player1.AddPosition(1);
    // player1.AddPosition(7);
    player1.AddPosition(5);
    // player2.AddPosition(2);
    player2.AddPosition(6);
    // player2.AddPosition(9);
    AIMove(&player2);
    AIMove(&player1);
    AIMove(&player2);
}

void Game::AIMove(Player* play){
    bool end = false;
    int k = 1;
    fc = 0;
    int step = MiniMax(*map.FreePlaces().begin(), fc, map.iters, map.FreePlaces(), *play, player1, player2).second;
    std::cout << "Step " << step << std::endl;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(k != step){
                    std::cout << k << std::endl; 
                    std::cout << k << std::endl; 
                    k++;
                    continue;
                }
                std::cout << "HERE2\n";
                *map.iters[i][j] = play->Symbol();
                for(auto it: play->positions){
                    std::cout << it << " ";
                }
                std::cout << std::endl;
                play->AddPosition(step);
                for(auto it: play->positions){
                    std::cout << it << " ";
                }
                end = true;
                break;
            }
            if(end) break;
        }
    fc = 0;
    map.DeletePlace(step);
    map.PrintTable();
}


//добвить выбор наилучшего хода за наименьшее кол-во ходов
//что-то не так с добавлением ...
// 85 IDX 2
// 86 COUNT 9 O
// 6 3 4 7 2 8 2 2 2

std::pair<int, int> Game::MiniMax(int indx, int f, std::vector<std::vector<vecString::iterator>> iterat, std::vector<int> free, Player play, Player human, Player ai){
    fc++;
    if(fc > 100){
        return std::make_pair(0, indx);
    }

    std::cout << fc << " COUNT " << play.Count() << " " << play.Symbol() << std::endl;
    std::vector<int> pos = play.Pos();
    for(int p = 0; p < play.Count(); p++){
        std::cout << pos[p] << " "; 
    }
    std::cout << std::endl;

    std::vector<std::pair<int, int>> moves;
    // std::vector<std::pair<std::pair<int, int>, int>> moves;
    if(CheckWinline(&play)){
        if(play.Symbol() == ai.Symbol()){
            return std::make_pair(-10, indx);
        }
        else{
            return std::make_pair(10, indx);
        }
    }
    if(free.empty()){
        return std::make_pair(0, indx);
    }
    int l;
    std::vector<int>::iterator it;
    int result, idx;
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            it = std::find(free.begin(), free.end(), i*3 + j+1);
            if(it != free.end()){
                *iterat[i][j] = "*";
                idx = *it;
                std::cout << fc << " IDX " << idx << std::endl;
                free.erase(it);
                if(play.Symbol() == ai.Symbol()){
                    human.AddPosition(idx);
                    l = MiniMax(idx, f, iterat, free, human, human, ai).first;
                    // std::cout << "ADDhuman " << l << " " << idx << "|" << std::endl;
                    moves.push_back(std::make_pair(l, idx));
                    human.DeletePosition(idx);
                }else{
                    ai.AddPosition(idx);
                    l = MiniMax(idx, f, iterat, free, ai, human, ai).first;
                    // std::cout << "ADD " << l << " " << idx << "|\n";
                    moves.push_back(std::make_pair(l, idx));
                    ai.DeletePosition(idx);
                    // moves.push_back(std::make_pair(MiniMax(idx, iterat, free, ai, human, ai).first, idx));
                }
            }
            free.push_back(idx);
        }
    }
    std::cout << moves.size() << std::endl;
    int beststep = 0, bestscore;
    std::cout << "MOVES\n";
    for(auto it: moves){
        std::cout << it.first << " " << it.second << std::endl;
    }
    if(play.Symbol() == ai.Symbol()){
        std::cout << "AI\n";
        bestscore = -1000;
        for(int i = 0; i < moves.size(); i++){
            if(moves[i].first > bestscore){
                beststep = moves[i].second;
                bestscore = moves[i].first;
            }
        }
    }
    else{
        std::cout << "HUMAN\n";
        bestscore = 1000;
        for(int i = 0; i < moves.size(); i++){
            if(moves[i].first < bestscore){
                beststep = moves[i].second;
                bestscore = moves[i].first;
            }
        }
    }
    std::cout << "BestScore " << bestscore << " beststep " << beststep << std::endl;
    return std::make_pair(bestscore, beststep);
}