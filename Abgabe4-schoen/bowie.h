#ifndef BOWIE_H
#define BOWIE_H
#pragma once

#include "std_lib_inc.h"

// Klasse, die einen Bowie-Geist kapselt
class Bowie {
    public:
        Bowie(const int& startRow, const int& startColumn);
       
        void set_position(const vector<int>& position);
        vector<int> get_position();

        bool moving_left();
        void change_direction();
        
    private:
        vector<int> position_; // Aktuelle des Bowie-Geistes im Labyrinth
        bool moving_left_; // Gibt die Bewegungsrichtung von Bowie wieder
};

#endif