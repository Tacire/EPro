#ifndef CONELLY_H
#define CONELLY_H
#pragma once

#include "std_lib_inc.h"

// Klasse, die einen Conelly-Geist kapselt
class Conelly {
    public:
        Conelly(const int& startRow, const int& startColumn);
       
        void set_position(const vector<int>& position);
        vector<int> get_position();

    private:
        vector<int> position_; // Aktuelle des Bowie-Geistes im Labyrinth
};

#endif