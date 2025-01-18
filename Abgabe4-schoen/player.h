#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "std_lib_inc.h"

// Klasse, die eine SpielerIn kapselt
class Player {
    public:
        Player(unsigned int startRow, unsigned int startColumn);
        Player(unsigned int startRow, unsigned int startColumn, unsigned int numberOfKeys);
        bool hasKey();
        void addKey();
        bool useKey();
        vector<unsigned int> position; // Aktuelle Position der SpielerIn im Labyrinth
    private:
        unsigned int no_keys; // Anzahl der Schlüssel der SpielerIn
};

#endif