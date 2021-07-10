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
    stringNumber = 1;
    colomnNumber = 1;
    iter = table[stringNumber].begin();
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
    else{
        MoveDown();
    }
}

void Map::MoveDown(){
    if(stringNumber < intervalBetweenStrings*2 + startString){
        stringNumber += intervalBetweenStrings;
    }
}

void Map::MoveUp(){
    if(stringNumber > startString){
        stringNumber -= intervalBetweenStrings;
    }
}

void Map::MoveLeft(){
    if(colomnNumber > startColomn){
        iter--;
        iter--;
        colomnNumber--;
    }
        
}

void Map::MoveRight(){
    if(colomnNumber < intervalBetweenColomns*2 + startColomn){
        iter++;
        iter++;
        colomnNumber++;
    }
}