#include "conelly.h"

Conelly::Conelly(const int& startRow, const int& startColumn){
    position_ = {startRow,startColumn};
}

void Conelly::set_position(const vector<int>& position){
    position_ = position;
};

vector<int> Conelly::get_position(){
    return position_;
};