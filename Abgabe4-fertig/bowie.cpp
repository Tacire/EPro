// Klasse, die einen Bowie-Geist kapselt, hat Positions und Richtungsattribut
#include "bowie.h"

//Konstruktor für Klasse Bowie, generiert Bowies immer mit Bewegungsrichtung links
//an Position {startRow, startColumn}
Bowie::Bowie(const int& startRow, const int& startColumn){
    position_ = {startRow,startColumn};
    moving_left_ = true;
}

//Ändert die position von einem Bowie Geist
void Bowie::set_position(const vector<int>& position){
    if(position.size() != 2){
        throw BadMovement{};
    }
    position_ = position;
};

//Gibt Bowie Position als vector<int> zurück
vector<int> Bowie::get_position(){
    return position_;
};

//gibt true zurück, wenn Bewegungsrichtung von Bowie Geist links ist
bool Bowie::moving_left(){
    return moving_left_;
};

//Ändert die Bewegunsrichtung von einem Bowie Geist von links auf rechts
void Bowie::change_direction(){
    moving_left_ = !moving_left_;
};

