#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "std_lib_inc.h"

// Klasse, die eine SpielerIn kapselt
class Player {
    public:
        Player(int startRow, int startColumn);
        Player(int startRow, int startColumn, int numberOfKeys);
        bool hasKey();
        void addKey();
        bool useKey();
        vector<int> position; // Aktuelle Position der SpielerIn im Labyrinth
    private:
        int no_keys; // Anzahl der Schlüssel der SpielerIn
};

#endif