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

std::vector<int> Player::Pos(){
    return positions;
}

int Player::Score(){
    return score;
}

void Player::IncreaseScore(){
    score += 10;
}

Player::Player(){}
Player::Player(std::string a): symbol(a), countOfElems(0), score(0){}

void Player::DeletePosition(int a){
    for(std::vector<int>::iterator it = positions.begin(); it != positions.end(); it++){
        if(*it == a){
            positions.erase(it);
            break;
        }
    }
    countOfElems--;
}