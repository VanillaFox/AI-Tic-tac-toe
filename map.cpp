#include "map.h"

Map::Map(){
    table = startTable;
    FillIters();
    RestartMap();
}

void Map::RestartMap(){
    table = startTable;
    strNumber = startStr;
    colNumber = startCol;
    *iters[strNumber][colNumber] = cursor;
    curSymbol = " ";
    RandomPlaces();
}

void Map::FillIters(){
    std::vector<std::vector<std::string>::iterator> vec;
    strNumber = firstStr;
    for(int i = 0; i < 3; i++){
        NewLine();
        vec.push_back(iter);
        for(int j = 0; j < 2; j++){
            MoveToNextCol();
            vec.push_back(iter);
        }
        iters.push_back(vec);
        vec.clear();
        strNumber += intervBetwStrs;
    }
}

void Map::MoveToNextCol(){
    for(int i = 0; i < intervBetwCols; i++)
        iter++;
}


void Map::RandomPlaces(){
    freePlaces = StartFreePlaces;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(freePlaces.begin(), freePlaces.end(), g);
}


void Map::NewLine(){
    iter = table[strNumber].begin();
    for(int i = 0; i < firstCol; i++)
        iter++;
}


void Map::Move(char a){
    if(a == 'l') MoveLeft();
    else if(a == 'r') MoveRight();
    else if(a == 'u') MoveUp();
    else if(a == 'd') MoveDown();
}


void Map::MoveLeft(){
    if(colNumber)
        Left();
}

void Map::Left(){
    SetCurSym();
    colNumber--;
    SetCursor();
}

void Map::MoveRight(){
    if(colNumber < 2)
        Right();
}

void Map::Right(){
    SetCurSym();
    colNumber++;
    SetCursor();
}

void Map::MoveUp(){
    if(strNumber)
        Up();
}


void Map::Up(){
    SetCurSym();
    strNumber--;
    SetCursor();
}

void Map::MoveDown(){
    if(strNumber < 2)
        Down();
}

void Map::Down(){
    SetCurSym();
    strNumber++;
    SetCursor();
}

void Map::SetCurSym(){
    *iters[strNumber][colNumber] = curSymbol;
}

void Map::SetCursor(){
    curSymbol = *iters[strNumber][colNumber];
    *iters[strNumber][colNumber] = cursor;
}


bool Map::SetPlayerSym(Player* a){
    if(curSymbol == " "){
        SetSym(a);
        return true;
    }
    return false;
}

void Map::SetSym(Player* play){
    *iters[strNumber][colNumber] = play->Symbol();
    curSymbol = play->Symbol();
    int place = Position();
    play->AddPosition(place);
    DeletePlace(place);
}


void Map::SetSymByAI(Player* player, int step){
    int curStr = (step - 1)/3;
    int curCol = (step - 1)%3;
    *iters[curStr][curCol] = player->Symbol();
    player->AddPosition(step);
    DeletePlace(step);
}

void Map::DeletePlace(int a){
    std::vector<int>::iterator it;
    it = std::find(freePlaces.begin(), freePlaces.end(), a);
    if(it != freePlaces.end()) freePlaces.erase(it);
}

void Map::PrintFreePlaces(){
    for(int i: freePlaces){
        std::cout << i << std::endl;
    }
}

int Map::Position(){
    return strNumber*3 + colNumber+1;
}


void Map::SetSymbol(){
    *iters[strNumber][colNumber] = curSymbol;
}

void Map::PrintTable(){
    for(int i = 0; i < table.size(); i++){
        for(std::vector<std::string>::iterator it = table[i].begin(); it != table[i].end(); it++){
            std::cout << (*it);
        }
    }
}

void Map::PrintWinLine(int a){
    if(a < 4) PrintHorizontalLine(a);
    else if(a < 7) PrintVerticalLine(a);
    else if(a == 7) PrintLeftLine(a);
    else if(a == 8) PrintRightLine(a);
}

void Map::PrintVerticalLine(int a){
    int count = firstCol + intervBetwCols * (a - 4);
    for(int i = 0; i < 11; i = i+2){
        std::vector<std::string>::iterator it = table[i].begin();
        for(int j = 0; j < count; j++){
            it++;
        }
        *it = "|";
    }
}

void Map::PrintHorizontalLine(int a){
    int k = firstStr + intervBetwStrs*(a-1);
    std::vector<std::string>::iterator it = table[k].begin();
    k = 1;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < k; j++){
            it++;
        }
        *it = "-";
        if(k == 2 || k == 1) k = 4;
        else k = 2;
    }    
}

void Map::PrintLeftLine(int a){
    int count = 1;
    int k = 1;
    for(int i = 0; i < 11; i = i+2){
        std::vector<std::string>::iterator it = table[i].begin();
        for(int j = 0; j < count; j++){
            it++;
        }
        *it = "\\";
        if(k % 2) count += 4;
        else count += 2;
        k++;
    }
}

void Map::PrintRightLine(int a){
    int k = 1;
    int count = 17;
    for(int i = 0; i < 11; i = i+2){
        std::vector<std::string>::iterator it = table[i].begin();
        for(int j = 0; j < count; j++){
            it++;
        }
        *it = "/";
        if(k % 2) count -= 4;
        else count -= 2;
        k++;
    }
}

bool Map::FullMap(){
    if(freePlaces.empty()) return true;
    return false;
}