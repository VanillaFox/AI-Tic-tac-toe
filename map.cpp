#include "map.h"

Map::Map(){
    table = {{"       |       |       \n"},
        {"   ", " ", "   |   ", " ", "   |   ", " ", "   \n"},
        {"       |       |       \n"},
        {"-----------------------\n"},
        {"       |       |       \n"},
        {"   ", " ", "   |   ", " ", "   |   ", " ", "   \n"},
        {"       |       |       \n"},
        {"-----------------------\n"},
        {"       |       |       \n"},
        {"   ", " ", "   |   ", " ", "   |   ", " ", "   \n"},
        {"       |       |       \n"}
    };
    strNumber = startStr;
    colNumber = startCol;
    NewLine();
    *iter = cursor;
    curSymbol = " ";
}

void Map::Move(char a){
    if(a == 'l'){
        MoveLeft();
    }
    else if(a == 'r'){
        MoveRight();
    }
    else if(a == 'u'){
        MoveUp();
    }
    else if(a == 'd'){
        MoveDown();
    }
}


void Map::NewLine(){
    iter = table[strNumber].begin();
    iter++;
}

void Map::MoveToColomn(){
    for(int i = 1; i < colNumber; i++){
        iter++;
        iter++;
    }
}

void Map::SetSym(Player play){
    *iter = play.Symbol();
    curSymbol = play.Symbol();
    play.AddPosition(Position());
}

int Map::Position(){
    return colNumber + strNumber - strNumber/intervBetwStrs - 1;
}

void Map::MoveDown(){
    if(strNumber < intervBetwStrs*2 + startStr){
        // std::cout << "DOWN!\n";
        Down();
    }
}

void Map::Down(){
    SetSymbol();
    strNumber += intervBetwStrs;
    NewLine();
    MoveToColomn();
    SetCursor();
}

void Map::MoveUp(){
    if(strNumber > startStr){
        Up();
    }
}

void Map::Up(){
    SetSymbol();
    strNumber -= intervBetwStrs;
    NewLine();
    MoveToColomn();
    SetCursor();
}

void Map::MoveLeft(){
    if(colNumber > startCol){
        Left();
    }        
}

void Map::Left(){
    SetSymbol();
    iter--;
    iter--;
    colNumber--;
    SetCursor();
}

void Map::MoveRight(){
    if(colNumber < intervBetwCols*2 + startCol){
        Right();
    }
}

void Map::Right(){
    SetSymbol();
    iter++;
    iter++;
    colNumber++;
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
    std::cout << startCol << " " << startStr << std::endl;
    for(int i = 0; i < table.size(); i++){
        for(std::vector<std::string>::iterator it = table[i].begin(); it != table[i].end(); it++){
            std::cout << (*it);
        }
    }
}