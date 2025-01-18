#include "player.h"

Player::Player(unsigned int startRow, unsigned int startColumn){
    position = {startRow,startColumn};
    no_keys = 0;
}

Player::Player(unsigned int startRow, unsigned int startColumn, unsigned int numberOfKeys){
    position = {startRow,startColumn};
    no_keys = numberOfKeys;
}

 bool Player::hasKey(){
    if(no_keys>0){
        return true;
    }
    return false;
}

void Player::addKey(){
    no_keys++;
}

bool Player::useKey(){
    if(no_keys>0){
        no_keys--;
        return true;
    }
    return false;
}