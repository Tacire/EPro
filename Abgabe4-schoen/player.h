#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "std_lib_inc.h"

// Klasse, die eine SpielerIn kapselt
class Player {
    public:
        Player(const int& startRow, const int& startColumn);
        Player(const int& startRow, const int& startColumn, const int& numberOfKeys);

        
        bool has_key();
        void add_key();
        bool use_key();
        
        void set_position(const vector<int>& position);
        vector<int> get_position();
        
    private:
        vector<int> position_; // Aktuelle Position der SpielerIn im Labyrinth
        int no_keys_; // Anzahl der Schlüssel der SpielerIn
};

#endif