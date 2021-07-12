#include "map.h"

Map::Map(){
    RestartMap();
}

void Map::RestartMap(){
    table = startTable;
    strNumber = startStr;
    colNumber = startCol;
    NewLine();
    *iter = cursor;
    curSymbol = " ";
}

void Map::Move(char a){
    if(a == 'l') MoveLeft();
    else if(a == 'r') MoveRight();
    else if(a == 'u') MoveUp();
    else if(a == 'd') MoveDown();
}


void Map::NewLine(){
    iter = table[strNumber].begin();
    for(int i = 0; i < startCol; i++){
        iter++;
    }
}

void Map::MoveToColomn(){
    for(int i = startCol; i < colNumber; i++){
        iter++;
    }
}

bool Map::SetPlayerSym(Player* a){
    if(curSymbol == " "){
        SetSym(a);
        return true;
    }
    return false;
}

void Map::SetSym(Player* play){
    *iter = play->Symbol();
    curSymbol = play->Symbol();
    play->AddPosition(Position());
}

int Map::Position(){
    return strNumber + colNumber/7 - strNumber/4;
}

void Map::MoveDown(){
    if(strNumber < intervBetwStrs*2 + startStr) Down();
}

void Map::Down(){
    SetSymbol();
    strNumber += intervBetwStrs;
    NewLine();
    MoveToColomn();
    SetCursor();
}

void Map::MoveUp(){
    if(strNumber > startStr) Up();
}

void Map::Up(){
    SetSymbol();
    strNumber -= intervBetwStrs;
    NewLine();
    MoveToColomn();
    SetCursor();
}

void Map::MoveLeft(){
    if(colNumber > startCol) Left();    
}

void Map::Left(){
    SetSymbol();
    colNumber -= intervBetwCols;
    MoveToPrevCol();
    SetCursor();
}

void Map::MoveRight(){
    if(colNumber < intervBetwCols*2 + startCol) Right();
}

void Map::MoveToNextCol(){
    for(int i = 0; i < intervBetwCols; i++){
        iter++;
    }
}

void Map::MoveToPrevCol(){
    for(int i = 0; i < intervBetwCols; i++){
        iter--;
    }
}

void Map::Right(){
    SetSymbol();
    colNumber += intervBetwCols;
    MoveToNextCol();
    SetCursor();
}

void Map::SetCursor(){
    curSymbol = *iter;
    *iter = cursor;
}

void Map::SetSymbol(){
    *iter = curSymbol;
}

void Map::PrintTable(){
    for(int i = 0; i < table.size(); i++){
        for(std::vector<std::string>::iterator it = table[i].begin(); it != table[i].end(); it++){
            std::cout << (*it);
        }
    }
}