
// Klasse, die einen Conelly-Geist kapselt, hat Positions Attribut
#include "conelly.h"

//Konstuktor für Conelly Geist, wird erzeugt an Stelle {startRow, startColumn}
Conelly::Conelly(const int& startRow, const int& startColumn){
    position_ = {startRow,startColumn};
}

//Ändert Position von Conelly Geist
void Conelly::set_position(const vector<int>& position){
    if(position.size() != 2){
        throw BadMovement{};
    }
    position_ = position;
};

//Gibt Position von Conelly Geist zurück
vector<int> Conelly::get_position(){
    return position_;
};