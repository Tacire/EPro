#include "bowie.h"

Bowie::Bowie(const int& startRow, const int& startColumn){
    position_ = {startRow,startColumn};
    moving_left_ = true;
}

void Bowie::set_position(const vector<int>& position){
    position_ = position;
};

vector<int> Bowie::get_position(){
    return position_;
};

bool Bowie::moving_left(){
    return moving_left_;
};
void Bowie::change_direction(){
    moving_left_ = !moving_left_;
};

