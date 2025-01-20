// Klasse, die eine SpielerIn kapselt
// Player besitzt eine Koordinate & eine Anzahl an Schlüsseln die erhöht / verringert werden kann.

#include "player.h"

//Konstruktor für Player, erzeugt einen Spieler mit 0 Schlüsseln bei {startRow, startColumn}
Player::Player(const int& startRow, const int& startColumn){
    position_ = {startRow,startColumn};
    no_keys_ = 0;
}

//Konstruktor für Player, bei dem zusätzlich die Anzahl der Schlüssel mit numberOfKeys festgelegt werden kann
Player::Player(const int& startRow, const int& startColumn, const int& numberOfKeys){
    position_ = {startRow,startColumn};
    no_keys_ = numberOfKeys;
}

//Gibt true zurück, wenn der Spiler min. einen Schlüssel hat
bool Player::has_key(){
    if(no_keys_>0){
        return true;
    }
    return false;
}

//Erhöht die Schlüsselzahl um einen
void Player::add_key(){
    no_keys_++;
}

//Benutzt einen Schlüssel, gibt false zurück falls keine mehr vorhanden
bool Player::use_key(){
    if(no_keys_>0){
        no_keys_--;
        return true;
    }
    return false;
}

//Settet Spieler Koordinaten
void Player::set_position(const vector<int>& position){
    if(position.size() != 2){
        throw BadMovement{};
    }
    position_ = position;
};

//Gibt Position des Spielers zurück
vector<int> Player::get_position(){
    return position_;
};