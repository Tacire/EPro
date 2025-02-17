#ifndef BOWIE_H
#define BOWIE_H
#pragma once

#include "std_lib_inc.h"
#include "helper.h"

// Klasse, die einen Bowie-Geist kapselt
class Bowie {
    public:
        Bowie(const int& startRow, const int& startColumn);
       
        void set_position(const vector<int>& position);
        vector<int> get_position();

        bool moving_left();
        void change_direction();
        
    private:
        vector<int> position_; // Aktuelle Position des Bowie-Geistes im Labyrinth
        bool moving_left_; // Gibt die Bewegungsrichtung von Bowie wieder, true wenn Bewegungsrichtung nach links
};

#endif