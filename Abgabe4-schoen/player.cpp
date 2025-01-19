#include "player.h"

Player::Player(const int& startRow, const int& startColumn){
    position_ = {startRow,startColumn};
    no_keys_ = 0;
}

Player::Player(const int& startRow, const int& startColumn, const int& numberOfKeys){
    position_ = {startRow,startColumn};
    no_keys_ = numberOfKeys;
}

 bool Player::has_key(){
    if(no_keys_>0){
        return true;
    }
    return false;
}

void Player::add_key(){
    no_keys_++;
}

bool Player::use_key(){
    if(no_keys_>0){
        no_keys_--;
        return true;
    }
    return false;
}

void Player::set_position(const vector<int>& position){
    position_ = position;
};

vector<int> Player::get_position(){
    return position_;
};