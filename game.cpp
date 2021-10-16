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
    player1.AddPosition(5);
    // player1.AddPosition(4);
    player2.AddPosition(6);

    // player1.AddPosition(3);
    // player2.AddPosition(9);
    // player2.AddPosition(8);

    // player2.AddPosition(9);

    // AIMove(player1, player2);
    // std::cout << "-----------------------------------------------------------------------------------------\n";
    AIMove(player2, player1);
    // AIMove(player1, player2);
    // AIMove(player1, player2);
    // AIMove(player2, player1);


}

void Game::AIMove(Player& ai, Player& human){
    bool end = false;
    int k = 1;
    int fc = 0;
    int step = MiniMax(*map.FreePlaces().begin(), fc, map.FreePlaces(), ai, human, ai).first.second;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(k != step){
                k++;
                continue;
            }
            *map.iters[i][j] = ai.Symbol();
            ai.AddPosition(step);
            end = true;
            break;
        }
        if(end) break;
    }
    fc = 0;
    std::cout << std::endl;
    std::cout << "-----------------------------------------\n";
    std::cout << std::endl;

    map.DeletePlace(step);
    map.PrintTable();
}



int Game::SearchWinline(Player* play){
    bool win;
    for(int i = 0; i < winStrategy.size(); i++){
        win = true;
        std::vector<int>::iterator it;
        for(int j = 0; j < winLine; j++){
            it = std::find(play->Positions()->begin(), play->Positions()->end(), winStrategy[i][j]);
            if(it == play->Positions()->end()){
                win = false;
            }
        }
        if(win) return i + 1;
    }
    return 0;
}


int Game::CheckWinline(Player* player){
    int winline = 0;
    if(player->Count() > 2){ 
        winline = SearchWinline(player);
    }
    return winline;
}

std::pair<std::pair<int, int>, int> Game::MiniMax(int indx, int f, std::vector<int> free, Player play, Player human, Player ai){
    if(CheckWinline(&ai)){
        return std::make_pair(std::make_pair(10, indx), f);
    }
    else if(CheckWinline(&human)){
        return std::make_pair(std::make_pair(-10, indx), f);
    }
    else if(free.empty()){
        return std::make_pair(std::make_pair(0, indx), f);
    }

    // if(f > 4){
    //     return std::make_pair(std::make_pair(0, indx), f);
    // }
    f++;

    std::vector<std::pair<std::pair<int, int>, int>> moves; //((score, id), f)
    std::vector<int>::iterator it;
    int id;
    std::pair<std::pair<int, int>, int> cur;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            it = std::find(free.begin(), free.end(), i*3 + j+1);
            if(it != free.end()){
                id = *it;
                free.erase(it);
                if(play.Symbol() == ai.Symbol()){
                    ai.AddPosition(id);    
                    cur = MiniMax(id, f, free, human, human, ai);
                    ai.DeletePosition(id);
                }
                else{
                    human.AddPosition(id);
                    cur = MiniMax(id, f, free, ai, human, ai);
                    human.DeletePosition(id);
                }
                moves.push_back(std::make_pair(std::make_pair(cur.first.first, id), cur.second));
                free.push_back(id);
            }
        }
    }
    std::cout << "MOVE " << play.Symbol() << std::endl;
    // for(auto it: moves){
    //     std::cout << it.first.first << " " << it.first.second << " " << it.second << std::endl;
    // }
    int bestscore, beststep, bestf = 100000;
    if(play.Symbol() == ai.Symbol()){
        bestscore = -100;
        for(int i = 0; i < moves.size(); i++){
            if((moves[i].first.first > bestscore) || ((moves[i].first.first == bestscore) && (moves[i].second < bestf))){
                beststep = i;
                bestscore = moves[i].first.first;
                bestf = moves[i].second;
            }
        }
    }
    else{
        bestscore = 100;
        for(int i = 0; i < moves.size(); i++){
            if((moves[i].first.first < bestscore )|| ((moves[i].first.first == bestscore) && (moves[i].second < bestf))){
                beststep = i;
                bestscore = moves[i].first.first;
                bestf = moves[i].second;
            }
        }
    }
    std::cout << "BESTSCORE " << bestscore << " BESTSTEP " << moves[beststep].first.second <<" BESTF " << bestf << " NOWF " << f<< std::endl;
    return moves[beststep];
}

