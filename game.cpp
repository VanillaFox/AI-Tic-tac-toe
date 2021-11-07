#include "game.h"
#include "input.h"
#include "player.h"
#include "map.h"

Game::Game():gameOver(false), playerNum(1), player1(X), player2(O), winlineNum(0){
    curPlayer = &player1;
    HelloText();
    if(!gameMode){
        return;
    }
    RestartGame();
    StartGame();
}


void Game::StartGame(){
    while(!gameOver){
        int r = std::system("clear");
        WhoPlayText();
        if(gameMode==2 && curPlayer==aiplay){
            AIMove(*aiplay, *human);
        }
        else{
            EnterMove();
            Move();
        }
        map.PrintTable();
        usleep(7700);
        if(winlineNum){
            if(winlineNum!=9){
                if(gameMode==2){
                    if(curPlayer==aiplay)
                        ai.IncreaseScore();
                    else
                        player.IncreaseScore();
                }
                else
                    curPlayer->IncreaseScore();
            }
            WinText();
            Replay();
        }
    }
    FinalWinText();
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
            if(!map.SetPlayerSym(curPlayer)) break;
            if(CheckWinline()) break;
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


void Game::AIMove(Player& ai, Player& human){
    bool end = false;
    int k = 1;
    int step = MiniMax(*map.FreePlaces().begin(), 0, map.FreePlaces(), ai, human, ai).first.second;
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
    map.DeletePlace(step);
    end = CheckWinline();
}


std::pair<std::pair<int, int>, int> Game::MiniMax(int indx, int f, std::vector<int> free, Player play, Player human, Player ai){
    if(Winline(&ai)){
        return std::make_pair(std::make_pair(10, indx), f);
    }
    else if(Winline(&human)){
        return std::make_pair(std::make_pair(-10, indx), f);
    }
    else if(free.empty()){
        return std::make_pair(std::make_pair(0, indx), f);
    }

    f++;
    // if(f == 3){
    //     return std::make_pair(std::make_pair(0, indx), f);
    // }

    std::vector<std::pair<std::pair<int, int>, int>> moves; //((score, id), f)
    std::vector<int>::iterator it;
    std::vector<int> curfree = free;
    std::pair<std::pair<int, int>, int> cur;

    for(auto vec: free){
        it = std::find(curfree.begin(), curfree.end(), vec);
        curfree.erase(it);
        if(play.Symbol() == ai.Symbol()){
            ai.AddPosition(vec);    
            cur = MiniMax(vec, f, curfree, human, human, ai);    
            ai.DeletePosition(vec);
        }
        else{
            human.AddPosition(vec);
            cur = MiniMax(vec, f, curfree, ai, human, ai);
            human.DeletePosition(vec);
        }
        moves.push_back(cur);
        curfree.push_back(vec);
    }

    int bestscore, beststep, bestf = 100000;
    if(play.Symbol() == ai.Symbol()){
        bestscore = -100;
        for(int i = 0; i < moves.size(); i++){
            if(bestf == f){
                break;
            }
            if(moves[i].first.first>bestscore || 
            (moves[i].first.first==bestscore && moves[i].second<bestf) ||
            (moves[i].first.first==-10 && moves[i].second==f+1)){
                if(bestscore==-10 && bestf==f+1 && !(moves[i].second==f)){
                    continue;
                }
                beststep = moves[i].first.second;
                bestscore = moves[i].first.first;
                bestf = moves[i].second;
            }
        }
    }
    else{
        bestscore = 100;
        for(int i = 0; i < moves.size(); i++){
            if(bestf == f){
                break;
            }
            if(moves[i].first.first<bestscore || 
            (moves[i].first.first==bestscore && moves[i].second<bestf) ||
            (moves[i].first.first==10 && moves[i].second==f+1)){
                if(bestscore==10 && bestf==f+1 && !(moves[i].second==f)){
                    continue;
                }
                beststep = moves[i].first.second;
                bestscore = moves[i].first.first;
                bestf = moves[i].second;
            }
        }
    }
    return std::make_pair(std::make_pair(bestscore, beststep), bestf);
}


bool Game::CheckWinline(){
    line = Winline(curPlayer);
    if(line){
        map.PrintWinLine(line);
        winlineNum = line;
        return true;
    }
    if(map.FullMap()){
        winlineNum = 9;
        return true;
    }
    SwitchPlayerSymbol();
    return false;
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
        if(win) return i+1;
    }
    return 0;
}


int Game::Winline(Player* player){
    int winline = 0;
    if(player->Count() > 2){ 
        winline = SearchWinline(player);
    }
    return winline;
}


void Game::SwitchPlayerSymbol(){
    if(playerNum)
        curPlayer = &player2;
    else
        curPlayer = &player1;
    playerNum = (playerNum + 1) % 2;
}


void Game::Replay(){
    std::cin >> choice;
    if(choice=="N" || choice=="n") gameOver = true;
    else RestartGame();
}


void Game::RestartGame(){
    player1.ClearAll();
    player2.ClearAll();
    curPlayer = &player1;
    playerNum = 1;
    winlineNum = 0;
    map.RestartMap();
    if(gameMode==2){
        WhoAI();
    }
}


void Game::HelloText(){
    std::cout << "Welcome to Tic-tac-toe!\n";
    std::cout << "Select game mode:\n";
    std::cout << "\t[1] Two players\n";
    std::cout << "\t[2] Player and computer\n";
    std::cout << "Press '0' to exit\n";
    std::cout << ">> ";
    std::cin >> gameMode;
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
    if(gameMode==2)
        WhoForWhomText();
    std::cout << "Now is " << curPlayer->Symbol() << "'s step!\n";
    std::cout << std::endl;
}


void Game::WhoAI(){
    std::cout << "Whant to go first? [y/n]\n";
    std::cout << ">> ";
    std::cin >> choice;
    if(choice=="N" || choice=="n"){
        aiplay = &player1;
        human = &player2;
    }
    else{
        aiplay = &player2;
        human = &player1;
    }
    ai.SetSym(aiplay->Symbol());
    player.SetSym(human->Symbol());
}


void Game::WhoForWhomText(){
    std::cout << "Human: " << human->Symbol() << std::endl;
    std::cout << "AI " << aiplay->Symbol() << std::endl;
    std::cout << std::endl;
}


void Game::WinText(){
    if(winlineNum == 9) std::cout << "Draw!\n";
    else{
        std::cout << curPlayer->Symbol() << " is won!\n";
        if(gameMode==2)
            std::cout << "Current score:\n Human: " << player.Score() << "\n AI: " << ai.Score();
        else
            std::cout << "Current score:\n PlayerX: " << player1.Score() << "\n PlayerO: " << player2.Score();
    }
    std::cout << "\nWant to replay? [y/n] ";
}


void Game::FinalWinText(){
    std::cout << std::endl;
    if(gameMode==1){
        if(player1.Score()==player2.Score()){
            std::cout << "Draw!\n";
            return;
        }
        if(player1.Score()>player2.Score()) curPlayer = &player1;
        else curPlayer = &player2;
        std::cout << curPlayer->Symbol() << " is won!\n";
    }
    else{
        if(player.Score()==ai.Score()){
            std::cout << "Draw!\n";
            return;
        }
        if(human->Score()>ai.Score()) std::cout << "Human ";
        else std::cout << "AI ";
        std::cout << "is won!\n";
    }
}