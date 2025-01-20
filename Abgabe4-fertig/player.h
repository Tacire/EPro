#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "std_lib_inc.h"
#include "helper.h"

// Klasse, die eine SpielerIn kapselt
// Player besitzt eine Koordinate & eine Anzahl an Schlüsseln die erhöht / verringert werden kann.
class Player {
    public:
        // Konstruktoren. Player kann mit oder ohne Schlüssel generiert werden
        Player(const int& startRow, const int& startColumn);
        Player(const int& startRow, const int& startColumn, const int& numberOfKeys);

        // minimale Schlüsser Getter & Setter
        bool has_key();
        void add_key();
        bool use_key();
        // Position Setter & Getter
        void set_position(const vector<int>& position);
        vector<int> get_position();
        
    private:
        vector<int> position_; // Aktuelle Position der SpielerIn im Labyrinth
        int no_keys_; // Anzahl der Schlüssel der SpielerIn
};

#endif