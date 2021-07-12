#include "player.h"

std::string Player::Symbol(){
    return symbol;
}

std::vector<int>* Player::Positions(){
    return &positions;
}

int Player::Count(){
    return countOfElems;
}

void Player::AddPosition(int a){
    positions.push_back(a);
    countOfElems++;
}

void Player::ClearAll(){
    positions.clear();
    countOfElems = 0;
}

Player::Player(){}
Player::Player(std::string a): symbol(a), countOfElems(0){}